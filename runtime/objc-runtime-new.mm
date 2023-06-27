/*
 * Copyright (c) 2005-2009 Apple Inc.  All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/***********************************************************************
* objc-runtime-new.m
* Support for new-ABI classes and images.
**********************************************************************/

#if __OBJC2__

#include "objc-private.h"
#include "objc-runtime-new.h"
#include "objc-file.h"
#include "objc-cache.h"
#include <Block.h>
#include <objc/message.h>

/*
 for ios
 //#include <mach/shared_region.h>
 */

#ifdef  IS_iOS
    
#else

#include <mach/shared_region.h>

#endif



#define newprotocol(p) ((protocol_t *)p)

static void disableTaggedPointers();
static void detach_class(Class cls, bool isMeta);
static void free_class(Class cls);
static Class setSuperclass(Class cls, Class newSuper);
static Class realizeClass(Class cls);
static method_t *getMethodNoSuper_nolock(Class cls, SEL sel);
static method_t *getMethod_nolock(Class cls, SEL sel);
static IMP addMethod(Class cls, SEL name, IMP imp, const char *types, bool replace);
static bool isRRSelector(SEL sel);
static bool isAWZSelector(SEL sel);
static bool methodListImplementsRR(const method_list_t *mlist);
static bool methodListImplementsAWZ(const method_list_t *mlist);
static void updateCustomRR_AWZ(Class cls, method_t *meth);
static method_t *search_method_list(const method_list_t *mlist, SEL sel);
static void flushCaches(Class cls);
static void initializeTaggedPointerObfuscator(void);
#if SUPPORT_FIXUP
static void fixupMessageRef(message_ref_t *msg);
#endif

static bool MetaclassNSObjectAWZSwizzled;
static bool ClassNSObjectRRSwizzled;


/***********************************************************************
* Lock management
**********************************************************************/
mutex_t runtimeLock;
mutex_t selLock;
mutex_t cacheUpdateLock;
recursive_mutex_t loadMethodLock;

void lock_init(void)
{
}


/***********************************************************************
* Class structure decoding
**********************************************************************/

const uintptr_t objc_debug_class_rw_data_mask = FAST_DATA_MASK;


/***********************************************************************
* Non-pointer isa decoding
**********************************************************************/
#if SUPPORT_INDEXED_ISA

// Indexed non-pointer isa.

// These are used to mask the ISA and see if its got an index or not.
const uintptr_t objc_debug_indexed_isa_magic_mask  = ISA_INDEX_MAGIC_MASK;
const uintptr_t objc_debug_indexed_isa_magic_value = ISA_INDEX_MAGIC_VALUE;

// die if masks overlap
STATIC_ASSERT((ISA_INDEX_MASK & ISA_INDEX_MAGIC_MASK) == 0);

// die if magic is wrong
STATIC_ASSERT((~ISA_INDEX_MAGIC_MASK & ISA_INDEX_MAGIC_VALUE) == 0);

// Then these are used to extract the index from the ISA.
const uintptr_t objc_debug_indexed_isa_index_mask  = ISA_INDEX_MASK;
const uintptr_t objc_debug_indexed_isa_index_shift  = ISA_INDEX_SHIFT;

asm("\n .globl _objc_absolute_indexed_isa_magic_mask"                   \
    "\n _objc_absolute_indexed_isa_magic_mask = " STRINGIFY2(ISA_INDEX_MAGIC_MASK));
asm("\n .globl _objc_absolute_indexed_isa_magic_value" \
    "\n _objc_absolute_indexed_isa_magic_value = " STRINGIFY2(ISA_INDEX_MAGIC_VALUE));
asm("\n .globl _objc_absolute_indexed_isa_index_mask"                   \
    "\n _objc_absolute_indexed_isa_index_mask = " STRINGIFY2(ISA_INDEX_MASK));
asm("\n .globl _objc_absolute_indexed_isa_index_shift" \
    "\n _objc_absolute_indexed_isa_index_shift = " STRINGIFY2(ISA_INDEX_SHIFT));


// And then we can use that index to get the class from this array.  Note
// the size is provided so that clients can ensure the index they get is in
// bounds and not read off the end of the array.
// Defined in the objc-msg-*.s files
// const Class objc_indexed_classes[]

// When we don't have enough bits to store a class*, we can instead store an
// index in to this array.  Classes are added here when they are realized.
// Note, an index of 0 is illegal.
uintptr_t objc_indexed_classes_count = 0;

// SUPPORT_INDEXED_ISA
#else
// not SUPPORT_INDEXED_ISA

// These variables exist but are all set to 0 so that they are ignored.
const uintptr_t objc_debug_indexed_isa_magic_mask  = 0;
const uintptr_t objc_debug_indexed_isa_magic_value = 0;
const uintptr_t objc_debug_indexed_isa_index_mask  = 0;
const uintptr_t objc_debug_indexed_isa_index_shift = 0;
Class objc_indexed_classes[1] = { nil };
uintptr_t objc_indexed_classes_count = 0;

// not SUPPORT_INDEXED_ISA
#endif


#if SUPPORT_PACKED_ISA

// Packed non-pointer isa.

asm("\n .globl _objc_absolute_packed_isa_class_mask" \
    "\n _objc_absolute_packed_isa_class_mask = " STRINGIFY2(ISA_MASK));

const uintptr_t objc_debug_isa_class_mask  = ISA_MASK;
const uintptr_t objc_debug_isa_magic_mask  = ISA_MAGIC_MASK;
const uintptr_t objc_debug_isa_magic_value = ISA_MAGIC_VALUE;

// die if masks overlap
STATIC_ASSERT((ISA_MASK & ISA_MAGIC_MASK) == 0);

// die if magic is wrong
STATIC_ASSERT((~ISA_MAGIC_MASK & ISA_MAGIC_VALUE) == 0);

// die if virtual address space bound goes up
STATIC_ASSERT((~ISA_MASK & MACH_VM_MAX_ADDRESS) == 0  ||  
              ISA_MASK + sizeof(void*) == MACH_VM_MAX_ADDRESS);

// SUPPORT_PACKED_ISA
#else
// not SUPPORT_PACKED_ISA

// These variables exist but enforce pointer alignment only.
const uintptr_t objc_debug_isa_class_mask  = (~WORD_MASK);
const uintptr_t objc_debug_isa_magic_mask  = WORD_MASK;
const uintptr_t objc_debug_isa_magic_value = 0;

// not SUPPORT_PACKED_ISA
#endif


/***********************************************************************
* allocatedClasses
* A table of all classes (and metaclasses) which have been allocated
* with objc_allocateClassPair.
**********************************************************************/
static NXHashTable *allocatedClasses = nil;


typedef locstamped_category_list_t category_list;


/*
  Low two bits of mlist->entsize is used as the fixed-up marker.
  PREOPTIMIZED VERSION:
    Method lists from shared cache are 1 (uniqued) or 3 (uniqued and sorted).
    (Protocol method lists are not sorted because of their extra parallel data)
    Runtime fixed-up method lists get 3.
  UN-PREOPTIMIZED VERSION:
    Method lists from shared cache are 1 (uniqued) or 3 (uniqued and sorted)
    Shared cache's sorting and uniquing are not trusted, but do affect the 
    location of the selector name string.
    Runtime fixed-up method lists get 2.

  High two bits of protocol->flags is used as the fixed-up marker.
  PREOPTIMIZED VERSION:
    Protocols from shared cache are 1<<30.
    Runtime fixed-up protocols get 1<<30.
  UN-PREOPTIMIZED VERSION:
  Protocols from shared cache are 1<<30.
    Shared cache's fixups are not trusted.
    Runtime fixed-up protocols get 3<<30.
*/

static uint32_t fixed_up_method_list = 3;
static uint32_t fixed_up_protocol = PROTOCOL_FIXED_UP_1;

void
disableSharedCacheOptimizations(void)
{
    fixed_up_method_list = 2;
    fixed_up_protocol = PROTOCOL_FIXED_UP_1 | PROTOCOL_FIXED_UP_2;
}

bool method_list_t::isFixedUp() const {
    return flags() == fixed_up_method_list;
}

void method_list_t::setFixedUp() {
    runtimeLock.assertLocked();
    assert(!isFixedUp());
    entsizeAndFlags = entsize() | fixed_up_method_list;
}

bool protocol_t::isFixedUp() const {
    return (flags & PROTOCOL_FIXED_UP_MASK) == fixed_up_protocol;
}

void protocol_t::setFixedUp() {
    runtimeLock.assertLocked();
    assert(!isFixedUp());
    flags = (flags & ~PROTOCOL_FIXED_UP_MASK) | fixed_up_protocol;
}


method_list_t **method_array_t::endCategoryMethodLists(Class cls) 
{
    method_list_t **mlists = beginLists();
    method_list_t **mlistsEnd = endLists();
    
    if (mlists == mlistsEnd  ||  !cls->data()->ro->baseMethods()) 
    {
        // No methods, or no base methods. 
        // Everything here is a category method.
        return mlistsEnd;
    }
    
    // Have base methods. Category methods are 
    // everything except the last method list.
    return mlistsEnd - 1;
}

static const char *sel_cname(SEL sel)
{
    return (const char *)(void *)sel;
}


static size_t protocol_list_size(const protocol_list_t *plist)
{
    return sizeof(protocol_list_t) + plist->count * sizeof(protocol_t *);
}


static void try_free(const void *p) 
{
    if (p && malloc_size(p)) free((void *)p);
}


static void (*classCopyFixupHandler)(Class _Nonnull oldClass,
                                     Class _Nonnull newClass);

void _objc_setClassCopyFixupHandler(void (* _Nonnull newFixupHandler)
    (Class _Nonnull oldClass, Class _Nonnull newClass)) {
    classCopyFixupHandler = newFixupHandler;
}

static Class 
alloc_class_for_subclass(Class supercls, size_t extraBytes)
{
    if (!supercls  ||  !supercls->isAnySwift()) {
        return _calloc_class(sizeof(objc_class) + extraBytes);
    }

    // Superclass is a Swift class. New subclass must duplicate its extra bits.

    // Allocate the new class, with space for super's prefix and suffix
    // and self's extraBytes.
    swift_class_t *swiftSupercls = (swift_class_t *)supercls;
    size_t superSize = swiftSupercls->classSize;
    void *superBits = swiftSupercls->baseAddress();
    void *bits = malloc(superSize + extraBytes);

    // Copy all of the superclass's data to the new class.
    memcpy(bits, superBits, superSize);

    // Erase the objc data and the Swift description in the new class.
    swift_class_t *swcls = (swift_class_t *)
        ((uint8_t *)bits + swiftSupercls->classAddressOffset);
    bzero(swcls, sizeof(objc_class));
    swcls->description = nil;

    if (classCopyFixupHandler) {
        classCopyFixupHandler(supercls, (Class)swcls);
    }

    // Mark this class as Swift-enhanced.
    if (supercls->isSwiftStable()) {
        swcls->bits.setIsSwiftStable();
    }
    if (supercls->isSwiftLegacy()) {
        swcls->bits.setIsSwiftLegacy();
    }
    
    return (Class)swcls;
}


/***********************************************************************
* object_getIndexedIvars.
**********************************************************************/
void *object_getIndexedIvars(id obj)
{
    uint8_t *base = (uint8_t *)obj;

    if (!obj) return nil;
    if (obj->isTaggedPointer()) return nil;

    if (!obj->isClass()) return base + obj->ISA()->alignedInstanceSize();

    Class cls = (Class)obj;
    if (!cls->isAnySwift()) return base + sizeof(objc_class);
    
    swift_class_t *swcls = (swift_class_t *)cls;
    return base - swcls->classAddressOffset + word_align(swcls->classSize);
}


/***********************************************************************
* make_ro_writeable
* Reallocates rw->ro if necessary to make it writeable.
* Locking: runtimeLock must be held by the caller.
* 申请一块新的内存，然后将旧的rw中的ro通过内存拷贝，拷贝到新的内存中，然后返回新的内存地址
**********************************************************************/
static class_ro_t *make_ro_writeable(class_rw_t *rw)
{
    runtimeLock.assertLocked();

    if (rw->flags & RW_COPIED_RO) {
        // already writeable, do nothing
    } else {
        /*
         memdup()会新申请一块内存，然后将旧的ro通过内存拷贝，拷贝到新的内存中
         */
        class_ro_t *ro = (class_ro_t *)memdup(rw->ro, sizeof(*rw->ro));
        //将rw中的ro指向新的ro的内存地址
        rw->ro = ro;
        rw->flags |= RW_COPIED_RO;
    }
    return (class_ro_t *)rw->ro;
}


/***********************************************************************
* unattachedCategories//
* Returns the class => categories map of unattached categories.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
/**
 * 全局的用来专门存放类与之相关联的所有分类的map
 *  以类cls 作为key,以category_list 作为value的map
 * category_map = {
 *    classA : category_list, (category_list 用来存放类A的所有分类)
 *    classB : category_list,
 *    classC : category_list
 * }
 */
static NXMapTable *unattachedCategories(void)
{
    runtimeLock.assertLocked();

    static NXMapTable *category_map = nil;

    if (category_map) return category_map;

    // fixme initial map size
    category_map = NXCreateMapTable(NXPtrValueMapPrototype, 16);

    return category_map;
}


/***********************************************************************
* dataSegmentsContain
* Returns true if the given address lies within a data segment in any
* loaded image.
*
* This is optimized for use where the return value is expected to be
* true. A call where the return value is false always results in a
* slow linear search of all loaded images. A call where the return
* value is fast will often be fast due to caching.
**********************************************************************/
static bool dataSegmentsContain(const void *ptr) {
    struct Range {
        uintptr_t start, end;
        bool contains(uintptr_t ptr) {
            return start <= ptr && ptr <= end;
        }
    };
    
    // This is a really simple linear searched cache. On a cache hit,
    // the hit entry is moved to the front of the array. On a cache
    // miss where a range is successfully found on the slow path, the
    // found range is inserted at the beginning of the cache. This gives
    // us fast access to the most recently used elements, and LRU
    // eviction.
    enum { cacheCount = 16 };
    static Range cache[cacheCount];
    
    uintptr_t addr = (uintptr_t)ptr;
    
    // Special case a hit on the first entry of the cache. No
    // bookkeeping is required at all in this case.
    if (cache[0].contains(addr)) {
        return true;
    }
    
    // Search the rest of the cache.
    for (unsigned i = 1; i < cacheCount; i++) {
        if (cache[i].contains(addr)) {
            // Cache hit. Move all preceding entries down one element,
            // then place this entry at the front.
            Range r = cache[i];
            memmove(&cache[1], &cache[0], i * sizeof(cache[0]));
            cache[0] = r;
            return true;
        }
    }
    
    // Cache miss. Find the image header containing the given address.
    // If there isn't one, then we're definitely not in any image,
    // so return false.
    Range found = { 0, 0 };
    auto *h = (headerType *)dyld_image_header_containing_address(ptr);
    if (h == nullptr)
        return false;
    
    // Iterate over the data segments in the found image. If the address
    // lies within one, note the data segment range in `found`.
    // TODO: this is more work than we'd like to do. All we really need
    // is the full range of the image. Addresses within the TEXT segment
    // would also be acceptable for our use case. If possible, we should
    // change this to work with the full address range of the found
    // image header. Another possibility would be to use the range
    // from `h` to the end of the page containing `addr`.
    foreach_data_segment(h, [&](const segmentType *seg, intptr_t slide) {
        Range r;
        r.start = seg->vmaddr + slide;
        r.end = r.start + seg->vmsize;
        if (r.contains(addr))
            found = r;
    });
    
    if (found.start != 0) {
        memmove(&cache[1], &cache[0], (cacheCount - 1) * sizeof(cache[0]));
        cache[0] = found;
        return true;
    }
    
    return false;
}


/***********************************************************************
* isKnownClass
* Return true if the class is known to the runtime (located within the
* shared cache, within the data segment of a loaded image, or has been
* allocated with obj_allocateClassPair).
**********************************************************************/
static bool isKnownClass(Class cls) {
    // The order of conditionals here is important for speed. We want to
    // put the most common cases first, but also the fastest cases
    // first. Checking the shared region is both fast and common.
    // Checking allocatedClasses is fast, but may not be common,
    // depending on what the program is doing. Checking if data segments
    // contain the address is slow, so do it last.
    return (sharedRegionContains(cls) ||
            NXHashMember(allocatedClasses, cls) ||
            dataSegmentsContain(cls));
}


/***********************************************************************
* addClassTableEntry
* Add a class to the table of all classes. If addMeta is true,
* automatically adds the metaclass of the class as well.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void addClassTableEntry(Class cls, bool addMeta = true) {
    runtimeLock.assertLocked();

    // This class is allowed to be a known class via the shared cache or via 这个类允许是已知的类通过共享缓存或通过
    // data segments, but it is not allowed to be in the dynamic table already. 数据段，但它不允许已经在动态表中。
    assert(!NXHashMember(allocatedClasses, cls));

    if (!isKnownClass(cls))
        // 如果共享缓存，或者allocatedClasses，dataSegmentsContain中都没有添加过，那么就添加到allocatedClasses中
        NXHashInsert(allocatedClasses, cls); //
    if (addMeta)
        addClassTableEntry(cls->ISA(), false);
}


/***********************************************************************
* checkIsKnownClass
* Checks the given class against the list of all known classes. Dies
* with a fatal error if the class is not known.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void checkIsKnownClass(Class cls)
{
    if (!isKnownClass(cls))
        _objc_fatal("Attempt to use unknown class %p.", cls);
}


/***********************************************************************
* addUnattachedCategoryForClass
* Records an unattached category.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
///将cat(分类) 插入到 与cls 对应的List中,
static void addUnattachedCategoryForClass(category_t *cat, Class cls, 
                                          header_info *catHeader)
{
    runtimeLock.assertLocked();

    // DO NOT use cat->cls! cls may be cat->cls->isa instead
    NXMapTable *cats = unattachedCategories();//全局的保存了所有类对应的分类的map
    category_list *list;

    //以class 作为key ,获取专门存放class对应的分类的list
    list = (category_list *)NXMapGet(cats, cls);
    if (!list) {
        list = (category_list *)
            calloc(sizeof(*list) + sizeof(list->list[0]), 1);
    } else {
        list = (category_list *)
            realloc(list, sizeof(*list) + sizeof(list->list[0]) * (list->count + 1));
    }
    //将分类信息插入到一个表中，后续需要的时候从这个表获取
    list->list[list->count++] = (locstamped_category_t){cat, catHeader};
    //以cls作为key ,list作为value 插入到cats 这张全局map中
    NXMapInsert(cats, cls, list);
}


/***********************************************************************
* removeUnattachedCategoryForClass
* Removes an unattached category.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void removeUnattachedCategoryForClass(category_t *cat, Class cls)
{
    runtimeLock.assertLocked();

    // DO NOT use cat->cls! cls may be cat->cls->isa instead
    NXMapTable *cats = unattachedCategories();
    category_list *list;

    list = (category_list *)NXMapGet(cats, cls);
    if (!list) return;

    uint32_t i;
    for (i = 0; i < list->count; i++) {
        if (list->list[i].cat == cat) {
            // shift entries to preserve list order
            memmove(&list->list[i], &list->list[i+1], 
                    (list->count-i-1) * sizeof(list->list[i]));
            list->count--;
            return;
        }
    }
}


/***********************************************************************
* unattachedCategoriesForClass
* Returns the list of unattached categories for a class, and 
* deletes them from the list. 
* The result must be freed by the caller. 
* Locking: runtimeLock must be held by the caller.
* 《获取类对应的分类列表》
**********************************************************************/
static category_list *
unattachedCategoriesForClass(Class cls, bool realizing)
{
    runtimeLock.assertLocked();
    return (category_list *)NXMapRemove(unattachedCategories(), cls);
}


/***********************************************************************
* removeAllUnattachedCategoriesForClass
* Deletes all unattached categories (loaded or not) for a class.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void removeAllUnattachedCategoriesForClass(Class cls)
{
    runtimeLock.assertLocked();

    void *list = NXMapRemove(unattachedCategories(), cls);
    if (list) free(list);
}


/***********************************************************************
* classNSObject
* Returns class NSObject.
* Locking: none
**********************************************************************/
static Class classNSObject(void)
{
    extern objc_class OBJC_CLASS_$_NSObject;
    return (Class)&OBJC_CLASS_$_NSObject;
}


/***********************************************************************
* printReplacements
* Implementation of PrintReplacedMethods / OBJC_PRINT_REPLACED_METHODS.
* Warn about methods from cats that override other methods in cats or cls.
* Assumes no methods from cats have been added to cls yet.
**********************************************************************/
static void printReplacements(Class cls, category_list *cats)
{
    uint32_t c;
    bool isMeta = cls->isMetaClass();

    if (!cats) return;

    // Newest categories are LAST in cats
    // Later categories override earlier ones.
    for (c = 0; c < cats->count; c++) {
        category_t *cat = cats->list[c].cat;

        method_list_t *mlist = cat->methodsForMeta(isMeta);
        if (!mlist) continue;

        for (const auto& meth : *mlist) {
            SEL s = sel_registerName(sel_cname(meth.name));

            // Search for replaced methods in method lookup order.
            // Complain about the first duplicate only.

            // Look for method in earlier categories
            for (uint32_t c2 = 0; c2 < c; c2++) {
                category_t *cat2 = cats->list[c2].cat;

                const method_list_t *mlist2 = cat2->methodsForMeta(isMeta);
                if (!mlist2) continue;

                for (const auto& meth2 : *mlist2) {
                    SEL s2 = sel_registerName(sel_cname(meth2.name));
                    if (s == s2) {
                        logReplacedMethod(cls->nameForLogging(), s, 
                                          cls->isMetaClass(), cat->name, 
                                          meth2.imp, meth.imp);
                        goto complained;
                    }
                }
            }

            // Look for method in cls
            for (const auto& meth2 : cls->data()->methods) {
                SEL s2 = sel_registerName(sel_cname(meth2.name));
                if (s == s2) {
                    logReplacedMethod(cls->nameForLogging(), s, 
                                      cls->isMetaClass(), cat->name, 
                                      meth2.imp, meth.imp);
                    goto complained;
                }
            }

        complained:
            ;
        }
    }
}


static bool isBundleClass(Class cls)
{
    return cls->data()->ro->flags & RO_FROM_BUNDLE;
}


static void 
fixupMethodList(method_list_t *mlist, bool bundleCopy, bool sort)
{
    runtimeLock.assertLocked();
    assert(!mlist->isFixedUp());

    // fixme lock less in attachMethodLists ?
    {
        mutex_locker_t lock(selLock);
    
        // Unique selectors in list.
        for (auto& meth : *mlist) {
            const char *name = sel_cname(meth.name);
            meth.name = sel_registerNameNoLock(name, bundleCopy);
        }
    }

    // Sort by selector address.
    if (sort) {
        method_t::SortBySELAddress sorter;
        std::stable_sort(mlist->begin(), mlist->end(), sorter);
    }
    
    // Mark method list as uniqued and sorted
    mlist->setFixedUp();
}


static void 
prepareMethodLists(Class cls, method_list_t **addedLists, int addedCount, 
                   bool baseMethods, bool methodsFromBundle)
{
    runtimeLock.assertLocked();

    if (addedCount == 0) return;

    // Don't scan redundantly
    bool scanForCustomRR = !cls->hasCustomRR();
    bool scanForCustomAWZ = !cls->hasCustomAWZ();

    // There exist RR/AWZ special cases for some class's base methods. 
    // But this code should never need to scan base methods for RR/AWZ: 
    // default RR/AWZ cannot be set before setInitialized().
    // Therefore we need not handle any special cases here.
    if (baseMethods) {
        assert(!scanForCustomRR  &&  !scanForCustomAWZ);
    }

    // Add method lists to array.
    // Reallocate un-fixed method lists.
    // The new methods are PREPENDED to the method list array.

    for (int i = 0; i < addedCount; i++) {
        method_list_t *mlist = addedLists[i];
        assert(mlist);

        // Fixup selectors if necessary
        if (!mlist->isFixedUp()) {
            fixupMethodList(mlist, methodsFromBundle, true/*sort*/);
        }

        // Scan for method implementations tracked by the class's flags
        if (scanForCustomRR  &&  methodListImplementsRR(mlist)) {
            cls->setHasCustomRR();
            scanForCustomRR = false;
        }
        if (scanForCustomAWZ  &&  methodListImplementsAWZ(mlist)) {
            cls->setHasCustomAWZ();
            scanForCustomAWZ = false;
        }
    }
}

//将分类的方法，属性，协议添加到类的class_rw_t字段中对应的methods ,properties, protocols
// Attach method lists and properties and protocols from categories to a class.
// Assumes the categories in cats are all loaded and sorted by load order, 
// oldest categories first.
static void 
attachCategories(Class cls, category_list *cats, bool flush_caches)
{
    if (!cats) return;
    if (PrintReplacedMethods) printReplacements(cls, cats);

    bool isMeta = cls->isMetaClass();

    // fixme rearrange to remove these intermediate allocations
    method_list_t **mlists = (method_list_t **)
        malloc(cats->count * sizeof(*mlists));
    property_list_t **proplists = (property_list_t **)
        malloc(cats->count * sizeof(*proplists));
    protocol_list_t **protolists = (protocol_list_t **)
        malloc(cats->count * sizeof(*protolists));

    // Count backwards through cats to get newest categories first
    int mcount = 0;
    int propcount = 0;
    int protocount = 0;
    int i = cats->count;
    bool fromBundle = NO;
    while (i--) {//因为这里是倒序遍历，所以后编译的分类会放在前面
        auto& entry = cats->list[i];

        //这里获取的是分类里面的类方法
        method_list_t *mlist = entry.cat->methodsForMeta(isMeta);
        if (mlist) {
            mlists[mcount++] = mlist;
            fromBundle |= entry.hi->isBundle();
        }

        property_list_t *proplist = 
            entry.cat->propertiesForMeta(isMeta, entry.hi);
        if (proplist) {
            proplists[propcount++] = proplist;
        }

        protocol_list_t *protolist = entry.cat->protocols;
        if (protolist) {
            protolists[protocount++] = protolist;
        }
    }

    auto rw = cls->data();

    prepareMethodLists(cls, mlists, mcount, NO, fromBundle);
    /*
     将分类中的方法添加到rw->methods 中，
     添加步骤分3步：
     1，先追加更多内存空间，
     2，将rw->methods中旧的数据往后挪
     3，将新的数据添加到rw->methods的前面
     这也就是为什么，如果分类中有与类原来同名的方法，
     调用同名方法时，被执行的是分类的方法
     
     */
    rw->methods.attachLists(mlists, mcount);
    free(mlists);
    if (flush_caches  &&  mcount > 0) flushCaches(cls);

    rw->properties.attachLists(proplists, propcount);
    free(proplists);

    rw->protocols.attachLists(protolists, protocount);
    free(protolists);
}


/***********************************************************************
* methodizeClass
* Fixes up cls's method list, protocol list, and property list.
* Attaches any outstanding categories.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void methodizeClass(Class cls)
{
    runtimeLock.assertLocked();

    bool isMeta = cls->isMetaClass();
    auto rw = cls->data();
    auto ro = rw->ro;

    // Methodizing for the first time
    if (PrintConnecting) {
        _objc_inform("CLASS: methodizing class '%s' %s", 
                     cls->nameForLogging(), isMeta ? "(meta)" : "");
    }

    /*
     Install methods and properties that the class implements itself.
     也就是：
     1，将class_ro_t 中的baseMethods 拷贝到 class_rw_t 中的methods 中去
     2，将class_ro_t 中的baseProperties 拷贝到 class_rw_t 中的properties 中去
     3，将class_ro_t 中的baseProtocols 拷贝到 class_rw_t 中的protocols 中去
     */
    method_list_t *list = ro->baseMethods();
    if (list) {
        prepareMethodLists(cls, &list, 1, YES, isBundleClass(cls));
        rw->methods.attachLists(&list, 1);
    }

    property_list_t *proplist = ro->baseProperties;
    if (proplist) {
        rw->properties.attachLists(&proplist, 1);
    }

    protocol_list_t *protolist = ro->baseProtocols;
    if (protolist) {
        rw->protocols.attachLists(&protolist, 1);
    }

    // Root classes get bonus method implementations if they don't have 
    // them already. These apply before category replacements.
    if (cls->isRootMetaclass()) {
        // root metaclass
        addMethod(cls, SEL_initialize, (IMP)&objc_noop_imp, "", NO);
    }

    /*
     Attach categories.
     获取类对应的所有分类
     */
    category_list *cats = unattachedCategoriesForClass(cls, true /*realizing*/);
    //将分类的方法添加到类的rw->methods 的前面
    attachCategories(cls, cats, false /*don't flush caches*/);

    if (PrintConnecting) {
        if (cats) {
            for (uint32_t i = 0; i < cats->count; i++) {
                _objc_inform("CLASS: attached category %c%s(%s)", 
                             isMeta ? '+' : '-', 
                             cls->nameForLogging(), cats->list[i].cat->name);
            }
        }
    }
    
    if (cats) free(cats);

