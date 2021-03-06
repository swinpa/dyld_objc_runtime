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
static __NSConstantStringImpl __NSConstantStringImpl__var_folders_f3_6cl3xw6j4nl8414jl94d5yzm0000gn_T_clangMain_f4f397_mi_0 __attribute__ ((section ("__DATA, __cfstring"))) = {__CFConstantStringClassReference,0x000007c8,"",0};
















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



static inline
uint16_t
_OSSwapInt16(
 uint16_t _data
 )
{

 return (uint16_t)(_data << 8 | _data >> 8);
}

static inline
uint32_t
_OSSwapInt32(
 uint32_t _data
 )
{

 _data = __builtin_bswap32(_data);





 return _data;
}

static inline
uint64_t
_OSSwapInt64(
 uint64_t _data
 )
{

 return __builtin_bswap64(_data);
}



struct _OSUnalignedU16 {
 volatile uint16_t __val;
} __attribute__((__packed__));

struct _OSUnalignedU32 {
 volatile uint32_t __val;
} __attribute__((__packed__));

struct _OSUnalignedU64 {
 volatile uint64_t __val;
} __attribute__((__packed__));
static inline
uint16_t
OSReadSwapInt16(
 const volatile void * _base,
 uintptr_t _offset
 )
{
 return _OSSwapInt16(((struct _OSUnalignedU16 *)((uintptr_t)_base + _offset))->__val);
}
static inline
uint32_t
OSReadSwapInt32(
 const volatile void * _base,
 uintptr_t _offset
 )
{
 return _OSSwapInt32(((struct _OSUnalignedU32 *)((uintptr_t)_base + _offset))->__val);
}
static inline
uint64_t
OSReadSwapInt64(
 const volatile void * _base,
 uintptr_t _offset
 )
{
 return _OSSwapInt64(((struct _OSUnalignedU64 *)((uintptr_t)_base + _offset))->__val);
}
static inline
void
OSWriteSwapInt16(
 volatile void * _base,
 uintptr_t _offset,
 uint16_t _data
 )
{
 ((struct _OSUnalignedU16 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt16(_data);
}
static inline
void
OSWriteSwapInt32(
 volatile void * _base,
 uintptr_t _offset,
 uint32_t _data
 )
{
 ((struct _OSUnalignedU32 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt32(_data);
}
static inline
void
OSWriteSwapInt64(
 volatile void * _base,
 uintptr_t _offset,
 uint64_t _data
 )
{
 ((struct _OSUnalignedU64 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt64(_data);
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

int __darwin_check_fd_set_overflow(int, const void *, int) __attribute__((availability(macosx,introduced=11.0))) __attribute__((availability(ios,introduced=14.0))) __attribute__((availability(tvos,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0)));
}

inline __attribute__ ((__always_inline__)) int
__darwin_check_fd_set(int _a, const void *_b)
{

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability-new"

 if ((uintptr_t)&__darwin_check_fd_set_overflow != (uintptr_t) 0) {



  return __darwin_check_fd_set_overflow(_a, _b, 0);

 } else {
  return 1;
 }

#pragma clang diagnostic pop

}


inline __attribute__ ((__always_inline__)) int
__darwin_fd_isset(int _fd, const struct fd_set *_p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  return _p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] & ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8))));
 }

 return 0;
}

inline __attribute__ ((__always_inline__)) void
__darwin_fd_set(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] |= ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
}

