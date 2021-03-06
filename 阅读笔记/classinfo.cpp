#ifndef __OBJC2__
#define __OBJC2__
#endif
struct objc_selector; struct objc_class;
struct __rw_objc_super { 
	struct objc_object *object; 
	struct objc_object *superClass; 
	__rw_objc_super(struct objc_object *o, struct objc_object *s) : object(o), superClass(s) {} 
};
#ifndef _REWRITER_typedef_Protocol
typedef struct objc_object Protocol;
#define _REWRITER_typedef_Protocol
#endif
#define __OBJC_RW_DLLIMPORT extern
__OBJC_RW_DLLIMPORT void objc_msgSend(void);
__OBJC_RW_DLLIMPORT void objc_msgSendSuper(void);
__OBJC_RW_DLLIMPORT void objc_msgSend_stret(void);
__OBJC_RW_DLLIMPORT void objc_msgSendSuper_stret(void);
__OBJC_RW_DLLIMPORT void objc_msgSend_fpret(void);
__OBJC_RW_DLLIMPORT struct objc_class *objc_getClass(const char *);
__OBJC_RW_DLLIMPORT struct objc_class *class_getSuperclass(struct objc_class *);
__OBJC_RW_DLLIMPORT struct objc_class *objc_getMetaClass(const char *);
__OBJC_RW_DLLIMPORT void objc_exception_throw( struct objc_object *);
__OBJC_RW_DLLIMPORT int objc_sync_enter( struct objc_object *);
__OBJC_RW_DLLIMPORT int objc_sync_exit( struct objc_object *);
__OBJC_RW_DLLIMPORT Protocol *objc_getProtocol(const char *);
#ifdef _WIN64
typedef unsigned long long  _WIN_NSUInteger;
#else
typedef unsigned int _WIN_NSUInteger;
#endif
#ifndef __FASTENUMERATIONSTATE
struct __objcFastEnumerationState {
	unsigned long state;
	void **itemsPtr;
	unsigned long *mutationsPtr;
	unsigned long extra[5];
};
__OBJC_RW_DLLIMPORT void objc_enumerationMutation(struct objc_object *);
#define __FASTENUMERATIONSTATE
#endif
#ifndef __NSCONSTANTSTRINGIMPL
struct __NSConstantStringImpl {
  int *isa;
  int flags;
  char *str;
#if _WIN64
  long long length;
#else
  long length;
#endif
};
#ifdef CF_EXPORT_CONSTANT_STRING
extern "C" __declspec(dllexport) int __CFConstantStringClassReference[];
#else
__OBJC_RW_DLLIMPORT int __CFConstantStringClassReference[];
#endif
#define __NSCONSTANTSTRINGIMPL
#endif
#ifndef BLOCK_IMPL
#define BLOCK_IMPL
struct __block_impl {
  void *isa;
  int Flags;
  int Reserved;
  void *FuncPtr;
};
// Runtime copy/destroy helper functions (from Block_private.h)
#ifdef __OBJC_EXPORT_BLOCKS
extern "C" __declspec(dllexport) void _Block_object_assign(void *, const void *, const int);
extern "C" __declspec(dllexport) void _Block_object_dispose(const void *, const int);
extern "C" __declspec(dllexport) void *_NSConcreteGlobalBlock[32];
extern "C" __declspec(dllexport) void *_NSConcreteStackBlock[32];
#else
__OBJC_RW_DLLIMPORT void _Block_object_assign(void *, const void *, const int);
__OBJC_RW_DLLIMPORT void _Block_object_dispose(const void *, const int);
__OBJC_RW_DLLIMPORT void *_NSConcreteGlobalBlock[32];
__OBJC_RW_DLLIMPORT void *_NSConcreteStackBlock[32];
#endif
#endif
#define __block
#define __weak

#include <stdarg.h>
struct __NSContainer_literal {
  void * *arr;
  __NSContainer_literal (unsigned int count, ...) {
	va_list marker;
	va_start(marker, count);
	arr = new void *[count];
	for (unsigned i = 0; i < count; i++)
	  arr[i] = va_arg(marker, void *);
	va_end( marker );
  };
  ~__NSContainer_literal() {
	delete[] arr;
  }
};
extern "C" __declspec(dllimport) void * objc_autoreleasePoolPush(void);
extern "C" __declspec(dllimport) void objc_autoreleasePoolPop(void *);

struct __AtAutoreleasePool {
  __AtAutoreleasePool() {atautoreleasepoolobj = objc_autoreleasePoolPush();}
  ~__AtAutoreleasePool() {objc_autoreleasePoolPop(atautoreleasepoolobj);}
  void * atautoreleasepoolobj;
};

#define __OFFSETOFIVAR__(TYPE, MEMBER) ((long long) &((TYPE *)0)->MEMBER)
static __NSConstantStringImpl __NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_ClassInfo_a9184a_mi_0 __attribute__ ((section ("__DATA, __cfstring"))) = {__CFConstantStringClassReference,0x000007c8,"",0};
static __NSConstantStringImpl __NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_ClassInfo_a9184a_mi_1 __attribute__ ((section ("__DATA, __cfstring"))) = {__CFConstantStringClassReference,0x000007c8,"",0};


typedef signed char __int8_t;

typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
typedef int __darwin_ct_rune_t;

typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;

typedef long int __darwin_ptrdiff_t;

typedef long unsigned int __darwin_size_t;

typedef __builtin_va_list __darwin_va_list;

typedef int __darwin_wchar_t;

typedef __darwin_wchar_t __darwin_rune_t;

typedef int __darwin_wint_t;

typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef int64_t register_t;

typedef __darwin_intptr_t intptr_t;
typedef unsigned long uintptr_t;

typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;
typedef u_int64_t syscall_arg_t;
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;

typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];

struct __darwin_pthread_handler_rec {
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};

struct _opaque_pthread_attr_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_cond_t {
 long __sig;
 char __opaque[40];
};

struct _opaque_pthread_condattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_mutex_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_mutexattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_once_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_rwlock_t {
 long __sig;
 char __opaque[192];
};

struct _opaque_pthread_rwlockattr_t {
 long __sig;
 char __opaque[16];
};

struct _opaque_pthread_t {
 long __sig;
 struct __darwin_pthread_handler_rec *__cleanup_stack;
 char __opaque[8176];
};

typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;
typedef long int intmax_t;
typedef long unsigned int uintmax_t;

static __inline__
uint16_t
_OSSwapInt16(
 uint16_t data
 )
{

 return (uint16_t)(data << 8 | data >> 8);
}

static __inline__
uint32_t
_OSSwapInt32(
 uint32_t data
 )
{
 data = __builtin_bswap32(data);

 return data;
}

static __inline__
uint64_t
_OSSwapInt64(
 uint64_t data
 )
{

 return __builtin_bswap64(data);
}

static __inline__
uint16_t
OSReadSwapInt16(
 const volatile void * base,
 uintptr_t offset
 )
{
 uint16_t result;

 result = *(volatile uint16_t *)((volatile uintptr_t)base + offset);
 return _OSSwapInt16(result);
}

static __inline__
uint32_t
OSReadSwapInt32(
 const volatile void * base,
 uintptr_t offset
 )
{
 uint32_t result;

 result = *(volatile uint32_t *)((volatile uintptr_t)base + offset);
 return _OSSwapInt32(result);
}

static __inline__
uint64_t
OSReadSwapInt64(
 const volatile void * base,
 uintptr_t offset
 )
{
 volatile uint32_t * inp;
 union ullc {
  uint64_t ull;
  uint32_t ul[2];
 } outv;

 inp = (volatile uint32_t *)((volatile uintptr_t)base + offset);
 outv.ul[0] = inp[1];
 outv.ul[1] = inp[0];
 outv.ul[0] = _OSSwapInt32(outv.ul[0]);
 outv.ul[1] = _OSSwapInt32(outv.ul[1]);
 return outv.ull;
}

static __inline__
void
OSWriteSwapInt16(
 volatile void * base,
 uintptr_t offset,
 uint16_t data
 )
{
 *(volatile uint16_t *)((volatile uintptr_t)base + offset) = _OSSwapInt16(data);
}

static __inline__
void
OSWriteSwapInt32(
 volatile void * base,
 uintptr_t offset,
 uint32_t data
 )
{
 *(volatile uint32_t *)((volatile uintptr_t)base + offset) = _OSSwapInt32(data);
}

static __inline__
void
OSWriteSwapInt64(
 volatile void * base,
 uintptr_t offset,
 uint64_t data
 )
{
 *(volatile uint64_t *)((volatile uintptr_t)base + offset) = _OSSwapInt64(data);
}

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

typedef unsigned long u_long;

typedef unsigned short ushort;
typedef unsigned int uint;

typedef u_int64_t u_quad_t;
typedef int64_t quad_t;
typedef quad_t * qaddr_t;

typedef char * caddr_t;

typedef int32_t daddr_t;

typedef __darwin_dev_t dev_t;

typedef u_int32_t fixpt_t;

typedef __darwin_blkcnt_t blkcnt_t;
typedef __darwin_blksize_t blksize_t;
typedef __darwin_gid_t gid_t;
typedef __uint32_t in_addr_t;
typedef __uint16_t in_port_t;
typedef __darwin_ino_t ino_t;

typedef __darwin_ino64_t ino64_t;

typedef __int32_t key_t;
typedef __darwin_mode_t mode_t;
typedef __uint16_t nlink_t;
typedef __darwin_id_t id_t;
typedef __darwin_pid_t pid_t;
typedef __darwin_off_t off_t;

typedef int32_t segsz_t;
typedef int32_t swblk_t;


typedef __darwin_uid_t uid_t;
static inline __int32_t
major(__uint32_t _x)
{
 return (__int32_t)(((__uint32_t)_x >> 24) & 0xff);
}

static inline __int32_t
minor(__uint32_t _x)
{
 return (__int32_t)((_x) & 0xffffff);
}

static inline dev_t
makedev(__uint32_t _major, __uint32_t _minor)
{
 return (dev_t)(((_major) << 24) | (_minor));
}
typedef __darwin_clock_t clock_t;
typedef __darwin_size_t size_t;
typedef __darwin_ssize_t ssize_t;
typedef __darwin_time_t time_t;

typedef __darwin_useconds_t useconds_t;
typedef __darwin_suseconds_t suseconds_t;