#if DEBUG
    // Debug: sanity-check all SELs; log method list contents
    for (const auto& meth : rw->methods) {
        if (PrintConnecting) {
            _objc_inform("METHOD %c[%s %s]", isMeta ? '+' : '-', 
                         cls->nameForLogging(), sel_getName(meth.name));
        }
        assert(sel_registerName(sel_getName(meth.name)) == meth.name); 
    }
#endif
}


/***********************************************************************
* remethodizeClass
* Attach outstanding categories to an existing class.
* Fixes up cls's method list, protocol list, and property list.
* Updates method caches for cls and its subclasses.
* Locking: runtimeLock must be held by the caller
* 《将分类的信息，方法，协议，属性添加到类中的对应列表中methods，protocols，properties》
**********************************************************************/
static void remethodizeClass(Class cls)
{
    category_list *cats;
    bool isMeta;

    runtimeLock.assertLocked();

    isMeta = cls->isMetaClass();

    // Re-methodizing: check for more categories
    if ((cats = unattachedCategoriesForClass(cls, false/*not realizing*/))) {
        if (PrintConnecting) {
            _objc_inform("CLASS: attaching categories to class '%s' %s", 
                         cls->nameForLogging(), isMeta ? "(meta)" : "");
        }
        //将分类cats的方法，协议，属性添加到类cls中的对应列表中methods，protocols，properties
        attachCategories(cls, cats, true /*flush caches*/);        
        free(cats);
    }
}


/***********************************************************************
* nonMetaClasses
* Returns the secondary metaclass => class map
* Used for some cases of +initialize and +resolveClassMethod:.
* This map does not contain all class and metaclass pairs. It only 
* contains metaclasses whose classes would be in the runtime-allocated 
* named-class table, but are not because some other class with the same name 
* is in that table.
* Classes with no duplicates are not included.
* Classes in the preoptimized named-class table are not included.
* Classes whose duplicates are in the preoptimized table are not included.
* Most code should use getNonMetaClass() instead of reading this table.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static NXMapTable *nonmeta_class_map = nil;
static NXMapTable *nonMetaClasses(void)
{
    runtimeLock.assertLocked();

    if (nonmeta_class_map) return nonmeta_class_map;

    // nonmeta_class_map is typically small
    INIT_ONCE_PTR(nonmeta_class_map, 
                  NXCreateMapTable(NXPtrValueMapPrototype, 32), 
                  NXFreeMapTable(v));

    return nonmeta_class_map;
}


/***********************************************************************
* addNonMetaClass
* Adds metacls => cls to the secondary metaclass map
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void addNonMetaClass(Class cls)
{
    runtimeLock.assertLocked();
    void *old;
    old = NXMapInsert(nonMetaClasses(), cls->ISA(), cls);

    assert(!cls->isMetaClass());
    assert(cls->ISA()->isMetaClass());
    assert(!old);
}


static void removeNonMetaClass(Class cls)
{
    runtimeLock.assertLocked();
    NXMapRemove(nonMetaClasses(), cls->ISA());
}


static bool scanMangledField(const char *&string, const char *end, 
                             const char *&field, int& length)
{
    // Leading zero not allowed.
    if (*string == '0') return false;

    length = 0;
    field = string;
    while (field < end) {
        char c = *field;
        if (!isdigit(c)) break;
        field++;
        if (__builtin_smul_overflow(length, 10, &length)) return false;
        if (__builtin_sadd_overflow(length, c - '0', &length)) return false;
    }

    string = field + length;
    return length > 0  &&  string <= end;
}


/***********************************************************************
* copySwiftV1DemangledName
* Returns the pretty form of the given Swift-v1-mangled class or protocol name. 
* Returns nil if the string doesn't look like a mangled Swift v1 name.
* The result must be freed with free().
**********************************************************************/
static char *copySwiftV1DemangledName(const char *string, bool isProtocol = false)
{
    if (!string) return nil;

    // Swift mangling prefix.
    if (strncmp(string, isProtocol ? "_TtP" : "_TtC", 4) != 0) return nil;
    string += 4;

    const char *end = string + strlen(string);

    // Module name.
    const char *prefix;
    int prefixLength;
    if (string[0] == 's') {
        // "s" is the Swift module.
        prefix = "Swift";
        prefixLength = 5;
        string += 1;
    } else {
        if (! scanMangledField(string, end, prefix, prefixLength)) return nil;
    }

    // Class or protocol name.
    const char *suffix;
    int suffixLength;
    if (! scanMangledField(string, end, suffix, suffixLength)) return nil;

    if (isProtocol) {
        // Remainder must be "_".
        if (strcmp(string, "_") != 0) return nil;
    } else {
        // Remainder must be empty.
        if (string != end) return nil;
    }

    char *result;
    asprintf(&result, "%.*s.%.*s", prefixLength,prefix, suffixLength,suffix);
    return result;
}


/***********************************************************************
* copySwiftV1MangledName
* Returns the Swift 1.0 mangled form of the given class or protocol name. 
* Returns nil if the string doesn't look like an unmangled Swift name.
* The result must be freed with free().
**********************************************************************/
static char *copySwiftV1MangledName(const char *string, bool isProtocol = false)
{
    if (!string) return nil;

    size_t dotCount = 0;
    size_t dotIndex;
    const char *s;
    for (s = string; *s; s++) {
        if (*s == '.') {
            dotCount++;
            dotIndex = s - string;
        }
    }
    size_t stringLength = s - string;

    if (dotCount != 1  ||  dotIndex == 0  ||  dotIndex >= stringLength-1) {
        return nil;
    }
    
    const char *prefix = string;
    size_t prefixLength = dotIndex;
    const char *suffix = string + dotIndex + 1;
    size_t suffixLength = stringLength - (dotIndex + 1);
    
    char *name;

    if (prefixLength == 5  &&  memcmp(prefix, "Swift", 5) == 0) {
        asprintf(&name, "_Tt%cs%zu%.*s%s", 
                 isProtocol ? 'P' : 'C', 
                 suffixLength, (int)suffixLength, suffix, 
                 isProtocol ? "_" : "");
    } else {
        asprintf(&name, "_Tt%c%zu%.*s%zu%.*s%s", 
                 isProtocol ? 'P' : 'C', 
                 prefixLength, (int)prefixLength, prefix, 
                 suffixLength, (int)suffixLength, suffix, 
                 isProtocol ? "_" : "");
    }
    return name;
}


/***********************************************************************
* getClass
* Looks up a class by name. The class MIGHT NOT be realized.
* Demangled Swift names are recognized.
* Locking: runtimeLock must be read- or write-locked by the caller.
**********************************************************************/

// This is a misnomer: gdb_objc_realized_classes is actually a list of 
// named classes not in the dyld shared cache, whether realized or not.
NXMapTable *gdb_objc_realized_classes;  // exported for debuggers in objc-gdb.h

static Class getClass_impl(const char *name)
{
    runtimeLock.assertLocked();

    // allocated in _read_images
    assert(gdb_objc_realized_classes);

    // Try runtime-allocated table
    
    Class result = (Class)NXMapGet(gdb_objc_realized_classes, name);
    if (result) return result;

    // Try table from dyld shared cache
    return getPreoptimizedClass(name);
}

static Class getClass(const char *name)
{
    runtimeLock.assertLocked();

    // Try name as-is
    Class result = getClass_impl(name);
    if (result) return result;

    // Try Swift-mangled equivalent of the given name.
    if (char *swName = copySwiftV1MangledName(name)) {
        result = getClass_impl(swName);
        free(swName);
        return result;
    }

    return nil;
}


/***********************************************************************
* addNamedClass
* Adds name => cls to the named non-meta class map.
* Warns about duplicate class names and keeps the old mapping.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void addNamedClass(Class cls, const char *name, Class replacing = nil)
{
    runtimeLock.assertLocked();
    Class old;
    if ((old = getClass(name))  &&  old != replacing) {
        inform_duplicate(name, old, cls);
        // getNonMetaClass uses name lookups. Classes not found by name 
        // lookup must be in the secondary meta->nonmeta table.
        addNonMetaClass(cls);
    } else {
        /*
         将非元类添加到一张hash表示上, 以name 作为key ,以cls 作为value
         根据hash(name)计算出MapPair<name,cls>节点在hash表中的index，然后插入其中
         */
        NXMapInsert(gdb_objc_realized_classes, name, cls);
    }
    //如果该类为元类，则抛出异常，断言中断
    assert(!(cls->data()->flags & RO_META));

    // wrong: constructed classes are already realized when they get here
    // assert(!cls->isRealized());
}


/***********************************************************************
* removeNamedClass
* Removes cls from the name => cls map.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void removeNamedClass(Class cls, const char *name)
{
    runtimeLock.assertLocked();
    assert(!(cls->data()->flags & RO_META));
    if (cls == NXMapGet(gdb_objc_realized_classes, name)) {
        NXMapRemove(gdb_objc_realized_classes, name);
    } else {
        // cls has a name collision with another class - don't remove the other
        // but do remove cls from the secondary metaclass->class map.
        removeNonMetaClass(cls);
    }
}


/***********************************************************************
* unreasonableClassCount
* Provides an upper bound for any iteration of classes, 
* to prevent spins when runtime metadata is corrupted.
**********************************************************************/
unsigned unreasonableClassCount()
{
    runtimeLock.assertLocked();

    int base = NXCountMapTable(gdb_objc_realized_classes) +
        getPreoptimizedClassUnreasonableCount();

    // Provide lots of slack here. Some iterations touch metaclasses too.
    // Some iterations backtrack (like realized class iteration).
    // We don't need an efficient bound, merely one that prevents spins.
    return (base + 1) * 16;
}


/***********************************************************************
* futureNamedClasses
* Returns the classname => future class map for unrealized future classes.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static NXMapTable *future_named_class_map = nil;
static NXMapTable *futureNamedClasses()
{
    runtimeLock.assertLocked();
    
    if (future_named_class_map) return future_named_class_map;

    // future_named_class_map is big enough for CF's classes and a few others
    future_named_class_map = 
        NXCreateMapTable(NXStrValueMapPrototype, 32);

    return future_named_class_map;
}


static bool haveFutureNamedClasses() {
    return future_named_class_map  &&  NXCountMapTable(future_named_class_map);
}


/***********************************************************************
* addFutureNamedClass
* Installs cls as the class structure to use for the named class if it appears.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void addFutureNamedClass(const char *name, Class cls)
{
    void *old;

    runtimeLock.assertLocked();

    if (PrintFuture) {
        _objc_inform("FUTURE: reserving %p for %s", (void*)cls, name);
    }

    // 申请存放类信息的class_rw_t大小的内存
    class_rw_t *rw = (class_rw_t *)calloc(sizeof(class_rw_t), 1);
    // 申请存放原始类信息的class_ro_t大小的内存
    class_ro_t *ro = (class_ro_t *)calloc(sizeof(class_ro_t), 1);
    ro->name = strdupIfMutable(name);
    rw->ro = ro;
    cls->setData(rw);
    cls->data()->flags = RO_FUTURE;

    old = NXMapKeyCopyingInsert(futureNamedClasses(), name, cls);
    assert(!old);
}


/***********************************************************************
* popFutureNamedClass
* Removes the named class from the unrealized future class list, 
* because it has been realized.
* 将类名为name 的类从unrealized 的类列表中移除，因为他已经进行了realized操作
* Returns nil if the name is not used by a future class.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static Class popFutureNamedClass(const char *name)
{
    runtimeLock.assertLocked();

    Class cls = nil;

    if (future_named_class_map) {
        cls = (Class)NXMapKeyFreeingRemove(future_named_class_map, name);
        if (cls && NXCountMapTable(future_named_class_map) == 0) {
            NXFreeMapTable(future_named_class_map);
            future_named_class_map = nil;
        }
    }

    return cls;
}


/***********************************************************************
* remappedClasses
* Returns the oldClass => newClass map for realized future classes.
* Returns the oldClass => nil map for ignored weak-linked classes.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static NXMapTable *remappedClasses(bool create)
{
    static NXMapTable *remapped_class_map = nil;

    runtimeLock.assertLocked();

    if (remapped_class_map) return remapped_class_map;
    if (!create) return nil;

    // remapped_class_map is big enough to hold CF's classes and a few others
    INIT_ONCE_PTR(remapped_class_map, 
                  NXCreateMapTable(NXPtrValueMapPrototype, 32), 
                  NXFreeMapTable(v));

    return remapped_class_map;
}


/***********************************************************************
* noClassesRemapped
* Returns YES if no classes have been remapped
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static bool noClassesRemapped(void)
{
    runtimeLock.assertLocked();

    bool result = (remappedClasses(NO) == nil);
#if DEBUG
    // Catch construction of an empty table, which defeats optimization.
    NXMapTable *map = remappedClasses(NO);
    if (map) assert(NXCountMapTable(map) > 0);
#endif
    return result;
}


/***********************************************************************
* addRemappedClass
* newcls is a realized future class, replacing oldcls.
* OR newcls is nil, replacing ignored weak-linked class oldcls.
* Locking: runtimeLock must be write-locked by the caller
**********************************************************************/
static void addRemappedClass(Class oldcls, Class newcls)
{
    runtimeLock.assertLocked();

    if (PrintFuture) {
        _objc_inform("FUTURE: using %p instead of %p for %s", 
                     (void*)newcls, (void*)oldcls, oldcls->nameForLogging());
    }

    void *old;
    old = NXMapInsert(remappedClasses(YES), oldcls, newcls);
    assert(!old);
}


/***********************************************************************
* remapClass
* Returns the live class pointer for cls, which may be pointing to 
* a class struct that has been reallocated.
* Returns nil if cls is ignored because of weak linking.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static Class remapClass(Class cls)
{
    runtimeLock.assertLocked();

    Class c2;

    if (!cls) return nil;

    NXMapTable *map = remappedClasses(NO);
    if (!map  ||  NXMapMember(map, cls, (void**)&c2) == NX_MAPNOTAKEY) {
        return cls;
    } else {
        return c2;
    }
}

static Class remapClass(classref_t cls)
{
    return remapClass((Class)cls);
}

Class _class_remap(Class cls)
{
    mutex_locker_t lock(runtimeLock);
    return remapClass(cls);
}

/***********************************************************************
* remapClassRef
* Fix up a class ref, in case the class referenced has been reallocated 
* or is an ignored weak-linked class.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static void remapClassRef(Class *clsref)
{
    runtimeLock.assertLocked();

    Class newcls = remapClass(*clsref);    
    if (*clsref != newcls) *clsref = newcls;
}


/***********************************************************************
* getNonMetaClass
* Return the ordinary class for this class or metaclass. 
* `inst` is an instance of `cls` or a subclass thereof, or nil. 
* Non-nil inst is faster.
* Used by +initialize. 
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static Class getNonMetaClass(Class metacls, id inst)
{
    static int total, named, secondary, sharedcache;
    runtimeLock.assertLocked();

    realizeClass(metacls);

    total++;

    // return cls itself if it's already a non-meta class
    if (!metacls->isMetaClass()) return metacls;

    // metacls really is a metaclass

    // special case for root metaclass
    // where inst == inst->ISA() == metacls is possible
    if (metacls->ISA() == metacls) {
        Class cls = metacls->superclass;
        assert(cls->isRealized());
        assert(!cls->isMetaClass());
        assert(cls->ISA() == metacls);
        if (cls->ISA() == metacls) return cls;
    }

    // use inst if available
    if (inst) {
        Class cls = (Class)inst;
        realizeClass(cls);
        // cls may be a subclass - find the real class for metacls
        while (cls  &&  cls->ISA() != metacls) {
            cls = cls->superclass;
            realizeClass(cls);
        }
        if (cls) {
            assert(!cls->isMetaClass());
            assert(cls->ISA() == metacls);
            return cls;
        }
#if DEBUG
        _objc_fatal("cls is not an instance of metacls");
#else
        // release build: be forgiving and fall through to slow lookups
#endif
    }

    // try name lookup
    {
        Class cls = getClass(metacls->mangledName());
        if (cls->ISA() == metacls) {
            named++;
            if (PrintInitializing) {
                _objc_inform("INITIALIZE: %d/%d (%g%%) "
                             "successful by-name metaclass lookups",
                             named, total, named*100.0/total);
            }

            realizeClass(cls);
            return cls;
        }
    }

    // try secondary table
    {
        Class cls = (Class)NXMapGet(nonMetaClasses(), metacls);
        if (cls) {
            secondary++;
            if (PrintInitializing) {
                _objc_inform("INITIALIZE: %d/%d (%g%%) "
                             "successful secondary metaclass lookups",
                             secondary, total, secondary*100.0/total);
            }

            assert(cls->ISA() == metacls);            
            realizeClass(cls);
            return cls;
        }
    }

    // try any duplicates in the dyld shared cache
    {
        Class cls = nil;

        int count;
        Class *classes = copyPreoptimizedClasses(metacls->mangledName(),&count);
        if (classes) {
            for (int i = 0; i < count; i++) {
                if (classes[i]->ISA() == metacls) {
                    cls = classes[i];
                    break;
                }
            }
            free(classes);
        }

        if (cls) {
            sharedcache++;
            if (PrintInitializing) {
                _objc_inform("INITIALIZE: %d/%d (%g%%) "
                             "successful shared cache metaclass lookups",
                             sharedcache, total, sharedcache*100.0/total);
            }

            realizeClass(cls);
            return cls;
        }
    }

    _objc_fatal("no class for metaclass %p", (void*)metacls);
}


/***********************************************************************
* _class_getNonMetaClass
* Return the ordinary class for this class or metaclass. 
* Used by +initialize. 
* Locking: acquires runtimeLock
**********************************************************************/
Class _class_getNonMetaClass(Class cls, id obj)
{
    mutex_locker_t lock(runtimeLock);
    cls = getNonMetaClass(cls, obj);
    assert(cls->isRealized());
    return cls;
}


/***********************************************************************
* addRootClass
* Adds cls as a new realized root class.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static Class _firstRealizedClass = nil;
Class firstRealizedClass() 
{
    runtimeLock.assertLocked();
    return _firstRealizedClass;
}
///该接口主要在realizeClass中调用，或者用户动态创建类时调用
static void addRootClass(Class cls)
{
    runtimeLock.assertLocked();

    assert(cls->isRealized());
    cls->data()->nextSiblingClass = _firstRealizedClass;
    _firstRealizedClass = cls;
}

static void removeRootClass(Class cls)
{
    runtimeLock.assertLocked();

    Class *classp;
    for (classp = &_firstRealizedClass; 
         *classp != cls; 
         classp = &(*classp)->data()->nextSiblingClass)
    { }
    
    *classp = (*classp)->data()->nextSiblingClass;
}


/***********************************************************************
* addSubclass
* Adds subcls as a subclass of supercls.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void addSubclass(Class supercls, Class subcls)
{
    runtimeLock.assertLocked();

    if (supercls  &&  subcls) {
        assert(supercls->isRealized());
        assert(subcls->isRealized());
        subcls->data()->nextSiblingClass = supercls->data()->firstSubclass;
        supercls->data()->firstSubclass = subcls;

        if (supercls->hasCxxCtor()) {
            subcls->setHasCxxCtor();
        }

        if (supercls->hasCxxDtor()) {
            subcls->setHasCxxDtor();
        }

        if (supercls->hasCustomRR()) {
            subcls->setHasCustomRR(true);
        }

        if (supercls->hasCustomAWZ()) {
            subcls->setHasCustomAWZ(true);
        }

        // Special case: instancesRequireRawIsa does not propagate 
        // from root class to root metaclass
        if (supercls->instancesRequireRawIsa()  &&  supercls->superclass) {
            subcls->setInstancesRequireRawIsa(true);
        }
    }
}


/***********************************************************************
* removeSubclass
* Removes subcls as a subclass of supercls.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void removeSubclass(Class supercls, Class subcls)
{
    runtimeLock.assertLocked();
    assert(supercls->isRealized());
    assert(subcls->isRealized());
    assert(subcls->superclass == supercls);

    Class *cp;
    for (cp = &supercls->data()->firstSubclass; 
         *cp  &&  *cp != subcls; 
         cp = &(*cp)->data()->nextSiblingClass)
        ;
    assert(*cp == subcls);
    *cp = subcls->data()->nextSiblingClass;
}



/***********************************************************************
* protocols
* Returns the protocol name => protocol map for protocols.
* Locking: runtimeLock must read- or write-locked by the caller
**********************************************************************/
static NXMapTable *protocols(void)
{
    static NXMapTable *protocol_map = nil;
    
    runtimeLock.assertLocked();

    INIT_ONCE_PTR(protocol_map, 
                  NXCreateMapTable(NXStrValueMapPrototype, 16), 
                  NXFreeMapTable(v) );

    return protocol_map;
}


/***********************************************************************
* getProtocol
* Looks up a protocol by name. Demangled Swift names are recognized.
* Locking: runtimeLock must be read- or write-locked by the caller.
**********************************************************************/
static Protocol *getProtocol(const char *name)
{
    runtimeLock.assertLocked();

    // Try name as-is.
    Protocol *result = (Protocol *)NXMapGet(protocols(), name);
    if (result) return result;

    // Try Swift-mangled equivalent of the given name.
    if (char *swName = copySwiftV1MangledName(name, true/*isProtocol*/)) {
        result = (Protocol *)NXMapGet(protocols(), swName);
        free(swName);
        return result;
    }

    return nil;
}


/***********************************************************************
* remapProtocol
* Returns the live protocol pointer for proto, which may be pointing to 
* a protocol struct that has been reallocated.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static protocol_t *remapProtocol(protocol_ref_t proto)
{
    runtimeLock.assertLocked();

    protocol_t *newproto = (protocol_t *)
        getProtocol(((protocol_t *)proto)->mangledName);
    return newproto ? newproto : (protocol_t *)proto;
}


/***********************************************************************
* remapProtocolRef
* Fix up a protocol ref, in case the protocol referenced has been reallocated.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static size_t UnfixedProtocolReferences;
static void remapProtocolRef(protocol_t **protoref)
{
    runtimeLock.assertLocked();

    protocol_t *newproto = remapProtocol((protocol_ref_t)*protoref);
    if (*protoref != newproto) {
        *protoref = newproto;
        UnfixedProtocolReferences++;
    }
}


/***********************************************************************
* moveIvars
* Slides a class's ivars to accommodate the given superclass size.
* Ivars are NOT compacted to compensate for a superclass that shrunk.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void moveIvars(class_ro_t *ro, uint32_t superSize)
{
    runtimeLock.assertLocked();

    uint32_t diff;

    assert(superSize > ro->instanceStart);
    diff = superSize - ro->instanceStart;

    if (ro->ivars) {
        // Find maximum alignment in this class's ivars
        uint32_t maxAlignment = 1;
        for (const auto& ivar : *ro->ivars) {
            if (!ivar.offset) continue;  // anonymous bitfield

            uint32_t alignment = ivar.alignment();
            if (alignment > maxAlignment) maxAlignment = alignment;
        }

        // Compute a slide value that preserves that alignment
        uint32_t alignMask = maxAlignment - 1;
        diff = (diff + alignMask) & ~alignMask;

        // Slide all of this class's ivars en masse
        for (const auto& ivar : *ro->ivars) {
            if (!ivar.offset) continue;  // anonymous bitfield

            uint32_t oldOffset = (uint32_t)*ivar.offset;
            uint32_t newOffset = oldOffset + diff;
            *ivar.offset = newOffset;

            if (PrintIvars) {
                _objc_inform("IVARS:    offset %u -> %u for %s "
                             "(size %u, align %u)", 
                             oldOffset, newOffset, ivar.name, 
                             ivar.size, ivar.alignment());
            }
        }
    }

    *(uint32_t *)&ro->instanceStart += diff;
    *(uint32_t *)&ro->instanceSize += diff;
}

/**
 reconcile [ˈrekənsaɪl]
 v. 调和，使协调一致；（使）和解，（使）恢复友好关系
 1. 修正类中的ivar_list_t * ivars变量列表中的所有变量的偏移量
 2. 修正uint32_t instanceStart;以及uint32_t instanceSize;
 */
static void reconcileInstanceVariables(Class cls, Class supercls, const class_ro_t*& ro) 
{
    class_rw_t *rw = cls->data();

    assert(supercls);
    assert(!cls->isMetaClass());

    /* debug: print them all before sliding
    if (ro->ivars) {
        for (const auto& ivar : *ro->ivars) {
            if (!ivar.offset) continue;  // anonymous bitfield

            _objc_inform("IVARS: %s.%s (offset %u, size %u, align %u)", 
                         ro->name, ivar.name, 
                         *ivar.offset, ivar.size, ivar.alignment());
        }
    }
    */

    // Non-fragile ivars - reconcile this class with its superclass
    const class_ro_t *super_ro = supercls->data()->ro;
    
    if (DebugNonFragileIvars) {
        // Debugging: Force non-fragile ivars to slide.
        // Intended to find compiler, runtime, and program bugs.
        // If it fails with this and works without, you have a problem.
        
        // Operation: Reset everything to 0 + misalignment. 
        // Then force the normal sliding logic to push everything back.
        
        // Exceptions: root classes, metaclasses, *NSCF* classes, 
        // __CF* classes, NSConstantString, NSSimpleCString
        
        // (already know it's not root because supercls != nil)
        const char *clsname = cls->mangledName();
        if (!strstr(clsname, "NSCF")  &&  
            0 != strncmp(clsname, "__CF", 4)  &&  
            0 != strcmp(clsname, "NSConstantString")  &&  
            0 != strcmp(clsname, "NSSimpleCString")) 
        {
            uint32_t oldStart = ro->instanceStart;
            class_ro_t *ro_w = make_ro_writeable(rw);
            ro = rw->ro;
            
            // Find max ivar alignment in class.
            // default to word size to simplify ivar update
            uint32_t alignment = 1<<WORD_SHIFT;
            if (ro->ivars) {
                for (const auto& ivar : *ro->ivars) {
                    if (ivar.alignment() > alignment) {
                        alignment = ivar.alignment();
                    }
                }
            }
            uint32_t misalignment = ro->instanceStart % alignment;
            uint32_t delta = ro->instanceStart - misalignment;
            ro_w->instanceStart = misalignment;
            ro_w->instanceSize -= delta;
            
            if (PrintIvars) {
                _objc_inform("IVARS: DEBUG: forcing ivars for class '%s' "
                             "to slide (instanceStart %zu -> %zu)", 
                             cls->nameForLogging(), (size_t)oldStart, 
                             (size_t)ro->instanceStart);
            }
            
            if (ro->ivars) {
                for (const auto& ivar : *ro->ivars) {
                    if (!ivar.offset) continue;  // anonymous bitfield
                    *ivar.offset -= delta;
                }
            }
        }
    }

    /*
     这里是否是父类没成员变量？？，也就是父类不需要分配成员变量的内存空间？？
     或者当前类的首个成员变量的前面的内存空间已经足够父类使用？？
     例子：ManSuperClass:NSObjcet Man:ManSuperClass
     运行到 ManSuperClass ro start = 8 super_ro instanceSize = 8 相同 默认留有一定的空间也就是说 偏移的start 就是8 如果父类中 instanceSize需求空间大于了8 都必须 进行偏移
     */
    if (ro->instanceStart >= super_ro->instanceSize) {
        // Superclass has not overgrown its space. We're done here.
        return;
    }
    // fixme can optimize for "class has no new ivars", etc

    if (ro->instanceStart < super_ro->instanceSize) {
        // Superclass has changed size. This class's ivars must move.
        // Also slide layout bits in parallel.
        // This code is incapable of compacting the subclass to 
        //   compensate for a superclass that shrunk, so don't do that.
        if (PrintIvars) {
            _objc_inform("IVARS: sliding ivars for class %s "
                         "(superclass was %u bytes, now %u)", 
                         cls->nameForLogging(), ro->instanceStart, 
                         super_ro->instanceSize);
        }
        /*
         这里扩展成员变量的内存空间
         1.申请一块新的内存(class_ro_t)，然后将旧的class_rw_t->ro所指向的内存，通过内存拷贝的方式，拷贝到新申请的内存中
         */
        class_ro_t *ro_w = make_ro_writeable(rw);
        ro = rw->ro;
        /*
         这里将当前类的成员变量移到父类成员变量后面（其实是更新当前类的成员变量的offset,将offset变更到父类的instanceSize 后面）
         2. 更新当前类的instanceSize，以及instanceStart
         */
        moveIvars(ro_w, super_ro->instanceSize);
        gdb_objc_class_changed(cls, OBJC_CLASS_IVARS_CHANGED, ro->name);
    } 
}