inline __attribute__ ((__always_inline__)) void
__darwin_fd_clr(int _fd, struct fd_set *const _p)
{
 if (__darwin_check_fd_set(_fd, (const void *) _p)) {
  (_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] &= ~((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
 }
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
    __attribute__((availability(macosx,introduced=10.0))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
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


// @protocol NSObject

// - (BOOL)isEqual:(id)object;
// @property (readonly) NSUInteger hash;

// @property (readonly) Class superclass;
// - (Class)class __attribute__((availability(swift, unavailable, message="use 'type(of: anObject)' instead")));
// - (instancetype)self;

// - (id)performSelector:(SEL)aSelector;
// - (id)performSelector:(SEL)aSelector withObject:(id)object;
// - (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

// - (BOOL)isProxy;

// - (BOOL)isKindOfClass:(Class)aClass;
// - (BOOL)isMemberOfClass:(Class)aClass;
// - (BOOL)conformsToProtocol:(Protocol *)aProtocol;

// - (BOOL)respondsToSelector:(SEL)aSelector;

// - (instancetype)retain ;
// - (oneway void)release ;
// - (instancetype)autorelease ;
// - (NSUInteger)retainCount ;

// - (struct _NSZone *)zone ;

// @property (readonly, copy) NSString *description;
/* @optional */
// @property (readonly, copy) NSString *debugDescription;

/* @end */



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


// + (void)load;

// + (void)initialize;
#if 0
- (instancetype)init

    __attribute__((objc_designated_initializer))

    ;
#endif


// + (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
// + (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((availability(swift, unavailable, message="use object initializers instead")));
// + (instancetype)alloc __attribute__((availability(swift, unavailable, message="use object initializers instead")));
// - (void)dealloc __attribute__((availability(swift, unavailable, message="use 'deinit' to define a de-initializer")));

// - (void)finalize __attribute__((deprecated("Objective-C garbage collection is no longer supported")));

// - (id)copy;
// - (id)mutableCopy;

// + (id)copyWithZone:(struct _NSZone *)zone ;
// + (id)mutableCopyWithZone:(struct _NSZone *)zone ;

// + (BOOL)instancesRespondToSelector:(SEL)aSelector;
// + (BOOL)conformsToProtocol:(Protocol *)protocol;
// - (IMP)methodForSelector:(SEL)aSelector;
// + (IMP)instanceMethodForSelector:(SEL)aSelector;
// - (void)doesNotRecognizeSelector:(SEL)aSelector;

// - (id)forwardingTargetForSelector:(SEL)aSelector __attribute__((availability(macosx,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
// - (void)forwardInvocation:(NSInvocation *)anInvocation __attribute__((availability(swift, unavailable, message="")));
// - (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector __attribute__((availability(swift, unavailable, message="")));

// + (NSMethodSignature *)instanceMethodSignatureForSelector:(SEL)aSelector __attribute__((availability(swift, unavailable, message="")));

// - (BOOL)allowsWeakReference __attribute__((unavailable));
// - (BOOL)retainWeakReference __attribute__((unavailable));

// + (BOOL)isSubclassOfClass:(Class)aClass;

// + (BOOL)resolveClassMethod:(SEL)sel __attribute__((availability(macosx,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));
// + (BOOL)resolveInstanceMethod:(SEL)sel __attribute__((availability(macosx,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,introduced=1.0)));

// + (NSUInteger)hash;
// + (Class)superclass;
// + (Class)class __attribute__((availability(swift, unavailable, message="use 'aClass.self' instead")));
// + (NSString *)description;
// + (NSString *)debugDescription;

/* @end */

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
typedef enum {
  ptrauth_key_asia = 0,
  ptrauth_key_asib = 1,
  ptrauth_key_asda = 2,
  ptrauth_key_asdb = 3,




  ptrauth_key_process_independent_code = ptrauth_key_asia,




  ptrauth_key_process_dependent_code = ptrauth_key_asib,




  ptrauth_key_process_independent_data = ptrauth_key_asda,




  ptrauth_key_process_dependent_data = ptrauth_key_asdb,



  ptrauth_key_function_pointer = ptrauth_key_process_independent_code,





  ptrauth_key_return_address = ptrauth_key_process_dependent_code,





  ptrauth_key_frame_pointer = ptrauth_key_process_dependent_data,
  ptrauth_key_block_function = ptrauth_key_asia,



  ptrauth_key_cxx_vtable_pointer = ptrauth_key_asda,


  ptrauth_key_method_list_pointer = ptrauth_key_asda,


  ptrauth_key_objc_isa_pointer = ptrauth_key_process_independent_data,
  ptrauth_key_objc_super_pointer = ptrauth_key_process_independent_data,


  ptrauth_key_block_descriptor_pointer = ptrauth_key_asda,



} ptrauth_key;


typedef long unsigned int ptrauth_extra_data_t;


typedef long unsigned int ptrauth_generic_signature_t;





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
extern "C" {
// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

// @class NSAttributedString;
#ifndef _REWRITER_typedef_NSAttributedString
#define _REWRITER_typedef_NSAttributedString
typedef struct objc_object NSAttributedString;
typedef struct {} _objc_exc_NSAttributedString;
#endif

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSNull;
#ifndef _REWRITER_typedef_NSNull
#define _REWRITER_typedef_NSNull
typedef struct objc_object NSNull;
typedef struct {} _objc_exc_NSNull;
#endif

// @class NSCharacterSet;
#ifndef _REWRITER_typedef_NSCharacterSet
#define _REWRITER_typedef_NSCharacterSet
typedef struct objc_object NSCharacterSet;
typedef struct {} _objc_exc_NSCharacterSet;
#endif

// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

// @class NSDate;
#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

// @class NSTimeZone;
#ifndef _REWRITER_typedef_NSTimeZone
#define _REWRITER_typedef_NSTimeZone
typedef struct objc_object NSTimeZone;
typedef struct {} _objc_exc_NSTimeZone;
#endif

// @class NSDictionary;
#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

// @class NSError;
#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

// @class NSLocale;
#ifndef _REWRITER_typedef_NSLocale
#define _REWRITER_typedef_NSLocale
typedef struct objc_object NSLocale;
typedef struct {} _objc_exc_NSLocale;
#endif

// @class NSNumber;
#ifndef _REWRITER_typedef_NSNumber
#define _REWRITER_typedef_NSNumber
typedef struct objc_object NSNumber;
typedef struct {} _objc_exc_NSNumber;
#endif

// @class NSSet;
#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif

// @class NSURL;
#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif

extern double kCFCoreFoundationVersionNumber;
typedef unsigned long CFTypeID;
typedef unsigned long CFOptionFlags;
typedef unsigned long CFHashCode;
typedef signed long CFIndex;



typedef const __attribute__((objc_bridge(id))) void * CFTypeRef;

typedef const struct __attribute__((objc_bridge(NSString))) __CFString * CFStringRef;
typedef struct __attribute__((objc_bridge_mutable(NSMutableString))) __CFString * CFMutableStringRef;






typedef __attribute__((objc_bridge(id))) CFTypeRef CFPropertyListRef;


typedef CFIndex CFComparisonResult; enum {
    kCFCompareLessThan = -1L,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1
};


typedef CFComparisonResult (*CFComparatorFunction)(const void *val1, const void *val2, void *context);


static const CFIndex kCFNotFound = -1;



typedef struct {
    CFIndex location;
    CFIndex length;
} CFRange;


static __inline__ __attribute__((always_inline)) CFRange CFRangeMake(CFIndex loc, CFIndex len) {
    CFRange range;
    range.location = loc;
    range.length = len;
    return range;
}





extern
CFRange __CFRangeMake(CFIndex loc, CFIndex len);




typedef const struct __attribute__((objc_bridge(NSNull))) __CFNull * CFNullRef;

extern
CFTypeID CFNullGetTypeID(void);

extern
const CFNullRef kCFNull;
typedef const struct __attribute__((objc_bridge(id))) __CFAllocator * CFAllocatorRef;


extern
const CFAllocatorRef kCFAllocatorDefault;


extern
const CFAllocatorRef kCFAllocatorSystemDefault;







extern
const CFAllocatorRef kCFAllocatorMalloc;





extern
const CFAllocatorRef kCFAllocatorMallocZone;





extern
const CFAllocatorRef kCFAllocatorNull;





extern
const CFAllocatorRef kCFAllocatorUseContext;

typedef const void * (*CFAllocatorRetainCallBack)(const void *info);
typedef void (*CFAllocatorReleaseCallBack)(const void *info);
typedef CFStringRef (*CFAllocatorCopyDescriptionCallBack)(const void *info);
typedef void * (*CFAllocatorAllocateCallBack)(CFIndex allocSize, CFOptionFlags hint, void *info);
typedef void * (*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize, CFOptionFlags hint, void *info);
typedef void (*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef CFIndex (*CFAllocatorPreferredSizeCallBack)(CFIndex size, CFOptionFlags hint, void *info);
typedef struct {
    CFIndex version;
    void * info;
    CFAllocatorRetainCallBack retain;
    CFAllocatorReleaseCallBack release;
    CFAllocatorCopyDescriptionCallBack copyDescription;
    CFAllocatorAllocateCallBack allocate;
    CFAllocatorReallocateCallBack reallocate;
    CFAllocatorDeallocateCallBack deallocate;
    CFAllocatorPreferredSizeCallBack preferredSize;
} CFAllocatorContext;

extern
CFTypeID CFAllocatorGetTypeID(void);
extern
void CFAllocatorSetDefault(CFAllocatorRef allocator);

extern
CFAllocatorRef CFAllocatorGetDefault(void);

extern
CFAllocatorRef CFAllocatorCreate(CFAllocatorRef allocator, CFAllocatorContext *context);

extern
void *CFAllocatorAllocate(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

extern
void *CFAllocatorReallocate(CFAllocatorRef allocator, void *ptr, CFIndex newsize, CFOptionFlags hint);

extern
void CFAllocatorDeallocate(CFAllocatorRef allocator, void *ptr);

extern
CFIndex CFAllocatorGetPreferredSizeForSize(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

extern
void CFAllocatorGetContext(CFAllocatorRef allocator, CFAllocatorContext *context);






extern
CFTypeID CFGetTypeID(CFTypeRef cf);

extern
CFStringRef CFCopyTypeIDDescription(CFTypeID type_id);

extern
CFTypeRef CFRetain(CFTypeRef cf);

extern
void CFRelease(CFTypeRef cf);



extern
CFTypeRef CFAutorelease(CFTypeRef __attribute__((cf_consumed)) arg) __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern
CFIndex CFGetRetainCount(CFTypeRef cf);


extern
Boolean CFEqual(CFTypeRef cf1, CFTypeRef cf2);

extern
CFHashCode CFHash(CFTypeRef cf);

extern
CFStringRef CFCopyDescription(CFTypeRef cf);

extern
CFAllocatorRef CFGetAllocator(CFTypeRef cf);




extern
CFTypeRef CFMakeCollectable(CFTypeRef cf) ;
}
typedef long int ptrdiff_t;

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin

typedef struct _NSZone NSZone;

extern "C" NSZone *NSDefaultMallocZone(void) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" NSZone *NSCreateZone(NSUInteger startSize, NSUInteger granularity, BOOL canFree) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" void NSRecycleZone(NSZone *zone)__attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));

extern "C" void NSSetZoneName(NSZone * _Nullable zone, NSString *name)__attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" NSString *NSZoneName(NSZone * _Nullable zone) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" NSZone * _Nullable NSZoneFromPointer(void *ptr) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));

extern "C" void *NSZoneMalloc(NSZone * _Nullable zone, NSUInteger size) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" void *NSZoneCalloc(NSZone * _Nullable zone, NSUInteger numElems, NSUInteger byteSize) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" void *NSZoneRealloc(NSZone * _Nullable zone, void * _Nullable ptr, NSUInteger size) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
extern "C" void NSZoneFree(NSZone * _Nullable zone, void *ptr) __attribute__((availability(swift, unavailable, message="Zone-based memory management is unavailable")));
static __inline__ __attribute__((always_inline)) __attribute__((ns_returns_retained)) id _Nullable NSMakeCollectable(CFTypeRef _Nullable __attribute__((cf_consumed)) cf) __attribute__((availability(swift, unavailable, message="Garbage Collection is not supported")));
static __inline__ __attribute__((always_inline)) __attribute__((ns_returns_retained)) id _Nullable NSMakeCollectable(CFTypeRef _Nullable __attribute__((cf_consumed)) cf) {



    return (id)cf;

}

extern "C" NSUInteger NSPageSize(void);
extern "C" NSUInteger NSLogPageSize(void);
extern "C" NSUInteger NSRoundUpToMultipleOfPageSize(NSUInteger bytes);
extern "C" NSUInteger NSRoundDownToMultipleOfPageSize(NSUInteger bytes);
extern "C" void *NSAllocateMemoryPages(NSUInteger bytes);
extern "C" void NSDeallocateMemoryPages(void *ptr, NSUInteger bytes);
extern "C" void NSCopyMemoryPages(const void *source, void *dest, NSUInteger bytes);
extern "C" NSUInteger NSRealMemoryAvailable(void) __attribute__((availability(macos,introduced=10.0,deprecated=10.8,message="Use NSProcessInfo instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=6.0,message="Use NSProcessInfo instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use NSProcessInfo instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use NSProcessInfo instead")));
#pragma clang assume_nonnull end

// @class NSInvocation;
#ifndef _REWRITER_typedef_NSInvocation
#define _REWRITER_typedef_NSInvocation
typedef struct objc_object NSInvocation;
typedef struct {} _objc_exc_NSInvocation;
#endif

#ifndef _REWRITER_typedef_NSMethodSignature
#define _REWRITER_typedef_NSMethodSignature
typedef struct objc_object NSMethodSignature;
typedef struct {} _objc_exc_NSMethodSignature;
#endif

#ifndef _REWRITER_typedef_NSCoder
#define _REWRITER_typedef_NSCoder
typedef struct objc_object NSCoder;
typedef struct {} _objc_exc_NSCoder;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_NSEnumerator
#define _REWRITER_typedef_NSEnumerator
typedef struct objc_object NSEnumerator;
typedef struct {} _objc_exc_NSEnumerator;
#endif

// @class Protocol;
#ifndef _REWRITER_typedef_Protocol
#define _REWRITER_typedef_Protocol
typedef struct objc_object Protocol;
typedef struct {} _objc_exc_Protocol;
#endif


#pragma clang assume_nonnull begin



// @protocol NSCopying

// - (id)copyWithZone:(nullable NSZone *)zone;

/* @end */


// @protocol NSMutableCopying

// - (id)mutableCopyWithZone:(nullable NSZone *)zone;

/* @end */


// @protocol NSCoding

// - (void)encodeWithCoder:(NSCoder *)coder;
// - (nullable instancetype)initWithCoder:(NSCoder *)coder;

/* @end */





// @protocol NSSecureCoding <NSCoding>
/* @required */


@property (class, readonly) BOOL supportsSecureCoding;
/* @end */




// @interface NSObject (NSCoderMethods)

// + (NSInteger)version;
// + (void)setVersion:(NSInteger)aVersion;
// @property (readonly) Class classForCoder;
// - (nullable id)replacementObjectForCoder:(NSCoder *)coder;
// - (nullable id)awakeAfterUsingCoder:(NSCoder *)coder __attribute__((ns_consumes_self)) __attribute__((ns_returns_retained));

/* @end */

// @protocol NSDiscardableContent
/* @required */
// - (BOOL)beginContentAccess;
// - (void)endContentAccess;
// - (void)discardContentIfPossible;
// - (BOOL)isContentDiscarded;
/* @end */


// @interface NSObject (NSDiscardableContentProxy)
// @property (readonly, retain) id autoContentAccessingProxy __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */





extern "C" id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone * _Nullable zone) ;

extern "C" void NSDeallocateObject(id object) ;

extern "C" id NSCopyObject(id object, NSUInteger extraBytes, NSZone * _Nullable zone) __attribute__((availability(macos,introduced=10.0,deprecated=10.8,message="Not supported"))) __attribute__((availability(ios,introduced=2.0,deprecated=6.0,message="Not supported"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Not supported"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Not supported")));

extern "C" BOOL NSShouldRetainWithZone(id anObject, NSZone * _Nullable requestedZone) ;

extern "C" void NSIncrementExtraRefCount(id object) ;

extern "C" BOOL NSDecrementExtraRefCountWasZero(id object) ;

extern "C" NSUInteger NSExtraRefCount(id object) ;
static __inline__ __attribute__((always_inline)) __attribute__((cf_returns_retained)) CFTypeRef _Nullable CFBridgingRetain(id _Nullable X) {
    return X ? CFRetain((CFTypeRef)X) : __null;
}


static __inline__ __attribute__((always_inline)) id _Nullable CFBridgingRelease(CFTypeRef __attribute__((cf_consumed)) _Nullable X) __attribute__((ns_returns_retained)) {
    return ((id (*)(id, SEL))(void *)objc_msgSend)((id)CFMakeCollectable(X), sel_registerName("autorelease"));
}
#pragma clang assume_nonnull end
typedef unsigned short unichar;














// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif


#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSValue
#define _REWRITER_typedef_NSValue
typedef struct objc_object NSValue;
typedef struct {} _objc_exc_NSValue;
#endif

struct NSValue_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// - (void)getValue:(void *)value size:(NSUInteger)size __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));

// @property (readonly) const char *objCType __attribute__((objc_returns_inner_pointer));

// - (instancetype)initWithBytes:(const void *)value objCType:(const char *)type __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

/* @end */


// @interface NSValue (NSValueCreation)

// + (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
// + (NSValue *)value:(const void *)value withObjCType:(const char *)type;

/* @end */


// @interface NSValue (NSValueExtensionMethods)

// + (NSValue *)valueWithNonretainedObject:(nullable id)anObject;
// @property (nullable, readonly) id nonretainedObjectValue;

// + (NSValue *)valueWithPointer:(nullable const void *)pointer;
// @property (nullable, readonly) void *pointerValue;

// - (BOOL)isEqualToValue:(NSValue *)value;

/* @end */



#ifndef _REWRITER_typedef_NSNumber
#define _REWRITER_typedef_NSNumber
typedef struct objc_object NSNumber;
typedef struct {} _objc_exc_NSNumber;
#endif

struct NSNumber_IMPL {
	struct NSValue_IMPL NSValue_IVARS;
};


// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithChar:(char)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedChar:(unsigned char)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithShort:(short)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedShort:(unsigned short)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithInt:(int)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedInt:(unsigned int)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithLong:(long)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedLong:(unsigned long)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithLongLong:(long long)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedLongLong:(unsigned long long)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithFloat:(float)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithDouble:(double)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithBool:(BOOL)value __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithInteger:(NSInteger)value __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));
// - (NSNumber *)initWithUnsignedInteger:(NSUInteger)value __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));

// @property (readonly) char charValue;
// @property (readonly) unsigned char unsignedCharValue;
// @property (readonly) short shortValue;
// @property (readonly) unsigned short unsignedShortValue;
// @property (readonly) int intValue;
// @property (readonly) unsigned int unsignedIntValue;
// @property (readonly) long longValue;
// @property (readonly) unsigned long unsignedLongValue;
// @property (readonly) long long longLongValue;
// @property (readonly) unsigned long long unsignedLongLongValue;
// @property (readonly) float floatValue;
// @property (readonly) double doubleValue;
// @property (readonly) BOOL boolValue;
// @property (readonly) NSInteger integerValue __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) NSUInteger unsignedIntegerValue __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) NSString *stringValue;

// - (NSComparisonResult)compare:(NSNumber *)otherNumber;

// - (BOOL)isEqualToNumber:(NSNumber *)number;

// - (NSString *)descriptionWithLocale:(nullable id)locale;

/* @end */


// @interface NSNumber (NSNumberCreation)

// + (NSNumber *)numberWithChar:(char)value;
// + (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
// + (NSNumber *)numberWithShort:(short)value;
// + (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
// + (NSNumber *)numberWithInt:(int)value;
// + (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
// + (NSNumber *)numberWithLong:(long)value;
// + (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
// + (NSNumber *)numberWithLongLong:(long long)value;
// + (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
// + (NSNumber *)numberWithFloat:(float)value;
// + (NSNumber *)numberWithDouble:(double)value;
// + (NSNumber *)numberWithBool:(BOOL)value;
// + (NSNumber *)numberWithInteger:(NSInteger)value __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSNumber *)numberWithUnsignedInteger:(NSUInteger)value __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSValue (NSDeprecated)


// - (void)getValue:(void *)value __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="getValue:size:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="getValue:size:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="getValue:size:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="getValue:size:")));
/* @end */

#pragma clang assume_nonnull end


// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin

typedef struct _NSRange {
    NSUInteger location;
    NSUInteger length;
} NSRange;

typedef NSRange *NSRangePointer;

static __inline__ __attribute__((always_inline)) NSRange NSMakeRange(NSUInteger loc, NSUInteger len) {
    NSRange r;
    r.location = loc;
    r.length = len;
    return r;
}

static __inline__ __attribute__((always_inline)) NSUInteger NSMaxRange(NSRange range) {
    return (range.location + range.length);
}

static __inline__ __attribute__((always_inline)) BOOL NSLocationInRange(NSUInteger loc, NSRange range) {
    return (!(loc < range.location) && (loc - range.location) < range.length) ? ((bool)1) : ((bool)0);
}

static __inline__ __attribute__((always_inline)) BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location && range1.length == range2.length);
}

extern "C" NSRange NSUnionRange(NSRange range1, NSRange range2);
extern "C" NSRange NSIntersectionRange(NSRange range1, NSRange range2);
extern "C" NSString *NSStringFromRange(NSRange range);
extern "C" NSRange NSRangeFromString(NSString *aString);

// @interface NSValue (NSValueRangeExtensions)

// + (NSValue *)valueWithRange:(NSRange)range;
// @property (readonly) NSRange rangeValue;

/* @end */

#pragma clang assume_nonnull end















// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif


#pragma clang assume_nonnull begin
typedef struct {
    unsigned long state;
    id __attribute__((objc_ownership(none))) _Nullable * _Nullable itemsPtr;
    unsigned long * _Nullable mutationsPtr;
    unsigned long extra[5];
} NSFastEnumerationState;

// @protocol NSFastEnumeration

// - (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id __attribute__((objc_ownership(none))) _Nullable [_Nonnull])buffer count:(NSUInteger)len;

/* @end */



#ifndef _REWRITER_typedef_NSEnumerator
#define _REWRITER_typedef_NSEnumerator
typedef struct objc_object NSEnumerator;
typedef struct {} _objc_exc_NSEnumerator;
#endif

struct NSEnumerator_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// - (nullable ObjectType)nextObject;

/* @end */


// @interface NSEnumerator<ObjectType> (NSExtendedEnumerator)

// @property (readonly, copy) NSArray<ObjectType> *allObjects;

/* @end */

#pragma clang assume_nonnull end






// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif









#pragma clang assume_nonnull begin

typedef NSInteger NSCollectionChangeType; enum {
    NSCollectionChangeInsert,
    NSCollectionChangeRemove
} __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

__attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))

#ifndef _REWRITER_typedef_NSOrderedCollectionChange
#define _REWRITER_typedef_NSOrderedCollectionChange
typedef struct objc_object NSOrderedCollectionChange;
typedef struct {} _objc_exc_NSOrderedCollectionChange;
#endif

struct NSOrderedCollectionChange_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};