typedef __darwin_size_t rsize_t;
typedef int errno_t;

extern "C" {
typedef struct fd_set {
 __int32_t fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;
}

static inline int
__darwin_fd_isset(int _n, const struct fd_set *_p)
{
 return _p->fds_bits[(unsigned long)_n / (sizeof(__int32_t) * 8)] & ((__int32_t)(((unsigned long)1) << ((unsigned long)_n % (sizeof(__int32_t) * 8))));
}

typedef __int32_t fd_mask;

typedef __darwin_pthread_attr_t pthread_attr_t;
typedef __darwin_pthread_cond_t pthread_cond_t;
typedef __darwin_pthread_condattr_t pthread_condattr_t;
typedef __darwin_pthread_mutex_t pthread_mutex_t;
typedef __darwin_pthread_mutexattr_t pthread_mutexattr_t;
typedef __darwin_pthread_once_t pthread_once_t;
typedef __darwin_pthread_rwlock_t pthread_rwlock_t;
typedef __darwin_pthread_rwlockattr_t pthread_rwlockattr_t;
typedef __darwin_pthread_t pthread_t;

typedef __darwin_pthread_key_t pthread_key_t;

typedef __darwin_fsblkcnt_t fsblkcnt_t;
typedef __darwin_fsfilcnt_t fsfilcnt_t;

typedef struct objc_class *Class;

struct objc_object {
    Class _Nonnull isa __attribute__((deprecated));
};

typedef struct objc_object *id;

typedef struct objc_selector *SEL;

typedef void (*IMP)(void );
    typedef bool BOOL;
extern "C" __attribute__((visibility("default"))) const char * _Nonnull sel_getName(SEL _Nonnull sel)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
extern "C" __attribute__((visibility("default"))) SEL _Nonnull sel_registerName(const char * _Nonnull str)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
extern "C" __attribute__((visibility("default"))) const char * _Nonnull object_getClassName(id _Nullable obj)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
extern "C" __attribute__((visibility("default"))) void * _Nullable object_getIndexedIvars(id _Nullable obj)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)))
                        ;
extern "C" __attribute__((visibility("default"))) BOOL sel_isMapped(SEL _Nonnull sel)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
extern "C" __attribute__((visibility("default"))) SEL _Nonnull sel_getUid(const char * _Nonnull str)
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));

typedef const void* objc_objectptr_t;

extern "C" __attribute__((visibility("default"))) id _Nullable objc_retainedObject(objc_objectptr_t _Nullable obj)

    __attribute__((unavailable("use CFBridgingRelease() or a (__bridge_transfer id) cast instead")))

    ;
extern "C" __attribute__((visibility("default"))) id _Nullable objc_unretainedObject(objc_objectptr_t _Nullable obj)

    __attribute__((unavailable("use a (__bridge id) cast instead")))

    ;
extern "C" __attribute__((visibility("default"))) objc_objectptr_t _Nullable objc_unretainedPointer(id _Nullable obj)

    __attribute__((unavailable("use a __bridge cast instead")))

    ;
typedef long NSInteger;
typedef unsigned long NSUInteger;

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_NSMethodSignature
#define _REWRITER_typedef_NSMethodSignature
typedef struct objc_object NSMethodSignature;
typedef struct {} _objc_exc_NSMethodSignature;
#endif

#ifndef _REWRITER_typedef_NSInvocation
#define _REWRITER_typedef_NSInvocation
typedef struct objc_object NSInvocation;
typedef struct {} _objc_exc_NSInvocation;
#endif


__attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)))
__attribute__((objc_root_class))
extern "C" __attribute__((visibility("default")))

#ifndef _REWRITER_typedef_NSObject
#define _REWRITER_typedef_NSObject
typedef struct objc_object NSObject;
typedef struct {} _objc_exc_NSObject;
#endif

struct NSObject_IMPL {
	Class isa;
};

#if 0
- (instancetype)init

    __attribute__((objc_designated_initializer))

    ;
#endif

typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;

#pragma clang assume_nonnull begin

extern "C" double NSFoundationVersionNumber;
// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_Protocol
#define _REWRITER_typedef_Protocol
typedef struct objc_object Protocol;
typedef struct {} _objc_exc_Protocol;
#endif


typedef NSString * NSExceptionName __attribute__((swift_wrapper(struct)));
typedef NSString * NSRunLoopMode __attribute__((swift_wrapper(struct)));

extern "C" NSString *NSStringFromSelector(SEL aSelector);
extern "C" SEL NSSelectorFromString(NSString *aSelectorName);

extern "C" NSString *NSStringFromClass(Class aClass);
extern "C" Class _Nullable NSClassFromString(NSString *aClassName);

extern "C" NSString *NSStringFromProtocol(Protocol *proto) __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" Protocol * _Nullable NSProtocolFromString(NSString *namestr) __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" const char *NSGetSizeAndAlignment(const char *typePtr, NSUInteger * _Nullable sizep, NSUInteger * _Nullable alignp);