/***********************************************************************
* realizeClass
* Performs first-time initialization on class cls, 
* including allocating its read-write data.
* Returns the real class structure for the class. 
* Locking: runtimeLock must be write-locked by the caller
**********************************************************************/

/**
* 主要做一下几件事情:
* 1，申请 (class_rw_t) 内存空间，并通过rw 指针指向这片内存空间， 将class_rw_t 的 ro 指向 编译器确定了的 ro 内存空间，
* 然后将rw指针赋值给class中的bit中用来保存class_rw_t指针的3-47位，也就是class->bit 中的3-47位保存了指向class_rw_t内存空间的指针
* 这片内存空间是运行时allocation的，所以是可读写的。
* 《《很重要》》
 根据父类的ro空间，为当前类的ro扩展父类的成员变量的内存空间，并且把当前类的成员变量的offset更新到父类成员变量的空间后面
 （其实编译期间当前类的instanceSize 已经包含了父类的空间大小，只是offset没做好处理，而在这里主要就是offset的处理）
 
* 2，设置类的父类(superclass)，以及设置类的isa (指向元类)
* 3，将ro中的一些标志(flag) 设置到类的rw 中的标志中（可能是为了后续方便访问）
* 4，将ro中的方法，协议，属性拷贝到rw中，并且把分类的方法，协议，属性也拷贝到rw中，后续通过class 的rw中的methods 就能访问到该类的
 所有的方法，协议，与属性
 
 struct _class_t {
     struct _class_t *isa;
     struct _class_t *superclass;
     void *cache;
     void *vtable;
     struct _class_ro_t *ro;
 };
 
 struct Class {
     isa_t isa;
     Class superclass;
     cache_t cache;             // formerly cache pointer and vtable
     //存放对象相关数据的地方，比如成员变量
     class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
     class_rw_t *data() { return bits.data();}
  }
 传进来的是_class_t 类型，返回的是Class 类型，其实相当于只是把ro 数据保存到bits 中
 
*/

static Class realizeClass(Class cls)
{
    runtimeLock.assertLocked();

    const class_ro_t *ro;
    class_rw_t *rw;
    Class supercls;
    Class metacls;
    bool isMeta;

    if (!cls) return nil;
    if (cls->isRealized()) {
        return cls;
    }
    assert(cls == remapClass(cls));

    /*
     fixme verify class is not in an un-dlopened part of the shared cache?
     调整class 中的rw（class_rw_t） 数据
     struct _class_t {这是编译阶段的类数据结构，
         struct _class_t *isa;
         struct _class_t *superclass;
         void *cache;
         void *vtable;
         struct _class_ro_t *ro;
     };
     union isa_t {
         uintptr_t bits;
         Class cls;
     }

     这其实跟运行时的struct objc_class : objc_object {
         //isa_t isa;//这里展开就是uintptr_t bits;Class cls;
         uintptr_t bits;
         Class cls;
         Class superclass;
         cache_t cache;
         class_data_bits_t bits;
     }
     是差不多一致的
     也就是通过ro = (const class_ro_t *)cls->data(); 从_class_t 中获取struct _class_ro_t *ro;字段应该可以的
     */
    ro = (const class_ro_t *)cls->data();//编译器已确定的ro 在之前只有ro
    if (ro->flags & RO_FUTURE) {//第一次使用时才进行realized，而不是应用启动时就进行realized
        /*
         class is unrealized future class - must never be set by compiler
         意思是：该类还没经过realized？在后面再进行realized？
         #define RO_FUTURE             (1<<30)
         
         objc_getFutureClass(const char *name)过程中
         如果look_up_class(const char *name, ..)查询不到时，通过Class _objc_allocateFutureClass(const char *name)接口
         进行创建对应的class，并添加到future_named_class_map中，这些类就是RO_FUTURE类型的类
         
         */
        // This was a future class. rw data is already allocated.
        rw = cls->data();
        ro = cls->data()->ro;
        cls->changeInfo(RW_REALIZED|RW_REALIZING, RW_FUTURE);
    } else {
        // 编译期间确定的用户声明的类
        // Normal class. Allocate writeable class data.
        //为class 申请class_rw_t的大小的内存空间，并通过rw指针指向该片空间
        rw = (class_rw_t *)calloc(sizeof(class_rw_t), 1);
        //将rw->ro 指向编译期已确定的ro内存，这可能是处在只读数据段内
        rw->ro = ro;
        rw->flags = RW_REALIZED|RW_REALIZING;
        /*
         将指向新申请的class_rw_t大小的内存空间的指针rw赋值给class
         也就是将指针rw保存到objc_class->bits中用来指向保存类信息的3-47位内容，
         （objc_class->bits指针中的3-47位内容是一个指向类信息的指针，这个指针的值就是rw
         换句话就是objc_class->bits（3-47位） == rw ）
         此时rw 中只有ro数据，也就是原始的编译器确定下来的ro数据
         */
        cls->setData(rw);
    }

    isMeta = ro->flags & RO_META;

    rw->version = isMeta ? 7 : 0;  // old runtime went up to 6


    // Choose an index for this class.
    // Sets cls->instancesRequireRawIsa if indexes no more indexes are available
    cls->chooseClassArrayIndex();

    if (PrintConnecting) {
        _objc_inform("CLASS: realizing class '%s'%s %p %p #%u", 
                     cls->nameForLogging(), isMeta ? " (meta)" : "", 
                     (void*)cls, ro, cls->classArrayIndex());
    }

    /*
     这里递归
     realizeClass(remapClass(cls->superclass))
     以及
     metacls = realizeClass(remapClass(cls->ISA()));
     就能确保
     reconcileInstanceVariables(cls, supercls, ro);
     时能确定父类的InstanceSize
     要保证 superclass 和 isa 的完整性，也就是保证类的完整性
     */
    {
        // Realize superclass and metaclass, if they aren't already.
        // This needs to be done after RW_REALIZED is set above, for root classes.
        // This needs to be done after class index is chosen, for root metaclasses.
        supercls = realizeClass(remapClass(cls->superclass));
        metacls = realizeClass(remapClass(cls->ISA()));
    }
    
#if SUPPORT_NONPOINTER_ISA
    // Disable non-pointer isa for some classes and/or platforms.
    // Set instancesRequireRawIsa.
    bool instancesRequireRawIsa = cls->instancesRequireRawIsa();
    bool rawIsaIsInherited = false;
    static bool hackedDispatch = false;

    if (DisableNonpointerIsa) {
        // Non-pointer isa disabled by environment or app SDK version
        instancesRequireRawIsa = true;
    }
    else if (!hackedDispatch  &&  !(ro->flags & RO_META)  &&  
             0 == strcmp(ro->name, "OS_object")) 
    {
        // hack for libdispatch et al - isa also acts as vtable pointer
        hackedDispatch = true;
        instancesRequireRawIsa = true;
    }
    else if (supercls  &&  supercls->superclass  &&  
             supercls->instancesRequireRawIsa()) 
    {
        // This is also propagated by addSubclass() 
        // but nonpointer isa setup needs it earlier.
        // Special case: instancesRequireRawIsa does not propagate 
        // from root class to root metaclass
        instancesRequireRawIsa = true;
        rawIsaIsInherited = true;
    }
    
    if (instancesRequireRawIsa) {
        cls->setInstancesRequireRawIsa(rawIsaIsInherited);
    }
// SUPPORT_NONPOINTER_ISA
#endif

    // Update superclass and metaclass in case of remapping
    // 设置当前类的父类
    cls->superclass = supercls;
    cls->initClassIsa(metacls);

    // Reconcile instance variable offsets / layout.
    // This may reallocate class_ro_t, updating our ro variable.
    
    if (supercls  &&  !isMeta) {
        
        /*
         《《很重要》》
         根据父类的ro空间，为当前类的ro扩展父类的成员变量的内存空间，并且把当前类的成员变量的offset更新到父类成员变量的空间后面
         （其实编译期间当前类的instanceSize 已经包含了父类的空间大小，只是offset没做好处理，而在这里主要就是offset的处理）
         
         也就是当前类的class_ro_t中的相应信息
         1. 修正类中的ivar_list_t * ivars变量列表中的所有变量的偏移量
         2. 修正uint32_t instanceStart;以及uint32_t instanceSize;
         */
        reconcileInstanceVariables(cls, supercls, ro);
    }

    // Set fastInstanceSize if it wasn't set already.
    cls->setInstanceSize(ro->instanceSize); //按道理ro 已经在上面 reconcileInstanceVariables 通过地址形式去修改 不需要改变 但是 在新旧objc对比中发现 旧版的nothing 变成了 cache相关的setFastInstanceSize 估计是为了以后的优化

    /*
     Copy some flags from ro to rw
     将ro 中的某些标识拷贝到rw 中
     */
    if (ro->flags & RO_HAS_CXX_STRUCTORS) {
        cls->setHasCxxDtor();
        if (! (ro->flags & RO_HAS_CXX_DTOR_ONLY)) {
            cls->setHasCxxCtor();
        }
    }

    // Connect this class to its superclass's subclass lists
    if (supercls) {
        addSubclass(supercls, cls);
    } else {
        addRootClass(cls);
    }

    // Attach categories
    methodizeClass(cls);

    return cls;
}


/***********************************************************************
* missingWeakSuperclass
* Return YES if some superclass of cls was weak-linked and is missing.
**********************************************************************/
static bool 
missingWeakSuperclass(Class cls)
{
    assert(!cls->isRealized());

    if (!cls->superclass) {
        // superclass nil. This is normal for root classes only.
        return (!(cls->data()->flags & RO_ROOT));
    } else {
        // superclass not nil. Check if a higher superclass is missing.
        Class supercls = remapClass(cls->superclass);
        assert(cls != cls->superclass);
        assert(cls != supercls);
        if (!supercls) return YES;
        if (supercls->isRealized()) return NO;
        return missingWeakSuperclass(supercls);
    }
}


/***********************************************************************
* realizeAllClassesInImage
* Non-lazily realizes all unrealized classes in the given image.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void realizeAllClassesInImage(header_info *hi)
{
    runtimeLock.assertLocked();

    size_t count, i;
    classref_t *classlist;

    if (hi->areAllClassesRealized()) return;

    classlist = _getObjc2ClassList(hi, &count);

    for (i = 0; i < count; i++) {
        realizeClass(remapClass(classlist[i]));
    }

    hi->setAllClassesRealized(YES);
}


/***********************************************************************
* realizeAllClasses
* Non-lazily realizes all unrealized classes in all known images.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void realizeAllClasses(void)
{
    runtimeLock.assertLocked();

    header_info *hi;
    for (hi = FirstHeader; hi; hi = hi->getNext()) {
        realizeAllClassesInImage(hi);
    }
}


/***********************************************************************
* _objc_allocateFutureClass
* Allocate an unresolved future class for the given class name.
* Returns any existing allocation if one was already made.
* Assumes the named class doesn't exist yet.
* Locking: acquires runtimeLock
**********************************************************************/
Class _objc_allocateFutureClass(const char *name)
{
    mutex_locker_t lock(runtimeLock);

    Class cls;
    NXMapTable *map = futureNamedClasses();

    if ((cls = (Class)NXMapGet(map, name))) {
        // Already have a future class for this name.
        return cls;
    }

    cls = _calloc_class(sizeof(objc_class));
    addFutureNamedClass(name, cls);

    return cls;
}


/***********************************************************************
* objc_getFutureClass.  Return the id of the named class.
* If the class does not exist, return an uninitialized class 
* structure that will be used for the class when and if it 
* does get loaded.
* Not thread safe. 
**********************************************************************/
Class objc_getFutureClass(const char *name)
{
    Class cls;

    // YES unconnected, NO class handler
    // (unconnected is OK because it will someday be the real class)
    cls = look_up_class(name, YES, NO);
    if (cls) {
        if (PrintFuture) {
            _objc_inform("FUTURE: found %p already in use for %s", 
                         (void*)cls, name);
        }

        return cls;
    }
    
    // No class or future class with that name yet. Make one.
    // fixme not thread-safe with respect to 
    // simultaneous library load or getFutureClass.
    return _objc_allocateFutureClass(name);
}


BOOL _class_isFutureClass(Class cls)
{
    return cls  &&  cls->isFuture();
}


/***********************************************************************
* _objc_flush_caches
* Flushes all caches.
* (Historical behavior: flush caches for cls, its metaclass, 
* and subclasses thereof. Nil flushes all classes.)
* Locking: acquires runtimeLock
**********************************************************************/
static void flushCaches(Class cls)
{
    runtimeLock.assertLocked();

    mutex_locker_t lock(cacheUpdateLock);

    if (cls) {
        foreach_realized_class_and_subclass(cls, ^(Class c){
            cache_erase_nolock(c);
        });
    }
    else {
        foreach_realized_class_and_metaclass(^(Class c){
            cache_erase_nolock(c);
        });
    }
}


void _objc_flush_caches(Class cls)
{
    {
        mutex_locker_t lock(runtimeLock);
        flushCaches(cls);
        if (cls  &&  cls->superclass  &&  cls != cls->getIsa()) {
            flushCaches(cls->getIsa());
        } else {
            // cls is a root class or root metaclass. Its metaclass is itself
            // or a subclass so the metaclass caches were already flushed.
        }
    }

    if (!cls) {
        // collectALot if cls==nil
        mutex_locker_t lock(cacheUpdateLock);
        cache_collect(true);
    }
}


/***********************************************************************
* map_images
* Process the given images which are being mapped in by dyld.
* Calls ABI-agnostic code after taking ABI-specific locks.
*
* Locking: write-locks runtimeLock
**********************************************************************/
void
map_images(unsigned count, const char * const paths[],
           const struct mach_header * const mhdrs[])
{
    mutex_locker_t lock(runtimeLock);
    return map_images_nolock(count, paths, mhdrs);
}


/***********************************************************************
* load_images
* Process +load in the given images which are being mapped in by dyld.
*
* Locking: write-locks runtimeLock and loadMethodLock
**********************************************************************/
extern bool hasLoadMethods(const headerType *mhdr);
extern void prepare_load_methods(const headerType *mhdr);

void
load_images(const char *path __unused, const struct mach_header *mh)
{
    // Return without taking locks if there are no +load methods here.
    if (!hasLoadMethods((const headerType *)mh)) return;

    recursive_mutex_locker_t lock(loadMethodLock);

    // Discover load methods
    {
        mutex_locker_t lock2(runtimeLock);
        /*
         1, 获取非懒加载的类（带+load方法的类），将其以及他对应的+load 的IMP放到一全局的loadable_classes 数组中，
            A：通过递归的方式获取，确保父类的+load放在最前面
            B：通过查询类的元类（类方法在其元类中）中的rw->ro->baseMethods()列表中有没有名字为"load"方法得知
         
         2，获取非懒加载的分类（带+load方法的分类），将其以及他对应的+load 的IMP放到一全局的loadable_categories 数组中
            A：从分类category_t 的classMethods 列表中查询有没有名字为"load"方法得知
         */
        prepare_load_methods((const headerType *)mh);
    }

    // Call +load methods (without runtimeLock - re-entrant)
    /*
     上面将+load的方法都放到全局的列表后，下面就开始调用执行
     先遍历类的loadable_classes 执行，再遍历分类的loadable_categories 执行
     
     +load方法执行顺序：
     父类->当前类->分类
     */
    call_load_methods();
}


/***********************************************************************
* unmap_image
* Process the given image which is about to be unmapped by dyld.
*
* Locking: write-locks runtimeLock and loadMethodLock
**********************************************************************/
void 
unmap_image(const char *path __unused, const struct mach_header *mh)
{
    recursive_mutex_locker_t lock(loadMethodLock);
    mutex_locker_t lock2(runtimeLock);
    unmap_image_nolock(mh);
}




/***********************************************************************
* mustReadClasses
* Preflight check in advance of readClass() from an image.
**********************************************************************/
bool mustReadClasses(header_info *hi)
{
    const char *reason;

    // If the image is not preoptimized then we must read classes.
    if (!hi->isPreoptimized()) {
        reason = nil; // Don't log this one because it is noisy.
        goto readthem;
    }

    // If iOS simulator then we must read classes.
#if TARGET_OS_SIMULATOR
    reason = "the image is for iOS simulator";
    goto readthem;
#endif

    assert(!hi->isBundle());  // no MH_BUNDLE in shared cache

    // If the image may have missing weak superclasses then we must read classes
    if (!noMissingWeakSuperclasses()) {
        reason = "the image may contain classes with missing weak superclasses";
        goto readthem;
    }

    // If there are unresolved future classes then we must read classes.
    if (haveFutureNamedClasses()) {
        reason = "there are unresolved future classes pending";
        goto readthem;
    }

    // readClass() does not need to do anything.
    return NO;

 readthem:
    if (PrintPreopt  &&  reason) {
        _objc_inform("PREOPTIMIZATION: reading classes manually from %s "
                     "because %s", hi->fname(), reason);
    }
    return YES;
}


/***********************************************************************
* readClass
* Read a class and metaclass as written by a compiler.（读取被编译器写的class 和 metaclass）
* Returns the new class pointer. This could be: 返回新类指针
* - cls
* - nil  (cls has a missing weak-linked superclass)
* - something else (space for this class was reserved by a future class)
*
* Note that all work performed by this function is preflighted by 
* mustReadClasses(). Do not change this function without updating that one.
*
* Locking: runtimeLock acquired by map_images or objc_readClassPair
 
 struct _class_t {
     struct _class_t *isa;
     struct _class_t *superclass;
     void *cache;
     void *vtable;
     struct _class_ro_t *ro;
 };
 union isa_t {
     uintptr_t bits;
     Class cls;
 }
 struct objc_class : objc_object {
     isa_t isa;
     Class superclass;
     cache_t cache;             // formerly cache pointer and vtable
     //存放对象相关数据的地方，比如成员变量
     class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
     class_rw_t *data() { return bits.data();}
  }
 传进来的是_class_t，返回的是Class（objc_class）
 typedef struct objc_class *Class;
**********************************************************************/
Class readClass(Class cls, bool headerIsBundle, bool headerIsPreoptimized)
{
    const char *mangledName = cls->mangledName();
    
    if (missingWeakSuperclass(cls)) {
        // No superclass (probably weak-linked). 
        // Disavow any knowledge of this subclass.
        if (PrintConnecting) {
            _objc_inform("CLASS: IGNORING class '%s' with "
                         "missing weak-linked superclass", 
                         cls->nameForLogging());
        }
        addRemappedClass(cls, nil);
        cls->superclass = nil;
        return nil;
    }
    
    // Note: Class __ARCLite__'s hack does not go through here. 
    // Class structure fixups that apply to it also need to be 
    // performed in non-lazy realization below.
    
    // These fields should be set to zero because of the 
    // binding of _objc_empty_vtable, but OS X 10.8's dyld 
    // does not bind shared cache absolute symbols as expected.
    // This (and the __ARCLite__ hack below) can be removed 
    // once the simulator drops 10.8 support.
#if TARGET_OS_SIMULATOR
    if (cls->cache._mask)
        cls->cache._mask = 0;
    if (cls->cache._occupied)
        cls->cache._occupied = 0;
    if (cls->ISA()->cache._mask)
        cls->ISA()->cache._mask = 0;
    if (cls->ISA()->cache._occupied)
        cls->ISA()->cache._occupied = 0;
#endif

    Class replacing = nil;
    /*
     从future_named_class_map中获取对应的class
     future_named_class_map中的class是在objc_getFutureClass(const char *name)过程中
     如果look_up_class(const char *name, ..)查询不到时，通过Class _objc_allocateFutureClass(const char *name)接口
     进行创建对应的class，并添加到future_named_class_map中，
     */
    if (Class newCls = popFutureNamedClass(mangledName)) {
        // 如果cls是通过_objc_allocateFutureClass()在运行时生成的
        // This name was previously allocated as a future class.
        // Copy objc_class to future class's struct.
        // Preserve future's rw data block.
        
        if (newCls->isAnySwift()) {
            _objc_fatal("Can't complete future class request for '%s' "
                        "because the real class is too big.", 
                        cls->nameForLogging());
        }
        /*
         获取objc_class中指向类信息内存块的class_rw_t类型指针rw
         //old_ro 则是编译期间的类信息内存块指针
         因为newCls是通过allocated生成的future class（在_objc_allocateFutureClass中创建），
         所以他的class_rw_t *rw = newCls->data();
         所指向的内存是可读写的？？也许还没有值，但这片内存是可读写的
         */
        class_rw_t *rw = newCls->data();
        const class_ro_t *old_ro = rw->ro;
        /*
         void* memcpy(void *restrict dst, const void *restrict src, size_t n);
         通过内存拷贝，将需要readClass 的cls 的数据覆盖在newCls上
         因为从上面的注释来看newCls是之前通过allocated生成的future class，也就是之前allocated的内存块
         还没有具体的class数据，所以需要把cls的数据填充到该内存块内
         */
        memcpy(newCls, cls, sizeof(objc_class));
        
        /*
         因为是内存拷贝，所以
         此时的(class_ro_t *)newCls->data(); 相当于(class_ro_t *)cls->data()
         因此通过allocated生成的future class中的rw->ro 指向了(class_ro_t *)cls->data()
         */
        rw->ro = (class_ro_t *)newCls->data();
        
        //将rw更新到通过allocated生成的future classs上
        newCls->setData(rw);
        freeIfMutable((char *)old_ro->name);
        /*
         释放掉通过allocated生成的future class中旧的rw->ro指向的内存
         因为此时的rw->ro已经指向了(class_ro_t *)cls->data()
        */
        free((void *)old_ro);
        
        addRemappedClass(cls, newCls);
        
        replacing = cls;
        cls = newCls;
        
        /*
         所以整个过程是不是可以这样子理解？？？
         1. 运行时初始化的时候通过allocated生成一块objc_class类型的内存块（也就是future class）
            在readClass的时候，将从mach-o读取到的_class_t类型的数据内存拷贝到这份内存块中
         
         2.在allocated生成objc_class类型内存块的同时，也会生成一块用来保存class_rw_t信息的内存块
           并且是通过objc_class->bit指向这块内存的
           所以在1中进行类内存拷贝后，需要恢复objc_class->bit这个字段，同时将生成的class_rw_t内存块中的
           rw->ro字段指向原始的（编译器）类信息内存块rw->ro = (class_ro_t *)newCls->data();
         
           因为class_rw_t是运行时生成，所以可读写但是原始的类信息rw->ro不变
           那么在后续的操作中就可以对运行时生成的class_rw_t进行读写操作，比如将分类的方法添加进来
         */
        
    }
    
    if (headerIsPreoptimized  &&  !replacing) {
        // class list built in shared cache
        // fixme strict assert doesn't work because of duplicates
        // assert(cls == getClass(name));
        assert(getClass(mangledName));
    } else {
        // 主要还是要进入这个分支的
        addNamedClass(cls, mangledName, replacing);
        addClassTableEntry(cls);
    }

    // for future reference: shared cache never contains MH_BUNDLEs
    if (headerIsBundle) {
        cls->data()->flags |= RO_FROM_BUNDLE;
        cls->ISA()->data()->flags |= RO_FROM_BUNDLE;
    }
    
    return cls;
}


/***********************************************************************
* readProtocol
* Read a protocol as written by a compiler.
**********************************************************************/
static void
readProtocol(protocol_t *newproto, Class protocol_class,
             NXMapTable *protocol_map, 
             bool headerIsPreoptimized, bool headerIsBundle)
{
    // This is not enough to make protocols in unloaded bundles safe, 
    // but it does prevent crashes when looking up unrelated protocols.
    auto insertFn = headerIsBundle ? NXMapKeyCopyingInsert : NXMapInsert;

    protocol_t *oldproto = (protocol_t *)getProtocol(newproto->mangledName);

    if (oldproto) {
        // Some other definition already won.
        if (PrintProtocols) {
            _objc_inform("PROTOCOLS: protocol at %p is %s  "
                         "(duplicate of %p)",
                         newproto, oldproto->nameForLogging(), oldproto);
        }
    }
    else if (headerIsPreoptimized) {
        // Shared cache initialized the protocol object itself, 
        // but in order to allow out-of-cache replacement we need 
        // to add it to the protocol table now.

        protocol_t *cacheproto = (protocol_t *)
            getPreoptimizedProtocol(newproto->mangledName);
        protocol_t *installedproto;
        if (cacheproto  &&  cacheproto != newproto) {
            // Another definition in the shared cache wins (because 
            // everything in the cache was fixed up to point to it).
            installedproto = cacheproto;
        }
        else {
            // This definition wins.
            installedproto = newproto;
        }
        
        assert(installedproto->getIsa() == protocol_class);
        assert(installedproto->size >= sizeof(protocol_t));
        insertFn(protocol_map, installedproto->mangledName, 
                 installedproto);
        
        if (PrintProtocols) {
            _objc_inform("PROTOCOLS: protocol at %p is %s", 
                         installedproto, installedproto->nameForLogging());
            if (newproto != installedproto) {
                _objc_inform("PROTOCOLS: protocol at %p is %s  "
                             "(duplicate of %p)", 
                             newproto, installedproto->nameForLogging(), 
                             installedproto);
            }
        }
    }
    else if (newproto->size >= sizeof(protocol_t)) {
        // New protocol from an un-preoptimized image
        // with sufficient storage. Fix it up in place.
        // fixme duplicate protocols from unloadable bundle
        newproto->initIsa(protocol_class);  // fixme pinned
        insertFn(protocol_map, newproto->mangledName, newproto);
        if (PrintProtocols) {
            _objc_inform("PROTOCOLS: protocol at %p is %s",
                         newproto, newproto->nameForLogging());
        }
    }
    else {
        // New protocol from an un-preoptimized image 
        // with insufficient storage. Reallocate it.
        // fixme duplicate protocols from unloadable bundle
        size_t size = max(sizeof(protocol_t), (size_t)newproto->size);
        protocol_t *installedproto = (protocol_t *)calloc(size, 1);
        memcpy(installedproto, newproto, newproto->size);
        installedproto->size = (typeof(installedproto->size))size;
        
        installedproto->initIsa(protocol_class);  // fixme pinned
        insertFn(protocol_map, installedproto->mangledName, installedproto);
        if (PrintProtocols) {
            _objc_inform("PROTOCOLS: protocol at %p is %s  ", 
                         installedproto, installedproto->nameForLogging());
            _objc_inform("PROTOCOLS: protocol at %p is %s  "
                         "(reallocated to %p)", 
                         newproto, installedproto->nameForLogging(), 
                         installedproto);
        }
    }
}

/***********************************************************************
* _read_images
* Perform initial processing of the headers in the linked 
* list beginning with headerList. 
*
* Called by: map_images_nolock
*
* Locking: runtimeLock acquired by map_images
**********************************************************************/
/*
 
 将分类的实例方法添加到类的rw中的methods 列表中
 将分类的类方法添加到类的isa（元类）的rw中的methods列表中
 */