#if 0
+ (NSOrderedCollectionChange<ObjectType> *)changeWithObject:(nullable ObjectType)anObject
                                                       type:(NSCollectionChangeType)type
                                                      index:(NSUInteger)index;
#endif


#if 0
+ (NSOrderedCollectionChange<ObjectType> *)changeWithObject:(nullable ObjectType)anObject
                                                       type:(NSCollectionChangeType)type
                                                      index:(NSUInteger)index
                                            associatedIndex:(NSUInteger)associatedIndex;
#endif



// @property (readonly, strong, nullable) ObjectType object;


// @property (readonly) NSCollectionChangeType changeType;



// @property (readonly) NSUInteger index;





// @property (readonly) NSUInteger associatedIndex;

// - (id)init __attribute__((availability(macos,unavailable))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));

#if 0
- (instancetype)initWithObject:(nullable ObjectType)anObject
                          type:(NSCollectionChangeType)type
                         index:(NSUInteger)index;
#endif


#if 0
- (instancetype)initWithObject:(nullable ObjectType)anObject
                          type:(NSCollectionChangeType)type
                         index:(NSUInteger)index
               associatedIndex:(NSUInteger)associatedIndex __attribute__((objc_designated_initializer));
#endif

/* @end */

#pragma clang assume_nonnull end
#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSIndexSet
#define _REWRITER_typedef_NSIndexSet
typedef struct objc_object NSIndexSet;
typedef struct {} _objc_exc_NSIndexSet;
#endif