extern "C" void NSLog(NSString *format, ...) __attribute__((format(__NSString__, 1, 2))) __attribute__((not_tail_called));
extern "C" void NSLogv(NSString *format, va_list args) __attribute__((format(__NSString__, 1, 0))) __attribute__((not_tail_called));
typedef NSInteger NSComparisonResult; enum {
    NSOrderedAscending = -1L,
    NSOrderedSame,
    NSOrderedDescending
};


typedef NSComparisonResult (*NSComparator)(id obj1, id obj2);


typedef NSUInteger NSEnumerationOptions; enum {
    NSEnumerationConcurrent = (1UL << 0),
    NSEnumerationReverse = (1UL << 1),
};

typedef NSUInteger NSSortOptions; enum {
    NSSortConcurrent = (1UL << 0),
    NSSortStable = (1UL << 4),
};

typedef NSInteger NSQualityOfService; enum {
    NSQualityOfServiceUserInteractive = 0x21,
    NSQualityOfServiceUserInitiated = 0x19,
    NSQualityOfServiceUtility = 0x11,
    NSQualityOfServiceBackground = 0x09,
    NSQualityOfServiceDefault = -1
} __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

static const NSInteger NSNotFound = 9223372036854775807L;
#pragma clang assume_nonnull end

extern "C" {

extern "C" void *_Block_copy(const void *aBlock)
    __attribute__((availability(ios,introduced=3.2)));


extern "C" void _Block_release(const void *aBlock)
    __attribute__((availability(ios,introduced=3.2)));



extern "C" void _Block_object_assign(void *, const void *, const int)
    __attribute__((availability(ios,introduced=3.2)));


extern "C" void _Block_object_dispose(const void *, const int)
    __attribute__((availability(ios,introduced=3.2)));


extern "C" void * _NSConcreteGlobalBlock[32]
    __attribute__((availability(ios,introduced=3.2)));
extern "C" void * _NSConcreteStackBlock[32]
    __attribute__((availability(ios,introduced=3.2)));

}