void _read_images(header_info **hList, uint32_t hCount, int totalClasses, int unoptimizedTotalClasses)
{
    header_info *hi;
    uint32_t hIndex;
    size_t count;
    size_t i;
    Class *resolvedFutureClasses = nil;
    size_t resolvedFutureClassCount = 0;
    static bool doneOnce;
    TimeLogger ts(PrintImageTimes);

    runtimeLock.assertLocked();

#define EACH_HEADER \
    hIndex = 0;         \
    hIndex < hCount && (hi = hList[hIndex]); \
    hIndex++

    if (!doneOnce) {
        doneOnce = YES;

#if SUPPORT_NONPOINTER_ISA
        // Disable non-pointer isa under some conditions.

# if SUPPORT_INDEXED_ISA
        // Disable nonpointer isa if any image contains old Swift code
        for (EACH_HEADER) {
            if (hi->info()->containsSwift()  &&
                hi->info()->swiftVersion() < objc_image_info::SwiftVersion3)
            {
                DisableNonpointerIsa = true;
                if (PrintRawIsa) {
                    _objc_inform("RAW ISA: disabling non-pointer isa because "
                                 "the app or a framework contains Swift code "
                                 "older than Swift 3.0");
                }
                break;
            }
        }
# endif

# if TARGET_OS_OSX
        // Disable non-pointer isa if the app is too old
        // (linked before OS X 10.11)
        if (dyld_get_program_sdk_version() < DYLD_MACOSX_VERSION_10_11) {
            DisableNonpointerIsa = true;
            if (PrintRawIsa) {
                _objc_inform("RAW ISA: disabling non-pointer isa because "
                             "the app is too old (SDK version " SDK_FORMAT ")",
                             FORMAT_SDK(dyld_get_program_sdk_version()));
            }
        }
        //如果应用程序有__DATA，__objc_rawisa节，则禁用非指针isa
        //加载旧扩展的新应用程序可能需要这个。
        // Disable non-pointer isa if the app has a __DATA,__objc_rawisa section
        // New apps that load old extensions may need this.
        for (EACH_HEADER) {//for  hIndex = 0; hIndex < hCount && (hi = hList[hIndex]); hIndex++
            if (hi->mhdr()->filetype != MH_EXECUTE) continue; //如果文件类型不是可执行文件类型 跳过
            unsigned long size;
            if (getsectiondata(hi->mhdr(), "__DATA", "__objc_rawisa", &size)) {
                DisableNonpointerIsa = true;
                if (PrintRawIsa) {
                    _objc_inform("RAW ISA: disabling non-pointer isa because "
                                 "the app has a __DATA,__objc_rawisa section");
                }
            }
            break;  // assume only one MH_EXECUTE image
        }
# endif

#endif

        if (DisableTaggedPointers) {//禁用 Tagged Pointer，与环境变量 OBJC_DISABLE_TAGGED_POINTERS 相关
            /*
             参考文章：https://www.jianshu.com/p/3176e30c040b
             【参考文章】(https://www.infoq.cn/article/r5s0budukwyndafrivh4)
             如果环境变量设置了禁止Tagged Pointer，则调用Tagged Pointer禁用函数
             禁用NSNumber等的 Tagged Pointer 指针优化
             
             
             苹果预留了环境变量 OBJC_DISABLE_TAGGED_POINTERS，通过设置该变量的布尔值，可以将Tagged Pointer技术的启用与关闭的决定权交给开发者！
             如果禁用Tagged Pointer，只需设置环境变量 OBJC_DISABLE_TAGGED_POINTERS为YES 即可！
             
             */
            disableTaggedPointers();
        }
        //初始化 TaggedPointer 混淆器：用于保护 Tagged Pointer 上的数据
        initializeTaggedPointerObfuscator();

        if (PrintConnecting) {
            _objc_inform("CLASS: found %d classes during launch", totalClasses);
        }

        // namedClasses
        // Preoptimized classes don't go in this table.
        // 4/3 is NXMapTable's load factor
        int namedClassesSize = 
            (isPreoptimized() ? unoptimizedTotalClasses : totalClasses) * 4 / 3;
        gdb_objc_realized_classes =
            NXCreateMapTable(NXStrValueMapPrototype, namedClassesSize); //所有类的表 -实现/未实现
        
        allocatedClasses = NXCreateHashTable(NXPtrPrototype, 0, nil); //包含包含objc)allocateClassPair分配的所有类和元类的表（已分配）
        // 新版在objc_init runtime.init()处理
        // robjc::allocatedClasses.init();

        
        ts.log("IMAGE TIMES: first time tasks");
    }


    // Discover classes. Fix up unresolved future classes. Mark bundle classes.

    /*
     循环遍历所有的image，获取image中所有的classref_t
     */
    for (EACH_HEADER) {// 相当于 for (hIndex = 0;hIndex < hCount && (hi = hList[hIndex]); hIndex++) {}
        /*
         从image的数据段__objc_classlist 中读取所有的类
         读出来时的类型如下,编译期的类型
         struct _class_ro_t {
             unsigned int flags;
             //-----------确定了成员变量的地址空间----------------
             unsigned int instanceStart;
             unsigned int instanceSize;
             //---------------------------
             const unsigned char *ivarLayout;
             const char *name;
             const struct _method_list_t *baseMethods;
             const struct _objc_protocol_list *baseProtocols;
             const struct _ivar_list_t *ivars;
             const unsigned char *weakIvarLayout;
             const struct _prop_list_t *properties;
         };
         struct _class_t {
             struct _class_t *isa;
             struct _class_t *superclass;
             void *cache;
             void *vtable;
             struct _class_ro_t *ro;
         };
         union isa_t {
             uintptr_t bits;
             Class cls;
         }
         struct Class {
             isa_t isa;
             Class superclass;
             cache_t cache;             // formerly cache pointer and vtable
             //存放对象相关数据的地方，比如成员变量
             class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
             class_rw_t *data() { return bits.data();}
          }
         */
        /*
         因为 通过 xcrun -sdk iphoneos clang -arch arm64 -rewrite-objc -fobjc-arc -fobjc-runtime=ios-8.0.0 main.m
         经过一层编译 将oc代码转化为C++代码 可得 __objc_classlist 如何存入 由此可得以上类型
         
         static struct _class_ro_t _OBJC_CLASS_RO_$_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
             0,
             __OFFSETOFIVAR__(struct Person, father_var_loves),
             
              // sizeof() 是一个运算符，并不是一个函数。sizeof() 传进来的是类型，用来计算这个类型占多大内存，
              // 这个在 编译器编译阶段 就会确定大小并直接转化成 8 、16 、24 这样的常数，而不是在运行时计算。参数可以是数组、指针、类型、对象、结构体、函数等。
              
             sizeof(struct Person_IMPL),
             0,
             "Person",
             (const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Person,
             0,
             (const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Person,
             0,
             (const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Person,
         };
         extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Person __attribute__ ((used, section ("__DATA,__objc_data"))) = {
             0, // &OBJC_METACLASS_$_Person,
             0, // &OBJC_CLASS_$_NSObject,
             0, // (void *)&_objc_empty_cache,
             0, // unused, was (void *)&_objc_empty_vtable,
             &_OBJC_CLASS_RO_$_Person,
         };
         static struct _class_t *L_OBJC_LABEL_CLASS_$ [2] __attribute__((used, section ("__DATA, __objc_classlist,regular,no_dead_strip")))= {
             &OBJC_CLASS_$_Person,
             &OBJC_CLASS_$_Man,
         };
         */
        /*
         从mach-o 中读取"__objc_classlist"段内容，该段内容就是所有的类信息
         读取到的应该是_class_t类型数据
         这里获取到的应该是所有懒加载的类，不需要在启动时对齐进行realized
         在第一次发送消息执行到lookUpImpOrForward()这一步时才调用realizeClass(cls)对类进行处理
         */
        classref_t *classlist = _getObjc2ClassList(hi, &count);
        if (! mustReadClasses(hi)) {
            // Image is sufficiently optimized that we need not call readClass()
            continue;
        }
        bool headerIsBundle = hi->isBundle();
        bool headerIsPreoptimized = hi->isPreoptimized();
        /*
         遍历所有从image的数据段__objc_classlist中读取出来的classref_t，对其进行readClass, 也就是将_class_t转换成Class
         
         */
        for (i = 0; i < count; i++) {
            Class cls = (Class)classlist[i];
            /*
             读取被编译器写的_class_t,将其保存在gdb_objc_realized_classes中
             在这里调用readClass对cls操作主要作用是将cls添加到gdb_objc_realized_classes中
             */
            Class newCls = readClass(cls, headerIsBundle, headerIsPreoptimized);

            if (newCls != cls  &&  newCls) {//应用启动时基本跑不进if中
                // Class was moved but not deleted. Currently this occurs 
                // only when the new class resolved a future class.
                // Non-lazily realize the class below.
                resolvedFutureClasses = (Class *)
                    realloc(resolvedFutureClasses, 
                            (resolvedFutureClassCount+1) * sizeof(Class));
                resolvedFutureClasses[resolvedFutureClassCount++] = newCls;
            }
        }
    }//-------for (EACH_HEADER) {} 结束

    ts.log("IMAGE TIMES: discover classes");

    // Fix up remapped classes
    // Class list and nonlazy class list remain unremapped.
    // Class refs and super refs are remapped for message dispatching.
    
    if (!noClassesRemapped()) {
        for (EACH_HEADER) {
            Class *classrefs = _getObjc2ClassRefs(hi, &count);
            for (i = 0; i < count; i++) {
                remapClassRef(&classrefs[i]);
            }
            // fixme why doesn't test future1 catch the absence of this?
            classrefs = _getObjc2SuperRefs(hi, &count);
            for (i = 0; i < count; i++) {
                remapClassRef(&classrefs[i]);
            }
        }
    }

    ts.log("IMAGE TIMES: remap classes");

    // Fix up @selector references
    static size_t UnfixedSelectors;
    {
        mutex_locker_t lock(selLock);
        for (EACH_HEADER) {
            if (hi->isPreoptimized()) continue;
            
            bool isBundle = hi->isBundle();
            SEL *sels = _getObjc2SelectorRefs(hi, &count);
            UnfixedSelectors += count;
            for (i = 0; i < count; i++) {
                const char *name = sel_cname(sels[i]);
                sels[i] = sel_registerNameNoLock(name, isBundle);
            }
        }
    }

    ts.log("IMAGE TIMES: fix up selector references");

#if SUPPORT_FIXUP
    // Fix up old objc_msgSend_fixup call sites
    for (EACH_HEADER) {
        message_ref_t *refs = _getObjc2MessageRefs(hi, &count);
        if (count == 0) continue;

        if (PrintVtables) {
            _objc_inform("VTABLES: repairing %zu unsupported vtable dispatch "
                         "call sites in %s", count, hi->fname());
        }
        for (i = 0; i < count; i++) {
            fixupMessageRef(refs+i);
        }
    }

    ts.log("IMAGE TIMES: fix up objc_msgSend_fixup");
#endif

    // Discover protocols. Fix up protocol refs.
    for (EACH_HEADER) {
        extern objc_class OBJC_CLASS_$_Protocol;
        Class cls = (Class)&OBJC_CLASS_$_Protocol;
        assert(cls);
        NXMapTable *protocol_map = protocols();
        bool isPreoptimized = hi->isPreoptimized();
        bool isBundle = hi->isBundle();

        protocol_t **protolist = _getObjc2ProtocolList(hi, &count);
        for (i = 0; i < count; i++) {
            readProtocol(protolist[i], cls, protocol_map, 
                         isPreoptimized, isBundle);
        }
    }

    ts.log("IMAGE TIMES: discover protocols");

    // Fix up @protocol references
    // Preoptimized images may have the right 
    // answer already but we don't know for sure.
    for (EACH_HEADER) {
        protocol_t **protolist = _getObjc2ProtocolRefs(hi, &count);
        for (i = 0; i < count; i++) {
            remapProtocolRef(&protolist[i]);
        }
    }

    ts.log("IMAGE TIMES: fix up @protocol references");

    /*
     Realize non-lazy classes (for +load methods and static instances)
     non-lazy classes 也就是有 +load 的类
     处理非懒加载的类，非懒加载的类需要在启动时进行realize，因为启动过程中会调用对应的+load方法
     */
    for (EACH_HEADER) {//应用启动时，主要跑了这里对class进行fix,也就是realizeClass
        classref_t *classlist = 
            _getObjc2NonlazyClassList(hi, &count);//新旧版的差别 在于新版支持opt 套多一层opt判断获取
        for (i = 0; i < count; i++) {
            Class cls = remapClass(classlist[i]);//重映射的map中 里面有个_did_init估计是还没初始化 第一次时候都为空 返回本身？？
            if (!cls) continue;

            // hack for class __ARCLite__, which didn't get this above
#if TARGET_OS_SIMULATOR
            if (cls->cache._buckets == (void*)&_objc_empty_cache  &&  
                (cls->cache._mask  ||  cls->cache._occupied)) 
            {
                cls->cache._mask = 0;
                cls->cache._occupied = 0;
            }
            if (cls->ISA()->cache._buckets == (void*)&_objc_empty_cache  &&  
                (cls->ISA()->cache._mask  ||  cls->ISA()->cache._occupied)) 
            {
                cls->ISA()->cache._mask = 0;
                cls->ISA()->cache._occupied = 0;
            }
#endif
            
            addClassTableEntry(cls); //将cls添加到allocatedClasseshash表中
            /*
             启动过程中的重点在这里
             */
            realizeClass(cls);
        }
    }

    ts.log("IMAGE TIMES: realize non-lazy classes");

    // Realize newly-resolved future classes, in case CF manipulates them
    if (resolvedFutureClasses) {
        for (i = 0; i < resolvedFutureClassCount; i++) {
            realizeClass(resolvedFutureClasses[i]);
            resolvedFutureClasses[i]->setInstancesRequireRawIsa(false/*inherited*/);
        }
        free(resolvedFutureClasses);
    }    

    ts.log("IMAGE TIMES: realize future classes");

    /*
     Discover categories.
     将分类从image中获取，并插入到类对应的分类列表中  //新版的这部分内容 提前到了objc_msgSend_fixup 之后
     */
    for (EACH_HEADER) {
        //从 __objc_catlist 段中读取image中的所有的分类信息
        category_t **catlist = 
            _getObjc2CategoryList(hi, &count);
        bool hasClassProperties = hi->info()->hasCategoryClassProperties();

        for (i = 0; i < count; i++) {
            category_t *cat = catlist[i];
            Class cls = remapClass(cat->cls);

            if (!cls) {
                // Category's target class is missing (probably weak-linked).
                // Disavow any knowledge of this category.
                catlist[i] = nil;
                if (PrintConnecting) {
                    _objc_inform("CLASS: IGNORING category \?\?\?(%s) %p with "
                                 "missing weak-linked target class", 
                                 cat->name, cat);
                }
                continue;
            }

            // Process this category. 
            // First, register the category with its target class. 
            // Then, rebuild the class's method lists (etc) if 
            // the class is realized. 
            bool classExists = NO;
            if (cat->instanceMethods ||  cat->protocols  
                ||  cat->instanceProperties) 
            {
                /*
                 如果分类中有实例方法，协议，或者属性，则执行addUnattachedCategoryForClass方法
                 将分类信息插入到类对应的分类列表中
                 有一个全局的map
                 category_map = {
                    class_A : category_list,
                    class_B : category_list
                 }
                 category_list = [category_t,category_t,category_t]
                 */
                addUnattachedCategoryForClass(cat, cls, hi);
                if (cls->isRealized()) {
                    /*
                     内部使用attachCategories 接口，将分类的方法添加到类的rw中的的methods 中
                     同时也会把属性，协议添加到类的rw中对应的列表中
                     
                     */
                    remethodizeClass(cls);
                    classExists = YES;
                }
                if (PrintConnecting) {
                    _objc_inform("CLASS: found category -%s(%s) %s", 
                                 cls->nameForLogging(), cat->name, 
                                 classExists ? "on existing class" : "");
                }
            }

            if (cat->classMethods  ||  cat->protocols  
                ||  (hasClassProperties && cat->_classProperties)) 
            {
                /*
                如果分类中有类方法，协议，或者属性，则执行addUnattachedCategoryForClass方法
                将分类信息插入到类的元类对应的分类列表中（元类才保存类的类方法）
                */
                addUnattachedCategoryForClass(cat, cls->ISA(), hi);
                if (cls->ISA()->isRealized()) {
                    /*
                    内部使用attachCategories 接口，将分类的方法添加到类的rw中的的methods 中
                    同时也会把属性，协议添加到类的rw中对应的列表中
                    */
                    remethodizeClass(cls->ISA());
                }
                if (PrintConnecting) {
                    _objc_inform("CLASS: found category +%s(%s)", 
                                 cls->nameForLogging(), cat->name);
                }
            }
        }
    }

    ts.log("IMAGE TIMES: discover categories");

    // Category discovery MUST BE LAST to avoid potential races 
    // when other threads call the new category code before 
    // this thread finishes its fixups.

    // +load handled by prepare_load_methods()

    if (DebugNonFragileIvars) {
        realizeAllClasses();
    }


    // Print preoptimization statistics
    if (PrintPreopt) {
        static unsigned int PreoptTotalMethodLists;
        static unsigned int PreoptOptimizedMethodLists;
        static unsigned int PreoptTotalClasses;
        static unsigned int PreoptOptimizedClasses;

        for (EACH_HEADER) {
            if (hi->isPreoptimized()) {
                _objc_inform("PREOPTIMIZATION: honoring preoptimized selectors "
                             "in %s", hi->fname());
            }
            else if (hi->info()->optimizedByDyld()) {
                _objc_inform("PREOPTIMIZATION: IGNORING preoptimized selectors "
                             "in %s", hi->fname());
            }

            classref_t *classlist = _getObjc2ClassList(hi, &count);
            for (i = 0; i < count; i++) {
                Class cls = remapClass(classlist[i]);
                if (!cls) continue;

                PreoptTotalClasses++;
                if (hi->isPreoptimized()) {
                    PreoptOptimizedClasses++;
                }
                
                const method_list_t *mlist;
                if ((mlist = ((class_ro_t *)cls->data())->baseMethods())) {
                    PreoptTotalMethodLists++;
                    if (mlist->isFixedUp()) {
                        PreoptOptimizedMethodLists++;
                    }
                }
                if ((mlist=((class_ro_t *)cls->ISA()->data())->baseMethods())) {
                    PreoptTotalMethodLists++;
                    if (mlist->isFixedUp()) {
                        PreoptOptimizedMethodLists++;
                    }
                }
            }
        }

        _objc_inform("PREOPTIMIZATION: %zu selector references not "
                     "pre-optimized", UnfixedSelectors);
        _objc_inform("PREOPTIMIZATION: %u/%u (%.3g%%) method lists pre-sorted",
                     PreoptOptimizedMethodLists, PreoptTotalMethodLists, 
                     PreoptTotalMethodLists
                     ? 100.0*PreoptOptimizedMethodLists/PreoptTotalMethodLists 
                     : 0.0);
        _objc_inform("PREOPTIMIZATION: %u/%u (%.3g%%) classes pre-registered",
                     PreoptOptimizedClasses, PreoptTotalClasses, 
                     PreoptTotalClasses 
                     ? 100.0*PreoptOptimizedClasses/PreoptTotalClasses
                     : 0.0);
        _objc_inform("PREOPTIMIZATION: %zu protocol references not "
                     "pre-optimized", UnfixedProtocolReferences);
    }

#undef EACH_HEADER
}


/***********************************************************************
* prepare_load_methods
* Schedule +load for classes in this image, any un-+load-ed 
* superclasses in other images, and any categories in this image.
**********************************************************************/
// Recursively schedule +load for cls and any un-+load-ed superclasses.
// cls must already be connected.
/////将类以及他对应的+load 的IMP 加入到一个全局的loadable_classes 数组中
static void schedule_class_load(Class cls)
{
    if (!cls) return;
    assert(cls->isRealized());  // _read_images should realize

    if (cls->data()->flags & RW_LOADED) return;

    /*
     Ensure superclass-first ordering
     为确保父类的+load会被先执行，在这里通过递归的方式，先将父类以及他对应的+load 的IMP 加入到一个全局的loadable_classes 数组中
     */
    schedule_class_load(cls->superclass);

    //将类以及他对应的+load 的IMP 加入到一个全局的loadable_classes 数组中
    add_class_to_loadable_list(cls);
    cls->setInfo(RW_LOADED); 
}

// Quick scan for +load methods that doesn't take a lock.
bool hasLoadMethods(const headerType *mhdr)
{
    size_t count;
    if (_getObjc2NonlazyClassList(mhdr, &count)  &&  count > 0) return true;
    if (_getObjc2NonlazyCategoryList(mhdr, &count)  &&  count > 0) return true;
    return false;
}

void prepare_load_methods(const headerType *mhdr)
{
    size_t count, i;

    runtimeLock.assertLocked();

    //获取非懒加载的类，也就是有+load方法的类
    classref_t *classlist = 
        _getObjc2NonlazyClassList(mhdr, &count);
    for (i = 0; i < count; i++) {
        /*
         遍历所有的类，将类以及他对应的+load 的IMP 加入到一个全局的loadable_classes 数组中
         内部会有一个递归的处理父类的调用，所以父类会被加在loadable_classes数组的前面
         */
        schedule_class_load(remapClass(classlist[i]));
    }

    //获取非懒加载的分类，也就是有+load方法的分类
    category_t **categorylist = _getObjc2NonlazyCategoryList(mhdr, &count);
    for (i = 0; i < count; i++) {
        /*
        遍历所有的非懒加载分类，将其以及他对应的+load 的IMP 加入到一个全局的loadable_categories 数组中
        */
        category_t *cat = categorylist[i];
        Class cls = remapClass(cat->cls);
        if (!cls) continue;  // category for ignored weak-linked class
        realizeClass(cls); //为什么需要这步骤 诉诸宿主类不一定有load方法实现 那么现在如果他的分类进行了load 方法的实现 这里必须也提前去realize
        assert(cls->ISA()->isRealized());
        add_category_to_loadable_list(cat);
    }
}


/***********************************************************************
* _unload_image
* Only handles MH_BUNDLE for now.
* Locking: write-lock and loadMethodLock acquired by unmap_image
**********************************************************************/
void _unload_image(header_info *hi)
{
    size_t count, i;

    loadMethodLock.assertLocked();
    runtimeLock.assertLocked();

    // Unload unattached categories and categories waiting for +load.

    category_t **catlist = _getObjc2CategoryList(hi, &count);
    for (i = 0; i < count; i++) {
        category_t *cat = catlist[i];
        if (!cat) continue;  // category for ignored weak-linked class
        Class cls = remapClass(cat->cls);
        assert(cls);  // shouldn't have live category for dead class

        // fixme for MH_DYLIB cat's class may have been unloaded already

        // unattached list
        removeUnattachedCategoryForClass(cat, cls);

        // +load queue
        remove_category_from_loadable_list(cat);
    }

    // Unload classes.

    // Gather classes from both __DATA,__objc_clslist 
    // and __DATA,__objc_nlclslist. arclite's hack puts a class in the latter
    // only, and we need to unload that class if we unload an arclite image.

    NXHashTable *classes = NXCreateHashTable(NXPtrPrototype, 0, nil);
    classref_t *classlist;

    classlist = _getObjc2ClassList(hi, &count);
    for (i = 0; i < count; i++) {
        Class cls = remapClass(classlist[i]);
        if (cls) NXHashInsert(classes, cls);
    }

    classlist = _getObjc2NonlazyClassList(hi, &count);
    for (i = 0; i < count; i++) {
        Class cls = remapClass(classlist[i]);
        if (cls) NXHashInsert(classes, cls);
    }

    // First detach classes from each other. Then free each class.
    // This avoid bugs where this loop unloads a subclass before its superclass

    NXHashState hs;
    Class cls;

    hs = NXInitHashState(classes);
    while (NXNextHashState(classes, &hs, (void**)&cls)) {
        remove_class_from_loadable_list(cls);
        detach_class(cls->ISA(), YES);
        detach_class(cls, NO);
    }
    hs = NXInitHashState(classes);
    while (NXNextHashState(classes, &hs, (void**)&cls)) {
        free_class(cls->ISA());
        free_class(cls);
    }

    NXFreeHashTable(classes);
    
    // XXX FIXME -- Clean up protocols:
    // <rdar://problem/9033191> Support unloading protocols at dylib/image unload time

    // fixme DebugUnload
}


/***********************************************************************
* method_getDescription
* Returns a pointer to this method's objc_method_description.
* Locking: none
**********************************************************************/
struct objc_method_description *
method_getDescription(Method m)
{
    if (!m) return nil;
    return (struct objc_method_description *)m;
}


IMP 
method_getImplementation(Method m)
{
    return m ? m->imp : nil;
}


/***********************************************************************
* method_getName
* Returns this method's selector.
* The method must not be nil.
* The method must already have been fixed-up.
* Locking: none
**********************************************************************/
SEL 
method_getName(Method m)
{
    if (!m) return nil;

    assert(m->name == sel_registerName(sel_getName(m->name)));
    return m->name;
}


/***********************************************************************
* method_getTypeEncoding
* Returns this method's old-style type encoding string.
* The method must not be nil.
* Locking: none
**********************************************************************/
const char *
method_getTypeEncoding(Method m)
{
    if (!m) return nil;
    return m->types;
}


/***********************************************************************
* method_setImplementation
* Sets this method's implementation to imp.
* The previous implementation is returned.
**********************************************************************/
static IMP 
_method_setImplementation(Class cls, method_t *m, IMP imp)
{
    runtimeLock.assertLocked();

    if (!m) return nil;
    if (!imp) return nil;

    IMP old = m->imp;
    m->imp = imp;

    // Cache updates are slow if cls is nil (i.e. unknown)
    // RR/AWZ updates are slow if cls is nil (i.e. unknown)
    // fixme build list of classes whose Methods are known externally?

    flushCaches(cls);

    updateCustomRR_AWZ(cls, m);

    return old;
}

IMP 
method_setImplementation(Method m, IMP imp)
{
    // Don't know the class - will be slow if RR/AWZ are affected
    // fixme build list of classes whose Methods are known externally?
    mutex_locker_t lock(runtimeLock);
    return _method_setImplementation(Nil, m, imp);
}


void method_exchangeImplementations(Method m1, Method m2)
{
    if (!m1  ||  !m2) return;

    mutex_locker_t lock(runtimeLock);

    IMP m1_imp = m1->imp;
    m1->imp = m2->imp;
    m2->imp = m1_imp;


    // RR/AWZ updates are slow because class is unknown
    // Cache updates are slow because class is unknown
    // fixme build list of classes whose Methods are known externally?

    flushCaches(nil);

    updateCustomRR_AWZ(nil, m1);
    updateCustomRR_AWZ(nil, m2);
}


/***********************************************************************
* ivar_getOffset
* fixme
* Locking: none
**********************************************************************/
ptrdiff_t
ivar_getOffset(Ivar ivar)
{
    if (!ivar) return 0;
    return *ivar->offset;
}


/***********************************************************************
* ivar_getName
* fixme
* Locking: none
**********************************************************************/
const char *
ivar_getName(Ivar ivar)
{
    if (!ivar) return nil;
    return ivar->name;
}


/***********************************************************************
* ivar_getTypeEncoding
* fixme
* Locking: none
**********************************************************************/
const char *
ivar_getTypeEncoding(Ivar ivar)
{
    if (!ivar) return nil;
    return ivar->type;
}



const char *property_getName(objc_property_t prop)
{
    return prop->name;
}

const char *property_getAttributes(objc_property_t prop)
{
    return prop->attributes;
}

objc_property_attribute_t *property_copyAttributeList(objc_property_t prop, 
                                                      unsigned int *outCount)
{
    if (!prop) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);
    return copyPropertyAttributeList(prop->attributes,outCount);
}

char * property_copyAttributeValue(objc_property_t prop, const char *name)
{
    if (!prop  ||  !name  ||  *name == '\0') return nil;
    
    mutex_locker_t lock(runtimeLock);
    return copyPropertyAttributeValue(prop->attributes, name);
}


/***********************************************************************
* getExtendedTypesIndexesForMethod
* Returns:
* a is the count of methods in all method lists before m's method list
* b is the index of m in m's method list
* a+b is the index of m's extended types in the extended types array
**********************************************************************/
static void getExtendedTypesIndexesForMethod(protocol_t *proto, const method_t *m, bool isRequiredMethod, bool isInstanceMethod, uint32_t& a, uint32_t &b)
{
    a = 0;

    if (proto->instanceMethods) {
        if (isRequiredMethod && isInstanceMethod) {
            b = proto->instanceMethods->indexOfMethod(m);
            return;
        }
        a += proto->instanceMethods->count;
    }

    if (proto->classMethods) {
        if (isRequiredMethod && !isInstanceMethod) {
            b = proto->classMethods->indexOfMethod(m);
            return;
        }
        a += proto->classMethods->count;
    }

    if (proto->optionalInstanceMethods) {
        if (!isRequiredMethod && isInstanceMethod) {
            b = proto->optionalInstanceMethods->indexOfMethod(m);
            return;
        }
        a += proto->optionalInstanceMethods->count;
    }

    if (proto->optionalClassMethods) {
        if (!isRequiredMethod && !isInstanceMethod) {
            b = proto->optionalClassMethods->indexOfMethod(m);
            return;
        }
        a += proto->optionalClassMethods->count;
    }
}


/***********************************************************************
* getExtendedTypesIndexForMethod
* Returns the index of m's extended types in proto's extended types array.
**********************************************************************/
static uint32_t getExtendedTypesIndexForMethod(protocol_t *proto, const method_t *m, bool isRequiredMethod, bool isInstanceMethod)
{
    uint32_t a;
    uint32_t b;
    getExtendedTypesIndexesForMethod(proto, m, isRequiredMethod, 
                                     isInstanceMethod, a, b);
    return a + b;
}