struct NSIndexSet_IMPL {
	struct NSObject_IMPL NSObject_IVARS;

	struct  {
	NSUInteger _isEmpty : 1;
	NSUInteger _hasSingleRange : 1;
	NSUInteger _cacheValid : 1;
	NSUInteger _reservedArrayBinderController : 29;
	} _indexSetFlags;

	union  {

	struct  {
	NSRange _range;
	} _singleRange;

	struct  {
	void * _Nonnull _data;
	void * _Nonnull _reserved;
	} _multipleRanges;
	} _internal;
};


// + (instancetype)indexSet;
// + (instancetype)indexSetWithIndex:(NSUInteger)value;
// + (instancetype)indexSetWithIndexesInRange:(NSRange)range;

// - (instancetype)initWithIndexesInRange:(NSRange)range __attribute__((objc_designated_initializer));
// - (instancetype)initWithIndexSet:(NSIndexSet *)indexSet __attribute__((objc_designated_initializer));

// - (instancetype)initWithIndex:(NSUInteger)value;

// - (BOOL)isEqualToIndexSet:(NSIndexSet *)indexSet;

// @property (readonly) NSUInteger count;



// @property (readonly) NSUInteger firstIndex;
// @property (readonly) NSUInteger lastIndex;
// - (NSUInteger)indexGreaterThanIndex:(NSUInteger)value;
// - (NSUInteger)indexLessThanIndex:(NSUInteger)value;
// - (NSUInteger)indexGreaterThanOrEqualToIndex:(NSUInteger)value;
// - (NSUInteger)indexLessThanOrEqualToIndex:(NSUInteger)value;



// - (NSUInteger)getIndexes:(NSUInteger *)indexBuffer maxCount:(NSUInteger)bufferSize inIndexRange:(nullable NSRangePointer)range;

// - (NSUInteger)countOfIndexesInRange:(NSRange)range __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (BOOL)containsIndex:(NSUInteger)value;
// - (BOOL)containsIndexesInRange:(NSRange)range;
// - (BOOL)containsIndexes:(NSIndexSet *)indexSet;

// - (BOOL)intersectsIndexesInRange:(NSRange)range;

// - (void)enumerateIndexesUsingBlock:(void (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateIndexesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateIndexesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSUInteger)indexPassingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSUInteger)indexWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSUInteger)indexInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSIndexSet *)indexesPassingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSIndexSet *)indexesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSIndexSet *)indexesInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// - (void)enumerateRangesUsingBlock:(void (__attribute__((noescape)) ^)(NSRange range, BOOL *stop))block __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateRangesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(NSRange range, BOOL *stop))block __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateRangesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(NSRange range, BOOL *stop))block __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */



#ifndef _REWRITER_typedef_NSMutableIndexSet
#define _REWRITER_typedef_NSMutableIndexSet
typedef struct objc_object NSMutableIndexSet;
typedef struct {} _objc_exc_NSMutableIndexSet;
#endif

struct NSMutableIndexSet_IMPL {
	struct NSIndexSet_IMPL NSIndexSet_IVARS;
	void *_reserved;
};


// - (void)addIndexes:(NSIndexSet *)indexSet;
// - (void)removeIndexes:(NSIndexSet *)indexSet;
// - (void)removeAllIndexes;
// - (void)addIndex:(NSUInteger)value;
// - (void)removeIndex:(NSUInteger)value;
// - (void)addIndexesInRange:(NSRange)range;
// - (void)removeIndexesInRange:(NSRange)range;



// - (void)shiftIndexesStartingAtIndex:(NSUInteger)index by:(NSInteger)delta;

/* @end */

#pragma clang assume_nonnull end


#pragma clang assume_nonnull begin


typedef NSUInteger NSOrderedCollectionDifferenceCalculationOptions; enum {

    NSOrderedCollectionDifferenceCalculationOmitInsertedObjects = (1 << 0UL),

    NSOrderedCollectionDifferenceCalculationOmitRemovedObjects = (1 << 1UL),


    NSOrderedCollectionDifferenceCalculationInferMoves = (1 << 2UL)
} __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

__attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))

#ifndef _REWRITER_typedef_NSOrderedCollectionDifference
#define _REWRITER_typedef_NSOrderedCollectionDifference
typedef struct objc_object NSOrderedCollectionDifference;
typedef struct {} _objc_exc_NSOrderedCollectionDifference;
#endif

struct NSOrderedCollectionDifference_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};

// - (instancetype)initWithChanges:(NSArray<NSOrderedCollectionChange<ObjectType> *> *)changes;

#if 0
- (instancetype)initWithInsertIndexes:(NSIndexSet *)inserts
                      insertedObjects:(nullable NSArray<ObjectType> *)insertedObjects
                        removeIndexes:(NSIndexSet *)removes
                       removedObjects:(nullable NSArray<ObjectType> *)removedObjects
                    additionalChanges:(NSArray<NSOrderedCollectionChange<ObjectType> *> *)changes __attribute__((objc_designated_initializer));
#endif


#if 0
- (instancetype)initWithInsertIndexes:(NSIndexSet *)inserts
                      insertedObjects:(nullable NSArray<ObjectType> *)insertedObjects
                        removeIndexes:(NSIndexSet *)removes
                       removedObjects:(nullable NSArray<ObjectType> *)removedObjects;
#endif


// @property (strong, readonly) NSArray<NSOrderedCollectionChange<ObjectType> *> *insertions __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));
// @property (strong, readonly) NSArray<NSOrderedCollectionChange<ObjectType> *> *removals __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