extern "C" {


#pragma pack(push, 2)
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef unsigned short UInt16;
typedef signed short SInt16;


typedef unsigned int UInt32;
typedef signed int SInt32;
struct wide {
  UInt32 lo;
  SInt32 hi;
};
typedef struct wide wide;
struct UnsignedWide {
  UInt32 lo;
  UInt32 hi;
};
typedef struct UnsignedWide UnsignedWide;
      typedef signed long long SInt64;
        typedef unsigned long long UInt64;
typedef SInt32 Fixed;
typedef Fixed * FixedPtr;
typedef SInt32 Fract;
typedef Fract * FractPtr;
typedef UInt32 UnsignedFixed;
typedef UnsignedFixed * UnsignedFixedPtr;
typedef short ShortFixed;
typedef ShortFixed * ShortFixedPtr;
typedef float Float32;
typedef double Float64;
struct Float80 {
    SInt16 exp;
    UInt16 man[4];
};
typedef struct Float80 Float80;

struct Float96 {
    SInt16 exp[2];
    UInt16 man[4];
};
typedef struct Float96 Float96;
struct Float32Point {
    Float32 x;
    Float32 y;
};
typedef struct Float32Point Float32Point;
typedef char * Ptr;
typedef Ptr * Handle;
typedef long Size;
typedef SInt16 OSErr;
typedef SInt32 OSStatus;
typedef void * LogicalAddress;
typedef const void * ConstLogicalAddress;
typedef void * PhysicalAddress;
typedef UInt8 * BytePtr;
typedef unsigned long ByteCount;
typedef unsigned long ByteOffset;
typedef SInt32 Duration;
typedef UnsignedWide AbsoluteTime;
typedef UInt32 OptionBits;
typedef unsigned long ItemCount;
typedef UInt32 PBVersion;
typedef SInt16 ScriptCode;
typedef SInt16 LangCode;
typedef SInt16 RegionCode;
typedef UInt32 FourCharCode;
typedef FourCharCode OSType;
typedef FourCharCode ResType;
typedef OSType * OSTypePtr;
typedef ResType * ResTypePtr;
typedef unsigned char Boolean;
typedef long ( * ProcPtr)(void);
typedef void ( * Register68kProcPtr)(void);

typedef ProcPtr UniversalProcPtr;


typedef ProcPtr * ProcHandle;
typedef UniversalProcPtr * UniversalProcHandle;
typedef void * PRefCon;

typedef void * URefCon;
typedef void * SRefCon;
enum {
  noErr = 0
};

enum {
  kNilOptions = 0
};


enum {
  kVariableLengthArray

  __attribute__((deprecated))

  = 1
};

enum {
  kUnknownType = 0x3F3F3F3F
};
typedef UInt32 UnicodeScalarValue;
typedef UInt32 UTF32Char;
typedef UInt16 UniChar;
typedef UInt16 UTF16Char;
typedef UInt8 UTF8Char;
typedef UniChar * UniCharPtr;
typedef unsigned long UniCharCount;
typedef UniCharCount * UniCharCountPtr;
typedef unsigned char Str255[256];
typedef unsigned char Str63[64];
typedef unsigned char Str32[33];
typedef unsigned char Str31[32];
typedef unsigned char Str27[28];
typedef unsigned char Str15[16];
typedef unsigned char Str32Field[34];
typedef Str63 StrFileName;
typedef unsigned char * StringPtr;
typedef StringPtr * StringHandle;
typedef const unsigned char * ConstStringPtr;
typedef const unsigned char * ConstStr255Param;
typedef const unsigned char * ConstStr63Param;
typedef const unsigned char * ConstStr32Param;
typedef const unsigned char * ConstStr31Param;
typedef const unsigned char * ConstStr27Param;
typedef const unsigned char * ConstStr15Param;
typedef ConstStr63Param ConstStrFileNameParam;

inline unsigned char StrLength(ConstStr255Param string) { return (*string); }
struct ProcessSerialNumber {
  UInt32 highLongOfPSN;
  UInt32 lowLongOfPSN;
};
typedef struct ProcessSerialNumber ProcessSerialNumber;
typedef ProcessSerialNumber * ProcessSerialNumberPtr;
struct Point {
  short v;
  short h;
};
typedef struct Point Point;
typedef Point * PointPtr;
struct Rect {
  short top;
  short left;
  short bottom;
  short right;
};
typedef struct Rect Rect;
typedef Rect * RectPtr;
struct FixedPoint {
  Fixed x;
  Fixed y;
};
typedef struct FixedPoint FixedPoint;
struct FixedRect {
  Fixed left;
  Fixed top;
  Fixed right;
  Fixed bottom;
};
typedef struct FixedRect FixedRect;

typedef short CharParameter;
enum {
  normal = 0,
  bold = 1,
  italic = 2,
  underline = 4,
  outline = 8,
  shadow = 0x10,
  condense = 0x20,
  extend = 0x40
};

typedef unsigned char Style;
typedef short StyleParameter;
typedef Style StyleField;
typedef SInt32 TimeValue;
typedef SInt32 TimeScale;
typedef wide CompTimeValue;
typedef SInt64 TimeValue64;
typedef struct TimeBaseRecord* TimeBase;
struct TimeRecord {
  CompTimeValue value;
  TimeScale scale;
  TimeBase base;
};
typedef struct TimeRecord TimeRecord;
struct NumVersion {

  UInt8 nonRelRev;
  UInt8 stage;
  UInt8 minorAndBugRev;
  UInt8 majorRev;
};
typedef struct NumVersion NumVersion;


enum {

  developStage = 0x20,
  alphaStage = 0x40,
  betaStage = 0x60,
  finalStage = 0x80
};

union NumVersionVariant {

  NumVersion parts;
  UInt32 whole;
};
typedef union NumVersionVariant NumVersionVariant;
typedef NumVersionVariant * NumVersionVariantPtr;
typedef NumVersionVariantPtr * NumVersionVariantHandle;
struct VersRec {

  NumVersion numericVersion;
  short countryCode;
  Str255 shortVersion;
  Str255 reserved;
};
typedef struct VersRec VersRec;
typedef VersRec * VersRecPtr;
typedef VersRecPtr * VersRecHndl;

typedef UInt8 Byte;
typedef SInt8 SignedByte;
typedef wide * WidePtr;
typedef UnsignedWide * UnsignedWidePtr;
typedef Float80 extended80;
typedef Float96 extended96;
typedef SInt8 VHSelect;
extern void
Debugger(void) __attribute__((availability(ios,unavailable)));
extern void
DebugStr(ConstStr255Param debuggerMsg) __attribute__((availability(ios,unavailable)));
extern void
SysBreak(void) __attribute__((availability(ios,unavailable)));
extern void
SysBreakStr(ConstStr255Param debuggerMsg) __attribute__((availability(ios,unavailable)));
extern void
SysBreakFunc(ConstStr255Param debuggerMsg) __attribute__((availability(ios,unavailable)));
#pragma pack(pop)


}

/*
 
 extern "C" 的作用是为了能够正确在 C++ 代码中调用 C 语言代码。
 加上 extern "C" 后指示编译器按 C 编译器编译这部分代码。
 使用它的本质的原因是 C++ 函数重载，C++ 中函数重载在编译后生成的不止是函数名，也会带上参数类型。而 C 编译器编译函数时不会带上函数的参数类型。
 
 
 // MyMath.c / MyMath.cpp 实现文件
 int add(int a, int b) { return a + b; }
 
 clang -S MyMath.c
    add 编译成了 _add
 
 clang -S MyMath.cpp
    add 编译成了 __Z3addii
 
 在MyMath.c的情况下
 如果在main.cpp 直接#include "MyMath.h"， 编译
    clang++ -S main.cpp -o main.s
 这时候链接时它要找的是 __Z3addii 函数，而我们编译MyMath.c生成的是 _add。 这就会导致错误了
 
 如果在main.cpp中使用 extern "C" { #include "MyMath.h" }，编译
    clang++ -S main.cpp -o main.s
 这时候链接时它找的是 _add 函数
 
 这就相当于extern "C"{}告诉编译器在编译main.cpp时 extern "C"{}内的符号是按照c的风格编译的，
 所以在编译main.cpp引入时需要按照c 的风格引入 _add
 
 */

extern "C" unsigned long OBJC_IVAR_$_Person$_height;
extern "C" unsigned long OBJC_IVAR_$_Person$_weight;