/***********************************************************************
* fixupProtocolMethodList
* Fixes up a single method list in a protocol.
**********************************************************************/
static void
fixupProtocolMethodList(protocol_t *proto, method_list_t *mlist,  
                        bool required, bool instance)
{
    runtimeLock.assertLocked();

    if (!mlist) return;
    if (mlist->isFixedUp()) return;

    const char **extTypes = proto->extendedMethodTypes();
    fixupMethodList(mlist, true/*always copy for simplicity*/,
                    !extTypes/*sort if no extended method types*/);
    
    if (extTypes) {
        // Sort method list and extended method types together.
        // fixupMethodList() can't do this.
        // fixme COW stomp
        uint32_t count = mlist->count;
        uint32_t prefix;
        uint32_t junk;
        getExtendedTypesIndexesForMethod(proto, &mlist->get(0), 
                                         required, instance, prefix, junk);
        for (uint32_t i = 0; i < count; i++) {
            for (uint32_t j = i+1; j < count; j++) {
                method_t& mi = mlist->get(i);
                method_t& mj = mlist->get(j);
                if (mi.name > mj.name) {
                    std::swap(mi, mj);
                    std::swap(extTypes[prefix+i], extTypes[prefix+j]);
                }
            }
        }
    }
}


/***********************************************************************
* fixupProtocol
* Fixes up all of a protocol's method lists.
**********************************************************************/
static void 
fixupProtocol(protocol_t *proto)
{
    runtimeLock.assertLocked();

    if (proto->protocols) {
        for (uintptr_t i = 0; i < proto->protocols->count; i++) {
            protocol_t *sub = remapProtocol(proto->protocols->list[i]);
            if (!sub->isFixedUp()) fixupProtocol(sub);
        }
    }

    fixupProtocolMethodList(proto, proto->instanceMethods, YES, YES);
    fixupProtocolMethodList(proto, proto->classMethods, YES, NO);
    fixupProtocolMethodList(proto, proto->optionalInstanceMethods, NO, YES);
    fixupProtocolMethodList(proto, proto->optionalClassMethods, NO, NO);

    // fixme memory barrier so we can check this with no lock
    proto->setFixedUp();
}


/***********************************************************************
* fixupProtocolIfNeeded
* Fixes up all of a protocol's method lists if they aren't fixed up already.
* Locking: write-locks runtimeLock.
**********************************************************************/
static void 
fixupProtocolIfNeeded(protocol_t *proto)
{
    runtimeLock.assertUnlocked();
    assert(proto);

    if (!proto->isFixedUp()) {
        mutex_locker_t lock(runtimeLock);
        fixupProtocol(proto);
    }
}


static method_list_t *
getProtocolMethodList(protocol_t *proto, bool required, bool instance)
{
    method_list_t **mlistp = nil;
    if (required) {
        if (instance) {
            mlistp = &proto->instanceMethods;
        } else {
            mlistp = &proto->classMethods;
        }
    } else {
        if (instance) {
            mlistp = &proto->optionalInstanceMethods;
        } else {
            mlistp = &proto->optionalClassMethods;
        }
    }

    return *mlistp;
}


/***********************************************************************
* protocol_getMethod_nolock
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static method_t *
protocol_getMethod_nolock(protocol_t *proto, SEL sel, 
                          bool isRequiredMethod, bool isInstanceMethod, 
                          bool recursive)
{
    runtimeLock.assertLocked();

    if (!proto  ||  !sel) return nil;

    assert(proto->isFixedUp());

    method_list_t *mlist = 
        getProtocolMethodList(proto, isRequiredMethod, isInstanceMethod);
    if (mlist) {
        method_t *m = search_method_list(mlist, sel);
        if (m) return m;
    }

    if (recursive  &&  proto->protocols) {
        method_t *m;
        for (uint32_t i = 0; i < proto->protocols->count; i++) {
            protocol_t *realProto = remapProtocol(proto->protocols->list[i]);
            m = protocol_getMethod_nolock(realProto, sel, 
                                          isRequiredMethod, isInstanceMethod, 
                                          true);
            if (m) return m;
        }
    }

    return nil;
}


/***********************************************************************
* protocol_getMethod
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
Method 
protocol_getMethod(protocol_t *proto, SEL sel, bool isRequiredMethod, bool isInstanceMethod, bool recursive)
{
    if (!proto) return nil;
    fixupProtocolIfNeeded(proto);

    mutex_locker_t lock(runtimeLock);
    return protocol_getMethod_nolock(proto, sel, isRequiredMethod, 
                                     isInstanceMethod, recursive);
}


/***********************************************************************
* protocol_getMethodTypeEncoding_nolock
* Return the @encode string for the requested protocol method.
* Returns nil if the compiler did not emit any extended @encode data.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
const char * 
protocol_getMethodTypeEncoding_nolock(protocol_t *proto, SEL sel, 
                                      bool isRequiredMethod, 
                                      bool isInstanceMethod)
{
    runtimeLock.assertLocked();

    if (!proto) return nil;
    if (!proto->extendedMethodTypes()) return nil;

    assert(proto->isFixedUp());

    method_t *m = 
        protocol_getMethod_nolock(proto, sel, 
                                  isRequiredMethod, isInstanceMethod, false);
    if (m) {
        uint32_t i = getExtendedTypesIndexForMethod(proto, m, 
                                                    isRequiredMethod, 
                                                    isInstanceMethod);
        return proto->extendedMethodTypes()[i];
    }

    // No method with that name. Search incorporated protocols.
    if (proto->protocols) {
        for (uintptr_t i = 0; i < proto->protocols->count; i++) {
            const char *enc = 
                protocol_getMethodTypeEncoding_nolock(remapProtocol(proto->protocols->list[i]), sel, isRequiredMethod, isInstanceMethod);
            if (enc) return enc;
        }
    }

    return nil;
}

/***********************************************************************
* _protocol_getMethodTypeEncoding
* Return the @encode string for the requested protocol method.
* Returns nil if the compiler did not emit any extended @encode data.
* Locking: acquires runtimeLock
**********************************************************************/
const char * 
_protocol_getMethodTypeEncoding(Protocol *proto_gen, SEL sel, 
                                BOOL isRequiredMethod, BOOL isInstanceMethod)
{
    protocol_t *proto = newprotocol(proto_gen);

    if (!proto) return nil;
    fixupProtocolIfNeeded(proto);

    mutex_locker_t lock(runtimeLock);
    return protocol_getMethodTypeEncoding_nolock(proto, sel, 
                                                 isRequiredMethod, 
                                                 isInstanceMethod);
}


/***********************************************************************
* protocol_t::demangledName
* Returns the (Swift-demangled) name of the given protocol.
* Locking: none
**********************************************************************/
const char *
protocol_t::demangledName() 
{
    assert(hasDemangledNameField());
    
    if (! _demangledName) {
        char *de = copySwiftV1DemangledName(mangledName, true/*isProtocol*/);
        if (! OSAtomicCompareAndSwapPtrBarrier(nil, (void*)(de ?: mangledName), 
                                               (void**)&_demangledName)) 
        {
            if (de) free(de);
        }
    }
    return _demangledName;
}

/***********************************************************************
* protocol_getName
* Returns the (Swift-demangled) name of the given protocol.
* Locking: runtimeLock must not be held by the caller
**********************************************************************/
const char *
protocol_getName(Protocol *proto)
{
    if (!proto) return "nil";
    else return newprotocol(proto)->demangledName();
}


/***********************************************************************
* protocol_getInstanceMethodDescription
* Returns the description of a named instance method.
* Locking: runtimeLock must not be held by the caller
**********************************************************************/
struct objc_method_description 
protocol_getMethodDescription(Protocol *p, SEL aSel, 
                              BOOL isRequiredMethod, BOOL isInstanceMethod)
{
    Method m = 
        protocol_getMethod(newprotocol(p), aSel, 
                           isRequiredMethod, isInstanceMethod, true);
    if (m) return *method_getDescription(m);
    else return (struct objc_method_description){nil, nil};
}


/***********************************************************************
* protocol_conformsToProtocol_nolock
* Returns YES if self conforms to other.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static bool 
protocol_conformsToProtocol_nolock(protocol_t *self, protocol_t *other)
{
    runtimeLock.assertLocked();

    if (!self  ||  !other) {
        return NO;
    }

    // protocols need not be fixed up

    if (0 == strcmp(self->mangledName, other->mangledName)) {
        return YES;
    }

    if (self->protocols) {
        uintptr_t i;
        for (i = 0; i < self->protocols->count; i++) {
            protocol_t *proto = remapProtocol(self->protocols->list[i]);
            if (0 == strcmp(other->mangledName, proto->mangledName)) {
                return YES;
            }
            if (protocol_conformsToProtocol_nolock(proto, other)) {
                return YES;
            }
        }
    }

    return NO;
}


/***********************************************************************
* protocol_conformsToProtocol
* Returns YES if self conforms to other.
* Locking: acquires runtimeLock
**********************************************************************/
BOOL protocol_conformsToProtocol(Protocol *self, Protocol *other)
{
    mutex_locker_t lock(runtimeLock);
    return protocol_conformsToProtocol_nolock(newprotocol(self), 
                                              newprotocol(other));
}


/***********************************************************************
* protocol_isEqual
* Return YES if two protocols are equal (i.e. conform to each other)
* Locking: acquires runtimeLock
**********************************************************************/
BOOL protocol_isEqual(Protocol *self, Protocol *other)
{
    if (self == other) return YES;
    if (!self  ||  !other) return NO;

    if (!protocol_conformsToProtocol(self, other)) return NO;
    if (!protocol_conformsToProtocol(other, self)) return NO;

    return YES;
}


/***********************************************************************
* protocol_copyMethodDescriptionList
* Returns descriptions of a protocol's methods.
* Locking: acquires runtimeLock
**********************************************************************/
struct objc_method_description *
protocol_copyMethodDescriptionList(Protocol *p, 
                                   BOOL isRequiredMethod,BOOL isInstanceMethod,
                                   unsigned int *outCount)
{
    protocol_t *proto = newprotocol(p);
    struct objc_method_description *result = nil;
    unsigned int count = 0;

    if (!proto) {
        if (outCount) *outCount = 0;
        return nil;
    }

    fixupProtocolIfNeeded(proto);

    mutex_locker_t lock(runtimeLock);

    method_list_t *mlist = 
        getProtocolMethodList(proto, isRequiredMethod, isInstanceMethod);

    if (mlist) {
        result = (struct objc_method_description *)
            calloc(mlist->count + 1, sizeof(struct objc_method_description));
        for (const auto& meth : *mlist) {
            result[count].name = meth.name;
            result[count].types = (char *)meth.types;
            count++;
        }
    }

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* protocol_getProperty
* fixme
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static property_t * 
protocol_getProperty_nolock(protocol_t *proto, const char *name, 
                            bool isRequiredProperty, bool isInstanceProperty)
{
    runtimeLock.assertLocked();

    if (!isRequiredProperty) {
        // Only required properties are currently supported.
        return nil;
    }

    property_list_t *plist = isInstanceProperty ? 
        proto->instanceProperties : proto->classProperties();
    if (plist) {
        for (auto& prop : *plist) {
            if (0 == strcmp(name, prop.name)) {
                return &prop;
            }
        }
    }

    if (proto->protocols) {
        uintptr_t i;
        for (i = 0; i < proto->protocols->count; i++) {
            protocol_t *p = remapProtocol(proto->protocols->list[i]);
            property_t *prop = 
                protocol_getProperty_nolock(p, name, 
                                            isRequiredProperty, 
                                            isInstanceProperty);
            if (prop) return prop;
        }
    }

    return nil;
}

objc_property_t protocol_getProperty(Protocol *p, const char *name, 
                              BOOL isRequiredProperty, BOOL isInstanceProperty)
{
    if (!p  ||  !name) return nil;

    mutex_locker_t lock(runtimeLock);
    return (objc_property_t)
        protocol_getProperty_nolock(newprotocol(p), name, 
                                    isRequiredProperty, isInstanceProperty);
}


/***********************************************************************
* protocol_copyPropertyList
* protocol_copyPropertyList2
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
static property_t **
copyPropertyList(property_list_t *plist, unsigned int *outCount)
{
    property_t **result = nil;
    unsigned int count = 0;

    if (plist) {
        count = plist->count;
    }

    if (count > 0) {
        result = (property_t **)malloc((count+1) * sizeof(property_t *));

        count = 0;
        for (auto& prop : *plist) {
            result[count++] = &prop;
        }
        result[count] = nil;
    }

    if (outCount) *outCount = count;
    return result;
}

objc_property_t *
protocol_copyPropertyList2(Protocol *proto, unsigned int *outCount, 
                           BOOL isRequiredProperty, BOOL isInstanceProperty)
{
    if (!proto  ||  !isRequiredProperty) {
        // Optional properties are not currently supported.
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    property_list_t *plist = isInstanceProperty
        ? newprotocol(proto)->instanceProperties
        : newprotocol(proto)->classProperties();
    return (objc_property_t *)copyPropertyList(plist, outCount);
}

objc_property_t *
protocol_copyPropertyList(Protocol *proto, unsigned int *outCount)
{
    return protocol_copyPropertyList2(proto, outCount, 
                                      YES/*required*/, YES/*instance*/);
}


/***********************************************************************
* protocol_copyProtocolList
* Copies this protocol's incorporated protocols. 
* Does not copy those protocol's incorporated protocols in turn.
* Locking: acquires runtimeLock
**********************************************************************/
Protocol * __unsafe_unretained * 
protocol_copyProtocolList(Protocol *p, unsigned int *outCount)
{
    unsigned int count = 0;
    Protocol **result = nil;
    protocol_t *proto = newprotocol(p);
    
    if (!proto) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    if (proto->protocols) {
        count = (unsigned int)proto->protocols->count;
    }
    if (count > 0) {
        result = (Protocol **)malloc((count+1) * sizeof(Protocol *));

        unsigned int i;
        for (i = 0; i < count; i++) {
            result[i] = (Protocol *)remapProtocol(proto->protocols->list[i]);
        }
        result[i] = nil;
    }

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* objc_allocateProtocol
* Creates a new protocol. The protocol may not be used until 
* objc_registerProtocol() is called.
* Returns nil if a protocol with the same name already exists.
* Locking: acquires runtimeLock
**********************************************************************/
Protocol *
objc_allocateProtocol(const char *name)
{
    mutex_locker_t lock(runtimeLock);

    if (getProtocol(name)) {
        return nil;
    }

    protocol_t *result = (protocol_t *)calloc(sizeof(protocol_t), 1);

    extern objc_class OBJC_CLASS_$___IncompleteProtocol;
    Class cls = (Class)&OBJC_CLASS_$___IncompleteProtocol;
    result->initProtocolIsa(cls);
    result->size = sizeof(protocol_t);
    // fixme mangle the name if it looks swift-y?
    result->mangledName = strdupIfMutable(name);

    // fixme reserve name without installing

    return (Protocol *)result;
}


/***********************************************************************
* objc_registerProtocol
* Registers a newly-constructed protocol. The protocol is now 
* ready for use and immutable.
* Locking: acquires runtimeLock
**********************************************************************/
void objc_registerProtocol(Protocol *proto_gen) 
{
    protocol_t *proto = newprotocol(proto_gen);

    mutex_locker_t lock(runtimeLock);

    extern objc_class OBJC_CLASS_$___IncompleteProtocol;
    Class oldcls = (Class)&OBJC_CLASS_$___IncompleteProtocol;
    extern objc_class OBJC_CLASS_$_Protocol;
    Class cls = (Class)&OBJC_CLASS_$_Protocol;

    if (proto->ISA() == cls) {
        _objc_inform("objc_registerProtocol: protocol '%s' was already "
                     "registered!", proto->nameForLogging());
        return;
    }
    if (proto->ISA() != oldcls) {
        _objc_inform("objc_registerProtocol: protocol '%s' was not allocated "
                     "with objc_allocateProtocol!", proto->nameForLogging());
        return;
    }

    // NOT initProtocolIsa(). The protocol object may already 
    // have been retained and we must preserve that count.
    proto->changeIsa(cls);

    NXMapKeyCopyingInsert(protocols(), proto->mangledName, proto);
}


/***********************************************************************
* protocol_addProtocol
* Adds an incorporated protocol to another protocol.
* No method enforcement is performed.
* `proto` must be under construction. `addition` must not.
* Locking: acquires runtimeLock
**********************************************************************/
void 
protocol_addProtocol(Protocol *proto_gen, Protocol *addition_gen) 
{
    protocol_t *proto = newprotocol(proto_gen);
    protocol_t *addition = newprotocol(addition_gen);

    extern objc_class OBJC_CLASS_$___IncompleteProtocol;
    Class cls = (Class)&OBJC_CLASS_$___IncompleteProtocol;

    if (!proto_gen) return;
    if (!addition_gen) return;

    mutex_locker_t lock(runtimeLock);

    if (proto->ISA() != cls) {
        _objc_inform("protocol_addProtocol: modified protocol '%s' is not "
                     "under construction!", proto->nameForLogging());
        return;
    }
    if (addition->ISA() == cls) {
        _objc_inform("protocol_addProtocol: added protocol '%s' is still "
                     "under construction!", addition->nameForLogging());
        return;        
    }
    
    protocol_list_t *protolist = proto->protocols;
    if (!protolist) {
        protolist = (protocol_list_t *)
            calloc(1, sizeof(protocol_list_t) 
                             + sizeof(protolist->list[0]));
    } else {
        protolist = (protocol_list_t *)
            realloc(protolist, protocol_list_size(protolist) 
                              + sizeof(protolist->list[0]));
    }

    protolist->list[protolist->count++] = (protocol_ref_t)addition;
    proto->protocols = protolist;
}


/***********************************************************************
* protocol_addMethodDescription
* Adds a method to a protocol. The protocol must be under construction.
* Locking: acquires runtimeLock
**********************************************************************/
static void
protocol_addMethod_nolock(method_list_t*& list, SEL name, const char *types)
{
    if (!list) {
        list = (method_list_t *)calloc(sizeof(method_list_t), 1);
        list->entsizeAndFlags = sizeof(list->first);
        list->setFixedUp();
    } else {
        size_t size = list->byteSize() + list->entsize();
        list = (method_list_t *)realloc(list, size);
    }

    method_t& meth = list->get(list->count++);
    meth.name = name;
    meth.types = types ? strdupIfMutable(types) : "";
    meth.imp = nil;
}

void 
protocol_addMethodDescription(Protocol *proto_gen, SEL name, const char *types,
                              BOOL isRequiredMethod, BOOL isInstanceMethod) 
{
    protocol_t *proto = newprotocol(proto_gen);

    extern objc_class OBJC_CLASS_$___IncompleteProtocol;
    Class cls = (Class)&OBJC_CLASS_$___IncompleteProtocol;

    if (!proto_gen) return;

    mutex_locker_t lock(runtimeLock);

    if (proto->ISA() != cls) {
        _objc_inform("protocol_addMethodDescription: protocol '%s' is not "
                     "under construction!", proto->nameForLogging());
        return;
    }

    if (isRequiredMethod  &&  isInstanceMethod) {
        protocol_addMethod_nolock(proto->instanceMethods, name, types);
    } else if (isRequiredMethod  &&  !isInstanceMethod) {
        protocol_addMethod_nolock(proto->classMethods, name, types);
    } else if (!isRequiredMethod  &&  isInstanceMethod) {
        protocol_addMethod_nolock(proto->optionalInstanceMethods, name,types);
    } else /*  !isRequiredMethod  &&  !isInstanceMethod) */ {
        protocol_addMethod_nolock(proto->optionalClassMethods, name, types);
    }
}


/***********************************************************************
* protocol_addProperty
* Adds a property to a protocol. The protocol must be under construction.
* Locking: acquires runtimeLock
**********************************************************************/
static void 
protocol_addProperty_nolock(property_list_t *&plist, const char *name, 
                            const objc_property_attribute_t *attrs, 
                            unsigned int count)
{
    if (!plist) {
        plist = (property_list_t *)calloc(sizeof(property_list_t), 1);
        plist->entsizeAndFlags = sizeof(property_t);
    } else {
        plist = (property_list_t *)
            realloc(plist, sizeof(property_list_t) 
                    + plist->count * plist->entsize());
    }

    property_t& prop = plist->get(plist->count++);
    prop.name = strdupIfMutable(name);
    prop.attributes = copyPropertyAttributeString(attrs, count);
}

void 
protocol_addProperty(Protocol *proto_gen, const char *name, 
                     const objc_property_attribute_t *attrs, 
                     unsigned int count,
                     BOOL isRequiredProperty, BOOL isInstanceProperty)
{
    protocol_t *proto = newprotocol(proto_gen);

    extern objc_class OBJC_CLASS_$___IncompleteProtocol;
    Class cls = (Class)&OBJC_CLASS_$___IncompleteProtocol;

    if (!proto) return;
    if (!name) return;

    mutex_locker_t lock(runtimeLock);

    if (proto->ISA() != cls) {
        _objc_inform("protocol_addProperty: protocol '%s' is not "
                     "under construction!", proto->nameForLogging());
        return;
    }

    if (isRequiredProperty  &&  isInstanceProperty) {
        protocol_addProperty_nolock(proto->instanceProperties, name, attrs, count);
    }
    else if (isRequiredProperty  &&  !isInstanceProperty) {
        protocol_addProperty_nolock(proto->_classProperties, name, attrs, count);
    }
    //else if (!isRequiredProperty  &&  isInstanceProperty) {
    //    protocol_addProperty_nolock(proto->optionalInstanceProperties, name, attrs, count);
    //}
    //else /*  !isRequiredProperty  &&  !isInstanceProperty) */ {
    //    protocol_addProperty_nolock(proto->optionalClassProperties, name, attrs, count);
    //}
}


/***********************************************************************
* objc_getClassList
* Returns pointers to all classes.
* This requires all classes be realized, which is regretfully non-lazy.
* Locking: acquires runtimeLock
**********************************************************************/
int 
objc_getClassList(Class *buffer, int bufferLen) 
{
    mutex_locker_t lock(runtimeLock);

    realizeAllClasses();

    __block int count = 0;
    foreach_realized_class_and_metaclass(^(Class cls) { 
        if (!cls->isMetaClass()) count++; 
    });

    if (buffer) {
        __block int c = 0;
        foreach_realized_class_and_metaclass(^(Class cls) { 
            if (c < bufferLen && !cls->isMetaClass()) {
                buffer[c++] = cls; 
            }
        });
    }

    return count;
}


/***********************************************************************
* objc_copyClassList
* Returns pointers to all classes.
* This requires all classes be realized, which is regretfully non-lazy.
* 
* outCount may be nil. *outCount is the number of classes returned. 
* If the returned array is not nil, it is nil-terminated and must be 
* freed with free().
* Locking: write-locks runtimeLock
**********************************************************************/
Class *
objc_copyClassList(unsigned int *outCount)
{
    mutex_locker_t lock(runtimeLock);

    realizeAllClasses();

    Class *result = nil;

    __block unsigned int count = 0;
    foreach_realized_class_and_metaclass(^(Class cls) {
        if (!cls->isMetaClass()) count++; 
    });

    if (count > 0) {
        result = (Class *)malloc((1+count) * sizeof(Class));
        __block unsigned int c = 0;
        foreach_realized_class_and_metaclass(^(Class cls) {
            if (!cls->isMetaClass()) {
                result[c++] = cls;
            }
        });
        result[c] = nil;
    }

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* objc_copyProtocolList
* Returns pointers to all protocols.
* Locking: read-locks runtimeLock
**********************************************************************/
Protocol * __unsafe_unretained * 
objc_copyProtocolList(unsigned int *outCount) 
{
    mutex_locker_t lock(runtimeLock);

    NXMapTable *protocol_map = protocols();

    unsigned int count = NXCountMapTable(protocol_map);
    if (count == 0) {
        if (outCount) *outCount = 0;
        return nil;
    }

    Protocol **result = (Protocol **)malloc((count+1) * sizeof(Protocol*));

    unsigned int i = 0;
    Protocol *proto;
    const char *name;
    NXMapState state = NXInitMapState(protocol_map);
    while (NXNextMapState(protocol_map, &state, 
                          (const void **)&name, (const void **)&proto))
    {
        result[i++] = proto;
    }
    
    result[i++] = nil;
    assert(i == count+1);

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* objc_getProtocol
* Get a protocol by name, or return nil
* Locking: read-locks runtimeLock
**********************************************************************/
Protocol *objc_getProtocol(const char *name)
{
    mutex_locker_t lock(runtimeLock); 
    return getProtocol(name);
}


/***********************************************************************
* class_copyMethodList
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
Method *
class_copyMethodList(Class cls, unsigned int *outCount)
{
    unsigned int count = 0;
    Method *result = nil;

    if (!cls) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);
    
    assert(cls->isRealized());

    count = cls->data()->methods.count();

    if (count > 0) {
        result = (Method *)malloc((count + 1) * sizeof(Method));
        
        count = 0;
        for (auto& meth : cls->data()->methods) {
            result[count++] = &meth;
        }
        result[count] = nil;
    }

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* class_copyIvarList
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
Ivar *
class_copyIvarList(Class cls, unsigned int *outCount)
{
    const ivar_list_t *ivars;
    Ivar *result = nil;
    unsigned int count = 0;

    if (!cls) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    assert(cls->isRealized());
    
    if ((ivars = cls->data()->ro->ivars)  &&  ivars->count) {
        result = (Ivar *)malloc((ivars->count+1) * sizeof(Ivar));
        /*
         对于一个有范围的集合而言，由程序员来说明循环的范围是多余的，有时候还会容易犯错误。因此C++11中引入了基于范围的for循环。
         for循环后的括号由冒号“ :”分为两部分:第一部分是范围内用于迭代的变量，第二部分则表示被迭代的范围。
         */
        for (auto& ivar : *ivars) {
            if (!ivar.offset) continue;  // anonymous bitfield
            result[count++] = &ivar;
        }
        result[count] = nil;
    }
    
    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* class_copyPropertyList. Returns a heap block containing the 
* properties declared in the class, or nil if the class 
* declares no properties. Caller must free the block.
* Does not copy any superclass's properties.
* Locking: read-locks runtimeLock
**********************************************************************/
objc_property_t *
class_copyPropertyList(Class cls, unsigned int *outCount)
{
    if (!cls) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);
    assert(cls->isRealized());
    
    auto rw = cls->data();

    property_t **result = nil;
    unsigned int count = rw->properties.count();
    if (count > 0) {
        result = (property_t **)malloc((count + 1) * sizeof(property_t *));

        count = 0;
        for (auto& prop : rw->properties) {
            result[count++] = &prop;
        }
        result[count] = nil;
    }

    if (outCount) *outCount = count;
    return (objc_property_t *)result;
}


/***********************************************************************
* objc_class::getLoadMethod
* fixme
* Called only from add_class_to_loadable_list.
* Locking: runtimeLock must be read- or write-locked by the caller.
**********************************************************************/
IMP 
objc_class::getLoadMethod()
{
    runtimeLock.assertLocked();

    const method_list_t *mlist;

    assert(isRealized());
    assert(ISA()->isRealized());
    assert(!isMetaClass());
    assert(ISA()->isMetaClass());

    mlist = ISA()->data()->ro->baseMethods();
    if (mlist) {
        for (const auto& meth : *mlist) {
            const char *name = sel_cname(meth.name);
            if (0 == strcmp(name, "load")) {
                return meth.imp;
            }
        }
    }

    return nil;
}


/***********************************************************************
* _category_getName
* Returns a category's name.
* Locking: none
**********************************************************************/
const char *
_category_getName(Category cat)
{
    return cat->name;
}


/***********************************************************************
* _category_getClassName
* Returns a category's class's name
* Called only from add_category_to_loadable_list and 
* remove_category_from_loadable_list for logging purposes.
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
const char *
_category_getClassName(Category cat)
{
    runtimeLock.assertLocked();
    return remapClass(cat->cls)->nameForLogging();
}


/***********************************************************************
* _category_getClass
* Returns a category's class
* Called only by call_category_loads.
* Locking: read-locks runtimeLock
**********************************************************************/
Class 
_category_getClass(Category cat)
{
    mutex_locker_t lock(runtimeLock);
    Class result = remapClass(cat->cls);
    assert(result->isRealized());  // ok for call_category_loads' usage
    return result;
}


/***********************************************************************
* _category_getLoadMethod
* fixme
* Called only from add_category_to_loadable_list
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
IMP 
_category_getLoadMethod(Category cat)
{
    runtimeLock.assertLocked();

    const method_list_t *mlist;

    mlist = cat->classMethods;
    if (mlist) {
        for (const auto& meth : *mlist) {
            const char *name = sel_cname(meth.name);
            if (0 == strcmp(name, "load")) {
                return meth.imp;
            }
        }
    }

    return nil;
}


/***********************************************************************
* category_t::propertiesForMeta
* Return a category's instance or class properties.
* hi is the image containing the category.
**********************************************************************/
property_list_t *
category_t::propertiesForMeta(bool isMeta, struct header_info *hi)
{
    if (!isMeta) return instanceProperties;
    else if (hi->info()->hasCategoryClassProperties()) return _classProperties;
    else return nil;
}


/***********************************************************************
* class_copyProtocolList
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
Protocol * __unsafe_unretained * 
class_copyProtocolList(Class cls, unsigned int *outCount)
{
    unsigned int count = 0;
    Protocol **result = nil;
    
    if (!cls) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);

    assert(cls->isRealized());
    
    count = cls->data()->protocols.count();

    if (count > 0) {
        result = (Protocol **)malloc((count+1) * sizeof(Protocol *));

        count = 0;
        for (const auto& proto : cls->data()->protocols) {
            result[count++] = (Protocol *)remapProtocol(proto);
        }
        result[count] = nil;
    }

    if (outCount) *outCount = count;
    return result;
}


/***********************************************************************
* objc_copyImageNames
* Copies names of loaded images with ObjC contents.
*
* Locking: acquires runtimeLock
**********************************************************************/
const char **objc_copyImageNames(unsigned int *outCount)
{
    mutex_locker_t lock(runtimeLock);
    
#if TARGET_OS_WIN32
    const TCHAR **names = (const TCHAR **)
        malloc((HeaderCount+1) * sizeof(TCHAR *));
#else
    const char **names = (const char **)
        malloc((HeaderCount+1) * sizeof(char *));
#endif

    unsigned int count = 0;
    for (header_info *hi = FirstHeader; hi != nil; hi = hi->getNext()) {
#if TARGET_OS_WIN32
        if (hi->moduleName) {
            names[count++] = hi->moduleName;
        }
#else
        const char *fname = hi->fname();
        if (fname) {
            names[count++] = fname;
        }
#endif
    }
    names[count] = nil;
    
    if (count == 0) {
        // Return nil instead of empty list if there are no images
        free((void *)names);
        names = nil;
    }

    if (outCount) *outCount = count;
    return names;
}


/***********************************************************************
* copyClassNamesForImage_nolock
* Copies class names from the given image.
* Missing weak-import classes are omitted.
* Swift class names are demangled.
*
* Locking: runtimeLock must be held by the caller
**********************************************************************/
const char **
copyClassNamesForImage_nolock(header_info *hi, unsigned int *outCount)
{
    runtimeLock.assertLocked();
    assert(hi);

    size_t count;
    classref_t *classlist = _getObjc2ClassList(hi, &count);
    const char **names = (const char **)
        malloc((count+1) * sizeof(const char *));

    size_t shift = 0;
    for (size_t i = 0; i < count; i++) {
        Class cls = remapClass(classlist[i]);
        if (cls) {
            names[i-shift] = cls->demangledName(true/*realize*/);
        } else {
            shift++;  // ignored weak-linked class
        }
    }
    count -= shift;
    names[count] = nil;

    if (outCount) *outCount = (unsigned int)count;
    return names;
}



/***********************************************************************
* objc_copyClassNamesForImage
* Copies class names from the named image.
* The image name must be identical to dladdr's dli_fname value.
* Missing weak-import classes are omitted.
* Swift class names are demangled.
*
* Locking: acquires runtimeLock
**********************************************************************/
const char **
objc_copyClassNamesForImage(const char *image, unsigned int *outCount)
{
    if (!image) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    // Find the image.
    header_info *hi;
    for (hi = FirstHeader; hi != nil; hi = hi->getNext()) {
#if TARGET_OS_WIN32
        if (0 == wcscmp((TCHAR *)image, hi->moduleName)) break;
#else
        if (0 == strcmp(image, hi->fname())) break;
#endif
    }

    if (!hi) {
        if (outCount) *outCount = 0;
        return nil;
    }

    return copyClassNamesForImage_nolock(hi, outCount);
}


/***********************************************************************
* objc_copyClassNamesForImageHeader
* Copies class names from the given image.
* Missing weak-import classes are omitted.
* Swift class names are demangled.
*
* Locking: acquires runtimeLock
**********************************************************************/
const char **
objc_copyClassNamesForImageHeader(const struct mach_header *mh, unsigned int *outCount)
{
    if (!mh) {
        if (outCount) *outCount = 0;
        return nil;
    }

    mutex_locker_t lock(runtimeLock);

    // Find the image.
    header_info *hi;
    for (hi = FirstHeader; hi != nil; hi = hi->getNext()) {
        if (hi->mhdr() == (const headerType *)mh) break;
    }

    if (!hi) {
        if (outCount) *outCount = 0;
        return nil;
    }

    return copyClassNamesForImage_nolock(hi, outCount);
}


/***********************************************************************
* saveTemporaryString
* Save a string in a thread-local FIFO buffer. 
* This is suitable for temporary strings generated for logging purposes.
**********************************************************************/
static void
saveTemporaryString(char *str)
{
    // Fixed-size FIFO. We free the first string, shift 
    // the rest, and add the new string to the end.
    _objc_pthread_data *data = _objc_fetch_pthread_data(true);
    if (data->printableNames[0]) {
        free(data->printableNames[0]);
    }
    int last = countof(data->printableNames) - 1;
    for (int i = 0; i < last; i++) {
        data->printableNames[i] = data->printableNames[i+1];
    }
    data->printableNames[last] = str;
}


/***********************************************************************
* objc_class::nameForLogging
* Returns the class's name, suitable for display.
* The returned memory is TEMPORARY. Print it or copy it immediately.
* Locking: none
**********************************************************************/
const char *
objc_class::nameForLogging()
{
    // Handle the easy case directly.
    if (isRealized()  ||  isFuture()) {
        if (data()->demangledName) return data()->demangledName;
    }

    char *result;

    const char *name = mangledName();
    char *de = copySwiftV1DemangledName(name);
    if (de) result = de;
    else result = strdup(name);

    saveTemporaryString(result);
    return result;
}


/***********************************************************************
* objc_class::demangledName
* If realize=false, the class must already be realized or future.
* Locking: If realize=true, runtimeLock must be held by the caller.
**********************************************************************/
mutex_t DemangleCacheLock;
static NXHashTable *DemangleCache;

/*
 mangle [ˈmæŋɡl] v. 压碎，撕烂；严重损坏；使变形
 demangled: 符号重组(demangle) 动态链接(Dynamic link) ...
 https://www.mikeash.com/pyblog/friday-qa-2014-08-15-swift-name-mangling.html
 理解思路：
     int foo(int a) {
        return a * 2;
     }
     int foo(double a) {
        return a * 2.0;
     }
     int main() {
        return foo(1) + foo(1.0);
     }
 
    C++，Swift中相同类中存在相同名字的方法（重载：相同作用域中存在函数名字相同，但参数不同的多个方法,或者参数个数不同）
    it is impossible to simply generate two _foo symbols; the linker would not know which was which.
    As a result, the C++ compiler "mangles" the symbols, using a strict set of encoding rules.
 */

const char *objc_class::demangledName(bool realize)
{
    // Return previously demangled name if available.
    if (isRealized()  ||  isFuture()) {
        if (data()->demangledName) return data()->demangledName;
    }

    // Try demangling the mangled name.
    const char *mangled = mangledName();
    char *de = copySwiftV1DemangledName(mangled);
    if (isRealized()  ||  isFuture()) {
        // Class is already realized or future. 
        // Save demangling result in rw data.
        // We may not own runtimeLock so use an atomic operation instead.
        if (! OSAtomicCompareAndSwapPtrBarrier(nil, (void*)(de ?: mangled), 
                                               (void**)&data()->demangledName)) 
        {
            if (de) free(de);
        }
        return data()->demangledName;
    }

    // Class is not yet realized.
    if (!de) {
        // Name is not mangled. Return it without caching.
        return mangled;
    }

    // Class is not yet realized and name is mangled. Realize the class.
    // Only objc_copyClassNamesForImage() should get here.
    
    // fixme lldb's calls to class_getName() can also get here when
    // interrogating the dyld shared cache. (rdar://27258517)
    // fixme runtimeLock.assertLocked();
    // fixme assert(realize);
    
    if (realize) {
        runtimeLock.assertLocked();
        realizeClass((Class)this);
        data()->demangledName = de;
        return de;
    }
    else {
        // Save the string to avoid leaks.
        char *cached;
        {
            mutex_locker_t lock(DemangleCacheLock);
            if (!DemangleCache) {
                DemangleCache = NXCreateHashTable(NXStrPrototype, 0, nil);
            }
            cached = (char *)NXHashInsertIfAbsent(DemangleCache, de);
        }
        if (cached != de) free(de);
        return cached;
    }
}


/***********************************************************************
* class_getName
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
const char *class_getName(Class cls)
{
    if (!cls) return "nil";
    // fixme lldb calls class_getName() on unrealized classes (rdar://27258517)
    // assert(cls->isRealized()  ||  cls->isFuture());
    return cls->demangledName();
}


/***********************************************************************
* class_getVersion
* fixme
* Locking: none
**********************************************************************/
int 
class_getVersion(Class cls)
{
    if (!cls) return 0;
    assert(cls->isRealized());
    return cls->data()->version;
}


/***********************************************************************
* class_setVersion
* fixme
* Locking: none
**********************************************************************/
void 
class_setVersion(Class cls, int version)
{
    if (!cls) return;
    assert(cls->isRealized());
    cls->data()->version = version;
}


static method_t *findMethodInSortedMethodList(SEL key, const method_list_t *list)
{
    assert(list);

    const method_t * const first = &list->first;
    const method_t *base = first;
    const method_t *probe;
    uintptr_t keyValue = (uintptr_t)key;
    uint32_t count;
    
    for (count = list->count; count != 0; count >>= 1) {
        probe = base + (count >> 1);
        
        uintptr_t probeValue = (uintptr_t)probe->name;
        
        if (keyValue == probeValue) {
            // `probe` is a match.
            // Rewind looking for the *first* occurrence of this value.
            // This is required for correct category overrides.
            while (probe > first && keyValue == (uintptr_t)probe[-1].name) {
                probe--;
            }
            return (method_t *)probe;
        }
        
        if (keyValue > probeValue) {
            base = probe + 1;
            count--;
        }
    }
    
    return nil;
}

/***********************************************************************
* getMethodNoSuper_nolock
* fixme
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static method_t *search_method_list(const method_list_t *mlist, SEL sel)
{
    int methodListIsFixedUp = mlist->isFixedUp();
    int methodListHasExpectedSize = mlist->entsize() == sizeof(method_t);
    
    if (__builtin_expect(methodListIsFixedUp && methodListHasExpectedSize, 1)) {
        return findMethodInSortedMethodList(sel, mlist);
    } else {
        // Linear search of unsorted method list
        for (auto& meth : *mlist) {
            if (meth.name == sel) return &meth;
        }
    }

#if DEBUG
    // sanity-check negative results
    if (mlist->isFixedUp()) {
        for (auto& meth : *mlist) {
            if (meth.name == sel) {
                _objc_fatal("linear search worked when binary search did not");
            }
        }
    }
#endif

    return nil;
}

static method_t *
getMethodNoSuper_nolock(Class cls, SEL sel)
{
    runtimeLock.assertLocked();

    assert(cls->isRealized());
    // fixme nil cls? 
    // fixme nil sel?

    /*
     struct objc_class : objc_object {
         // Class ISA;
         Class superclass;
         cache_t cache;             // formerly cache pointer and vtable
         class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
         class_rw_t *data() {
             return bits.data();
         }
     }
     struct class_rw_t {
         const class_ro_t *ro;
         //类realize后(realizeClass()执行后)，所有的实例方法都放在该变量中，包括分类中定义的
         method_array_t methods;
         property_array_t properties;
         protocol_array_t protocols;
     }
     */
    for (auto mlists = cls->data()->methods.beginLists(), 
              end = cls->data()->methods.endLists(); 
         mlists != end;
         ++mlists)
    {
        method_t *m = search_method_list(*mlists, sel);
        if (m) return m;
    }

    return nil;
}