// @property (assign, readonly) BOOL hasChanges;


// - (NSOrderedCollectionDifference<id> *)differenceByTransformingChangesWithBlock:(NSOrderedCollectionChange<id> *(__attribute__((noescape)) ^)(NSOrderedCollectionChange<ObjectType> *))block;







// - (instancetype)inverseDifference __attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

/* @end */

#pragma clang assume_nonnull end

// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSIndexSet
#define _REWRITER_typedef_NSIndexSet
typedef struct objc_object NSIndexSet;
typedef struct {} _objc_exc_NSIndexSet;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif




#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

struct NSArray_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// @property (readonly) NSUInteger count;
// - (ObjectType)objectAtIndex:(NSUInteger)index;
// - (instancetype)init __attribute__((objc_designated_initializer));
// - (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

/* @end */


// @interface NSArray<ObjectType> (NSExtendedArray)

// - (NSArray<ObjectType> *)arrayByAddingObject:(ObjectType)anObject;
// - (NSArray<ObjectType> *)arrayByAddingObjectsFromArray:(NSArray<ObjectType> *)otherArray;
// - (NSString *)componentsJoinedByString:(NSString *)separator;
// - (BOOL)containsObject:(ObjectType)anObject;
// @property (readonly, copy) NSString *description;
// - (NSString *)descriptionWithLocale:(nullable id)locale;
// - (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
// - (nullable ObjectType)firstObjectCommonWithArray:(NSArray<ObjectType> *)otherArray;
// - (void)getObjects:(ObjectType _Nonnull __attribute__((objc_ownership(none))) [_Nonnull])objects range:(NSRange)range __attribute__((availability(swift, unavailable, message="Use 'subarrayWithRange()' instead")));
// - (NSUInteger)indexOfObject:(ObjectType)anObject;
// - (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;
// - (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject;
// - (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
// - (BOOL)isEqualToArray:(NSArray<ObjectType> *)otherArray;
// @property (nullable, nonatomic, readonly) ObjectType firstObject __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, nonatomic, readonly) ObjectType lastObject;
// - (NSEnumerator<ObjectType> *)objectEnumerator;
// - (NSEnumerator<ObjectType> *)reverseObjectEnumerator;
// @property (readonly, copy) NSData *sortedArrayHint;
// - (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (__attribute__((noescape)) *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context;
// - (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (__attribute__((noescape)) *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context hint:(nullable NSData *)hint;
// - (NSArray<ObjectType> *)sortedArrayUsingSelector:(SEL)comparator;
// - (NSArray<ObjectType> *)subarrayWithRange:(NSRange)range;

// - (BOOL)writeToURL:(NSURL *)url error:(NSError **)error __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));


// - (void)makeObjectsPerformSelector:(SEL)aSelector __attribute__((availability(swift, unavailable, message="Use enumerateObjectsUsingBlock: or a for loop instead")));
// - (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument __attribute__((availability(swift, unavailable, message="Use enumerateObjectsUsingBlock: or a for loop instead")));

// - (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;

// - (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)enumerateObjectsUsingBlock:(void (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSUInteger)indexOfObjectPassingTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape))^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator __attribute__((noescape)))cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator __attribute__((noescape)))cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSUInteger NSBinarySearchingOptions; enum {
 NSBinarySearchingFirstEqual = (1UL << 8),
 NSBinarySearchingLastEqual = (1UL << 9),
 NSBinarySearchingInsertionIndex = (1UL << 10),
};

// - (NSUInteger)indexOfObject:(ObjectType)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator __attribute__((noescape)))cmp __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSArray<ObjectType> (NSArrayCreation)

// + (instancetype)array;
// + (instancetype)arrayWithObject:(ObjectType)anObject;
// + (instancetype)arrayWithObjects:(const ObjectType _Nonnull [_Nonnull])objects count:(NSUInteger)cnt;
// + (instancetype)arrayWithObjects:(ObjectType)firstObj, ... __attribute__((sentinel(0,1)));
// + (instancetype)arrayWithArray:(NSArray<ObjectType> *)array;

// - (instancetype)initWithObjects:(ObjectType)firstObj, ... __attribute__((sentinel(0,1)));
// - (instancetype)initWithArray:(NSArray<ObjectType> *)array;
// - (instancetype)initWithArray:(NSArray<ObjectType> *)array copyItems:(BOOL)flag;


// - (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url error:(NSError **)error __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));

// + (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url error:(NSError **)error __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(swift, unavailable, message="Use initializer instead")));

/* @end */


__attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
__attribute__((availability(swift, unavailable, message="NSArray diffing methods are not available in Swift, use Collection.difference(from:) instead")))
// @interface NSArray<ObjectType> (NSArrayDiffing)

// - (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options usingEquivalenceTest:(BOOL (__attribute__((noescape)) ^)(ObjectType obj1, ObjectType obj2))block;

// - (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options;


// - (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other;

// - (nullable NSArray<ObjectType> *)arrayByApplyingDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

/* @end */


// @interface NSArray<ObjectType> (NSDeprecated)




// - (void)getObjects:(ObjectType _Nonnull __attribute__((objc_ownership(none))) [_Nonnull])objects __attribute__((availability(swift, unavailable, message="Use 'as [AnyObject]' instead"))) __attribute__((availability(macos,introduced=10.0,deprecated=10.13,message="Use -getObjects:range: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=11.0,message="Use -getObjects:range: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=4.0,message="Use -getObjects:range: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=11.0,message="Use -getObjects:range: instead")));


// + (nullable NSArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:")));
// + (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="arrayWithContentsOfURL:error:")));
// - (nullable NSArray<ObjectType> *)initWithContentsOfFile:(NSString *)path __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="initWithContentsOfURL:error:")));
// - (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="initWithContentsOfURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="initWithContentsOfURL:error:")));
// - (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="writeToURL:error:")));
// - (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically __attribute__((availability(macos,introduced=10.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="writeToURL:error:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="writeToURL:error:")));

/* @end */





#ifndef _REWRITER_typedef_NSMutableArray
#define _REWRITER_typedef_NSMutableArray
typedef struct objc_object NSMutableArray;
typedef struct {} _objc_exc_NSMutableArray;
#endif

struct NSMutableArray_IMPL {
	struct NSArray_IMPL NSArray_IVARS;
};


// - (void)addObject:(ObjectType)anObject;
// - (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;
// - (void)removeLastObject;
// - (void)removeObjectAtIndex:(NSUInteger)index;
// - (void)replaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)anObject;
// - (instancetype)init __attribute__((objc_designated_initializer));
// - (instancetype)initWithCapacity:(NSUInteger)numItems __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

/* @end */


// @interface NSMutableArray<ObjectType> (NSExtendedMutableArray)

// - (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;
// - (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
// - (void)removeAllObjects;
// - (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;
// - (void)removeObject:(ObjectType)anObject;
// - (void)removeObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
// - (void)removeObjectIdenticalTo:(ObjectType)anObject;
// - (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt __attribute__((availability(macos,introduced=10.0,deprecated=10.6,message="Not supported"))) __attribute__((availability(ios,introduced=2.0,deprecated=4.0,message="Not supported"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Not supported"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Not supported")));
// - (void)removeObjectsInArray:(NSArray<ObjectType> *)otherArray;
// - (void)removeObjectsInRange:(NSRange)range;
// - (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray range:(NSRange)otherRange;
// - (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray;
// - (void)setArray:(NSArray<ObjectType> *)otherArray;
// - (void)sortUsingFunction:(NSInteger (__attribute__((noescape)) *)(ObjectType, ObjectType, void * _Nullable))compare context:(nullable void *)context;
// - (void)sortUsingSelector:(SEL)comparator;

// - (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;
// - (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
// - (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

// - (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)sortUsingComparator:(NSComparator __attribute__((noescape)))cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator __attribute__((noescape)))cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSMutableArray<ObjectType> (NSMutableArrayCreation)

// + (instancetype)arrayWithCapacity:(NSUInteger)numItems;

// + (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
// + (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
// - (nullable NSMutableArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
// - (nullable NSMutableArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

/* @end */