/*
 在这里将Person 类转成Person_IMPL 结构体的目的应该是用来计算类对象应该需要申请多少内存空间
 _class_ro_t 中有instanceSize 变量用来在 alloc 是指定申请的内存空间大小，所以在实例化_class_ro_t 变量时通过
 sizeof(struct Person_IMPL),来初始化_class_ro_t 中的 instanceSize
 */
struct Person_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	int father_var_loves;
	NSInteger _height;
	NSInteger _weight;
};

static void _C_Person_fatherClsFunc_Cry(Class self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_ClassInfo_a9184a_mi_0);
}

static void _I_Person_fatherInstanceFunc_walk(Person * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_ClassInfo_a9184a_mi_1);
}


static NSInteger _I_Person_height(Person * self, SEL _cmd) { return (*(NSInteger *)((char *)self + OBJC_IVAR_$_Person$_height)); }
static void _I_Person_setHeight_(Person * self, SEL _cmd, NSInteger height) { (*(NSInteger *)((char *)self + OBJC_IVAR_$_Person$_height)) = height; }

static NSInteger _I_Person_weight(Person * self, SEL _cmd) { return (*(NSInteger *)((char *)self + OBJC_IVAR_$_Person$_weight)); }
static void _I_Person_setWeight_(Person * self, SEL _cmd, NSInteger weight) { (*(NSInteger *)((char *)self + OBJC_IVAR_$_Person$_weight)) = weight; }
// @end


#ifndef _REWRITER_typedef_Man
#define _REWRITER_typedef_Man
typedef struct objc_object Man;
typedef struct {} _objc_exc_Man;
#endif

extern "C" unsigned long OBJC_IVAR_$_Man$_name;
extern "C" unsigned long OBJC_IVAR_$_Man$_phone;
extern "C" unsigned long OBJC_IVAR_$_Man$_extention_Age;
struct Man_IMPL {
	struct Person_IMPL Person_IVARS;
	int private_Money;
	int extention_var_Age;
	NSString *_name;
	NSString *_phone;
	NSInteger _extention_Age;
};

// @property(nonatomic, copy) NSString *name;
// @property(nonatomic, copy) NSString *phone;

// + (void)clsFunc_DoWork;
// - (void)instanceFunc_PlayFootball;

/* @end */


/** interface Man()
{
    int extention_var_Age;
**/ 
// @property(nonatomic, assign) NSInteger extention_Age;

/* @end */


// @implementation Man


static void _C_Man_clsFunc_DoWork(Class self, SEL _cmd) {

}

static void _I_Man_instanceFunc_PlayFootball(Man * self, SEL _cmd) {

}


static NSString * _I_Man_name(Man * self, SEL _cmd) { return (*(NSString **)((char *)self + OBJC_IVAR_$_Man$_name)); }
extern "C" __declspec(dllimport) void objc_setProperty (id, SEL, long, id, bool, bool);

/*
 #define __OFFSETOFIVAR__(TYPE, MEMBER) ((long long) &((TYPE *)0)->MEMBER)
 */
static void _I_Man_setName_(Man * self, SEL _cmd, NSString *name) { objc_setProperty (self, _cmd, __OFFSETOFIVAR__(struct Man, _name), (id)name, 0, 1); }

static NSString * _I_Man_phone(Man * self, SEL _cmd) { return (*(NSString **)((char *)self + OBJC_IVAR_$_Man$_phone)); }
static void _I_Man_setPhone_(Man * self, SEL _cmd, NSString *phone) { objc_setProperty (self, _cmd, __OFFSETOFIVAR__(struct Man, _phone), (id)phone, 0, 1); }

static NSInteger _I_Man_extention_Age(Man * self, SEL _cmd) { return (*(NSInteger *)((char *)self + OBJC_IVAR_$_Man$_extention_Age)); }
static void _I_Man_setExtention_Age_(Man * self, SEL _cmd, NSInteger extention_Age) { (*(NSInteger *)((char *)self + OBJC_IVAR_$_Man$_extention_Age)) = extention_Age; }
// @end

// @interface Man(Ex)

// @property(nonatomic, copy) NSString *category_address;

// + (void)categoryClsFunc_DoWork;
// - (void)categoryInstanceFunc_PlayFootball;

/* @end */


// @implementation Man(Ex)


static void _C_Man_Ex_categoryClsFunc_DoWork(Class self, SEL _cmd) {

}

static void _I_Man_Ex_categoryInstanceFunc_PlayFootball(Man * self, SEL _cmd) {

}

// @end

struct _prop_t {
	const char *name;
	const char *attributes;
};

struct _protocol_t;

struct _objc_method {
	struct objc_selector * _cmd;
	const char *method_type;
	void  *_imp;
};

struct _protocol_t {
	void * isa;  // NULL
	const char *protocol_name;
	const struct _protocol_list_t * protocol_list; // super protocols
	const struct method_list_t *instance_methods;
	const struct method_list_t *class_methods;
	const struct method_list_t *optionalInstanceMethods;
	const struct method_list_t *optionalClassMethods;
	const struct _prop_list_t * properties;
	const unsigned int size;  // sizeof(struct _protocol_t)
	const unsigned int flags;  // = 0
	const char ** extendedMethodTypes;
};

struct _ivar_t {
	unsigned long int *offset;  // pointer to ivar offset location
	const char *name;
	const char *type;
	unsigned int alignment;
	unsigned int  size;
};

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