/***********************************************************************
* getMethod_nolock
* fixme
* Locking: runtimeLock must be read- or write-locked by the caller
**********************************************************************/
static method_t *
getMethod_nolock(Class cls, SEL sel)
{
    method_t *m = nil;

    runtimeLock.assertLocked();

    // fixme nil cls?
    // fixme nil sel?

    assert(cls->isRealized());

    while (cls  &&  ((m = getMethodNoSuper_nolock(cls, sel))) == nil) {
        cls = cls->superclass;
    }

    return m;
}


/***********************************************************************
* _class_getMethod
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
static Method _class_getMethod(Class cls, SEL sel)
{
    mutex_locker_t lock(runtimeLock);
    return getMethod_nolock(cls, sel);
}


/***********************************************************************
* class_getInstanceMethod.  Return the instance method for the
* specified class and selector.
**********************************************************************/
Method class_getInstanceMethod(Class cls, SEL sel)
{
    if (!cls  ||  !sel) return nil;

    // This deliberately avoids +initialize because it historically did so.

    // This implementation is a bit weird because it's the only place that 
    // wants a Method instead of an IMP.

#warning fixme build and search caches
        
    // Search method lists, try method resolver, etc.
    //这有可能会在父类方法列表中查找，找到会放到缓存中
    lookUpImpOrNil(cls, sel, nil, 
                   NO/*initialize*/, NO/*cache*/, YES/*resolver*/);

#warning fixme build and search caches

    //这有可能会在父类方法列表中查找，找到会放到缓存中
    return _class_getMethod(cls, sel);
}


/***********************************************************************
* log_and_fill_cache
* Log this method call. If the logger permits it, fill the method cache.
* cls is the method whose cache should be filled. 
* implementer is the class that owns the implementation in question.
**********************************************************************/
static void
log_and_fill_cache(Class cls, IMP imp, SEL sel, id receiver, Class implementer)
{
#if SUPPORT_MESSAGE_LOGGING
    if (objcMsgLogEnabled) {
        bool cacheIt = logMessageSend(implementer->isMetaClass(), 
                                      cls->nameForLogging(),
                                      implementer->nameForLogging(), 
                                      sel);
        if (!cacheIt) return;
    }
#endif
    cache_fill (cls, sel, imp, receiver);
}


/***********************************************************************
* _class_lookupMethodAndLoadCache.
* Method lookup for dispatchers ONLY. OTHER CODE SHOULD USE lookUpImp().
* This lookup avoids optimistic cache scan because the dispatcher 
* already tried that.
**********************************************************************/
IMP _class_lookupMethodAndLoadCache3(id obj, SEL sel, Class cls)/*当objc_msgSend(id self, SEL _cmd, ...)中的self是实例对象时cls 为
                                                                 类对象，当self是类对象时cls 为元类对象
                                                                 */
{
    return lookUpImpOrForward(cls, sel, obj, 
                              YES/*initialize*/, NO/*cache*/, YES/*resolver*/);
}


/***********************************************************************
* lookUpImpOrForward.
* The standard IMP lookup. 
* initialize==NO tries to avoid +initialize (but sometimes fails)
* cache==NO skips optimistic unlocked lookup (but uses cache elsewhere)
* Most callers should use initialize==YES and cache==YES.
* inst is an instance of cls or a subclass thereof, or nil if none is known. 
*   If cls is an un-initialized metaclass then a non-nil inst is faster.
* May return _objc_msgForward_impcache. IMPs destined for external use 
*   must be converted to _objc_msgForward or _objc_msgForward_stret.
*   If you don't want forwarding at all, use lookUpImpOrNil() instead.
**********************************************************************/
IMP lookUpImpOrForward(Class cls, SEL sel, id inst, 
                       bool initialize, bool cache, bool resolver)
{
    /*
     1. 从当前类的缓存中查找，找到则返回
     2. 当前类的缓存没有，则去当前类的方法列表中查找，找到缓存并返回
        
        当前类的方法列表在class_rw_t->methods中
     
     3. 当前类的方法列表中没有找到则遍历整条继承链中父类的缓存查找，找到将其缓存到当前类并返回
     4. 父类的缓存没有则去父类的方法列表中查找，找到将其缓存到当前类并返回
     5. 如果遍历完整条继承链的缓存以及方法列表都没找到，则进行动态方法决议，检查有没有resolveInstanceMethod，或者resolveClassMethod,有则执行
     6. 进行动态方法决议后再重新从缓存开始的地方再跑一遍，再跑一遍也没找到方法imp，则进行消息转发
     7. 消息转发失败则崩溃
         消息转发流程
         1. 调用forwardingTargetForSelector返回响应该消息的对象，
         2. 如果forwardingTargetForSelector 返回nil 则调用methodSignatureForSelector返回NSMethodSignature
         3. 如果methodSignatureForSelector 返回nil,则调用doesNotRecognizeSelector 触发异常
     
     */
    
    IMP imp = nil;
    bool triedResolver = NO;

    runtimeLock.assertUnlocked();

    // Optimistic cache lookup
    if (cache) {
        //cache_getImp()汇编实现，在objc-msg-arm.s 中
        imp = cache_getImp(cls, sel);
        if (imp) return imp;
    }

    // runtimeLock is held during isRealized and isInitialized checking
    // to prevent races against concurrent realization.

    // runtimeLock is held during method search to make
    // method-lookup + cache-fill atomic with respect to method addition.
    // Otherwise, a category could be added but ignored indefinitely because
    // the cache was re-filled with the old value after the cache flush on
    // behalf of the category.

    runtimeLock.lock();
    checkIsKnownClass(cls);

    if (!cls->isRealized()) {
        realizeClass(cls);
    }

    //调用initialize 方法
    if (initialize  &&  !cls->isInitialized()) {
        runtimeLock.unlock();
        /*
         通过调用callInitialize(cls);方法，在callInitialize内发送一条((void(*)(Class, SEL))objc_msgSend)(cls, @selector(initialize));
         消息进行初始化
         
         当然在_class_initialize 内部会判断父类是否已经initialize，如果没有，则先进行父类的initialize
         所以在进行initialize时会优先保证父类先进行initialize
         通过递归的方式进行_class_initialize(supercls)
         
         需要注意的是initialize是通过消息发送进行的，也就是，如果当前类没有initialize方法，那么他在lookUpImpOrForward的时候，会通过继承链的方式
         找到父类的initialize方法执行，所以initialize就会出现多次执行的可能
         比如，父类有initialize，但子类没有initialize的情况，当第一次向父类发送消息，那么父类的initialize方法会被调用
         当子类第一次发送消息时，由于子类没有initialize方法，所以会在查找过程中获取到父类的initialize方法进行执行
         所以父类的initialize就被执行了2次
         */
        _class_initialize (_class_getNonMetaClass(cls, inst));
        runtimeLock.lock();
        // If sel == initialize, _class_initialize will send +initialize and 
        // then the messenger will send +initialize again after this 
        // procedure finishes. Of course, if this is not being called 
        // from the messenger then it won't happen. 2778172
    }

    
 retry:    
    runtimeLock.assertLocked();

    // Try this class's cache.

    imp = cache_getImp(cls, sel);
    if (imp) goto done;

    // Try this class's method lists.从方法列表中查找
    {
        Method meth = getMethodNoSuper_nolock(cls, sel);
        if (meth) {
            log_and_fill_cache(cls, meth->imp, sel, inst, cls);
            imp = meth->imp;
            goto done;
        }
    }

    // Try superclass caches and method lists.，从父类的缓存或方法列表中查找
    {
        unsigned attempts = unreasonableClassCount();
        for (Class curClass = cls->superclass;
             curClass != nil;
             curClass = curClass->superclass)
        {
            // Halt if there is a cycle in the superclass chain.
            if (--attempts == 0) {
                _objc_fatal("Memory corruption in class list.");
            }
            
            // Superclass cache.
            imp = cache_getImp(curClass, sel);
            if (imp) {
                if (imp != (IMP)_objc_msgForward_impcache) {
                    // Found the method in a superclass. Cache it in this class.
                    log_and_fill_cache(cls, imp, sel, inst, curClass);
                    goto done;
                }
                else {
                    // Found a forward:: entry in a superclass.
                    // Stop searching, but don't cache yet; call method 
                    // resolver for this class first.
                    break;
                }
            }
            
            // Superclass method list.
            Method meth = getMethodNoSuper_nolock(curClass, sel);
            if (meth) {
                log_and_fill_cache(cls, meth->imp, sel, inst, curClass);
                imp = meth->imp;
                goto done;
            }
        }
    }

    // No implementation found. Try method resolver once.

    if (resolver  &&  !triedResolver) {
        runtimeLock.unlock();
        /*
         从这里可以看出，不管类有没有进行动态方法决议（有没有实现resolveInstanceMethod这个方法），或者动态方法决议返回的值是什么
         都会再查下一遍，同样的类方法也是（resolveClassMethod）
         */
        _class_resolveMethod(cls, sel, inst);
        runtimeLock.lock();
        // Don't cache the result; we don't hold the lock so it may have 
        // changed already. Re-do the search from scratch instead.
        triedResolver = YES;
        goto retry;
    }

    // No implementation found, and method resolver didn't help. 
    // Use forwarding.
    /*
     如果走到这一步，那么说明类没实现方法（也就是没有IMP）
     同时也没进行动态方法决议（也没动态的给方法指定IMP（实现resolveInstanceMethod，并在其中给方法绑定IMP ））
     那么就尝试进行消息转发
     转发流程可参考：https://www.jianshu.com/p/86713913323f
     
     1. 调用forwardingTargetForSelector返回响应该消息的对象，
     2. 如果forwardingTargetForSelector 返回nil 则调用methodSignatureForSelector返回NSMethodSignature
     3. 如果methodSignatureForSelector 返回nil,则调用doesNotRecognizeSelector 触发异常
     
     */
    imp = (IMP)_objc_msgForward_impcache;
    cache_fill(cls, sel, imp, inst);

 done:
    runtimeLock.unlock();

    return imp;
}


/***********************************************************************
* lookUpImpOrNil.
* Like lookUpImpOrForward, but returns nil instead of _objc_msgForward_impcache
**********************************************************************/
IMP lookUpImpOrNil(Class cls, SEL sel, id inst, 
                   bool initialize, bool cache, bool resolver)
{
    //这有可能会在父类方法列表中查找
    IMP imp = lookUpImpOrForward(cls, sel, inst, initialize, cache, resolver);
    if (imp == _objc_msgForward_impcache) {
        return nil;
    }
    else return imp;
}


/***********************************************************************
* lookupMethodInClassAndLoadCache.
* Like _class_lookupMethodAndLoadCache, but does not search superclasses.
* Caches and returns objc_msgForward if the method is not found in the class.
**********************************************************************/
IMP lookupMethodInClassAndLoadCache(Class cls, SEL sel)
{
    Method meth;
    IMP imp;

    // fixme this is incomplete - no resolver, +initialize - 
    // but it's only used for .cxx_construct/destruct so we don't care
    assert(sel == SEL_cxx_construct  ||  sel == SEL_cxx_destruct);

    // Search cache first.
    imp = cache_getImp(cls, sel);
    if (imp) return imp;

    // Cache miss. Search method list.

    mutex_locker_t lock(runtimeLock);

    meth = getMethodNoSuper_nolock(cls, sel);

    if (meth) {
        // Hit in method list. Cache it.
        cache_fill(cls, sel, meth->imp, nil);
        return meth->imp;
    } else {
        // Miss in method list. Cache objc_msgForward.
        cache_fill(cls, sel, _objc_msgForward_impcache, nil);
        return _objc_msgForward_impcache;
    }
}


/***********************************************************************
* class_getProperty
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
objc_property_t class_getProperty(Class cls, const char *name)
{
    if (!cls  ||  !name) return nil;

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);
    
    assert(cls->isRealized());

    for ( ; cls; cls = cls->superclass) {
        for (auto& prop : cls->data()->properties) {
            if (0 == strcmp(name, prop.name)) {
                return (objc_property_t)&prop;
            }
        }
    }
    
    return nil;
}


/***********************************************************************
* Locking: fixme
**********************************************************************/

Class gdb_class_getClass(Class cls)
{
    const char *className = cls->mangledName();
    if(!className || !strlen(className)) return Nil;
    Class rCls = look_up_class(className, NO, NO);
    return rCls;
}

Class gdb_object_getClass(id obj)
{
    if (!obj) return nil;
    return gdb_class_getClass(obj->getIsa());
}


/***********************************************************************
* Locking: write-locks runtimeLock
**********************************************************************/
void 
objc_class::setInitialized()
{
    Class metacls;
    Class cls;

    assert(!isMetaClass());

    cls = (Class)this;
    metacls = cls->ISA();

    mutex_locker_t lock(runtimeLock);

    // Scan metaclass for custom AWZ.
    // Scan metaclass for custom RR.
    // Scan class for custom RR.
    // Also print custom RR/AWZ because we probably haven't done it yet.

    // Special cases:
    // NSObject AWZ class methods are default.
    // NSObject RR instance methods are default.
    // updateCustomRR_AWZ() also knows these special cases.
    // attachMethodLists() also knows these special cases.

    bool inherited;
    bool metaCustomAWZ = NO;
    if (MetaclassNSObjectAWZSwizzled) {
        // Somebody already swizzled NSObject's methods
        metaCustomAWZ = YES;
        inherited = NO;
    }
    else if (metacls == classNSObject()->ISA()) {
        // NSObject's metaclass AWZ is default, but we still need to check cats
        auto& methods = metacls->data()->methods;
        for (auto mlists = methods.beginCategoryMethodLists(), 
                  end = methods.endCategoryMethodLists(metacls); 
             mlists != end;
             ++mlists)
        {
            if (methodListImplementsAWZ(*mlists)) {
                metaCustomAWZ = YES;
                inherited = NO;
                break;
            }
        }
    }
    else if (metacls->superclass->hasCustomAWZ()) {
        // Superclass is custom AWZ, therefore we are too.
        metaCustomAWZ = YES;
        inherited = YES;
    } 
    else {
        // Not metaclass NSObject.
        auto& methods = metacls->data()->methods;
        for (auto mlists = methods.beginLists(),
                  end = methods.endLists(); 
             mlists != end;
             ++mlists)
        {
            if (methodListImplementsAWZ(*mlists)) {
                metaCustomAWZ = YES;
                inherited = NO;
                break;
            }
        }
    }
    if (!metaCustomAWZ) metacls->setHasDefaultAWZ();

    if (PrintCustomAWZ  &&  metaCustomAWZ) metacls->printCustomAWZ(inherited);
    // metacls->printCustomRR();


    bool clsCustomRR = NO;
    if (ClassNSObjectRRSwizzled) {
        // Somebody already swizzled NSObject's methods
        clsCustomRR = YES;
        inherited = NO;
    }
    if (cls == classNSObject()) {
        // NSObject's RR is default, but we still need to check categories
        auto& methods = cls->data()->methods;
        for (auto mlists = methods.beginCategoryMethodLists(), 
                  end = methods.endCategoryMethodLists(cls); 
             mlists != end;
             ++mlists)
        {
            if (methodListImplementsRR(*mlists)) {
                clsCustomRR = YES;
                inherited = NO;
                break;
            }
        }
    }
    else if (!cls->superclass) {
        // Custom root class
        clsCustomRR = YES;
        inherited = NO;
    } 
    else if (cls->superclass->hasCustomRR()) {
        // Superclass is custom RR, therefore we are too.
        clsCustomRR = YES;
        inherited = YES;
    } 
    else {
        // Not class NSObject.
        auto& methods = cls->data()->methods;
        for (auto mlists = methods.beginLists(), 
                  end = methods.endLists(); 
             mlists != end;
             ++mlists)
        {
            if (methodListImplementsRR(*mlists)) {
                clsCustomRR = YES;
                inherited = NO;
                break;
            }
        }
    }
    if (!clsCustomRR) cls->setHasDefaultRR();

    // cls->printCustomAWZ();
    if (PrintCustomRR  &&  clsCustomRR) cls->printCustomRR(inherited);

    // Update the +initialize flags.
    // Do this last.
    metacls->changeInfo(RW_INITIALIZED, RW_INITIALIZING);
}


/***********************************************************************
* Return YES if sel is used by retain/release implementors
**********************************************************************/
static bool 
isRRSelector(SEL sel)
{
    return (sel == SEL_retain          ||  sel == SEL_release              ||  
            sel == SEL_autorelease     ||  sel == SEL_retainCount          ||  
            sel == SEL_tryRetain       ||  sel == SEL_retainWeakReference  ||  
            sel == SEL_isDeallocating  ||  sel == SEL_allowsWeakReference);
}