__attribute__((availability(macosx,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
__attribute__((availability(swift, unavailable, message="NSMutableArray diffing methods are not available in Swift")))
// @interface NSMutableArray<ObjectType> (NSMutableArrayDiffing)

// - (void)applyDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

/* @end */

#pragma clang assume_nonnull end





#pragma clang assume_nonnull begin

// @class NSItemProvider;
#ifndef _REWRITER_typedef_NSItemProvider
#define _REWRITER_typedef_NSItemProvider
typedef struct objc_object NSItemProvider;
typedef struct {} _objc_exc_NSItemProvider;
#endif

#ifndef _REWRITER_typedef_NSProgress
#define _REWRITER_typedef_NSProgress
typedef struct objc_object NSProgress;
typedef struct {} _objc_exc_NSProgress;
#endif



typedef NSInteger NSItemProviderRepresentationVisibility; enum {
    NSItemProviderRepresentationVisibilityAll = 0,
    NSItemProviderRepresentationVisibilityTeam
    __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0))) __attribute__((availability(macos,unavailable))) = 1,
    NSItemProviderRepresentationVisibilityGroup
    __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 2 ,
    NSItemProviderRepresentationVisibilityOwnProcess = 3,
} __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



typedef NSInteger NSItemProviderFileOptions; enum {
    NSItemProviderFileOptionOpenInPlace = 1,
} __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



__attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)))
// @protocol NSItemProviderWriting <NSObject>

@property (class, nonatomic, readonly, copy) NSArray<NSString *> *writableTypeIdentifiersForItemProvider;

/* @optional */


// @property (nonatomic, readonly, copy) NSArray<NSString *> *writableTypeIdentifiersForItemProvider;

// + (NSItemProviderRepresentationVisibility)itemProviderVisibilityForRepresentationWithTypeIdentifier:(NSString *)typeIdentifier;


// - (NSItemProviderRepresentationVisibility)itemProviderVisibilityForRepresentationWithTypeIdentifier:(NSString *)typeIdentifier;

/* @required */

#if 0
- (nullable NSProgress *)loadDataWithTypeIdentifier:(NSString *)typeIdentifier
                   forItemProviderCompletionHandler:(void (^)(NSData * _Nullable data, NSError * _Nullable error))completionHandler;
#endif


/* @end */




__attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)))
// @protocol NSItemProviderReading <NSObject>

@property (class, nonatomic, readonly, copy) NSArray<NSString *> *readableTypeIdentifiersForItemProvider;

#if 0
+ (nullable instancetype)objectWithItemProviderData:(NSData *)data
                                     typeIdentifier:(NSString *)typeIdentifier
                                              error:(NSError **)outError;
#endif


/* @end */



typedef void (*NSItemProviderCompletionHandler)(_Nullable __kindof id /*<NSSecureCoding>*/ item, NSError * _Null_unspecified error);
typedef void (*NSItemProviderLoadHandler)(_Null_unspecified NSItemProviderCompletionHandler completionHandler, _Null_unspecified Class expectedValueClass, NSDictionary * _Null_unspecified options);



__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSItemProvider
#define _REWRITER_typedef_NSItemProvider
typedef struct objc_object NSItemProvider;
typedef struct {} _objc_exc_NSItemProvider;
#endif

struct NSItemProvider_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};








// - (instancetype)init __attribute__((objc_designated_initializer));




#if 0
- (void)registerDataRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                         visibility:(NSItemProviderRepresentationVisibility)visibility
                                        loadHandler:(NSProgress * _Nullable (^)(void (^completionHandler)(NSData * _Nullable data, NSError * _Nullable error)))loadHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif





#if 0
- (void)registerFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                        fileOptions:(NSItemProviderFileOptions)fileOptions
                                         visibility:(NSItemProviderRepresentationVisibility)visibility
                                        loadHandler:(NSProgress * _Nullable (^)(void (^completionHandler)(NSURL * _Nullable url, BOOL coordinated, NSError * _Nullable error)))loadHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif







// @property (copy, readonly, atomic) NSArray<NSString *> *registeredTypeIdentifiers;

// - (NSArray<NSString *> *)registeredTypeIdentifiersWithFileOptions:(NSItemProviderFileOptions)fileOptions __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));


// - (BOOL)hasItemConformingToTypeIdentifier:(NSString *)typeIdentifier;

#if 0
- (BOOL)hasRepresentationConformingToTypeIdentifier:(NSString *)typeIdentifier
                                        fileOptions:(NSItemProviderFileOptions)fileOptions __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif



#if 0
- (NSProgress *)loadDataRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                      completionHandler:(void(^)(NSData * _Nullable data, NSError * _Nullable error))completionHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif



#if 0
- (NSProgress *)loadFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                      completionHandler:(void(^)(NSURL * _Nullable url, NSError * _Nullable error))completionHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif




#if 0
- (NSProgress *)loadInPlaceFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                             completionHandler:(void (^)(NSURL * _Nullable url, BOOL isInPlace, NSError * _Nullable error))completionHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif






// @property (atomic, copy, nullable) NSString *suggestedName __attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));






// - (instancetype)initWithObject:(id<NSItemProviderWriting>)object __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));


// - (void)registerObject:(id<NSItemProviderWriting>)object visibility:(NSItemProviderRepresentationVisibility)visibility __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));


#if 0
- (void)registerObjectOfClass:(Class<NSItemProviderWriting>)aClass
                   visibility:(NSItemProviderRepresentationVisibility)visibility
                  loadHandler:(NSProgress * _Nullable (^)(void (^completionHandler)(__kindof id<NSItemProviderWriting> _Nullable object, NSError * _Nullable error)))loadHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif


// - (BOOL)canLoadObjectOfClass:(Class<NSItemProviderReading>)aClass __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));


#if 0
- (NSProgress *)loadObjectOfClass:(Class<NSItemProviderReading>)aClass
                completionHandler:(void (^)(__kindof id<NSItemProviderReading> _Nullable object, NSError * _Nullable error))completionHandler __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
#endif

// - (instancetype)initWithItem:(nullable id<NSSecureCoding>)item typeIdentifier:(nullable NSString *)typeIdentifier __attribute__((objc_designated_initializer));


// - (nullable instancetype)initWithContentsOfURL:(null_unspecified NSURL *)fileURL;


// - (void)registerItemForTypeIdentifier:(NSString *)typeIdentifier loadHandler:(NSItemProviderLoadHandler)loadHandler;







// - (void)loadItemForTypeIdentifier:(NSString *)typeIdentifier options:(nullable NSDictionary *)options completionHandler:(nullable NSItemProviderCompletionHandler)completionHandler;


/* @end */




extern "C" NSString * const NSItemProviderPreferredImageSizeKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// @interface NSItemProvider(NSPreviewSupport)


// @property (nullable, copy, atomic) NSItemProviderLoadHandler previewImageHandler __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// - (void)loadPreviewImageWithOptions:(null_unspecified NSDictionary *)options completionHandler:(null_unspecified NSItemProviderCompletionHandler)completionHandler __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */






extern "C" NSString * _Null_unspecified const NSExtensionJavaScriptPreprocessingResultsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSString * _Null_unspecified const NSExtensionJavaScriptFinalizeArgumentKey __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));






extern "C" NSString * const NSItemProviderErrorDomain __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


typedef NSInteger NSItemProviderErrorCode; enum {
    NSItemProviderUnknownError = -1,
    NSItemProviderItemUnavailableError = -1000,
    NSItemProviderUnexpectedValueClassError = -1100,
    NSItemProviderUnavailableCoercionError __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1200
} __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
#pragma clang assume_nonnull end


// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSCharacterSet
#define _REWRITER_typedef_NSCharacterSet
typedef struct objc_object NSCharacterSet;
typedef struct {} _objc_exc_NSCharacterSet;
#endif

#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

#ifndef _REWRITER_typedef_NSLocale
#define _REWRITER_typedef_NSLocale
typedef struct objc_object NSLocale;
typedef struct {} _objc_exc_NSLocale;
#endif


#pragma clang assume_nonnull begin



typedef NSUInteger NSStringCompareOptions; enum {
    NSCaseInsensitiveSearch = 1,
    NSLiteralSearch = 2,
    NSBackwardsSearch = 4,
    NSAnchoredSearch = 8,
    NSNumericSearch = 64,
    NSDiacriticInsensitiveSearch __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 128,
    NSWidthInsensitiveSearch __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 256,
    NSForcedOrderingSearch __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 512,
    NSRegularExpressionSearch __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=3.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1024
};





typedef NSUInteger NSStringEncoding;
enum {
    NSASCIIStringEncoding = 1,
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,
    NSShiftJISStringEncoding = 8,
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10,
    NSWindowsCP1251StringEncoding = 11,
    NSWindowsCP1252StringEncoding = 12,
    NSWindowsCP1253StringEncoding = 13,
    NSWindowsCP1254StringEncoding = 14,
    NSWindowsCP1250StringEncoding = 15,
    NSISO2022JPStringEncoding = 21,
    NSMacOSRomanStringEncoding = 30,