struct _category_t {
	const char *name;
	struct _class_t *cls;
	const struct _method_list_t *instance_methods;
	const struct _method_list_t *class_methods;
	const struct _protocol_list_t *protocols;
	const struct _prop_list_t *properties;
};
extern "C" __declspec(dllimport) struct objc_cache _objc_empty_cache;
#pragma warning(disable:4273)

extern "C" unsigned long int OBJC_IVAR_$_Person$father_var_loves __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Person, father_var_loves);
extern "C" unsigned long int OBJC_IVAR_$_Person$_height __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Person, _height);
extern "C" unsigned long int OBJC_IVAR_$_Person$_weight __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Person, _weight);

static struct /*_ivar_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count;
	struct _ivar_t ivar_list[3];
} _OBJC_$_INSTANCE_VARIABLES_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_ivar_t),
	3,
	{{(unsigned long int *)&OBJC_IVAR_$_Person$father_var_loves, "father_var_loves", "i", 2, 4},
	 {(unsigned long int *)&OBJC_IVAR_$_Person$_height, "_height", "q", 3, 8},
	 {(unsigned long int *)&OBJC_IVAR_$_Person$_weight, "_weight", "q", 3, 8}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[5];
} _OBJC_$_INSTANCE_METHODS_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	5,
	{{(struct objc_selector *)"fatherInstanceFunc_walk", "v16@0:8", (void *)_I_Person_fatherInstanceFunc_walk},
	{(struct objc_selector *)"height", "q16@0:8", (void *)_I_Person_height},
	{(struct objc_selector *)"setHeight:", "v24@0:8q16", (void *)_I_Person_setHeight_},
	{(struct objc_selector *)"weight", "q16@0:8", (void *)_I_Person_weight},
	{(struct objc_selector *)"setWeight:", "v24@0:8q16", (void *)_I_Person_setWeight_}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CLASS_METHODS_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"fatherClsFunc_Cry", "v16@0:8", (void *)_C_Person_fatherClsFunc_Cry}}
};

static struct /*_prop_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count_of_properties;
	struct _prop_t prop_list[2];
} _OBJC_$_PROP_LIST_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_prop_t),
	2,
	{{"height","Tq,N,V_height"},
	{"weight","Tq,N,V_weight"}}
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	1, sizeof(struct _class_t), sizeof(struct _class_t), 
	0, 
	"Person",
	(const struct _method_list_t *)&_OBJC_$_CLASS_METHODS_Person,
	0, 
	0, 
	0, 
	0, 
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	0,
    __OFFSETOFIVAR__(struct Person, father_var_loves),
    /*
     sizeof() 是一个运算符，并不是一个函数。sizeof() 传进来的是类型，用来计算这个类型占多大内存，
     这个在 编译器编译阶段 就会确定大小并直接转化成 8 、16 、24 这样的常数，而不是在运行时计算。参数可以是数组、指针、类型、对象、结构体、函数等。
     */
    sizeof(struct Person_IMPL),
	0, 
	"Person",
	(const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Person,
	0, 
	(const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Person,
	0, 
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Person,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Person __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_NSObject,
	0, // &OBJC_METACLASS_$_NSObject,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_METACLASS_RO_$_Person,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_CLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Person __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_Person,
	0, // &OBJC_CLASS_$_NSObject,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_CLASS_RO_$_Person,
};
static void OBJC_CLASS_SETUP_$_Person(void ) {
	OBJC_METACLASS_$_Person.isa = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Person.superclass = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Person.cache = &_objc_empty_cache;
	OBJC_CLASS_$_Person.isa = &OBJC_METACLASS_$_Person;
	OBJC_CLASS_$_Person.superclass = &OBJC_CLASS_$_NSObject;
	OBJC_CLASS_$_Person.cache = &_objc_empty_cache;
}

extern "C" unsigned long int OBJC_IVAR_$_Man$private_Money __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, private_Money);
extern "C" unsigned long int OBJC_IVAR_$_Man$extention_var_Age __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, extention_var_Age);
extern "C" unsigned long int OBJC_IVAR_$_Man$_name __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, _name);
extern "C" unsigned long int OBJC_IVAR_$_Man$_phone __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, _phone);
extern "C" unsigned long int OBJC_IVAR_$_Man$_extention_Age __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, _extention_Age);