/***********************************************************************
* Return YES if mlist implements one of the isRRSelector() methods
**********************************************************************/
static bool 
methodListImplementsRR(const method_list_t *mlist)
{
    return (search_method_list(mlist, SEL_retain)               ||  
            search_method_list(mlist, SEL_release)              ||  
            search_method_list(mlist, SEL_autorelease)          ||  
            search_method_list(mlist, SEL_retainCount)          ||  
            search_method_list(mlist, SEL_tryRetain)            ||  
            search_method_list(mlist, SEL_isDeallocating)       ||  
            search_method_list(mlist, SEL_retainWeakReference)  ||  
            search_method_list(mlist, SEL_allowsWeakReference));
}


/***********************************************************************
* Return YES if sel is used by alloc or allocWithZone implementors
**********************************************************************/
static bool 
isAWZSelector(SEL sel)
{
    return (sel == SEL_allocWithZone  ||  sel == SEL_alloc);
}


/***********************************************************************
* Return YES if mlist implements one of the isAWZSelector() methods
**********************************************************************/
static bool 
methodListImplementsAWZ(const method_list_t *mlist)
{
    return (search_method_list(mlist, SEL_allocWithZone)  ||
            search_method_list(mlist, SEL_alloc));
}


void 
objc_class::printCustomRR(bool inherited)
{
    assert(PrintCustomRR);
    assert(hasCustomRR());
    _objc_inform("CUSTOM RR:  %s%s%s", nameForLogging(), 
                 isMetaClass() ? " (meta)" : "", 
                 inherited ? " (inherited)" : "");
}

void 
objc_class::printCustomAWZ(bool inherited)
{
    assert(PrintCustomAWZ);
    assert(hasCustomAWZ());
    _objc_inform("CUSTOM AWZ:  %s%s%s", nameForLogging(), 
                 isMetaClass() ? " (meta)" : "", 
                 inherited ? " (inherited)" : "");
}

void 
objc_class::printInstancesRequireRawIsa(bool inherited)
{
    assert(PrintRawIsa);
    assert(instancesRequireRawIsa());
    _objc_inform("RAW ISA:  %s%s%s", nameForLogging(), 
                 isMetaClass() ? " (meta)" : "", 
                 inherited ? " (inherited)" : "");
}


/***********************************************************************
* Mark this class and all of its subclasses as implementors or 
* inheritors of custom RR (retain/release/autorelease/retainCount)
**********************************************************************/
void objc_class::setHasCustomRR(bool inherited) 
{
    Class cls = (Class)this;
    runtimeLock.assertLocked();

    if (hasCustomRR()) return;
    
    foreach_realized_class_and_subclass(cls, ^(Class c){
        if (c != cls  &&  !c->isInitialized()) {
            // Subclass not yet initialized. Wait for setInitialized() to do it
            // fixme short circuit recursion?
            return;
        }
        if (c->hasCustomRR()) {
            // fixme short circuit recursion?
            return;
        }

        c->bits.setHasCustomRR();

        if (PrintCustomRR) c->printCustomRR(inherited  ||  c != cls);
    });
}

/***********************************************************************
* Mark this class and all of its subclasses as implementors or 
* inheritors of custom alloc/allocWithZone:
**********************************************************************/
void objc_class::setHasCustomAWZ(bool inherited) 
{
    Class cls = (Class)this;
    runtimeLock.assertLocked();

    if (hasCustomAWZ()) return;
    
    foreach_realized_class_and_subclass(cls, ^(Class c){
        if (c != cls  &&  !c->isInitialized()) {
            // Subclass not yet initialized. Wait for setInitialized() to do it
            // fixme short circuit recursion?
            return;
        }
        if (c->hasCustomAWZ()) {
            // fixme short circuit recursion?
            return;
        }

        c->bits.setHasCustomAWZ();

        if (PrintCustomAWZ) c->printCustomAWZ(inherited  ||  c != cls);
    });
}


/***********************************************************************
* Mark this class and all of its subclasses as requiring raw isa pointers
**********************************************************************/
void objc_class::setInstancesRequireRawIsa(bool inherited) 
{
    Class cls = (Class)this;
    runtimeLock.assertLocked();

    if (instancesRequireRawIsa()) return;
    
    foreach_realized_class_and_subclass(cls, ^(Class c){
        if (c->instancesRequireRawIsa()) {
            // fixme short circuit recursion?
            return;
        }

        c->bits.setInstancesRequireRawIsa();

        if (PrintRawIsa) c->printInstancesRequireRawIsa(inherited || c != cls);
    });
}


/***********************************************************************
* Choose a class index. 
* Set instancesRequireRawIsa if no more class indexes are available.
**********************************************************************/
void objc_class::chooseClassArrayIndex()
{
#if SUPPORT_INDEXED_ISA
    Class cls = (Class)this;
    runtimeLock.assertLocked();

    if (objc_indexed_classes_count >= ISA_INDEX_COUNT) {
        // No more indexes available.
        assert(cls->classArrayIndex() == 0);
        cls->setInstancesRequireRawIsa(false/*not inherited*/);
        return;
    }

    unsigned index = objc_indexed_classes_count++;
    if (index == 0) index = objc_indexed_classes_count++;  // index 0 is unused
    classForIndex(index) = cls;
    cls->setClassArrayIndex(index);
#endif
}


/***********************************************************************
* Update custom RR and AWZ when a method changes its IMP
**********************************************************************/
static void
updateCustomRR_AWZ(Class cls, method_t *meth)
{
    // In almost all cases, IMP swizzling does not affect custom RR/AWZ bits. 
    // Custom RR/AWZ search will already find the method whether or not 
    // it is swizzled, so it does not transition from non-custom to custom.
    // 
    // The only cases where IMP swizzling can affect the RR/AWZ bits is 
    // if the swizzled method is one of the methods that is assumed to be 
    // non-custom. These special cases are listed in setInitialized().
    // We look for such cases here.

    if (isRRSelector(meth->name)) {
        
        if ((classNSObject()->isInitialized() && 
             classNSObject()->hasCustomRR())  
            ||  
            ClassNSObjectRRSwizzled) 
        {
            // already custom, nothing would change
            return;
        }

        bool swizzlingNSObject = NO;
        if (cls == classNSObject()) {
            swizzlingNSObject = YES;
        } else {
            // Don't know the class. 
            // The only special case is class NSObject.
            for (const auto& meth2 : classNSObject()->data()->methods) {
                if (meth == &meth2) {
                    swizzlingNSObject = YES;
                    break;
                }
            }
        }
        if (swizzlingNSObject) {
            if (classNSObject()->isInitialized()) {
                classNSObject()->setHasCustomRR();
            } else {
                // NSObject not yet +initialized, so custom RR has not yet 
                // been checked, and setInitialized() will not notice the 
                // swizzle. 
                ClassNSObjectRRSwizzled = YES;
            }
        }
    }
    else if (isAWZSelector(meth->name)) {
        Class metaclassNSObject = classNSObject()->ISA();

        if ((metaclassNSObject->isInitialized() && 
             metaclassNSObject->hasCustomAWZ())  
            ||  
            MetaclassNSObjectAWZSwizzled) 
        {
            // already custom, nothing would change
            return;
        }

        bool swizzlingNSObject = NO;
        if (cls == metaclassNSObject) {
            swizzlingNSObject = YES;
        } else {
            // Don't know the class. 
            // The only special case is metaclass NSObject.
            for (const auto& meth2 : metaclassNSObject->data()->methods) {
                if (meth == &meth2) {
                    swizzlingNSObject = YES;
                    break;
                }
            }
        }
        if (swizzlingNSObject) {
            if (metaclassNSObject->isInitialized()) {
                metaclassNSObject->setHasCustomAWZ();
            } else {
                // NSObject not yet +initialized, so custom RR has not yet 
                // been checked, and setInitialized() will not notice the 
                // swizzle. 
                MetaclassNSObjectAWZSwizzled = YES;
            }
        }
    }
}


/***********************************************************************
* class_getIvarLayout
* Called by the garbage collector. 
* The class must be nil or already realized. 
* Locking: none
**********************************************************************/
const uint8_t *
class_getIvarLayout(Class cls)
{
    if (cls) return cls->data()->ro->ivarLayout;
    else return nil;
}


/***********************************************************************
* class_getWeakIvarLayout
* Called by the garbage collector. 
* The class must be nil or already realized. 
* Locking: none
**********************************************************************/
const uint8_t *
class_getWeakIvarLayout(Class cls)
{
    if (cls) return cls->data()->ro->weakIvarLayout;
    else return nil;
}


/***********************************************************************
* class_setIvarLayout
* Changes the class's ivar layout.
* nil layout means no unscanned ivars
* The class must be under construction.
* fixme: sanity-check layout vs instance size?
* fixme: sanity-check layout vs superclass?
* Locking: acquires runtimeLock
**********************************************************************/
void
class_setIvarLayout(Class cls, const uint8_t *layout)
{
    if (!cls) return;

    mutex_locker_t lock(runtimeLock);
    
    checkIsKnownClass(cls);

    // Can only change layout of in-construction classes.
    // note: if modifications to post-construction classes were 
    //   allowed, there would be a race below (us vs. concurrent object_setIvar)
    if (!(cls->data()->flags & RW_CONSTRUCTING)) {
        _objc_inform("*** Can't set ivar layout for already-registered "
                     "class '%s'", cls->nameForLogging());
        return;
    }

    class_ro_t *ro_w = make_ro_writeable(cls->data());

    try_free(ro_w->ivarLayout);
    ro_w->ivarLayout = ustrdupMaybeNil(layout);
}


/***********************************************************************
* class_setWeakIvarLayout
* Changes the class's weak ivar layout.
* nil layout means no weak ivars
* The class must be under construction.
* fixme: sanity-check layout vs instance size?
* fixme: sanity-check layout vs superclass?
* Locking: acquires runtimeLock
**********************************************************************/
void
class_setWeakIvarLayout(Class cls, const uint8_t *layout)
{
    if (!cls) return;

    mutex_locker_t lock(runtimeLock);
    
    checkIsKnownClass(cls);

    // Can only change layout of in-construction classes.
    // note: if modifications to post-construction classes were 
    //   allowed, there would be a race below (us vs. concurrent object_setIvar)
    if (!(cls->data()->flags & RW_CONSTRUCTING)) {
        _objc_inform("*** Can't set weak ivar layout for already-registered "
                     "class '%s'", cls->nameForLogging());
        return;
    }

    class_ro_t *ro_w = make_ro_writeable(cls->data());

    try_free(ro_w->weakIvarLayout);
    ro_w->weakIvarLayout = ustrdupMaybeNil(layout);
}


/***********************************************************************
* getIvar
* Look up an ivar by name.
* Locking: runtimeLock must be read- or write-locked by the caller.
**********************************************************************/
static ivar_t *getIvar(Class cls, const char *name)
{
    runtimeLock.assertLocked();

    const ivar_list_t *ivars;
    assert(cls->isRealized());
    if ((ivars = cls->data()->ro->ivars)) {
        for (auto& ivar : *ivars) {
            if (!ivar.offset) continue;  // anonymous bitfield

            // ivar.name may be nil for anonymous bitfields etc.
            if (ivar.name  &&  0 == strcmp(name, ivar.name)) {
                return &ivar;
            }
        }
    }

    return nil;
}


/***********************************************************************
* _class_getClassForIvar
* Given a class and an ivar that is in it or one of its superclasses, 
* find the actual class that defined the ivar.
**********************************************************************/
Class _class_getClassForIvar(Class cls, Ivar ivar)
{
    mutex_locker_t lock(runtimeLock);

    for ( ; cls; cls = cls->superclass) {
        if (auto ivars = cls->data()->ro->ivars) {
            if (ivars->containsIvar(ivar)) {
                return cls;
            }
        }
    }

    return nil;
}


/***********************************************************************
* _class_getVariable
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
Ivar 
_class_getVariable(Class cls, const char *name)
{
    mutex_locker_t lock(runtimeLock);

    for ( ; cls; cls = cls->superclass) {
        ivar_t *ivar = getIvar(cls, name);
        if (ivar) {
            return ivar;
        }
    }

    return nil;
}


/***********************************************************************
* class_conformsToProtocol
* fixme
* Locking: read-locks runtimeLock
**********************************************************************/
BOOL class_conformsToProtocol(Class cls, Protocol *proto_gen)
{
    protocol_t *proto = newprotocol(proto_gen);
    
    if (!cls) return NO;
    if (!proto_gen) return NO;

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);
    
    assert(cls->isRealized());
    
    for (const auto& proto_ref : cls->data()->protocols) {
        protocol_t *p = remapProtocol(proto_ref);
        if (p == proto || protocol_conformsToProtocol_nolock(p, proto)) {
            return YES;
        }
    }

    return NO;
}


/**********************************************************************
* addMethod
* fixme
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static IMP 
addMethod(Class cls, SEL name, IMP imp, const char *types, bool replace)
{
    IMP result = nil;

    runtimeLock.assertLocked();

    checkIsKnownClass(cls);
    
    assert(types);
    assert(cls->isRealized());

    method_t *m;
    /*
     直接在类里面的方法列表查询cls->data()->methods
     如果方法列表中没有，则添加
     */
    if ((m = getMethodNoSuper_nolock(cls, name))) {
        // already exists
        /*
         如果类方法列表中已经有了对应的方法，则返回
         如果需要替换则替换，但返回的仍然是旧的IMP
        */
        if (!replace) {
            result = m->imp;
        } else {
            result = _method_setImplementation(cls, m, imp);
        }
    } else {
        // fixme optimize
        //如果类的方法列表中没有才添加，并返回空
        method_list_t *newlist;
        newlist = (method_list_t *)calloc(sizeof(*newlist), 1);
        newlist->entsizeAndFlags = 
            (uint32_t)sizeof(method_t) | fixed_up_method_list;
        newlist->count = 1;
        newlist->first.name = name;
        newlist->first.types = strdupIfMutable(types);
        newlist->first.imp = imp;

        prepareMethodLists(cls, &newlist, 1, NO, NO);
        cls->data()->methods.attachLists(&newlist, 1);
        flushCaches(cls);

        result = nil;
    }

    return result;
}

/**********************************************************************
* addMethods
* Add the given methods to a class in bulk.
* Returns the selectors which could not be added, when replace == NO and a
* method already exists. The returned selectors are NULL terminated and must be
* freed by the caller. They are NULL if no failures occurred.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static SEL *
addMethods(Class cls, const SEL *names, const IMP *imps, const char **types,
           uint32_t count, bool replace, uint32_t *outFailedCount)
{
    runtimeLock.assertLocked();
    
    assert(names);
    assert(imps);
    assert(types);
    assert(cls->isRealized());
    
    method_list_t *newlist;
    size_t newlistSize = method_list_t::byteSize(sizeof(method_t), count);
    newlist = (method_list_t *)calloc(newlistSize, 1);
    newlist->entsizeAndFlags =
        (uint32_t)sizeof(method_t) | fixed_up_method_list;
    newlist->count = 0;
    
    method_t *newlistMethods = &newlist->first;
    
    SEL *failedNames = nil;
    uint32_t failedCount = 0;
    
    for (uint32_t i = 0; i < count; i++) {
        method_t *m;
        if ((m = getMethodNoSuper_nolock(cls, names[i]))) {
            // already exists
            if (!replace) {
                // report failure
                if (failedNames == nil) {
                    // allocate an extra entry for a trailing NULL in case
                    // every method fails
                    failedNames = (SEL *)calloc(sizeof(*failedNames),
                                                count + 1);
                }
                failedNames[failedCount] = m->name;
                failedCount++;
            } else {
                _method_setImplementation(cls, m, imps[i]);
            }
        } else {
            method_t *newmethod = &newlistMethods[newlist->count];
            newmethod->name = names[i];
            newmethod->types = strdupIfMutable(types[i]);
            newmethod->imp = imps[i];
            newlist->count++;
        }
    }
    
    if (newlist->count > 0) {
        // fixme resize newlist because it may have been over-allocated above.
        // Note that realloc() alone doesn't work due to ptrauth.
        
        method_t::SortBySELAddress sorter;
        std::stable_sort(newlist->begin(), newlist->end(), sorter);
        
        prepareMethodLists(cls, &newlist, 1, NO, NO);
        cls->data()->methods.attachLists(&newlist, 1);
        flushCaches(cls);
    } else {
        // Attaching the method list to the class consumes it. If we don't
        // do that, we have to free the memory ourselves.
        free(newlist);
    }
    
    if (outFailedCount) *outFailedCount = failedCount;
    
    return failedNames;
}


BOOL 
class_addMethod(Class cls, SEL name, IMP imp, const char *types)
{
    if (!cls) return NO;

    mutex_locker_t lock(runtimeLock);
    return ! addMethod(cls, name, imp, types ?: "", NO);
}


IMP 
class_replaceMethod(Class cls, SEL name, IMP imp, const char *types)
{
    if (!cls) return nil;

    mutex_locker_t lock(runtimeLock);
    //
    return addMethod(cls, name, imp, types ?: "", YES);
}


SEL *
class_addMethodsBulk(Class cls, const SEL *names, const IMP *imps,
                     const char **types, uint32_t count,
                     uint32_t *outFailedCount)
{
    if (!cls) {
        if (outFailedCount) *outFailedCount = count;
        return (SEL *)memdup(names, count * sizeof(*names));
    }
    
    mutex_locker_t lock(runtimeLock);
    return addMethods(cls, names, imps, types, count, NO, outFailedCount);
}

void
class_replaceMethodsBulk(Class cls, const SEL *names, const IMP *imps,
                         const char **types, uint32_t count)
{
    if (!cls) return;
    
    mutex_locker_t lock(runtimeLock);
    addMethods(cls, names, imps, types, count, YES, nil);
}


/***********************************************************************
* class_addIvar
* Adds an ivar to a class.
* Locking: acquires runtimeLock
**********************************************************************/
BOOL 
class_addIvar(Class cls, const char *name, size_t size, 
              uint8_t alignment, const char *type)
{
    if (!cls) return NO;

    if (!type) type = "";
    if (name  &&  0 == strcmp(name, "")) name = nil;

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);
    assert(cls->isRealized());

    // No class variables
    if (cls->isMetaClass()) {
        return NO;
    }

    // Can only add ivars to in-construction classes.
    if (!(cls->data()->flags & RW_CONSTRUCTING)) {
        return NO;
    }

    // Check for existing ivar with this name, unless it's anonymous.
    // Check for too-big ivar.
    // fixme check for superclass ivar too?
    if ((name  &&  getIvar(cls, name))  ||  size > UINT32_MAX) {
        return NO;
    }

    /*
     make_ro_writeable 接口内部为rw中额ro重新申请一块内存，然后将旧的rw中的ro通过内存拷贝，
     拷贝到新的内存中，然后返回新的内存地址
     
     也就是扩展内存，用来存放新的成员变量
     */
    class_ro_t *ro_w = make_ro_writeable(cls->data());

    // fixme allocate less memory here
    
    ivar_list_t *oldlist, *newlist;
    if ((oldlist = (ivar_list_t *)cls->data()->ro->ivars)) {
        size_t oldsize = oldlist->byteSize();
        newlist = (ivar_list_t *)calloc(oldsize + oldlist->entsize(), 1);
        memcpy(newlist, oldlist, oldsize);
        free(oldlist);
    } else {
        newlist = (ivar_list_t *)calloc(sizeof(ivar_list_t), 1);
        newlist->entsizeAndFlags = (uint32_t)sizeof(ivar_t);
    }

    uint32_t offset = cls->unalignedInstanceSize();
    uint32_t alignMask = (1<<alignment)-1;
    offset = (offset + alignMask) & ~alignMask;

    ivar_t& ivar = newlist->get(newlist->count++);
#if __x86_64__
    // Deliberately over-allocate the ivar offset variable. 
    // Use calloc() to clear all 64 bits. See the note in struct ivar_t.
    ivar.offset = (int32_t *)(int64_t *)calloc(sizeof(int64_t), 1);
#else
    ivar.offset = (int32_t *)malloc(sizeof(int32_t));
#endif
    *ivar.offset = offset;
    ivar.name = name ? strdupIfMutable(name) : nil;
    ivar.type = strdupIfMutable(type);
    ivar.alignment_raw = alignment;
    ivar.size = (uint32_t)size;

    ro_w->ivars = newlist;
    cls->setInstanceSize((uint32_t)(offset + size));

    // Ivar layout updated in registerClass.

    return YES;
}


/***********************************************************************
* class_addProtocol
* Adds a protocol to a class.
* Locking: acquires runtimeLock
**********************************************************************/
BOOL class_addProtocol(Class cls, Protocol *protocol_gen)
{
    protocol_t *protocol = newprotocol(protocol_gen);

    if (!cls) return NO;
    if (class_conformsToProtocol(cls, protocol_gen)) return NO;

    mutex_locker_t lock(runtimeLock);

    assert(cls->isRealized());
    
    // fixme optimize
    protocol_list_t *protolist = (protocol_list_t *)
        malloc(sizeof(protocol_list_t) + sizeof(protocol_t *));
    protolist->count = 1;
    protolist->list[0] = (protocol_ref_t)protocol;

    cls->data()->protocols.attachLists(&protolist, 1);

    // fixme metaclass?

    return YES;
}


/***********************************************************************
* class_addProperty
* Adds a property to a class.
* Locking: acquires runtimeLock
**********************************************************************/
static bool 
_class_addProperty(Class cls, const char *name, 
                   const objc_property_attribute_t *attrs, unsigned int count, 
                   bool replace)
{
    if (!cls) return NO;
    if (!name) return NO;

    property_t *prop = class_getProperty(cls, name);
    if (prop  &&  !replace) {
        // already exists, refuse to replace
        return NO;
    } 
    else if (prop) {
        // replace existing
        mutex_locker_t lock(runtimeLock);
        try_free(prop->attributes);
        prop->attributes = copyPropertyAttributeString(attrs, count);
        return YES;
    }
    else {
        mutex_locker_t lock(runtimeLock);
        
        assert(cls->isRealized());
        
        property_list_t *proplist = (property_list_t *)
            malloc(sizeof(*proplist));
        proplist->count = 1;
        proplist->entsizeAndFlags = sizeof(proplist->first);
        proplist->first.name = strdupIfMutable(name);
        proplist->first.attributes = copyPropertyAttributeString(attrs, count);
        
        cls->data()->properties.attachLists(&proplist, 1);
        
        return YES;
    }
}

BOOL 
class_addProperty(Class cls, const char *name, 
                  const objc_property_attribute_t *attrs, unsigned int n)
{
    return _class_addProperty(cls, name, attrs, n, NO);
}

void 
class_replaceProperty(Class cls, const char *name, 
                      const objc_property_attribute_t *attrs, unsigned int n)
{
    _class_addProperty(cls, name, attrs, n, YES);
}


/***********************************************************************
* look_up_class
* Look up a class by name, and realize it.
* Locking: acquires runtimeLock
**********************************************************************/
Class 
look_up_class(const char *name, 
              bool includeUnconnected __attribute__((unused)), 
              bool includeClassHandler __attribute__((unused)))
{
    if (!name) return nil;

    Class result;
    bool unrealized;
    {
        mutex_locker_t lock(runtimeLock);
        /*
         从gdb_objc_realized_classes 表中获取类名对应的Class
         插入时机是在runtime初始化过程中map_images -> _read_images ->readClass 中调用
         addNamedClass(cls, mangledName, replacing);进行插入的，懒加载的类（没有+load方法的类）在runtime初始化时还没
         进行realize，延迟到运行时首次调用通过look_up_class()方法查询时才进行realize
         
         目的是为了加快应用启动
         
         */
        result = getClass(name);
        unrealized = result  &&  !result->isRealized();
    }
    if (unrealized) {
        mutex_locker_t lock(runtimeLock);
        realizeClass(result);
    }
    return result;
}


/***********************************************************************
* objc_duplicateClass
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
Class 
objc_duplicateClass(Class original, const char *name, 
                    size_t extraBytes)
{
    Class duplicate;

    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(original);

    assert(original->isRealized());
    assert(!original->isMetaClass());

    duplicate = alloc_class_for_subclass(original, extraBytes);

    duplicate->initClassIsa(original->ISA());
    duplicate->superclass = original->superclass;

    duplicate->cache.initializeToEmpty();

    class_rw_t *rw = (class_rw_t *)calloc(sizeof(*original->data()), 1);
    rw->flags = (original->data()->flags | RW_COPIED_RO | RW_REALIZING);
    rw->version = original->data()->version;
    rw->firstSubclass = nil;
    rw->nextSiblingClass = nil;

    duplicate->bits = original->bits;
    duplicate->setData(rw);

    rw->ro = (class_ro_t *)
        memdup(original->data()->ro, sizeof(*original->data()->ro));
    *(char **)&rw->ro->name = strdupIfMutable(name);

    rw->methods = original->data()->methods.duplicate();

    // fixme dies when categories are added to the base
    rw->properties = original->data()->properties;
    rw->protocols = original->data()->protocols;

    duplicate->chooseClassArrayIndex();

    if (duplicate->superclass) {
        addSubclass(duplicate->superclass, duplicate);
        // duplicate->isa == original->isa so don't addSubclass() for it
    } else {
        addRootClass(duplicate);
    }

    // Don't methodize class - construction above is correct

    addNamedClass(duplicate, duplicate->data()->ro->name);
    addClassTableEntry(duplicate, /*addMeta=*/false);
    
    if (PrintConnecting) {
        _objc_inform("CLASS: realizing class '%s' (duplicate of %s) %p %p", 
                     name, original->nameForLogging(), 
                     (void*)duplicate, duplicate->data()->ro);
    }

    duplicate->clearInfo(RW_REALIZING);

    return duplicate;
}

/***********************************************************************
* objc_initializeClassPair
* Locking: runtimeLock must be write-locked by the caller
**********************************************************************/

// &UnsetLayout is the default ivar layout during class construction
static const uint8_t UnsetLayout = 0;

static void objc_initializeClassPair_internal(Class superclass, const char *name, Class cls, Class meta)
{
    runtimeLock.assertLocked();

    class_ro_t *cls_ro_w, *meta_ro_w;
    
    cls->setData((class_rw_t *)calloc(sizeof(class_rw_t), 1));
    meta->setData((class_rw_t *)calloc(sizeof(class_rw_t), 1));
    cls_ro_w   = (class_ro_t *)calloc(sizeof(class_ro_t), 1);
    meta_ro_w  = (class_ro_t *)calloc(sizeof(class_ro_t), 1);
    cls->data()->ro = cls_ro_w;
    meta->data()->ro = meta_ro_w;

    // Set basic info

    cls->data()->flags = RW_CONSTRUCTING | RW_COPIED_RO | RW_REALIZED | RW_REALIZING;
    meta->data()->flags = RW_CONSTRUCTING | RW_COPIED_RO | RW_REALIZED | RW_REALIZING;
    cls->data()->version = 0;
    meta->data()->version = 7;

    cls_ro_w->flags = 0;
    meta_ro_w->flags = RO_META;
    if (!superclass) {
        cls_ro_w->flags |= RO_ROOT;
        meta_ro_w->flags |= RO_ROOT;
    }
    if (superclass) {
        cls_ro_w->instanceStart = superclass->unalignedInstanceSize();
        meta_ro_w->instanceStart = superclass->ISA()->unalignedInstanceSize();
        cls->setInstanceSize(cls_ro_w->instanceStart);
        meta->setInstanceSize(meta_ro_w->instanceStart);
    } else {
        cls_ro_w->instanceStart = 0;
        meta_ro_w->instanceStart = (uint32_t)sizeof(objc_class);
        cls->setInstanceSize((uint32_t)sizeof(id));  // just an isa
        meta->setInstanceSize(meta_ro_w->instanceStart);
    }

    cls_ro_w->name = strdupIfMutable(name);
    meta_ro_w->name = strdupIfMutable(name);

    cls_ro_w->ivarLayout = &UnsetLayout;
    cls_ro_w->weakIvarLayout = &UnsetLayout;

    meta->chooseClassArrayIndex();
    cls->chooseClassArrayIndex();

    // Connect to superclasses and metaclasses
    cls->initClassIsa(meta);
    if (superclass) {
        meta->initClassIsa(superclass->ISA()->ISA());
        cls->superclass = superclass;
        meta->superclass = superclass->ISA();
        addSubclass(superclass, cls);
        addSubclass(superclass->ISA(), meta);
    } else {
        meta->initClassIsa(meta);
        cls->superclass = Nil;
        meta->superclass = cls;
        addRootClass(cls);
        addSubclass(cls, meta);
    }

    cls->cache.initializeToEmpty();
    meta->cache.initializeToEmpty();
    
    addClassTableEntry(cls);
}