    NSUTF16StringEncoding = NSUnicodeStringEncoding,

    NSUTF16BigEndianStringEncoding = 0x90000100,
    NSUTF16LittleEndianStringEncoding = 0x94000100,

    NSUTF32StringEncoding = 0x8c000100,
    NSUTF32BigEndianStringEncoding = 0x98000100,
    NSUTF32LittleEndianStringEncoding = 0x9c000100
};

typedef NSUInteger NSStringEncodingConversionOptions; enum {
    NSStringEncodingConversionAllowLossy = 1,
    NSStringEncodingConversionExternalRepresentation = 2
};



#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

struct NSString_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};






// @property (readonly) NSUInteger length;
// - (unichar)characterAtIndex:(NSUInteger)index;



// - (instancetype)init __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

/* @end */


// @interface NSString (NSStringExtensionMethods)
// - (NSString *)substringFromIndex:(NSUInteger)from;
// - (NSString *)substringToIndex:(NSUInteger)to;
// - (NSString *)substringWithRange:(NSRange)range;

// - (void)getCharacters:(unichar *)buffer range:(NSRange)range;






// - (NSComparisonResult)compare:(NSString *)string;
// - (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask;
// - (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare;
// - (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare locale:(nullable id)locale;
// - (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;
// - (NSComparisonResult)localizedCompare:(NSString *)string;
// - (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;



// - (NSComparisonResult)localizedStandardCompare:(NSString *)string __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (BOOL)isEqualToString:(NSString *)aString;






// - (BOOL)hasPrefix:(NSString *)str;
// - (BOOL)hasSuffix:(NSString *)str;

// - (NSString *)commonPrefixWithString:(NSString *)str options:(NSStringCompareOptions)mask;



// - (BOOL)containsString:(NSString *)str __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (BOOL)localizedCaseInsensitiveContainsString:(NSString *)str __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (BOOL)localizedStandardContainsString:(NSString *)str __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSRange)localizedStandardRangeOfString:(NSString *)str __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));







// - (NSRange)rangeOfString:(NSString *)searchString;
// - (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask;
// - (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;
// - (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch locale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// - (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet;
// - (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask;
// - (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;

// - (NSRange)rangeOfComposedCharacterSequenceAtIndex:(NSUInteger)index;
// - (NSRange)rangeOfComposedCharacterSequencesForRange:(NSRange)range __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSString *)stringByAppendingString:(NSString *)aString;
// - (NSString *)stringByAppendingFormat:(NSString *)format, ... __attribute__((format(__NSString__, 1, 2)));






// @property (readonly) double doubleValue;
// @property (readonly) float floatValue;
// @property (readonly) int intValue;
// @property (readonly) NSInteger integerValue __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) long long longLongValue __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) BOOL boolValue __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// @property (readonly, copy) NSString *uppercaseString;
// @property (readonly, copy) NSString *lowercaseString;
// @property (readonly, copy) NSString *capitalizedString;



// @property (readonly, copy) NSString *localizedUppercaseString __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSString *localizedLowercaseString __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSString *localizedCapitalizedString __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSString *)uppercaseStringWithLocale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSString *)lowercaseStringWithLocale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSString *)capitalizedStringWithLocale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// - (void)getLineStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)lineEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
// - (NSRange)lineRangeForRange:(NSRange)range;

// - (void)getParagraphStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)parEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
// - (NSRange)paragraphRangeForRange:(NSRange)range;

typedef NSUInteger NSStringEnumerationOptions; enum {

    NSStringEnumerationByLines = 0,
    NSStringEnumerationByParagraphs = 1,
    NSStringEnumerationByComposedCharacterSequences = 2,
    NSStringEnumerationByWords = 3,
    NSStringEnumerationBySentences = 4,
    NSStringEnumerationByCaretPositions __attribute__((availability(macos,introduced=11.0))) __attribute__((availability(ios,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0))) __attribute__((availability(tvos,introduced=14.0))) = 5,
    NSStringEnumerationByDeletionClusters __attribute__((availability(macos,introduced=11.0))) __attribute__((availability(ios,introduced=14.0))) __attribute__((availability(watchos,introduced=7.0))) __attribute__((availability(tvos,introduced=14.0))) = 6,


    NSStringEnumerationReverse = 1UL << 8,
    NSStringEnumerationSubstringNotRequired = 1UL << 9,
    NSStringEnumerationLocalized = 1UL << 10
};



// - (void)enumerateSubstringsInRange:(NSRange)range options:(NSStringEnumerationOptions)opts usingBlock:(void (^)(NSString * _Nullable substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateLinesUsingBlock:(void (^)(NSString *line, BOOL *stop))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// @property (nullable, readonly) const char *UTF8String __attribute__((objc_returns_inner_pointer));

// @property (readonly) NSStringEncoding fastestEncoding;
// @property (readonly) NSStringEncoding smallestEncoding;

// - (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;
// - (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding;

// - (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;



// - (nullable const char *)cStringUsingEncoding:(NSStringEncoding)encoding __attribute__((objc_returns_inner_pointer));
// - (BOOL)getCString:(char *)buffer maxLength:(NSUInteger)maxBufferCount encoding:(NSStringEncoding)encoding;
// - (BOOL)getBytes:(nullable void *)buffer maxLength:(NSUInteger)maxBufferCount usedLength:(nullable NSUInteger *)usedBufferCount encoding:(NSStringEncoding)encoding options:(NSStringEncodingConversionOptions)options range:(NSRange)range remainingRange:(nullable NSRangePointer)leftover;



// - (NSUInteger)maximumLengthOfBytesUsingEncoding:(NSStringEncoding)enc;
// - (NSUInteger)lengthOfBytesUsingEncoding:(NSStringEncoding)enc;

@property (class, readonly) const NSStringEncoding *availableStringEncodings;

// + (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;



@property (class, readonly) NSStringEncoding defaultCStringEncoding;



// @property (readonly, copy) NSString *decomposedStringWithCanonicalMapping;
// @property (readonly, copy) NSString *precomposedStringWithCanonicalMapping;
// @property (readonly, copy) NSString *decomposedStringWithCompatibilityMapping;
// @property (readonly, copy) NSString *precomposedStringWithCompatibilityMapping;

// - (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;
// - (NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;
// - (NSString *)stringByPaddingToLength:(NSUInteger)newLength withString:(NSString *)padString startingAtIndex:(NSUInteger)padIndex;



// - (NSString *)stringByFoldingWithOptions:(NSStringCompareOptions)options locale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSString *)stringByReplacingCharactersInRange:(NSRange)range withString:(NSString *)replacement __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSString *NSStringTransform __attribute__((swift_wrapper(struct)));



// - (nullable NSString *)stringByApplyingTransform:(NSStringTransform)transform reverse:(BOOL)reverse __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStringTransform const NSStringTransformLatinToKatakana __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToHiragana __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToHangul __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToArabic __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToHebrew __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToThai __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToCyrillic __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformLatinToGreek __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformToLatin __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformMandarinToLatin __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformHiraganaToKatakana __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformFullwidthToHalfwidth __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformToXMLHex __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformToUnicodeName __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformStripCombiningMarks __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringTransform const NSStringTransformStripDiacritics __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// - (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;
// - (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

// @property (readonly, copy) NSString *description;

// @property (readonly) NSUInteger hash;






// - (instancetype)initWithCharactersNoCopy:(unichar *)characters length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer;
// - (instancetype)initWithCharactersNoCopy:(unichar *)chars length:(NSUInteger)len deallocator:(void(^_Nullable)(unichar *, NSUInteger))deallocator;
// - (instancetype)initWithCharacters:(const unichar *)characters length:(NSUInteger)length;
// - (nullable instancetype)initWithUTF8String:(const char *)nullTerminatedCString;
// - (instancetype)initWithString:(NSString *)aString;
// - (instancetype)initWithFormat:(NSString *)format, ... __attribute__((format(__NSString__, 1, 2)));
// - (instancetype)initWithFormat:(NSString *)format arguments:(va_list)argList __attribute__((format(__NSString__, 1, 0)));
// - (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale, ... __attribute__((format(__NSString__, 1, 3)));
// - (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale arguments:(va_list)argList __attribute__((format(__NSString__, 1, 0)));
// - (nullable instancetype)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
// - (nullable instancetype)initWithBytes:(const void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding;
// - (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;
// - (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding deallocator:(void(^_Nullable)(void *, NSUInteger))deallocator;