static struct /*_ivar_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count;
	struct _ivar_t ivar_list[5];
} _OBJC_$_INSTANCE_VARIABLES_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_ivar_t),
	5,
	{{(unsigned long int *)&OBJC_IVAR_$_Man$private_Money, "private_Money", "i", 2, 4},
	 {(unsigned long int *)&OBJC_IVAR_$_Man$extention_var_Age, "extention_var_Age", "i", 2, 4},
	 {(unsigned long int *)&OBJC_IVAR_$_Man$_name, "_name", "@\"NSString\"", 3, 8},
	 {(unsigned long int *)&OBJC_IVAR_$_Man$_phone, "_phone", "@\"NSString\"", 3, 8},
	 {(unsigned long int *)&OBJC_IVAR_$_Man$_extention_Age, "_extention_Age", "q", 3, 8}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[7];
} _OBJC_$_INSTANCE_METHODS_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	7,
	{{(struct objc_selector *)"instanceFunc_PlayFootball", "v16@0:8", (void *)_I_Man_instanceFunc_PlayFootball},
	{(struct objc_selector *)"name", "@16@0:8", (void *)_I_Man_name},
	{(struct objc_selector *)"setName:", "v24@0:8@16", (void *)_I_Man_setName_},
	{(struct objc_selector *)"phone", "@16@0:8", (void *)_I_Man_phone},
	{(struct objc_selector *)"setPhone:", "v24@0:8@16", (void *)_I_Man_setPhone_},
	{(struct objc_selector *)"extention_Age", "q16@0:8", (void *)_I_Man_extention_Age},
	{(struct objc_selector *)"setExtention_Age:", "v24@0:8q16", (void *)_I_Man_setExtention_Age_}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CLASS_METHODS_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"clsFunc_DoWork", "v16@0:8", (void *)_C_Man_clsFunc_DoWork}}
};

static struct /*_prop_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count_of_properties;
	struct _prop_t prop_list[2];
} _OBJC_$_PROP_LIST_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_prop_t),
	2,
	{{"name","T@\"NSString\",C,N,V_name"},
	{"phone","T@\"NSString\",C,N,V_phone"}}
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	1, sizeof(struct _class_t), sizeof(struct _class_t), 
	0, 
	"Man",
	(const struct _method_list_t *)&_OBJC_$_CLASS_METHODS_Man,
	0, 
	0, 
	0, 
	0, 
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	0, __OFFSETOFIVAR__(struct Man, private_Money),
    sizeof(struct Man_IMPL), 
	0, 
	"Man",
	(const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Man,
	0, 
	(const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Man,
	0, 
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Man,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Person;
extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Man __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_NSObject,
	0, // &OBJC_METACLASS_$_Person,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_METACLASS_RO_$_Man,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Person;

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Man __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_Man,
	0, // &OBJC_CLASS_$_Person,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_CLASS_RO_$_Man,
};
static void OBJC_CLASS_SETUP_$_Man(void ) {
	OBJC_METACLASS_$_Man.isa = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Man.superclass = &OBJC_METACLASS_$_Person;
	OBJC_METACLASS_$_Man.cache = &_objc_empty_cache;
	OBJC_CLASS_$_Man.isa = &OBJC_METACLASS_$_Man;
	OBJC_CLASS_$_Man.superclass = &OBJC_CLASS_$_Person;
	OBJC_CLASS_$_Man.cache = &_objc_empty_cache;
}
#pragma section(".objc_inithooks$B", long, read, write)
__declspec(allocate(".objc_inithooks$B")) static void *OBJC_CLASS_SETUP[] = {
	(void *)&OBJC_CLASS_SETUP_$_Person,
	(void *)&OBJC_CLASS_SETUP_$_Man,
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CATEGORY_INSTANCE_METHODS_Man_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"categoryInstanceFunc_PlayFootball", "v16@0:8", (void *)_I_Man_Ex_categoryInstanceFunc_PlayFootball}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CATEGORY_CLASS_METHODS_Man_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"categoryClsFunc_DoWork", "v16@0:8", (void *)_C_Man_Ex_categoryClsFunc_DoWork}}
};

static struct /*_prop_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count_of_properties;
	struct _prop_t prop_list[1];
} _OBJC_$_PROP_LIST_Man_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_prop_t),
	1,
	{{"category_address","T@\"NSString\",C,N"}}
};

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Man;

/*
 __attribute__ ((used, section ("__DATA,__objc_const"))) 编译函数语法说明文章
 http://liumh.com/2018/08/18/ios-attribute-section/
 
 https://github.com/guohongwei719/GHWAppLaunchManager
 */
static struct _category_t _OBJC_$_CATEGORY_Man_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = 
{
	"Man",
	0, // &OBJC_CLASS_$_Man,
	(const struct _method_list_t *)&_OBJC_$_CATEGORY_INSTANCE_METHODS_Man_$_Ex,
	(const struct _method_list_t *)&_OBJC_$_CATEGORY_CLASS_METHODS_Man_$_Ex,
	0,
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Man_$_Ex,
};
static void OBJC_CATEGORY_SETUP_$_Man_$_Ex(void ) {
	_OBJC_$_CATEGORY_Man_$_Ex.cls = &OBJC_CLASS_$_Man;
}
#pragma section(".objc_inithooks$B", long, read, write)
__declspec(allocate(".objc_inithooks$B")) static void *OBJC_CATEGORY_SETUP[] = {
	(void *)&OBJC_CATEGORY_SETUP_$_Man_$_Ex,
};
static struct _class_t *L_OBJC_LABEL_CLASS_$ [2] __attribute__((used, section ("__DATA, __objc_classlist,regular,no_dead_strip")))= {
	&OBJC_CLASS_$_Person,
	&OBJC_CLASS_$_Man,
};
static struct _category_t *L_OBJC_LABEL_CATEGORY_$ [1] __attribute__((used, section ("__DATA, __objc_catlist,regular,no_dead_strip")))= {
	&_OBJC_$_CATEGORY_Man_$_Ex,
};
static struct IMAGE_INFO { unsigned version; unsigned flag; } _OBJC_IMAGE_INFO = { 0, 2 };