/***********************************************************************
* verifySuperclass
* Sanity-check the superclass provided to 
* objc_allocateClassPair, objc_initializeClassPair, or objc_readClassPair.
**********************************************************************/
bool
verifySuperclass(Class superclass, bool rootOK)
{
    if (!superclass) {
        // Superclass does not exist.
        // If subclass may be a root class, this is OK.
        // If subclass must not be a root class, this is bad.
        return rootOK;
    }

    // Superclass must be realized.
    if (! superclass->isRealized()) return false;

    // Superclass must not be under construction.
    if (superclass->data()->flags & RW_CONSTRUCTING) return false;

    return true;
}


/***********************************************************************
* objc_initializeClassPair
**********************************************************************/
Class objc_initializeClassPair(Class superclass, const char *name, Class cls, Class meta)
{
    mutex_locker_t lock(runtimeLock);

    // Fail if the class name is in use.
    // Fail if the superclass isn't kosher.
    if (getClass(name)  ||  !verifySuperclass(superclass, true/*rootOK*/)) {
        return nil;
    }

    objc_initializeClassPair_internal(superclass, name, cls, meta);

    return cls;
}


/***********************************************************************
* objc_allocateClassPair
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
Class objc_allocateClassPair(Class superclass, const char *name, 
                             size_t extraBytes)
{
    Class cls, meta;

    mutex_locker_t lock(runtimeLock);

    // Fail if the class name is in use.
    // Fail if the superclass isn't kosher.
    if (getClass(name)  ||  !verifySuperclass(superclass, true/*rootOK*/)) {
        return nil;
    }

    // Allocate new classes.
    cls  = alloc_class_for_subclass(superclass, extraBytes);
    meta = alloc_class_for_subclass(superclass, extraBytes);

    // fixme mangle the name if it looks swift-y?
    objc_initializeClassPair_internal(superclass, name, cls, meta);

    return cls;
}


/***********************************************************************
* objc_registerClassPair
* fixme
* Locking: acquires runtimeLock
**********************************************************************/
void objc_registerClassPair(Class cls)
{
    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);

    if ((cls->data()->flags & RW_CONSTRUCTED)  ||
        (cls->ISA()->data()->flags & RW_CONSTRUCTED)) 
    {
        _objc_inform("objc_registerClassPair: class '%s' was already "
                     "registered!", cls->data()->ro->name);
        return;
    }

    if (!(cls->data()->flags & RW_CONSTRUCTING)  ||  
        !(cls->ISA()->data()->flags & RW_CONSTRUCTING))
    {
        _objc_inform("objc_registerClassPair: class '%s' was not "
                     "allocated with objc_allocateClassPair!", 
                     cls->data()->ro->name);
        return;
    }

    // Clear "under construction" bit, set "done constructing" bit
    cls->ISA()->changeInfo(RW_CONSTRUCTED, RW_CONSTRUCTING | RW_REALIZING);
    cls->changeInfo(RW_CONSTRUCTED, RW_CONSTRUCTING | RW_REALIZING);

    // Add to named class table.
    addNamedClass(cls, cls->data()->ro->name);
}


/***********************************************************************
* objc_readClassPair()
* Read a class and metaclass as written by a compiler.
* Assumes the class and metaclass are not referenced by other things 
* that might need to be fixed up (such as categories and subclasses).
* Does not call +load.
* Returns the class pointer, or nil.
*
* Locking: runtimeLock acquired by map_images
**********************************************************************/
Class objc_readClassPair(Class bits, const struct objc_image_info *info)
{
    mutex_locker_t lock(runtimeLock);

    // No info bits are significant yet.
    (void)info;

    // Fail if the superclass isn't kosher.
    bool rootOK = bits->data()->flags & RO_ROOT;
    if (!verifySuperclass(bits->superclass, rootOK)){
        return nil;
    }

    // Duplicate classes are allowed, just like they are for image loading.
    // readClass will complain about the duplicate.

    Class cls = readClass(bits, false/*bundle*/, false/*shared cache*/);
    if (cls != bits) {
        // This function isn't allowed to remap anything.
        _objc_fatal("objc_readClassPair for class %s changed %p to %p", 
                    cls->nameForLogging(), bits, cls);
    }
    realizeClass(cls);

    return cls;
}


/***********************************************************************
* detach_class
* Disconnect a class from other data structures.
* Exception: does not remove the class from the +load list
* Call this before free_class.
* Locking: runtimeLock must be held by the caller.
**********************************************************************/
static void detach_class(Class cls, bool isMeta)
{
    runtimeLock.assertLocked();

    // categories not yet attached to this class
    removeAllUnattachedCategoriesForClass(cls);

    // superclass's subclass list
    if (cls->isRealized()) {
        Class supercls = cls->superclass;
        if (supercls) {
            removeSubclass(supercls, cls);
        } else {
            removeRootClass(cls);
        }
    }

    // class tables and +load queue
    if (!isMeta) {
        removeNamedClass(cls, cls->mangledName());
    }
    NXHashRemove(allocatedClasses, cls);
}


/***********************************************************************
* free_class
* Frees a class's data structures.
* Call this after detach_class.
* Locking: runtimeLock must be held by the caller
**********************************************************************/
static void free_class(Class cls)
{
    runtimeLock.assertLocked();

    if (! cls->isRealized()) return;

    auto rw = cls->data();
    auto ro = rw->ro;

    cache_delete(cls);
    
    for (auto& meth : rw->methods) {
        try_free(meth.types);
    }
    rw->methods.tryFree();
    
    const ivar_list_t *ivars = ro->ivars;
    if (ivars) {
        for (auto& ivar : *ivars) {
            try_free(ivar.offset);
            try_free(ivar.name);
            try_free(ivar.type);
        }
        try_free(ivars);
    }

    for (auto& prop : rw->properties) {
        try_free(prop.name);
        try_free(prop.attributes);
    }
    rw->properties.tryFree();

    rw->protocols.tryFree();
    
    try_free(ro->ivarLayout);
    try_free(ro->weakIvarLayout);
    try_free(ro->name);
    try_free(ro);
    try_free(rw);
    try_free(cls);
}


void objc_disposeClassPair(Class cls)
{
    mutex_locker_t lock(runtimeLock);

    checkIsKnownClass(cls);

    if (!(cls->data()->flags & (RW_CONSTRUCTED|RW_CONSTRUCTING))  ||
        !(cls->ISA()->data()->flags & (RW_CONSTRUCTED|RW_CONSTRUCTING))) 
    {
        // class not allocated with objc_allocateClassPair
        // disposing still-unregistered class is OK!
        _objc_inform("objc_disposeClassPair: class '%s' was not "
                     "allocated with objc_allocateClassPair!", 
                     cls->data()->ro->name);
        return;
    }

    if (cls->isMetaClass()) {
        _objc_inform("objc_disposeClassPair: class '%s' is a metaclass, "
                     "not a class!", cls->data()->ro->name);
        return;
    }

    // Shouldn't have any live subclasses.
    if (cls->data()->firstSubclass) {
        _objc_inform("objc_disposeClassPair: class '%s' still has subclasses, "
                     "including '%s'!", cls->data()->ro->name, 
                     cls->data()->firstSubclass->nameForLogging());
    }
    if (cls->ISA()->data()->firstSubclass) {
        _objc_inform("objc_disposeClassPair: class '%s' still has subclasses, "
                     "including '%s'!", cls->data()->ro->name, 
                     cls->ISA()->data()->firstSubclass->nameForLogging());
    }

    // don't remove_class_from_loadable_list() 
    // - it's not there and we don't have the lock
    detach_class(cls->ISA(), YES);
    detach_class(cls, NO);
    free_class(cls->ISA());
    free_class(cls);
}


/***********************************************************************
* objc_constructInstance
* Creates an instance of `cls` at the location pointed to by `bytes`. 
* `bytes` must point to at least class_getInstanceSize(cls) bytes of 
*   well-aligned zero-filled memory.
* The new object's isa is set. Any C++ constructors are called.
* Returns `bytes` if successful. Returns nil if `cls` or `bytes` is 
*   nil, or if C++ constructors fail.
* Note: class_createInstance() and class_createInstances() preflight this.
**********************************************************************/
id 
objc_constructInstance(Class cls, void *bytes) 
{
    if (!cls  ||  !bytes) return nil;

    id obj = (id)bytes;

    // Read class's info bits all at once for performance
    bool hasCxxCtor = cls->hasCxxCtor();
    bool hasCxxDtor = cls->hasCxxDtor();
    bool fast = cls->canAllocNonpointer();
    
    if (fast) {
        obj->initInstanceIsa(cls, hasCxxDtor);
    } else {
        obj->initIsa(cls);
    }

    if (hasCxxCtor) {
        return object_cxxConstructFromClass(obj, cls);
    } else {
        return obj;
    }
}


/***********************************************************************
* class_createInstance
* fixme
* Locking: none
**********************************************************************/

static __attribute__((always_inline)) 
id
_class_createInstanceFromZone(Class cls, size_t extraBytes, void *zone, 
                              bool cxxConstruct = true, 
                              size_t *outAllocatedSize = nil)
{
    if (!cls) return nil;

    assert(cls->isRealized());

    // Read class's info bits all at once for performance
    bool hasCxxCtor = cls->hasCxxCtor();
    bool hasCxxDtor = cls->hasCxxDtor();
    bool fast = cls->canAllocNonpointer();

    //获取一个对象需要申请多少内存空间，最小占用的内存空间为16字节
    size_t size = cls->instanceSize(extraBytes);
    if (outAllocatedSize) {
        *outAllocatedSize = size;
    }

    /*
     typedef struct objc_object *id;
     */
    id obj;
    if (!zone  &&  fast) {
        obj = (id)calloc(1, size);
        if (!obj) return nil;
        obj->initInstanceIsa(cls, hasCxxDtor);
    } 
    else {
        if (zone) {
            /*
             * 从指定zone中申请内存
             * zone创建是通过底层接口szone_t * create_scalable_szone(size_t initial_size, unsigned debug_flags)创建的
             * 在create_scalable_szone中通过mvm_allocate_pages --> mach_vm_map 调用mach 接口从task中申请对应的内存，
             * 并设置zone->calloc函数指针，后续通过zone->calloc调用从zone中获取zone内的内存
             */
            obj = (id)malloc_zone_calloc ((malloc_zone_t *)zone, 1, size);
        } else {
            // 从default zone 中申请内存,OC 好像基本跑这分支，因为传进来的zone 参数都是nil
            obj = (id)calloc(1, size);
        }
        if (!obj) return nil;

        // Use raw pointer isa on the assumption that they might be 
        // doing something weird with the zone or RR.
        obj->initIsa(cls);
    }

    if (cxxConstruct && hasCxxCtor) {
        obj = _objc_constructOrFree(obj, cls);
    }

    return obj;
}


id 
class_createInstance(Class cls, size_t extraBytes)
{
    return _class_createInstanceFromZone(cls, extraBytes, nil);
}


/***********************************************************************
* class_createInstances
* fixme
* Locking: none
**********************************************************************/
#if SUPPORT_NONPOINTER_ISA
#warning fixme optimize class_createInstances
#endif
unsigned 
class_createInstances(Class cls, size_t extraBytes, 
                      id *results, unsigned num_requested)
{
    return _class_createInstancesFromZone(cls, extraBytes, nil, 
                                          results, num_requested);
}

/***********************************************************************
* object_copyFromZone
* fixme
* Locking: none
**********************************************************************/
static id 
_object_copyFromZone(id oldObj, size_t extraBytes, void *zone)
{
    if (!oldObj) return nil;
    if (oldObj->isTaggedPointer()) return oldObj;

    // fixme this doesn't handle C++ ivars correctly (#4619414)

    Class cls = oldObj->ISA();
    size_t size;
    id obj = _class_createInstanceFromZone(cls, extraBytes, zone, false, &size);
    if (!obj) return nil;

    // Copy everything except the isa, which was already set above.
    uint8_t *copyDst = (uint8_t *)obj + sizeof(Class);
    uint8_t *copySrc = (uint8_t *)oldObj + sizeof(Class);
    size_t copySize = size - sizeof(Class);
    memmove(copyDst, copySrc, copySize);

    fixupCopiedIvars(obj, oldObj);

    return obj;
}


/***********************************************************************
* object_copy
* fixme
* Locking: none
**********************************************************************/
id 
object_copy(id oldObj, size_t extraBytes)
{
    return _object_copyFromZone(oldObj, extraBytes, malloc_default_zone());
}


#if SUPPORT_ZONES

/***********************************************************************
* class_createInstanceFromZone
* fixme
* Locking: none
**********************************************************************/
id
class_createInstanceFromZone(Class cls, size_t extraBytes, void *zone)
{
    return _class_createInstanceFromZone(cls, extraBytes, zone);
}

/***********************************************************************
* object_copyFromZone
* fixme
* Locking: none
**********************************************************************/
id 
object_copyFromZone(id oldObj, size_t extraBytes, void *zone)
{
    return _object_copyFromZone(oldObj, extraBytes, zone);
}

#endif


/***********************************************************************
* objc_destructInstance
* Destroys an instance without freeing memory. 
* Calls C++ destructors.
* Calls ARC ivar cleanup.
* Removes associative references.
* Returns `obj`. Does nothing if `obj` is nil.
**********************************************************************/
void *objc_destructInstance(id obj) 
{
    if (obj) {
        // Read all of the flags at once for performance.
        bool cxx = obj->hasCxxDtor();
        bool assoc = obj->hasAssociatedObjects();

        // This order is important.
        if (cxx) {
            //执行C++析构函数
            object_cxxDestruct(obj);
        }
        if (assoc) {
            //删除关联对象
            _object_remove_assocations(obj);
        }
        //引用计数，弱指针处理
        obj->clearDeallocating();
    }

    return obj;
}


/***********************************************************************
* object_dispose
* fixme
* Locking: none
**********************************************************************/
id 
object_dispose(id obj)
{
    if (!obj) return nil;

    objc_destructInstance(obj);
    //这里才是真正的释放内存的接口
    free(obj);

    return nil;
}


/***********************************************************************
* _objc_getFreedObjectClass
* fixme
* Locking: none
**********************************************************************/
Class _objc_getFreedObjectClass (void)
{
    return nil;
}



/***********************************************************************
* Tagged pointer objects.  【参考文章】(https://www.infoq.cn/article/r5s0budukwyndafrivh4)
*
* Tagged pointer objects store the class and the object value in the 
* object pointer; the "pointer" does not actually point to anything.                                    ////  Tagged pointer 指针对象将 class 和对象数据存储在对象指针中；指针实际上不指向任何东西。
* 
* Tagged pointer objects currently use this representation:                                             ////  Tagged pointer 当前使用此表示形式：
* (LSB)                                                                                                                             ////  (macOS)64 位分布如下：
*  1 bit   set if tagged, clear if ordinary object pointer                                                      ////  1 bit 标记是 Tagged Pointer
*  3 bits  tag index                                                                                                           ////  3 bits 标记类型
* 60 bits  payload                                                                                                            ////  60 bits 负载数据容量，（存储对象数据）
* (MSB)                                                                                                                           ////  (iOS)64 位分布如下：
* The tag index defines the object's class.                                                                     ////  tag index 表示对象所属的 class
* The payload format is defined by the object's class.                                                   ////  负载格式由对象的 class 定义
*
* If the tag index is 0b111, the tagged pointer object uses an                                       ////  如果 tag index 是 0b111(7)， tagged pointer 对象使用 “扩展” 表示形式
* "extended" representation, allowing more classes but with smaller payloads:           ////  允许更多类，但 有效载荷 更小
* (LSB)                                                                                                                           ////  (macOS)(带有扩展内容)64 位分布如下：
*  1 bit   set if tagged, clear if ordinary object pointer                                                    ////  1 bit 标记是 Tagged Pointer
*  3 bits  0b111                                                                                                               ////  3 bits 是 0b111
*  8 bits  extended tag index                                                                                          ////  8 bits 扩展标记格式
* 52 bits  payload                                                                                                           ////  52 bits 负载数据容量，（存储对象数据）
* (MSB)
*
* Some architectures reverse the MSB and LSB in these representations.                  ////  在这些表示中，某些体系结构反转了 MSB 和 LSB。
*
* This representation is subject to change. Representation-agnostic SPI is:
* objc-internal.h for class implementers.
* objc-gdb.h for debuggers.
**********************************************************************/
#if !SUPPORT_TAGGED_POINTERS

// These variables are always provided for debuggers.
uintptr_t objc_debug_taggedpointer_obfuscator = 0;
uintptr_t objc_debug_taggedpointer_mask = 0;
unsigned  objc_debug_taggedpointer_slot_shift = 0;
uintptr_t objc_debug_taggedpointer_slot_mask = 0;
unsigned  objc_debug_taggedpointer_payload_lshift = 0;
unsigned  objc_debug_taggedpointer_payload_rshift = 0;
Class objc_debug_taggedpointer_classes[1] = { nil };

uintptr_t objc_debug_taggedpointer_ext_mask = 0;
unsigned  objc_debug_taggedpointer_ext_slot_shift = 0;
uintptr_t objc_debug_taggedpointer_ext_slot_mask = 0;
unsigned  objc_debug_taggedpointer_ext_payload_lshift = 0;
unsigned  objc_debug_taggedpointer_ext_payload_rshift = 0;
Class objc_debug_taggedpointer_ext_classes[1] = { nil };

static void
disableTaggedPointers() { }

static void
initializeTaggedPointerObfuscator(void) { }

#else

// The "slot" used in the class table and given to the debugger 
// includes the is-tagged bit. This makes objc_msgSend faster.
// The "ext" representation doesn't do that.

uintptr_t objc_debug_taggedpointer_obfuscator;
uintptr_t objc_debug_taggedpointer_mask = _OBJC_TAG_MASK;
unsigned  objc_debug_taggedpointer_slot_shift = _OBJC_TAG_SLOT_SHIFT;
uintptr_t objc_debug_taggedpointer_slot_mask = _OBJC_TAG_SLOT_MASK;
unsigned  objc_debug_taggedpointer_payload_lshift = _OBJC_TAG_PAYLOAD_LSHIFT;
unsigned  objc_debug_taggedpointer_payload_rshift = _OBJC_TAG_PAYLOAD_RSHIFT;
// objc_debug_taggedpointer_classes is defined in objc-msg-*.s

uintptr_t objc_debug_taggedpointer_ext_mask = _OBJC_TAG_EXT_MASK;
unsigned  objc_debug_taggedpointer_ext_slot_shift = _OBJC_TAG_EXT_SLOT_SHIFT;
uintptr_t objc_debug_taggedpointer_ext_slot_mask = _OBJC_TAG_EXT_SLOT_MASK;
unsigned  objc_debug_taggedpointer_ext_payload_lshift = _OBJC_TAG_EXT_PAYLOAD_LSHIFT;
unsigned  objc_debug_taggedpointer_ext_payload_rshift = _OBJC_TAG_EXT_PAYLOAD_RSHIFT;
// objc_debug_taggedpointer_ext_classes is defined in objc-msg-*.s

static void
disableTaggedPointers()
{
    objc_debug_taggedpointer_mask = 0;
    objc_debug_taggedpointer_slot_shift = 0;
    objc_debug_taggedpointer_slot_mask = 0;
    objc_debug_taggedpointer_payload_lshift = 0;
    objc_debug_taggedpointer_payload_rshift = 0;

    objc_debug_taggedpointer_ext_mask = 0;
    objc_debug_taggedpointer_ext_slot_shift = 0;
    objc_debug_taggedpointer_ext_slot_mask = 0;
    objc_debug_taggedpointer_ext_payload_lshift = 0;
    objc_debug_taggedpointer_ext_payload_rshift = 0;
}


// Returns a pointer to the class's storage in the tagged class arrays.
// Assumes the tag is a valid basic tag.
static Class *
classSlotForBasicTagIndex(objc_tag_index_t tag)
{
    uintptr_t tagObfuscator = ((objc_debug_taggedpointer_obfuscator
                                >> _OBJC_TAG_INDEX_SHIFT)
                               & _OBJC_TAG_INDEX_MASK);
    uintptr_t obfuscatedTag = tag ^ tagObfuscator;
    // Array index in objc_tag_classes includes the tagged bit itself
#if SUPPORT_MSB_TAGGED_POINTERS
    return &objc_tag_classes[0x8 | obfuscatedTag];
#else
    return &objc_tag_classes[(obfuscatedTag << 1) | 1];
#endif
}


// Returns a pointer to the class's storage in the tagged class arrays, 
// or nil if the tag is out of range.
static Class *  
classSlotForTagIndex(objc_tag_index_t tag)
{
    if (tag >= OBJC_TAG_First60BitPayload && tag <= OBJC_TAG_Last60BitPayload) {
        return classSlotForBasicTagIndex(tag);
    }

    if (tag >= OBJC_TAG_First52BitPayload && tag <= OBJC_TAG_Last52BitPayload) {
        int index = tag - OBJC_TAG_First52BitPayload;
        uintptr_t tagObfuscator = ((objc_debug_taggedpointer_obfuscator
                                    >> _OBJC_TAG_EXT_INDEX_SHIFT)
                                   & _OBJC_TAG_EXT_INDEX_MASK);
        return &objc_tag_ext_classes[index ^ tagObfuscator];
    }

    return nil;
}

/***********************************************************************
* initializeTaggedPointerObfuscator
* Initialize objc_debug_taggedpointer_obfuscator with randomness.
*
* The tagged pointer obfuscator is intended to make it more difficult
* for an attacker to construct a particular object as a tagged pointer,
* in the presence of a buffer overflow or other write control over some
* memory. The obfuscator is XORed with the tagged pointers when setting
* or retrieving payload values. They are filled with randomness on first
* use.
**********************************************************************/

#ifdef  IS_iOS
static void
initializeTaggedPointerObfuscator(void)
{
    if (sdkIsOlderThan(10_14, 12_0, 12_0, 5_0, 3_0) ||
        // Set the obfuscator to zero for apps linked against older SDKs,
        // in case they're relying on the tagged pointer representation.
        DisableTaggedPointerObfuscation) {
        objc_debug_taggedpointer_obfuscator = 0;
    } else {
        // Pull random data into the variable, then shift away all non-payload bits.
        arc4random_buf(&objc_debug_taggedpointer_obfuscator,
                       sizeof(objc_debug_taggedpointer_obfuscator));
        objc_debug_taggedpointer_obfuscator &= ~_OBJC_TAG_MASK;
    }
}
#else

static void
initializeTaggedPointerObfuscator(void)
{
    if (sdkIsOlderThan(10_14, 12_0, 12_0, 5_0, 3_0) ||
        // Set the obfuscator to zero for apps linked against older SDKs,
        // in case they're relying on the tagged pointer representation.
        DisableTaggedPointerObfuscation) {
        objc_debug_taggedpointer_obfuscator = 0;
    } else {
        // Pull random data into the variable, then shift away all non-payload bits.
        arc4random_buf(&objc_debug_taggedpointer_obfuscator,
                       sizeof(objc_debug_taggedpointer_obfuscator));
        objc_debug_taggedpointer_obfuscator &= ~_OBJC_TAG_MASK;
    }
}

#endif




/***********************************************************************
* _objc_registerTaggedPointerClass
* Set the class to use for the given tagged pointer index.
* Aborts if the tag is out of range, or if the tag is already 
* used by some other class.
**********************************************************************/
void
_objc_registerTaggedPointerClass(objc_tag_index_t tag, Class cls)
{
    if (objc_debug_taggedpointer_mask == 0) {
        _objc_fatal("tagged pointers are disabled");
    }

    Class *slot = classSlotForTagIndex(tag);
    if (!slot) {
        _objc_fatal("tag index %u is invalid", (unsigned int)tag);
    }

    Class oldCls = *slot;
    
    if (cls  &&  oldCls  &&  cls != oldCls) {
        _objc_fatal("tag index %u used for two different classes "
                    "(was %p %s, now %p %s)", tag, 
                    oldCls, oldCls->nameForLogging(), 
                    cls, cls->nameForLogging());
    }

    *slot = cls;

    // Store a placeholder class in the basic tag slot that is 
    // reserved for the extended tag space, if it isn't set already.
    // Do this lazily when the first extended tag is registered so 
    // that old debuggers characterize bogus pointers correctly more often.
    if (tag < OBJC_TAG_First60BitPayload || tag > OBJC_TAG_Last60BitPayload) {
        Class *extSlot = classSlotForBasicTagIndex(OBJC_TAG_RESERVED_7);
        if (*extSlot == nil) {
            extern objc_class OBJC_CLASS_$___NSUnrecognizedTaggedPointer;
            *extSlot = (Class)&OBJC_CLASS_$___NSUnrecognizedTaggedPointer;
        }
    }
}


/***********************************************************************
* _objc_getClassForTag
* Returns the class that is using the given tagged pointer tag.
* Returns nil if no class is using that tag or the tag is out of range.
**********************************************************************/
Class
_objc_getClassForTag(objc_tag_index_t tag)
{
    Class *slot = classSlotForTagIndex(tag);
    if (slot) return *slot;
    else return nil;
}

#endif


#if SUPPORT_FIXUP

OBJC_EXTERN void objc_msgSend_fixup(void);
OBJC_EXTERN void objc_msgSendSuper2_fixup(void);
OBJC_EXTERN void objc_msgSend_stret_fixup(void);
OBJC_EXTERN void objc_msgSendSuper2_stret_fixup(void);
#if defined(__i386__)  ||  defined(__x86_64__)
OBJC_EXTERN void objc_msgSend_fpret_fixup(void);
#endif
#if defined(__x86_64__)
OBJC_EXTERN void objc_msgSend_fp2ret_fixup(void);
#endif

OBJC_EXTERN void objc_msgSend_fixedup(void);
OBJC_EXTERN void objc_msgSendSuper2_fixedup(void);
OBJC_EXTERN void objc_msgSend_stret_fixedup(void);
OBJC_EXTERN void objc_msgSendSuper2_stret_fixedup(void);
#if defined(__i386__)  ||  defined(__x86_64__)
OBJC_EXTERN void objc_msgSend_fpret_fixedup(void);
#endif
#if defined(__x86_64__)
OBJC_EXTERN void objc_msgSend_fp2ret_fixedup(void);
#endif

/***********************************************************************
* fixupMessageRef
* Repairs an old vtable dispatch call site. 
* vtable dispatch itself is not supported.
**********************************************************************/
static void 
fixupMessageRef(message_ref_t *msg)
{    
    msg->sel = sel_registerName((const char *)msg->sel);

    if (msg->imp == &objc_msgSend_fixup) { 
        if (msg->sel == SEL_alloc) {
            msg->imp = (IMP)&objc_alloc;
        } else if (msg->sel == SEL_allocWithZone) {
            msg->imp = (IMP)&objc_allocWithZone;
        } else if (msg->sel == SEL_retain) {
            msg->imp = (IMP)&objc_retain;
        } else if (msg->sel == SEL_release) {
            msg->imp = (IMP)&objc_release;
        } else if (msg->sel == SEL_autorelease) {
            msg->imp = (IMP)&objc_autorelease;
        } else {
            msg->imp = &objc_msgSend_fixedup;
        }
    } 
    else if (msg->imp == &objc_msgSendSuper2_fixup) { 
        msg->imp = &objc_msgSendSuper2_fixedup;
    } 
    else if (msg->imp == &objc_msgSend_stret_fixup) { 
        msg->imp = &objc_msgSend_stret_fixedup;
    } 
    else if (msg->imp == &objc_msgSendSuper2_stret_fixup) { 
        msg->imp = &objc_msgSendSuper2_stret_fixedup;
    } 
#if defined(__i386__)  ||  defined(__x86_64__)
    else if (msg->imp == &objc_msgSend_fpret_fixup) { 
        msg->imp = &objc_msgSend_fpret_fixedup;
    } 
#endif
#if defined(__x86_64__)
    else if (msg->imp == &objc_msgSend_fp2ret_fixup) { 
        msg->imp = &objc_msgSend_fp2ret_fixedup;
    } 
#endif
}

// SUPPORT_FIXUP
#endif


// ProKit SPI
static Class setSuperclass(Class cls, Class newSuper)
{
    Class oldSuper;

    runtimeLock.assertLocked();

    assert(cls->isRealized());
    assert(newSuper->isRealized());

    oldSuper = cls->superclass;
    removeSubclass(oldSuper, cls);
    removeSubclass(oldSuper->ISA(), cls->ISA());

    cls->superclass = newSuper;
    cls->ISA()->superclass = newSuper->ISA();
    addSubclass(newSuper, cls);
    addSubclass(newSuper->ISA(), cls->ISA());

    // Flush subclass's method caches.
    flushCaches(cls);
    flushCaches(cls->ISA());
    
    return oldSuper;
}


Class class_setSuperclass(Class cls, Class newSuper)
{
    mutex_locker_t lock(runtimeLock);
    return setSuperclass(cls, newSuper);
}


// __OBJC2__
#endif