// + (instancetype)string;
// + (instancetype)stringWithString:(NSString *)string;
// + (instancetype)stringWithCharacters:(const unichar *)characters length:(NSUInteger)length;
// + (nullable instancetype)stringWithUTF8String:(const char *)nullTerminatedCString;
// + (instancetype)stringWithFormat:(NSString *)format, ... __attribute__((format(__NSString__, 1, 2)));
// + (instancetype)localizedStringWithFormat:(NSString *)format, ... __attribute__((format(__NSString__, 1, 2)));

// - (nullable instancetype)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding;
// + (nullable instancetype)stringWithCString:(const char *)cString encoding:(NSStringEncoding)enc;



// - (nullable instancetype)initWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
// - (nullable instancetype)initWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;
// + (nullable instancetype)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
// + (nullable instancetype)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;



// - (nullable instancetype)initWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
// - (nullable instancetype)initWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
// + (nullable instancetype)stringWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
// + (nullable instancetype)stringWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;

/* @end */


typedef NSString * NSStringEncodingDetectionOptionsKey __attribute__((swift_wrapper(enum)));

// @interface NSString (NSStringEncodingDetection)
#if 0
+ (NSStringEncoding)stringEncodingForData:(NSData *)data
                          encodingOptions:(nullable NSDictionary<NSStringEncodingDetectionOptionsKey, id> *)opts
                          convertedString:(NSString * _Nullable * _Nullable)string
                      usedLossyConversion:(nullable BOOL *)usedLossyConversion __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
#endif




extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionSuggestedEncodingsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionDisallowedEncodingsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionUseOnlySuggestedEncodingsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionAllowLossyKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionFromWindowsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLossySubstitutionKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLikelyLanguageKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */



// @interface NSString (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
/* @end */




#ifndef _REWRITER_typedef_NSMutableString
#define _REWRITER_typedef_NSMutableString
typedef struct objc_object NSMutableString;
typedef struct {} _objc_exc_NSMutableString;
#endif

struct NSMutableString_IMPL {
	struct NSString_IMPL NSString_IVARS;
};






// - (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

/* @end */


// @interface NSMutableString (NSMutableStringExtensionMethods)



// - (void)insertString:(NSString *)aString atIndex:(NSUInteger)loc;
// - (void)deleteCharactersInRange:(NSRange)range;
// - (void)appendString:(NSString *)aString;
// - (void)appendFormat:(NSString *)format, ... __attribute__((format(__NSString__, 1, 2)));
// - (void)setString:(NSString *)aString;



// - (NSUInteger)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange;



// - (BOOL)applyTransform:(NSStringTransform)transform reverse:(BOOL)reverse range:(NSRange)range updatedRange:(nullable NSRangePointer)resultingRange __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSMutableString *)initWithCapacity:(NSUInteger)capacity;
// + (NSMutableString *)stringWithCapacity:(NSUInteger)capacity;

/* @end */




extern "C" NSExceptionName const NSCharacterConversionException;
extern "C" NSExceptionName const NSParseErrorException;




// @interface NSString (NSExtendedStringPropertyListParsing)



// - (id)propertyList;
// - (nullable NSDictionary *)propertyListFromStringsFileFormat;

/* @end */


// @interface NSString (NSStringDeprecated)



// - (nullable const char *)cString __attribute__((objc_returns_inner_pointer)) __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -cStringUsingEncoding: instead")));
// - (nullable const char *)lossyCString __attribute__((objc_returns_inner_pointer)) __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -cStringUsingEncoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -cStringUsingEncoding: instead")));
// - (NSUInteger)cStringLength __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -lengthOfBytesUsingEncoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -lengthOfBytesUsingEncoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -lengthOfBytesUsingEncoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -lengthOfBytesUsingEncoding: instead")));
// - (void)getCString:(char *)bytes __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -getCString:maxLength:encoding: instead")));
// - (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -getCString:maxLength:encoding: instead")));
// - (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength range:(NSRange)aRange remainingRange:(nullable NSRangePointer)leftoverRange __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -getCString:maxLength:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -getCString:maxLength:encoding: instead")));

// - (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -writeToFile:atomically:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -writeToFile:atomically:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -writeToFile:atomically:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -writeToFile:atomically:error: instead")));
// - (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -writeToURL:atomically:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -writeToURL:atomically:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -writeToURL:atomically:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -writeToURL:atomically:error: instead")));

// - (nullable id)initWithContentsOfFile:(NSString *)path __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -initWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -initWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -initWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -initWithContentsOfFile:encoding:error: instead")));
// - (nullable id)initWithContentsOfURL:(NSURL *)url __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -initWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -initWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -initWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -initWithContentsOfURL:encoding:error: instead")));
// + (nullable id)stringWithContentsOfFile:(NSString *)path __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use +stringWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use +stringWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use +stringWithContentsOfFile:encoding:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use +stringWithContentsOfFile:encoding:error: instead")));
// + (nullable id)stringWithContentsOfURL:(NSURL *)url __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use +stringWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use +stringWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use +stringWithContentsOfURL:encoding:error: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use +stringWithContentsOfURL:encoding:error: instead")));

// - (nullable id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -initWithCString:encoding: instead")));
// - (nullable id)initWithCString:(const char *)bytes length:(NSUInteger)length __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -initWithCString:encoding: instead")));
// - (nullable id)initWithCString:(const char *)bytes __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -initWithCString:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -initWithCString:encoding: instead")));
// + (nullable id)stringWithCString:(const char *)bytes length:(NSUInteger)length __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use +stringWithCString:encoding:"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use +stringWithCString:encoding:"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use +stringWithCString:encoding:"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use +stringWithCString:encoding:")));
// + (nullable id)stringWithCString:(const char *)bytes __attribute__((availability(macos,introduced=10.0,deprecated=10.4,message="Use +stringWithCString:encoding: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=2.0,message="Use +stringWithCString:encoding: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use +stringWithCString:encoding: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use +stringWithCString:encoding: instead")));



// - (void)getCharacters:(unichar *)buffer;

/* @end */


enum {
    NSProprietaryStringEncoding = 65536
};
__attribute__((availability(swift, unavailable, message="Use String or NSString instead.")))

#ifndef _REWRITER_typedef_NSSimpleCString
#define _REWRITER_typedef_NSSimpleCString
typedef struct objc_object NSSimpleCString;
typedef struct {} _objc_exc_NSSimpleCString;
#endif

struct NSSimpleCString_IMPL {
	struct NSString_IMPL NSString_IVARS;
	char *bytes;
	int numBytes;
	int _unused;
};

/* @end */


__attribute__((availability(swift, unavailable, message="Use String or NSString instead.")))

#ifndef _REWRITER_typedef_NSConstantString
#define _REWRITER_typedef_NSConstantString
typedef struct objc_object NSConstantString;
typedef struct {} _objc_exc_NSConstantString;
#endif

struct NSConstantString_IMPL {
	struct NSSimpleCString_IMPL NSSimpleCString_IVARS;
};

/* @end */

#pragma clang assume_nonnull end
int main(int argc, char * argv[]) {


    NSObject *obj = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init"));
    {
        id _rethrow = 0;
        id _sync_obj = (id)obj;
        objc_sync_enter(_sync_obj);

        try {
	
            struct _SYNC_EXIT {
                _SYNC_EXIT(id arg) : sync_exit(arg) {
                    
                }
	
                ~_SYNC_EXIT() {
                    objc_sync_exit(sync_exit);
                }
	
                id sync_exit;
	
                /*
                 这在代码块结束时_sync_exit 变量会被释放，在_SYNC_EXIT结构体析构中执行了objc_sync_exit(sync_exit);
                 进行解锁
                 */
            } _sync_exit(_sync_obj);


        
            NSString *s = (NSString *)&__NSConstantStringImpl__var_folders_f3_6cl3xw6j4nl8414jl94d5yzm0000gn_T_clangMain_f4f397_mi_0;

    
        } catch (id e) {
            _rethrow = e;
        }

        {
            struct _FIN { _FIN(id reth) : rethrow(reth) {}
	
            ~_FIN() { if (rethrow) objc_exception_throw(rethrow); }
	
            id rethrow;
	
        }
            _fin_force_rethow(_rethrow);
        }

    }

    return 0;
}
static struct IMAGE_INFO { unsigned version; unsigned flag; } _OBJC_IMAGE_INFO = { 0, 2 };
