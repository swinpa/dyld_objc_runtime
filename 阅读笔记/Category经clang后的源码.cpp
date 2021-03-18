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




#pragma clang assume_nonnull end
// @class NSArray;
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

#ifndef _REWRITER_typedef_NSMapTable
#define _REWRITER_typedef_NSMapTable
typedef struct objc_object NSMapTable;
typedef struct {} _objc_exc_NSMapTable;
#endif


#pragma clang assume_nonnull begin







static const NSPointerFunctionsOptions NSMapTableStrongMemory __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = NSPointerFunctionsStrongMemory;
static const NSPointerFunctionsOptions NSMapTableZeroingWeakMemory __attribute__((availability(macos,introduced=10.5,deprecated=10.8,message="GC no longer supported"))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = NSPointerFunctionsZeroingWeakMemory;
static const NSPointerFunctionsOptions NSMapTableCopyIn __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSMapTableObjectPointerPersonality __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSMapTableWeakMemory __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = NSPointerFunctionsWeakMemory;

typedef NSUInteger NSMapTableOptions;

__attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSMapTable
#define _REWRITER_typedef_NSMapTable
typedef struct objc_object NSMapTable;
typedef struct {} _objc_exc_NSMapTable;
#endif

struct NSMapTable_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};





// @class NSNotification;
#ifndef _REWRITER_typedef_NSNotification
#define _REWRITER_typedef_NSNotification
typedef struct objc_object NSNotification;
typedef struct {} _objc_exc_NSNotification;
#endif

#ifndef _REWRITER_typedef_NSNotificationCenter
#define _REWRITER_typedef_NSNotificationCenter
typedef struct objc_object NSNotificationCenter;
typedef struct {} _objc_exc_NSNotificationCenter;
#endif

#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin

typedef NSUInteger NSPostingStyle; enum {
    NSPostWhenIdle = 1,
    NSPostASAP = 2,
    NSPostNow = 3
};

typedef NSUInteger NSNotificationCoalescing; enum {
    NSNotificationNoCoalescing = 0,
    NSNotificationCoalescingOnName = 1,
    NSNotificationCoalescingOnSender = 2
};


#ifndef _REWRITER_typedef_NSNotificationQueue
#define _REWRITER_typedef_NSNotificationQueue
typedef struct objc_object NSNotificationQueue;
typedef struct {} _objc_exc_NSNotificationQueue;
#endif

struct NSNotificationQueue_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _notificationCenter;
	id _asapQueue;
	id _asapObs;
	id _idleQueue;
	id _idleObs;
};

@property (class, readonly, strong) NSNotificationQueue *defaultQueue;

// - (instancetype)initWithNotificationCenter:(NSNotificationCenter *)notificationCenter __attribute__((objc_designated_initializer));

// - (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle;
// - (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle coalesceMask:(NSNotificationCoalescing)coalesceMask forModes:(nullable NSArray<NSRunLoopMode> *)modes;

// - (void)dequeueNotificationsMatching:(NSNotification *)notification coalesceMask:(NSUInteger)coalesceMask;

/* @end */

#pragma clang assume_nonnull end






#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSNull
#define _REWRITER_typedef_NSNull
typedef struct objc_object NSNull;
typedef struct {} _objc_exc_NSNull;
#endif

struct NSNull_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// + (NSNull *)null;

/* @end */

#pragma clang assume_nonnull end


// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif


#pragma clang assume_nonnull begin








__attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSOperation
#define _REWRITER_typedef_NSOperation
typedef struct objc_object NSOperation;
typedef struct {} _objc_exc_NSOperation;
#endif

struct NSOperation_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};

// - (void)start;
// - (void)main;

// @property (readonly, getter=isCancelled) BOOL cancelled;
// - (void)cancel;

// @property (readonly, getter=isExecuting) BOOL executing;
// @property (readonly, getter=isFinished) BOOL finished;
// @property (readonly, getter=isConcurrent) BOOL concurrent;
// @property (readonly, getter=isAsynchronous) BOOL asynchronous __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, getter=isReady) BOOL ready;

// - (void)addDependency:(NSOperation *)op;
// - (void)removeDependency:(NSOperation *)op;

// @property (readonly, copy) NSArray<NSOperation *> *dependencies;

typedef NSInteger NSOperationQueuePriority; enum {
 NSOperationQueuePriorityVeryLow = -8L,
 NSOperationQueuePriorityLow = -4L,
 NSOperationQueuePriorityNormal = 0,
 NSOperationQueuePriorityHigh = 4,
 NSOperationQueuePriorityVeryHigh = 8
};

// @property NSOperationQueuePriority queuePriority;

// @property (nullable, copy) void (^completionBlock)(void) __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)waitUntilFinished __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property double threadPriority __attribute__((availability(macos,introduced=10.6,deprecated=10.10,message="Not supported"))) __attribute__((availability(ios,introduced=4.0,deprecated=8.0,message="Not supported"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Not supported"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Not supported")));

// @property NSQualityOfService qualityOfService __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (nullable, copy) NSString *name __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */




__attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSBlockOperation
#define _REWRITER_typedef_NSBlockOperation
typedef struct objc_object NSBlockOperation;
typedef struct {} _objc_exc_NSBlockOperation;
#endif

struct NSBlockOperation_IMPL {
	struct NSOperation_IMPL NSOperation_IVARS;
};

// + (instancetype)blockOperationWithBlock:(void (^)(void))block;

// - (void)addExecutionBlock:(void (^)(void))block;
// @property (readonly, copy) NSArray<void (^)(void)> *executionBlocks;

/* @end */



__attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
__attribute__((availability(swift, unavailable, message="NSInvocation and related APIs not available")))

#ifndef _REWRITER_typedef_NSInvocationOperation
#define _REWRITER_typedef_NSInvocationOperation
typedef struct objc_object NSInvocationOperation;
typedef struct {} _objc_exc_NSInvocationOperation;
#endif

struct NSInvocationOperation_IMPL {
	struct NSOperation_IMPL NSOperation_IVARS;
};

// - (nullable instancetype)initWithTarget:(id)target selector:(SEL)sel object:(nullable id)arg;
// - (instancetype)initWithInvocation:(NSInvocation *)inv __attribute__((objc_designated_initializer));

// @property (readonly, retain) NSInvocation *invocation;

// @property (nullable, readonly, retain) id result;

/* @end */


extern "C" NSExceptionName const NSInvocationOperationVoidResultException __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSExceptionName const NSInvocationOperationCancelledException __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

static const NSInteger NSOperationQueueDefaultMaxConcurrentOperationCount = -1;

__attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSOperationQueue
#define _REWRITER_typedef_NSOperationQueue
typedef struct objc_object NSOperationQueue;
typedef struct {} _objc_exc_NSOperationQueue;
#endif

struct NSOperationQueue_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};

// @property (readonly, strong) NSProgress *progress __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));

// - (void)addOperation:(NSOperation *)op;
// - (void)addOperations:(NSArray<NSOperation *> *)ops waitUntilFinished:(BOOL)wait __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)addOperationWithBlock:(void (^)(void))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// - (void)addBarrierBlock:(void (^)(void))barrier __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));

// @property NSInteger maxConcurrentOperationCount;

// @property (getter=isSuspended) BOOL suspended;

// @property (nullable, copy) NSString *name __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property NSQualityOfService qualityOfService __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (nullable, assign ) dispatch_queue_t underlyingQueue __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)cancelAllOperations;

// - (void)waitUntilAllOperationsAreFinished;

@property (class, readonly, strong, nullable) NSOperationQueue *currentQueue __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
@property (class, readonly, strong) NSOperationQueue *mainQueue __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSOperationQueue (NSDeprecated)



// @property (readonly, copy) NSArray<__kindof NSOperation *> *operations __attribute__((availability(macos,introduced=10.5,deprecated=100000,message="access to operations is inherently a race condition, it should not be used. For barrier style behaviors please use addBarrierBlock: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=100000,message="access to operations is inherently a race condition, it should not be used. For barrier style behaviors please use addBarrierBlock: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,message="access to operations is inherently a race condition, it should not be used. For barrier style behaviors please use addBarrierBlock: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,message="access to operations is inherently a race condition, it should not be used. For barrier style behaviors please use addBarrierBlock: instead")));

// @property (readonly) NSUInteger operationCount __attribute__((availability(macos,introduced=10.6,deprecated=100000,replacement="progress.completedUnitCount"))) __attribute__((availability(ios,introduced=4.0,deprecated=100000,replacement="progress.completedUnitCount"))) __attribute__((availability(watchos,introduced=2.0,deprecated=100000,replacement="progress.completedUnitCount"))) __attribute__((availability(tvos,introduced=9.0,deprecated=100000,replacement="progress.completedUnitCount")));

/* @end */

#pragma clang assume_nonnull end







// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
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


#pragma clang assume_nonnull begin



__attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSOrthography
#define _REWRITER_typedef_NSOrthography
typedef struct objc_object NSOrthography;
typedef struct {} _objc_exc_NSOrthography;
#endif

struct NSOrthography_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};



// @property (readonly, copy) NSString *dominantScript;
// @property (readonly, copy) NSDictionary<NSString *, NSArray<NSString *> *> *languageMap;
// - (instancetype)initWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

/* @end */


// @interface NSOrthography (NSOrthographyExtended)


// - (nullable NSArray<NSString *> *)languagesForScript:(NSString *)script __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (nullable NSString *)dominantLanguageForScript:(NSString *)script __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// @property (readonly, copy) NSString *dominantLanguage __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSArray<NSString *> *allScripts __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSArray<NSString *> *allLanguages __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// + (instancetype)defaultOrthographyForLanguage:(NSString *)language __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));

/* @end */


// @interface NSOrthography (NSOrthographyCreation)

// + (instancetype)orthographyWithDominantScript:(NSString *)script languageMap:(NSDictionary<NSString *, NSArray<NSString *> *> *)map __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end

#pragma clang assume_nonnull begin
__attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSPointerArray
#define _REWRITER_typedef_NSPointerArray
typedef struct objc_object NSPointerArray;
typedef struct {} _objc_exc_NSPointerArray;
#endif

struct NSPointerArray_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// - (instancetype)initWithOptions:(NSPointerFunctionsOptions)options __attribute__((objc_designated_initializer));
// - (instancetype)initWithPointerFunctions:(NSPointerFunctions *)functions __attribute__((objc_designated_initializer));

// + (NSPointerArray *)pointerArrayWithOptions:(NSPointerFunctionsOptions)options;
// + (NSPointerArray *)pointerArrayWithPointerFunctions:(NSPointerFunctions *)functions;


// @property (readonly, copy) NSPointerFunctions *pointerFunctions;

// - (nullable void *)pointerAtIndex:(NSUInteger)index;


// - (void)addPointer:(nullable void *)pointer;
// - (void)removePointerAtIndex:(NSUInteger)index;
// - (void)insertPointer:(nullable void *)item atIndex:(NSUInteger)index;

// - (void)replacePointerAtIndex:(NSUInteger)index withPointer:(nullable void *)item;

// - (void)compact;



// @property NSUInteger count;

/* @end */



// @interface NSPointerArray (NSPointerArrayConveniences)







// + (NSPointerArray *)strongObjectsPointerArray __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSPointerArray *)weakObjectsPointerArray __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) NSArray *allObjects;

/* @end */

#pragma clang assume_nonnull end









typedef int NSSocketNativeHandle;

// @class NSRunLoop;
#ifndef _REWRITER_typedef_NSRunLoop
#define _REWRITER_typedef_NSRunLoop
typedef struct objc_object NSRunLoop;
typedef struct {} _objc_exc_NSRunLoop;
#endif

#ifndef _REWRITER_typedef_NSMutableArray
#define _REWRITER_typedef_NSMutableArray
typedef struct objc_object NSMutableArray;
typedef struct {} _objc_exc_NSMutableArray;
#endif

#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

// @class NSConnection;
#ifndef _REWRITER_typedef_NSConnection
#define _REWRITER_typedef_NSConnection
typedef struct objc_object NSConnection;
typedef struct {} _objc_exc_NSConnection;
#endif

#ifndef _REWRITER_typedef_NSPortMessage
#define _REWRITER_typedef_NSPortMessage
typedef struct objc_object NSPortMessage;
typedef struct {} _objc_exc_NSPortMessage;
#endif

// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

// @protocol NSPortDelegate, NSMachPortDelegate;

#pragma clang assume_nonnull begin

extern "C" NSNotificationName const NSPortDidBecomeInvalidNotification;


#ifndef _REWRITER_typedef_NSPort
#define _REWRITER_typedef_NSPort
typedef struct objc_object NSPort;
typedef struct {} _objc_exc_NSPort;
#endif

struct NSPort_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};








// + (NSPort *)port;

// - (void)invalidate;
// @property (readonly, getter=isValid) BOOL valid;

// - (void)setDelegate:(nullable id <NSPortDelegate>)anObject;
// - (nullable id <NSPortDelegate>)delegate;





// - (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;
// - (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;



// @property (readonly) NSUInteger reservedSpaceLength;
// - (BOOL)sendBeforeDate:(NSDate *)limitDate components:(nullable NSMutableArray *)components from:(nullable NSPort *) receivePort reserved:(NSUInteger)headerSpaceReserved;
// - (BOOL)sendBeforeDate:(NSDate *)limitDate msgid:(NSUInteger)msgID components:(nullable NSMutableArray *)components from:(nullable NSPort *)receivePort reserved:(NSUInteger)headerSpaceReserved;
/* @end */


// @protocol NSPortDelegate <NSObject>
/* @optional */

// - (void)handlePortMessage:(NSPortMessage *)message;



/* @end */




__attribute__((objc_arc_weak_reference_unavailable))

#ifndef _REWRITER_typedef_NSMachPort
#define _REWRITER_typedef_NSMachPort
typedef struct objc_object NSMachPort;
typedef struct {} _objc_exc_NSMachPort;
#endif

struct NSMachPort_IMPL {
	struct NSPort_IMPL NSPort_IVARS;
	id _delegate;
	NSUInteger _flags;
	uint32_t _machPort;
	NSUInteger _reserved;
};


// + (NSPort *)portWithMachPort:(uint32_t)machPort;
// - (instancetype)initWithMachPort:(uint32_t)machPort __attribute__((objc_designated_initializer));

// - (void)setDelegate:(nullable id <NSMachPortDelegate>)anObject;
// - (nullable id <NSMachPortDelegate>)delegate;

typedef NSUInteger NSMachPortOptions; enum {
    NSMachPortDeallocateNone = 0,
    NSMachPortDeallocateSendRight = (1UL << 0),
    NSMachPortDeallocateReceiveRight = (1UL << 1)
} __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// + (NSPort *)portWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (instancetype)initWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));

// @property (readonly) uint32_t machPort;

// - (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;
// - (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;




/* @end */


// @protocol NSMachPortDelegate <NSPortDelegate>
/* @optional */



// - (void)handleMachMessage:(void *)msg;

/* @end */






__attribute__((objc_arc_weak_reference_unavailable))

#ifndef _REWRITER_typedef_NSMessagePort
#define _REWRITER_typedef_NSMessagePort
typedef struct objc_object NSMessagePort;
typedef struct {} _objc_exc_NSMessagePort;
#endif

struct NSMessagePort_IMPL {
	struct NSPort_IMPL NSPort_IVARS;
	void *_port;
	id _delegate;
};


/* @end */

#pragma clang assume_nonnull end








#pragma clang assume_nonnull begin

enum {
    NSWindowsNTOperatingSystem = 1,
    NSWindows95OperatingSystem,
    NSSolarisOperatingSystem,
    NSHPUXOperatingSystem,
    NSMACHOperatingSystem,
    NSSunOSOperatingSystem,
    NSOSF1OperatingSystem
} __attribute__((availability(macos,introduced=10.0,deprecated=10.10,message="Not supported"))) __attribute__((availability(ios,introduced=2.0,deprecated=8.0,message="Not supported"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Not supported"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Not supported")));

typedef struct {
    NSInteger majorVersion;
    NSInteger minorVersion;
    NSInteger patchVersion;
} NSOperatingSystemVersion;

// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

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



#ifndef _REWRITER_typedef_NSProcessInfo
#define _REWRITER_typedef_NSProcessInfo
typedef struct objc_object NSProcessInfo;
typedef struct {} _objc_exc_NSProcessInfo;
#endif

struct NSProcessInfo_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSDictionary *environment;
	NSArray *arguments;
	NSString *hostName;
	NSString *name;
	NSInteger automaticTerminationOptOutCounter;
};


@property (class, readonly, strong) NSProcessInfo *processInfo;

// @property (readonly, copy) NSDictionary<NSString *, NSString *> *environment;
// @property (readonly, copy) NSArray<NSString *> *arguments;
// @property (readonly, copy) NSString *hostName;
// @property (copy) NSString *processName;
// @property (readonly) int processIdentifier;

// @property (readonly, copy) NSString *globallyUniqueString;

// - (NSUInteger)operatingSystem __attribute__((availability(macos,introduced=10.0,deprecated=10.10,message="-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=8.0,message="-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead")));
// - (NSString *)operatingSystemName __attribute__((availability(macos,introduced=10.0,deprecated=10.10,message="-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=8.0,message="-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead")));


// @property (readonly, copy) NSString *operatingSystemVersionString;

// @property (readonly) NSOperatingSystemVersion operatingSystemVersion __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly) NSUInteger processorCount __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) NSUInteger activeProcessorCount __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) unsigned long long physicalMemory __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (BOOL) isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion)version __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly) NSTimeInterval systemUptime __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// - (void)disableSuddenTermination __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
// - (void)enableSuddenTermination __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));







// - (void)disableAutomaticTermination:(NSString *)reason __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
// - (void)enableAutomaticTermination:(NSString *)reason __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));






// @property BOOL automaticTerminationSupportEnabled __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));

/* @end */

typedef uint64_t NSActivityOptions; enum {
    NSActivityIdleDisplaySleepDisabled = (1ULL << 40),


    NSActivityIdleSystemSleepDisabled = (1ULL << 20),


    NSActivitySuddenTerminationDisabled = (1ULL << 14),


    NSActivityAutomaticTerminationDisabled = (1ULL << 15),





    NSActivityUserInitiated = (0x00FFFFFFULL | NSActivityIdleSystemSleepDisabled),
    NSActivityUserInitiatedAllowingIdleSystemSleep = (NSActivityUserInitiated & ~NSActivityIdleSystemSleepDisabled),


    NSActivityBackground = 0x000000FFULL,


    NSActivityLatencyCritical = 0xFF00000000ULL,
} __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @interface NSProcessInfo (NSProcessInfoActivity)



// - (id <NSObject>)beginActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// - (void)endActivity:(id <NSObject>)activity __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// - (void)performActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason usingBlock:(void (^)(void))block __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));




// - (void)performExpiringActivityWithReason:(NSString *)reason usingBlock:(void(^)(BOOL expired))block __attribute__((availability(ios,introduced=8.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));

/* @end */


// @interface NSProcessInfo (NSUserInformation)

// @property (readonly, copy) NSString *userName __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
// @property (readonly, copy) NSString *fullUserName __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));

/* @end */



typedef NSInteger NSProcessInfoThermalState; enum {

    NSProcessInfoThermalStateNominal,


    NSProcessInfoThermalStateFair,


    NSProcessInfoThermalStateSerious,


    NSProcessInfoThermalStateCritical
} __attribute__((availability(macosx,introduced=10.10.3))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));

// @interface NSProcessInfo (NSProcessInfoThermalState)


// @property (readonly) NSProcessInfoThermalState thermalState __attribute__((availability(macosx,introduced=10.10.3))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));

/* @end */


// @interface NSProcessInfo (NSProcessInfoPowerState)


// @property (readonly, getter=isLowPowerModeEnabled) BOOL lowPowerModeEnabled __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));

/* @end */

extern "C" NSNotificationName const NSProcessInfoThermalStateDidChangeNotification __attribute__((availability(macosx,introduced=10.10.3))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
extern "C" NSNotificationName const NSProcessInfoPowerStateDidChangeNotification __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));

// @interface NSProcessInfo (NSProcessInfoPlatform)

// @property (readonly, getter=isMacCatalystApp) BOOL macCatalystApp __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

/* @end */

#pragma clang assume_nonnull end







// @class NSMethodSignature;
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


#pragma clang assume_nonnull begin

__attribute__((objc_root_class))

#ifndef _REWRITER_typedef_NSProxy
#define _REWRITER_typedef_NSProxy
typedef struct objc_object NSProxy;
typedef struct {} _objc_exc_NSProxy;
#endif

struct NSProxy_IMPL {
	Class isa;
};


// + (id)alloc;
// + (id)allocWithZone:(nullable NSZone *)zone ;
// + (Class)class;

// - (void)forwardInvocation:(NSInvocation *)invocation;
// - (nullable NSMethodSignature *)methodSignatureForSelector:(SEL)sel __attribute__((availability(swift, unavailable, message="NSInvocation and related APIs not available")));
// - (void)dealloc;
// - (void)finalize;
// @property (readonly, copy) NSString *description;
// @property (readonly, copy) NSString *debugDescription;
// + (BOOL)respondsToSelector:(SEL)aSelector;

// - (BOOL)allowsWeakReference __attribute__((availability(macos,unavailable))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
// - (BOOL)retainWeakReference __attribute__((availability(macos,unavailable))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));



/* @end */

#pragma clang assume_nonnull end















// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
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

#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

#ifndef _REWRITER_typedef_NSTimeZone
#define _REWRITER_typedef_NSTimeZone
typedef struct objc_object NSTimeZone;
typedef struct {} _objc_exc_NSTimeZone;
#endif

#ifndef _REWRITER_typedef_NSOrthography
#define _REWRITER_typedef_NSOrthography
typedef struct objc_object NSOrthography;
typedef struct {} _objc_exc_NSOrthography;
#endif

#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif

#ifndef _REWRITER_typedef_NSRegularExpression
#define _REWRITER_typedef_NSRegularExpression
typedef struct objc_object NSRegularExpression;
typedef struct {} _objc_exc_NSRegularExpression;
#endif


#pragma clang assume_nonnull begin



typedef uint64_t NSTextCheckingType; enum {
    NSTextCheckingTypeOrthography = 1ULL << 0,
    NSTextCheckingTypeSpelling = 1ULL << 1,
    NSTextCheckingTypeGrammar = 1ULL << 2,
    NSTextCheckingTypeDate = 1ULL << 3,
    NSTextCheckingTypeAddress = 1ULL << 4,
    NSTextCheckingTypeLink = 1ULL << 5,
    NSTextCheckingTypeQuote = 1ULL << 6,
    NSTextCheckingTypeDash = 1ULL << 7,
    NSTextCheckingTypeReplacement = 1ULL << 8,
    NSTextCheckingTypeCorrection = 1ULL << 9,
    NSTextCheckingTypeRegularExpression __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1ULL << 10,
    NSTextCheckingTypePhoneNumber __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1ULL << 11,
    NSTextCheckingTypeTransitInformation __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1ULL << 12
};

typedef uint64_t NSTextCheckingTypes;
enum {
    NSTextCheckingAllSystemTypes = 0xffffffffULL,
    NSTextCheckingAllCustomTypes = 0xffffffffULL << 32,
    NSTextCheckingAllTypes = (NSTextCheckingAllSystemTypes | NSTextCheckingAllCustomTypes)
};

typedef NSString *NSTextCheckingKey __attribute__((swift_wrapper(struct)));

__attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSTextCheckingResult
#define _REWRITER_typedef_NSTextCheckingResult
typedef struct objc_object NSTextCheckingResult;
typedef struct {} _objc_exc_NSTextCheckingResult;
#endif

struct NSTextCheckingResult_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};



// @property (readonly) NSTextCheckingType resultType;
// @property (readonly) NSRange range;

/* @end */


// @interface NSTextCheckingResult (NSTextCheckingResultOptional)


// @property (nullable, readonly, copy) NSOrthography *orthography;
// @property (nullable, readonly, copy) NSArray<NSDictionary<NSString *, id> *> *grammarDetails;
// @property (nullable, readonly, copy) NSDate *date;
// @property (nullable, readonly, copy) NSTimeZone *timeZone;
// @property (readonly) NSTimeInterval duration;
// @property (nullable, readonly, copy) NSDictionary<NSTextCheckingKey, NSString *> *components __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, readonly, copy) NSURL *URL;
// @property (nullable, readonly, copy) NSString *replacementString;
// @property (nullable, readonly, copy) NSArray<NSString *> *alternativeStrings __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, readonly, copy) NSRegularExpression *regularExpression __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, readonly, copy) NSString *phoneNumber __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// @property (readonly) NSUInteger numberOfRanges __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSRange)rangeAtIndex:(NSUInteger)idx __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSRange)rangeWithName:(NSString *)name __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// - (NSTextCheckingResult *)resultByAdjustingRangesWithOffset:(NSInteger)offset __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (nullable, readonly, copy) NSDictionary<NSTextCheckingKey, NSString *> *addressComponents;

/* @end */




extern "C" NSTextCheckingKey const NSTextCheckingNameKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingJobTitleKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingOrganizationKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingStreetKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingCityKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingStateKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingZIPKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingCountryKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingPhoneKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingAirlineKey __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSTextCheckingKey const NSTextCheckingFlightKey __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// @interface NSTextCheckingResult (NSTextCheckingResultCreation)


// + (NSTextCheckingResult *)orthographyCheckingResultWithRange:(NSRange)range orthography:(NSOrthography *)orthography;
// + (NSTextCheckingResult *)spellCheckingResultWithRange:(NSRange)range;
// + (NSTextCheckingResult *)grammarCheckingResultWithRange:(NSRange)range details:(NSArray<NSDictionary<NSString *, id> *> *)details;
// + (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date;
// + (NSTextCheckingResult *)dateCheckingResultWithRange:(NSRange)range date:(NSDate *)date timeZone:(NSTimeZone *)timeZone duration:(NSTimeInterval)duration;
// + (NSTextCheckingResult *)addressCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSTextCheckingKey, NSString *> *)components;
// + (NSTextCheckingResult *)linkCheckingResultWithRange:(NSRange)range URL:(NSURL *)url;
// + (NSTextCheckingResult *)quoteCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
// + (NSTextCheckingResult *)dashCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
// + (NSTextCheckingResult *)replacementCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
// + (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString;
// + (NSTextCheckingResult *)correctionCheckingResultWithRange:(NSRange)range replacementString:(NSString *)replacementString alternativeStrings:(NSArray<NSString *> *)alternativeStrings __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSTextCheckingResult *)regularExpressionCheckingResultWithRanges:(NSRangePointer)ranges count:(NSUInteger)count regularExpression:(NSRegularExpression *)regularExpression __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSTextCheckingResult *)phoneNumberCheckingResultWithRange:(NSRange)range phoneNumber:(NSString *)phoneNumber __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSTextCheckingResult *)transitInformationCheckingResultWithRange:(NSRange)range components:(NSDictionary<NSTextCheckingKey, NSString *> *)components __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end

// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif


#pragma clang assume_nonnull begin




typedef NSUInteger NSRegularExpressionOptions; enum {
   NSRegularExpressionCaseInsensitive = 1 << 0,
   NSRegularExpressionAllowCommentsAndWhitespace = 1 << 1,
   NSRegularExpressionIgnoreMetacharacters = 1 << 2,
   NSRegularExpressionDotMatchesLineSeparators = 1 << 3,
   NSRegularExpressionAnchorsMatchLines = 1 << 4,
   NSRegularExpressionUseUnixLineSeparators = 1 << 5,
   NSRegularExpressionUseUnicodeWordBoundaries = 1 << 6
};

__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSRegularExpression
#define _REWRITER_typedef_NSRegularExpression
typedef struct objc_object NSRegularExpression;
typedef struct {} _objc_exc_NSRegularExpression;
#endif

struct NSRegularExpression_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSString *_pattern;
	NSUInteger _options;
	void *_internal;
	id _reserved1;
	int32_t _checkout;
	int32_t _reserved2;
};




// + (nullable NSRegularExpression *)regularExpressionWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error;
// - (nullable instancetype)initWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options error:(NSError **)error __attribute__((objc_designated_initializer));

// @property (readonly, copy) NSString *pattern;
// @property (readonly) NSRegularExpressionOptions options;
// @property (readonly) NSUInteger numberOfCaptureGroups;



// + (NSString *)escapedPatternForString:(NSString *)string;

/* @end */



typedef NSUInteger NSMatchingOptions; enum {
   NSMatchingReportProgress = 1 << 0,
   NSMatchingReportCompletion = 1 << 1,
   NSMatchingAnchored = 1 << 2,
   NSMatchingWithTransparentBounds = 1 << 3,
   NSMatchingWithoutAnchoringBounds = 1 << 4
};

typedef NSUInteger NSMatchingFlags; enum {
   NSMatchingProgress = 1 << 0,
   NSMatchingCompleted = 1 << 1,
   NSMatchingHitEnd = 1 << 2,
   NSMatchingRequiredEnd = 1 << 3,
   NSMatchingInternalError = 1 << 4
};

// @interface NSRegularExpression (NSMatching)




// - (void)enumerateMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range usingBlock:(void (__attribute__((noescape)) ^)(NSTextCheckingResult * _Nullable result, NSMatchingFlags flags, BOOL *stop))block;

// - (NSArray<NSTextCheckingResult *> *)matchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
// - (NSUInteger)numberOfMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
// - (nullable NSTextCheckingResult *)firstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
// - (NSRange)rangeOfFirstMatchInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range;
/* @end */



// @interface NSRegularExpression (NSReplacement)



// - (NSString *)stringByReplacingMatchesInString:(NSString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;
// - (NSUInteger)replaceMatchesInString:(NSMutableString *)string options:(NSMatchingOptions)options range:(NSRange)range withTemplate:(NSString *)templ;



// - (NSString *)replacementStringForResult:(NSTextCheckingResult *)result inString:(NSString *)string offset:(NSInteger)offset template:(NSString *)templ;



// + (NSString *)escapedTemplateForString:(NSString *)string;

/* @end */


__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSDataDetector
#define _REWRITER_typedef_NSDataDetector
typedef struct objc_object NSDataDetector;
typedef struct {} _objc_exc_NSDataDetector;
#endif

struct NSDataDetector_IMPL {
	struct NSRegularExpression_IMPL NSRegularExpression_IVARS;
	NSTextCheckingTypes _types;
};




// + (nullable NSDataDetector *)dataDetectorWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error;
// - (nullable instancetype)initWithTypes:(NSTextCheckingTypes)checkingTypes error:(NSError **)error __attribute__((objc_designated_initializer));

// @property (readonly) NSTextCheckingTypes checkingTypes;

/* @end */

#pragma clang assume_nonnull end



#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSSortDescriptor
#define _REWRITER_typedef_NSSortDescriptor
typedef struct objc_object NSSortDescriptor;
typedef struct {} _objc_exc_NSSortDescriptor;
#endif

struct NSSortDescriptor_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSUInteger _sortDescriptorFlags;
	NSString *_key;
	SEL _selector;
	id _selectorOrBlock;
};


// + (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// - (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending;
// - (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector;
// - (nullable instancetype)initWithCoder:(NSCoder *)coder;

// @property (nullable, readonly, copy) NSString *key;
// @property (readonly) BOOL ascending;
// @property (nullable, readonly) SEL selector;

// - (void)allowEvaluation __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// + (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly) NSComparator comparator __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;
// @property (readonly, retain) id reversedSortDescriptor;

/* @end */


// @interface NSSet<ObjectType> (NSSortDescriptorSorting)

// - (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSArray<ObjectType> (NSSortDescriptorSorting)

// - (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;

/* @end */


// @interface NSMutableArray<ObjectType> (NSSortDescriptorSorting)

// - (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;

/* @end */


// @interface NSOrderedSet<ObjectType> (NSKeyValueSorting)


// - (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSMutableOrderedSet<ObjectType> (NSKeyValueSorting)


// - (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end







// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

#ifndef _REWRITER_typedef_NSHost
#define _REWRITER_typedef_NSHost
typedef struct objc_object NSHost;
typedef struct {} _objc_exc_NSHost;
#endif

#ifndef _REWRITER_typedef_NSInputStream
#define _REWRITER_typedef_NSInputStream
typedef struct objc_object NSInputStream;
typedef struct {} _objc_exc_NSInputStream;
#endif

#ifndef _REWRITER_typedef_NSOutputStream
#define _REWRITER_typedef_NSOutputStream
typedef struct objc_object NSOutputStream;
typedef struct {} _objc_exc_NSOutputStream;
#endif

#ifndef _REWRITER_typedef_NSRunLoop
#define _REWRITER_typedef_NSRunLoop
typedef struct objc_object NSRunLoop;
typedef struct {} _objc_exc_NSRunLoop;
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

// @protocol NSStreamDelegate;

typedef NSString * NSStreamPropertyKey __attribute__((swift_wrapper(struct)));

#pragma clang assume_nonnull begin

typedef NSUInteger NSStreamStatus; enum {
    NSStreamStatusNotOpen = 0,
    NSStreamStatusOpening = 1,
    NSStreamStatusOpen = 2,
    NSStreamStatusReading = 3,
    NSStreamStatusWriting = 4,
    NSStreamStatusAtEnd = 5,
    NSStreamStatusClosed = 6,
    NSStreamStatusError = 7
};

typedef NSUInteger NSStreamEvent; enum {
    NSStreamEventNone = 0,
    NSStreamEventOpenCompleted = 1UL << 0,
    NSStreamEventHasBytesAvailable = 1UL << 1,
    NSStreamEventHasSpaceAvailable = 1UL << 2,
    NSStreamEventErrorOccurred = 1UL << 3,
    NSStreamEventEndEncountered = 1UL << 4
};




#ifndef _REWRITER_typedef_NSStream
#define _REWRITER_typedef_NSStream
typedef struct objc_object NSStream;
typedef struct {} _objc_exc_NSStream;
#endif

struct NSStream_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};

// - (void)open;
// - (void)close;

// @property (nullable, assign) id <NSStreamDelegate> delegate;


// - (nullable id)propertyForKey:(NSStreamPropertyKey)key;
// - (BOOL)setProperty:(nullable id)property forKey:(NSStreamPropertyKey)key;

// - (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;
// - (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

// @property (readonly) NSStreamStatus streamStatus;
// @property (nullable, readonly, copy) NSError *streamError;
/* @end */





#ifndef _REWRITER_typedef_NSInputStream
#define _REWRITER_typedef_NSInputStream
typedef struct objc_object NSInputStream;
typedef struct {} _objc_exc_NSInputStream;
#endif

struct NSInputStream_IMPL {
	struct NSStream_IMPL NSStream_IVARS;
};

// - (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;


// - (BOOL)getBuffer:(uint8_t * _Nullable * _Nonnull)buffer length:(NSUInteger *)len;


// @property (readonly) BOOL hasBytesAvailable;


// - (instancetype)initWithData:(NSData *)data __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithURL:(NSURL *)url __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));

/* @end */





#ifndef _REWRITER_typedef_NSOutputStream
#define _REWRITER_typedef_NSOutputStream
typedef struct objc_object NSOutputStream;
typedef struct {} _objc_exc_NSOutputStream;
#endif

struct NSOutputStream_IMPL {
	struct NSStream_IMPL NSStream_IVARS;
};

// - (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;


// @property (readonly) BOOL hasSpaceAvailable;


// - (instancetype)initToMemory __attribute__((objc_designated_initializer));
// - (instancetype)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));

/* @end */



// @interface NSStream (NSSocketStreamCreationExtensions)

// + (void)getStreamsToHostWithName:(NSString *)hostname port:(NSInteger)port inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,unavailable)));





/* @end */


// @interface NSStream (NSStreamBoundPairCreationExtensions)
// + (void)getBoundStreamsWithBufferSize:(NSUInteger)bufferSize inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */



// @interface NSInputStream (NSInputStreamExtensions)
// - (nullable instancetype)initWithFileAtPath:(NSString *)path;

// + (nullable instancetype)inputStreamWithData:(NSData *)data;
// + (nullable instancetype)inputStreamWithFileAtPath:(NSString *)path;
// + (nullable instancetype)inputStreamWithURL:(NSURL *)url __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */



// @interface NSOutputStream (NSOutputStreamExtensions)
// - (nullable instancetype)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

// + (instancetype)outputStreamToMemory;
// + (instancetype)outputStreamToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
// + (instancetype)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
// + (nullable instancetype)outputStreamWithURL:(NSURL *)url append:(BOOL)shouldAppend __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */


// @protocol NSStreamDelegate <NSObject>
/* @optional */
// - (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
/* @end */




extern "C" NSStreamPropertyKey const NSStreamSocketSecurityLevelKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSString * NSStreamSocketSecurityLevel __attribute__((swift_wrapper(enum)));

extern "C" NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNone __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv2 __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv3 __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelTLSv1 __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNegotiatedSSL __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamPropertyKey const NSStreamSOCKSProxyConfigurationKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSString * NSStreamSOCKSProxyConfiguration __attribute__((swift_wrapper(enum)));

extern "C" NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyHostKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPortKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyVersionKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyUserKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPasswordKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


typedef NSString * NSStreamSOCKSProxyVersion __attribute__((swift_wrapper(enum)));

extern "C" NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion4 __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion5 __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSStreamPropertyKey const NSStreamDataWrittenToMemoryStreamKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSStreamPropertyKey const NSStreamFileCurrentOffsetKey __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



extern "C" NSErrorDomain const NSStreamSocketSSLErrorDomain __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSErrorDomain const NSStreamSOCKSErrorDomain __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






extern "C" NSStreamPropertyKey const NSStreamNetworkServiceType __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSString * NSStreamNetworkServiceTypeValue __attribute__((swift_wrapper(enum)));


extern "C" NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoIP __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVideo __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeBackground __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoice __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeCallSignaling __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0)));
#pragma clang assume_nonnull end










// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSMutableDictionary
#define _REWRITER_typedef_NSMutableDictionary
typedef struct objc_object NSMutableDictionary;
typedef struct {} _objc_exc_NSMutableDictionary;
#endif

#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

#ifndef _REWRITER_typedef_NSNumber
#define _REWRITER_typedef_NSNumber
typedef struct objc_object NSNumber;
typedef struct {} _objc_exc_NSNumber;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSThread
#define _REWRITER_typedef_NSThread
typedef struct objc_object NSThread;
typedef struct {} _objc_exc_NSThread;
#endif

struct NSThread_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _private;
	uint8_t _bytes[44];
};


@property (class, readonly, strong) NSThread *currentThread;

// + (void)detachNewThreadWithBlock:(void (^)(void))block __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0)));
// + (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

// + (BOOL)isMultiThreaded;

// @property (readonly, retain) NSMutableDictionary *threadDictionary;

// + (void)sleepUntilDate:(NSDate *)date;
// + (void)sleepForTimeInterval:(NSTimeInterval)ti;

// + (void)exit;

// + (double)threadPriority;
// + (BOOL)setThreadPriority:(double)p;

// @property double threadPriority __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property NSQualityOfService qualityOfService __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

@property (class, readonly, copy) NSArray<NSNumber *> *callStackReturnAddresses __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
@property (class, readonly, copy) NSArray<NSString *> *callStackSymbols __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (nullable, copy) NSString *name __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property NSUInteger stackSize __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly) BOOL isMainThread __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
@property (class, readonly) BOOL isMainThread __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
@property (class, readonly, strong) NSThread *mainThread __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (instancetype)init __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));
// - (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullable id)argument __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (instancetype)initWithBlock:(void (^)(void))block __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0)));

// @property (readonly, getter=isExecuting) BOOL executing __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, getter=isFinished) BOOL finished __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, getter=isCancelled) BOOL cancelled __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)cancel __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)start __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)main __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


extern "C" NSNotificationName const NSWillBecomeMultiThreadedNotification;
extern "C" NSNotificationName const NSDidBecomeSingleThreadedNotification;
extern "C" NSNotificationName const NSThreadWillExitNotification;

// @interface NSObject (NSThreadPerformAdditions)

// - (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array;
// - (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait;


// - (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end








// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
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

#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSLocale
#define _REWRITER_typedef_NSLocale
typedef struct objc_object NSLocale;
typedef struct {} _objc_exc_NSLocale;
#endif


#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSTimeZone
#define _REWRITER_typedef_NSTimeZone
typedef struct objc_object NSTimeZone;
typedef struct {} _objc_exc_NSTimeZone;
#endif

struct NSTimeZone_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// @property (readonly, copy) NSString *name;
// @property (readonly, copy) NSData *data;

// - (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
// - (nullable NSString *)abbreviationForDate:(NSDate *)aDate;
// - (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
// - (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (nullable NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSTimeZone (NSExtendedTimeZone)

@property (class, readonly, copy) NSTimeZone *systemTimeZone;
// + (void)resetSystemTimeZone;

@property (class, copy) NSTimeZone *defaultTimeZone;

@property (class, readonly, copy) NSTimeZone *localTimeZone;

@property (class, readonly, copy) NSArray<NSString *> *knownTimeZoneNames;

@property (class, copy) NSDictionary<NSString *, NSString *> *abbreviationDictionary __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// + (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;

@property (class, readonly, copy) NSString *timeZoneDataVersion __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly) NSInteger secondsFromGMT;
// @property (nullable, readonly, copy) NSString *abbreviation;
// @property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
// @property (readonly) NSTimeInterval daylightSavingTimeOffset __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, readonly, copy) NSDate *nextDaylightSavingTimeTransition __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) NSString *description;

// - (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

typedef NSInteger NSTimeZoneNameStyle; enum {
 NSTimeZoneNameStyleStandard,
 NSTimeZoneNameStyleShortStandard,
 NSTimeZoneNameStyleDaylightSaving,
 NSTimeZoneNameStyleShortDaylightSaving,
 NSTimeZoneNameStyleGeneric,
 NSTimeZoneNameStyleShortGeneric
};

// - (nullable NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(nullable NSLocale *)locale __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSTimeZone (NSTimeZoneCreation)




// + (nullable instancetype)timeZoneWithName:(NSString *)tzName;
// + (nullable instancetype)timeZoneWithName:(NSString *)tzName data:(nullable NSData *)aData;

// - (nullable instancetype)initWithName:(NSString *)tzName;
// - (nullable instancetype)initWithName:(NSString *)tzName data:(nullable NSData *)aData;




// + (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;

// + (nullable instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

/* @end */


extern "C" NSNotificationName const NSSystemTimeZoneDidChangeNotification __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
#pragma clang assume_nonnull end







#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_NSTimer
#define _REWRITER_typedef_NSTimer
typedef struct objc_object NSTimer;
typedef struct {} _objc_exc_NSTimer;
#endif

struct NSTimer_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};






typedef int SSLProtocol; enum {
    kSSLProtocolUnknown __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 0,
    kTLSProtocol1 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 4,
    kTLSProtocol11 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 7,
    kTLSProtocol12 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 8,
    kDTLSProtocol1 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 9,
    kTLSProtocol13 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 10,
    kDTLSProtocol12 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 11,
    kTLSProtocolMaxSupported __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 999,
    kSSLProtocol2 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 1,
    kSSLProtocol3 __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 2,
    kSSLProtocol3Only __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 3,
    kTLSProtocol1Only __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 5,
    kSSLProtocolAll __attribute__((availability(ios,introduced=5_0,deprecated=13_0,message="" ))) = 6,
};

extern "C" {

#pragma clang assume_nonnull begin
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable sec_trust_t
sec_trust_create(SecTrustRef trust);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
SecTrustRef
sec_trust_copy_ref(sec_trust_t trust);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable sec_identity_t
sec_identity_create(SecIdentityRef identity);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable sec_identity_t
sec_identity_create_with_certificates(SecIdentityRef identity, CFArrayRef certificates);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
bool
sec_identity_access_certificates(sec_identity_t identity,
                                 void (^handler)(sec_certificate_t certificate));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
_Nullable SecIdentityRef
sec_identity_copy_ref(sec_identity_t identity);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
_Nullable CFArrayRef
sec_identity_copy_certificates_ref(sec_identity_t identity);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable sec_certificate_t
sec_certificate_create(SecCertificateRef certificate);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
SecCertificateRef
sec_certificate_copy_ref(sec_certificate_t certificate);
#pragma clang assume_nonnull end


}
// @protocol OS_sec_protocol_metadata <NSObject> /* @end */
 typedef NSObject/*<OS_sec_protocol_metadata>*/ * __attribute__((objc_independent_class)) sec_protocol_metadata_t;


extern "C" {

#pragma clang assume_nonnull begin
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
const char * _Nullable
sec_protocol_metadata_get_negotiated_protocol(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable dispatch_data_t
sec_protocol_metadata_copy_peer_public_key(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
tls_protocol_version_t
sec_protocol_metadata_get_negotiated_tls_protocol_version(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,replacement="sec_protocol_metadata_get_negotiated_tls_protocol_version"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,replacement="sec_protocol_metadata_get_negotiated_tls_protocol_version"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,replacement="sec_protocol_metadata_get_negotiated_tls_protocol_version"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,replacement="sec_protocol_metadata_get_negotiated_tls_protocol_version")))

SSLProtocol
sec_protocol_metadata_get_negotiated_protocol_version(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
tls_ciphersuite_t
sec_protocol_metadata_get_negotiated_tls_ciphersuite(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,replacement="sec_protocol_metadata_get_negotiated_tls_ciphersuite"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,replacement="sec_protocol_metadata_get_negotiated_tls_ciphersuite"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,replacement="sec_protocol_metadata_get_negotiated_tls_ciphersuite"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,replacement="sec_protocol_metadata_get_negotiated_tls_ciphersuite")))

__attribute__((availability(macCatalyst,unavailable)))
SSLCipherSuite
sec_protocol_metadata_get_negotiated_ciphersuite(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_get_early_data_accepted(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_access_peer_certificate_chain(sec_protocol_metadata_t metadata,
                                                    void (^handler)(sec_certificate_t certificate));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_access_ocsp_response(sec_protocol_metadata_t metadata,
                                           void (^handler)(dispatch_data_t ocsp_data));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_access_supported_signature_algorithms(sec_protocol_metadata_t metadata,
                                                            void (^handler)(uint16_t signature_algorithm));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_access_distinguished_names(sec_protocol_metadata_t metadata,
                                                 void (^handler)(dispatch_data_t distinguished_name));
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
bool
sec_protocol_metadata_access_pre_shared_keys(sec_protocol_metadata_t metadata, void (^handler)(dispatch_data_t psk, dispatch_data_t psk_identity));
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
const char * _Nullable
sec_protocol_metadata_get_server_name(sec_protocol_metadata_t metadata);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_peers_are_equal(sec_protocol_metadata_t metadataA, sec_protocol_metadata_t metadataB);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
bool
sec_protocol_metadata_challenge_parameters_are_equal(sec_protocol_metadata_t metadataA, sec_protocol_metadata_t metadataB);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable dispatch_data_t
sec_protocol_metadata_create_secret(sec_protocol_metadata_t metadata, size_t label_len,
                                    const char *label, size_t exporter_length);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
__attribute__((__ns_returns_retained__)) _Nullable dispatch_data_t
sec_protocol_metadata_create_secret_with_context(sec_protocol_metadata_t metadata, size_t label_len,
                                                 const char *label, size_t context_len,
                                                 const uint8_t *context, size_t exporter_length);
#pragma clang assume_nonnull end


}
// @protocol OS_sec_protocol_options <NSObject> /* @end */
 typedef NSObject/*<OS_sec_protocol_options>*/ * __attribute__((objc_independent_class)) sec_protocol_options_t;


extern "C" {

#pragma clang assume_nonnull begin
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
bool
sec_protocol_options_are_equal(sec_protocol_options_t optionsA, sec_protocol_options_t optionsB);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_local_identity(sec_protocol_options_t options, sec_identity_t identity);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_append_tls_ciphersuite(sec_protocol_options_t options, tls_ciphersuite_t ciphersuite);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,message="Use sec_protocol_options_append_tls_ciphersuite"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,message="Use sec_protocol_options_append_tls_ciphersuite"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,message="Use sec_protocol_options_append_tls_ciphersuite"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,message="Use sec_protocol_options_append_tls_ciphersuite")))
__attribute__((availability(macCatalyst,unavailable)))
void
sec_protocol_options_add_tls_ciphersuite(sec_protocol_options_t options, SSLCipherSuite ciphersuite);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_append_tls_ciphersuite_group(sec_protocol_options_t options, tls_ciphersuite_group_t group);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,message="Use sec_protocol_options_append_tls_ciphersuite_group"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,message="Use sec_protocol_options_append_tls_ciphersuite_group"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,message="Use sec_protocol_options_append_tls_ciphersuite_group"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,message="Use sec_protocol_options_append_tls_ciphersuite_group")))
__attribute__((availability(macCatalyst,unavailable)))
void
sec_protocol_options_add_tls_ciphersuite_group(sec_protocol_options_t options, SSLCiphersuiteGroup group);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,replacement="sec_protocol_options_set_min_tls_protocol_version"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,replacement="sec_protocol_options_set_min_tls_protocol_version"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,replacement="sec_protocol_options_set_min_tls_protocol_version"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,replacement="sec_protocol_options_set_min_tls_protocol_version")))

__attribute__((availability(macCatalyst,unavailable)))
void
sec_protocol_options_set_tls_min_version(sec_protocol_options_t options, SSLProtocol version);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_set_min_tls_protocol_version(sec_protocol_options_t options, tls_protocol_version_t version);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
tls_protocol_version_t
sec_protocol_options_get_default_min_tls_protocol_version(void);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
tls_protocol_version_t
sec_protocol_options_get_default_min_dtls_protocol_version(void);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,replacement="sec_protocol_options_set_max_tls_protocol_version"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,replacement="sec_protocol_options_set_max_tls_protocol_version"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,replacement="sec_protocol_options_set_max_tls_protocol_version"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,replacement="sec_protocol_options_set_max_tls_protocol_version")))

__attribute__((availability(macCatalyst,unavailable)))
void
sec_protocol_options_set_tls_max_version(sec_protocol_options_t options, SSLProtocol version);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_set_max_tls_protocol_version(sec_protocol_options_t options, tls_protocol_version_t version);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
tls_protocol_version_t
sec_protocol_options_get_default_max_tls_protocol_version(void);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
tls_protocol_version_t
sec_protocol_options_get_default_max_dtls_protocol_version(void);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_add_tls_application_protocol(sec_protocol_options_t options, const char *application_protocol);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_server_name(sec_protocol_options_t options, const char *server_name);
__attribute__((availability(macos,introduced=10.14,deprecated=10.15,message="DHE ciphersuites are no longer supported"))) __attribute__((availability(ios,introduced=12.0,deprecated=13.0,message="DHE ciphersuites are no longer supported"))) __attribute__((availability(watchos,introduced=5.0,deprecated=6.0,message="DHE ciphersuites are no longer supported"))) __attribute__((availability(tvos,introduced=12.0,deprecated=13.0,message="DHE ciphersuites are no longer supported")))
void
sec_protocol_options_set_tls_diffie_hellman_parameters(sec_protocol_options_t options, dispatch_data_t params);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_add_pre_shared_key(sec_protocol_options_t options, dispatch_data_t psk, dispatch_data_t psk_identity);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_set_tls_pre_shared_key_identity_hint(sec_protocol_options_t options, dispatch_data_t psk_identity_hint);
typedef void (*sec_protocol_pre_shared_key_selection_complete_t)(dispatch_data_t _Nullable psk_identity);
typedef void (*sec_protocol_pre_shared_key_selection_t)(sec_protocol_metadata_t metadata, dispatch_data_t _Nullable psk_identity_hint, sec_protocol_pre_shared_key_selection_complete_t complete);
__attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)))
void
sec_protocol_options_set_pre_shared_key_selection_block(sec_protocol_options_t options, sec_protocol_pre_shared_key_selection_t psk_selection_block, dispatch_queue_t psk_selection_queue);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_tickets_enabled(sec_protocol_options_t options, bool tickets_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_is_fallback_attempt(sec_protocol_options_t options, bool is_fallback_attempt);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_resumption_enabled(sec_protocol_options_t options, bool resumption_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_false_start_enabled(sec_protocol_options_t options, bool false_start_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_ocsp_enabled(sec_protocol_options_t options, bool ocsp_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_sct_enabled(sec_protocol_options_t options, bool sct_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_tls_renegotiation_enabled(sec_protocol_options_t options, bool renegotiation_enabled);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_peer_authentication_required(sec_protocol_options_t options, bool peer_authentication_required);
typedef void (*sec_protocol_key_update_complete_t)(void);
typedef void (*sec_protocol_key_update_t)(sec_protocol_metadata_t metadata, sec_protocol_key_update_complete_t complete);
typedef void (*sec_protocol_challenge_complete_t)(sec_identity_t _Nullable identity);
typedef void (*sec_protocol_challenge_t)(sec_protocol_metadata_t metadata, sec_protocol_challenge_complete_t complete);
typedef void (*sec_protocol_verify_complete_t)(bool result);
typedef void (*sec_protocol_verify_t)(sec_protocol_metadata_t metadata, sec_trust_t trust_ref, sec_protocol_verify_complete_t complete);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_key_update_block(sec_protocol_options_t options, sec_protocol_key_update_t key_update_block, dispatch_queue_t key_update_queue);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_challenge_block(sec_protocol_options_t options, sec_protocol_challenge_t challenge_block, dispatch_queue_t challenge_queue);
__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))
void
sec_protocol_options_set_verify_block(sec_protocol_options_t options, sec_protocol_verify_t verify_block, dispatch_queue_t verify_block_queue);
#pragma clang assume_nonnull end




}

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif


#pragma clang assume_nonnull begin
typedef NSUInteger NSURLCredentialPersistence; enum {
    NSURLCredentialPersistenceNone,
    NSURLCredentialPersistenceForSession,
    NSURLCredentialPersistencePermanent,
    NSURLCredentialPersistenceSynchronizable __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
};

// @class NSURLCredentialInternal;
#ifndef _REWRITER_typedef_NSURLCredentialInternal
#define _REWRITER_typedef_NSURLCredentialInternal
typedef struct objc_object NSURLCredentialInternal;
typedef struct {} _objc_exc_NSURLCredentialInternal;
#endif








#ifndef _REWRITER_typedef_NSURLCredential
#define _REWRITER_typedef_NSURLCredential
typedef struct objc_object NSURLCredential;
typedef struct {} _objc_exc_NSURLCredential;
#endif

struct NSURLCredential_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLCredentialInternal *_internal;
};






// @property (readonly) NSURLCredentialPersistence persistence;

/* @end */





// @interface NSURLCredential(NSInternetPassword)
// - (instancetype)initWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;
// + (NSURLCredential *)credentialWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;





// @property (nullable, readonly, copy) NSString *user;
// @property (nullable, readonly, copy) NSString *password;
// @property (readonly) BOOL hasPassword;

/* @end */





// @interface NSURLCredential(NSClientCertificate)
// - (instancetype)initWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSURLCredential *)credentialWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// @property (nullable, readonly) SecIdentityRef identity;





// @property (readonly, copy) NSArray *certificates __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSURLCredential(NSServerTrust)






// - (instancetype)initWithTrust:(SecTrustRef)trust __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// + (NSURLCredential *)credentialForTrust:(SecTrustRef)trust __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end








// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif


#pragma clang assume_nonnull begin





extern "C" NSString * const NSURLProtectionSpaceHTTP __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLProtectionSpaceHTTPS __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLProtectionSpaceFTP __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLProtectionSpaceHTTPProxy;





extern "C" NSString * const NSURLProtectionSpaceHTTPSProxy;





extern "C" NSString * const NSURLProtectionSpaceFTPProxy;





extern "C" NSString * const NSURLProtectionSpaceSOCKSProxy;





extern "C" NSString * const NSURLAuthenticationMethodDefault;






extern "C" NSString * const NSURLAuthenticationMethodHTTPBasic;





extern "C" NSString * const NSURLAuthenticationMethodHTTPDigest;





extern "C" NSString * const NSURLAuthenticationMethodHTMLForm;





extern "C" NSString * const NSURLAuthenticationMethodNTLM __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLAuthenticationMethodNegotiate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLAuthenticationMethodClientCertificate __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSString * const NSURLAuthenticationMethodServerTrust __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @class NSURLProtectionSpaceInternal;
#ifndef _REWRITER_typedef_NSURLProtectionSpaceInternal
#define _REWRITER_typedef_NSURLProtectionSpaceInternal
typedef struct objc_object NSURLProtectionSpaceInternal;
typedef struct {} _objc_exc_NSURLProtectionSpaceInternal;
#endif








#ifndef _REWRITER_typedef_NSURLProtectionSpace
#define _REWRITER_typedef_NSURLProtectionSpace
typedef struct objc_object NSURLProtectionSpace;
typedef struct {} _objc_exc_NSURLProtectionSpace;
#endif

struct NSURLProtectionSpace_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLProtectionSpaceInternal *_internal;
};

// - (instancetype)initWithHost:(NSString *)host port:(NSInteger)port protocol:(nullable NSString *)protocol realm:(nullable NSString *)realm authenticationMethod:(nullable NSString *)authenticationMethod;
// - (instancetype)initWithProxyHost:(NSString *)host port:(NSInteger)port type:(nullable NSString *)type realm:(nullable NSString *)realm authenticationMethod:(nullable NSString *)authenticationMethod;
// @property (nullable, readonly, copy) NSString *realm;





// @property (readonly) BOOL receivesCredentialSecurely;





// @property (readonly) BOOL isProxy;





// @property (readonly, copy) NSString *host;





// @property (readonly) NSInteger port;





// @property (nullable, readonly, copy) NSString *proxyType;





// @property (nullable, readonly, copy) NSString *protocol;





// @property (readonly, copy) NSString *authenticationMethod;

/* @end */





// @interface NSURLProtectionSpace(NSClientCertificateSpace)





// @property (nullable, readonly, copy) NSArray<NSData *> *distinguishedNames __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */





// @interface NSURLProtectionSpace(NSServerTrustValidationSpace)





// @property (nullable, readonly) SecTrustRef serverTrust __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end


// @class NSDictionary;
#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSURLCredential;
#ifndef _REWRITER_typedef_NSURLCredential
#define _REWRITER_typedef_NSURLCredential
typedef struct objc_object NSURLCredential;
typedef struct {} _objc_exc_NSURLCredential;
#endif

// @class NSURLSessionTask;
#ifndef _REWRITER_typedef_NSURLSessionTask
#define _REWRITER_typedef_NSURLSessionTask
typedef struct objc_object NSURLSessionTask;
typedef struct {} _objc_exc_NSURLSessionTask;
#endif


// @class NSURLCredentialStorageInternal;
#ifndef _REWRITER_typedef_NSURLCredentialStorageInternal
#define _REWRITER_typedef_NSURLCredentialStorageInternal
typedef struct objc_object NSURLCredentialStorageInternal;
typedef struct {} _objc_exc_NSURLCredentialStorageInternal;
#endif


#pragma clang assume_nonnull begin







#ifndef _REWRITER_typedef_NSURLCredentialStorage
#define _REWRITER_typedef_NSURLCredentialStorage
typedef struct objc_object NSURLCredentialStorage;
typedef struct {} _objc_exc_NSURLCredentialStorage;
#endif

struct NSURLCredentialStorage_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLCredentialStorageInternal *_internal;
};







@property (class, readonly, strong) NSURLCredentialStorage *sharedCredentialStorage;







// - (nullable NSDictionary<NSString *, NSURLCredential *> *)credentialsForProtectionSpace:(NSURLProtectionSpace *)space;







// @property (readonly, copy) NSDictionary<NSURLProtectionSpace *, NSDictionary<NSString *, NSURLCredential *> *> *allCredentials;
// - (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;
// - (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;
// - (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space options:(nullable NSDictionary<NSString *, id> *)options __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// - (nullable NSURLCredential *)defaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space;
// - (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/* @end */


// @interface NSURLCredentialStorage (NSURLSessionTaskAdditions)
// - (void)getCredentialsForProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task completionHandler:(void (^) (NSDictionary<NSString *, NSURLCredential *> * _Nullable credentials))completionHandler __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace options:(nullable NSDictionary<NSString *, id> *)options task:(NSURLSessionTask *)task __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)getDefaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space task:(NSURLSessionTask *)task completionHandler:(void (^) (NSURLCredential * _Nullable credential))completionHandler __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */







extern "C" NSNotificationName const NSURLCredentialStorageChangedNotification;







extern "C" NSString *const NSURLCredentialStorageRemoveSynchronizableCredentials __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
#pragma clang assume_nonnull end



extern "C" {
#pragma clang assume_nonnull begin
extern const CFStringRef kCFErrorDomainCFNetwork __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFErrorDomainWinSock __attribute__((availability(ios,introduced=2_0)));
typedef int CFNetworkErrors; enum {

  kCFHostErrorHostNotFound = 1,
  kCFHostErrorUnknown = 2,

  kCFSOCKSErrorUnknownClientVersion = 100,
  kCFSOCKSErrorUnsupportedServerVersion = 101,

  kCFSOCKS4ErrorRequestFailed = 110,
  kCFSOCKS4ErrorIdentdFailed = 111,
  kCFSOCKS4ErrorIdConflict = 112,
  kCFSOCKS4ErrorUnknownStatusCode = 113,

  kCFSOCKS5ErrorBadState = 120,
  kCFSOCKS5ErrorBadResponseAddr = 121,
  kCFSOCKS5ErrorBadCredentials = 122,
  kCFSOCKS5ErrorUnsupportedNegotiationMethod = 123,
  kCFSOCKS5ErrorNoAcceptableMethod = 124,

  kCFFTPErrorUnexpectedStatusCode = 200,

  kCFErrorHTTPAuthenticationTypeUnsupported = 300,
  kCFErrorHTTPBadCredentials = 301,
  kCFErrorHTTPConnectionLost = 302,
  kCFErrorHTTPParseFailure = 303,
  kCFErrorHTTPRedirectionLoopDetected = 304,
  kCFErrorHTTPBadURL = 305,
  kCFErrorHTTPProxyConnectionFailure = 306,
  kCFErrorHTTPBadProxyCredentials = 307,
  kCFErrorPACFileError = 308,
  kCFErrorPACFileAuth = 309,
  kCFErrorHTTPSProxyConnectionFailure = 310,
  kCFStreamErrorHTTPSProxyFailureUnexpectedResponseToCONNECTMethod = 311,


  kCFURLErrorBackgroundSessionInUseByAnotherProcess = -996,
  kCFURLErrorBackgroundSessionWasDisconnected = -997,
  kCFURLErrorUnknown = -998,
  kCFURLErrorCancelled = -999,
  kCFURLErrorBadURL = -1000,
  kCFURLErrorTimedOut = -1001,
  kCFURLErrorUnsupportedURL = -1002,
  kCFURLErrorCannotFindHost = -1003,
  kCFURLErrorCannotConnectToHost = -1004,
  kCFURLErrorNetworkConnectionLost = -1005,
  kCFURLErrorDNSLookupFailed = -1006,
  kCFURLErrorHTTPTooManyRedirects = -1007,
  kCFURLErrorResourceUnavailable = -1008,
  kCFURLErrorNotConnectedToInternet = -1009,
  kCFURLErrorRedirectToNonExistentLocation = -1010,
  kCFURLErrorBadServerResponse = -1011,
  kCFURLErrorUserCancelledAuthentication = -1012,
  kCFURLErrorUserAuthenticationRequired = -1013,
  kCFURLErrorZeroByteResource = -1014,
  kCFURLErrorCannotDecodeRawData = -1015,
  kCFURLErrorCannotDecodeContentData = -1016,
  kCFURLErrorCannotParseResponse = -1017,
  kCFURLErrorInternationalRoamingOff = -1018,
  kCFURLErrorCallIsActive = -1019,
  kCFURLErrorDataNotAllowed = -1020,
  kCFURLErrorRequestBodyStreamExhausted = -1021,
  kCFURLErrorAppTransportSecurityRequiresSecureConnection = -1022,
  kCFURLErrorFileDoesNotExist = -1100,
  kCFURLErrorFileIsDirectory = -1101,
  kCFURLErrorNoPermissionsToReadFile = -1102,
  kCFURLErrorDataLengthExceedsMaximum = -1103,
  kCFURLErrorFileOutsideSafeArea = -1104,

  kCFURLErrorSecureConnectionFailed = -1200,
  kCFURLErrorServerCertificateHasBadDate = -1201,
  kCFURLErrorServerCertificateUntrusted = -1202,
  kCFURLErrorServerCertificateHasUnknownRoot = -1203,
  kCFURLErrorServerCertificateNotYetValid = -1204,
  kCFURLErrorClientCertificateRejected = -1205,
  kCFURLErrorClientCertificateRequired = -1206,
  kCFURLErrorCannotLoadFromNetwork = -2000,

  kCFURLErrorCannotCreateFile = -3000,
  kCFURLErrorCannotOpenFile = -3001,
  kCFURLErrorCannotCloseFile = -3002,
  kCFURLErrorCannotWriteToFile = -3003,
  kCFURLErrorCannotRemoveFile = -3004,
  kCFURLErrorCannotMoveFile = -3005,
  kCFURLErrorDownloadDecodingFailedMidStream = -3006,
  kCFURLErrorDownloadDecodingFailedToComplete = -3007,


  kCFHTTPCookieCannotParseCookieFile = -4000,


  kCFNetServiceErrorUnknown = -72000L,
  kCFNetServiceErrorCollision = -72001L,
  kCFNetServiceErrorNotFound = -72002L,
  kCFNetServiceErrorInProgress = -72003L,
  kCFNetServiceErrorBadArgument = -72004L,
  kCFNetServiceErrorCancel = -72005L,
  kCFNetServiceErrorInvalid = -72006L,
  kCFNetServiceErrorTimeout = -72007L,
  kCFNetServiceErrorDNSServiceFailure = -73000L
};
extern const CFStringRef kCFURLErrorFailingURLErrorKey __attribute__((availability(ios,introduced=2_2)));
extern const CFStringRef kCFURLErrorFailingURLStringErrorKey __attribute__((availability(ios,introduced=2_2)));
extern const CFStringRef kCFGetAddrInfoFailureKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFSOCKSStatusCodeKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFSOCKSVersionKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFSOCKSNegotiationMethodKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFDNSServiceFailureKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFFTPStatusCodeKey __attribute__((availability(ios,introduced=2_0)));
#pragma clang assume_nonnull end


}



extern "C" {
#pragma clang assume_nonnull begin

#pragma pack(push, 2)








typedef struct __CFHost* CFHostRef;
extern const SInt32 kCFStreamErrorDomainNetDB __attribute__((availability(ios,introduced=2_0)));
extern const SInt32 kCFStreamErrorDomainSystemConfiguration __attribute__((availability(ios,introduced=2_0)));
typedef int CFHostInfoType; enum {





  kCFHostAddresses = 0,




  kCFHostNames = 1,





  kCFHostReachability = 2
};
struct CFHostClientContext {






  CFIndex version;





  void * _Nullable info;
  CFAllocatorRetainCallBack _Nullable retain;





  CFAllocatorReleaseCallBack _Nullable release;







  CFAllocatorCopyDescriptionCallBack _Nullable copyDescription;
};
typedef struct CFHostClientContext CFHostClientContext;
typedef void ( * CFHostClientCallBack)(CFHostRef theHost, CFHostInfoType typeInfo, const CFStreamError * _Nullable error, void * _Nullable info);
extern CFTypeID
CFHostGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFHostRef
CFHostCreateWithName(CFAllocatorRef _Nullable allocator, CFStringRef hostname) __attribute__((availability(ios,introduced=2_0)));
extern CFHostRef
CFHostCreateWithAddress(CFAllocatorRef _Nullable allocator, CFDataRef addr) __attribute__((availability(ios,introduced=2_0)));
extern CFHostRef
CFHostCreateCopy(CFAllocatorRef _Nullable alloc, CFHostRef host) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHostStartInfoResolution(CFHostRef theHost, CFHostInfoType info, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFArrayRef
CFHostGetAddressing(CFHostRef theHost, Boolean * _Nullable hasBeenResolved) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFArrayRef
CFHostGetNames(CFHostRef theHost, Boolean * _Nullable hasBeenResolved) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDataRef
CFHostGetReachability(CFHostRef theHost, Boolean * _Nullable hasBeenResolved) __attribute__((availability(ios,introduced=2_0)));
extern void
CFHostCancelInfoResolution(CFHostRef theHost, CFHostInfoType info) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHostSetClient(CFHostRef theHost, CFHostClientCallBack _Nullable clientCB, CFHostClientContext * _Nullable clientContext) __attribute__((availability(ios,introduced=2_0)));
extern void
CFHostScheduleWithRunLoop(CFHostRef theHost, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern void
CFHostUnscheduleFromRunLoop(CFHostRef theHost, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));



#pragma pack(pop)
#pragma clang assume_nonnull end

}



extern "C" {
#pragma clang assume_nonnull begin

#pragma pack(push, 2)
typedef struct __CFNetService* CFNetServiceRef;
typedef struct __CFNetServiceMonitor* CFNetServiceMonitorRef;
typedef struct __CFNetServiceBrowser* CFNetServiceBrowserRef;
extern const SInt32 kCFStreamErrorDomainMach __attribute__((availability(ios,introduced=2_0)));
extern const SInt32 kCFStreamErrorDomainNetServices __attribute__((availability(ios,introduced=2_0)));
typedef int CFNetServicesError; enum {




  kCFNetServicesErrorUnknown = -72000L,






  kCFNetServicesErrorCollision = -72001L,




  kCFNetServicesErrorNotFound = -72002L,





  kCFNetServicesErrorInProgress = -72003L,




  kCFNetServicesErrorBadArgument = -72004L,




  kCFNetServicesErrorCancel = -72005L,





  kCFNetServicesErrorInvalid = -72006L,





  kCFNetServicesErrorTimeout = -72007L
};
typedef int CFNetServiceMonitorType; enum {




  kCFNetServiceMonitorTXT = 1
};
typedef CFOptionFlags CFNetServiceRegisterFlags; enum {




  kCFNetServiceFlagNoAutoRename = 1
};
typedef CFOptionFlags CFNetServiceBrowserFlags; enum {




  kCFNetServiceFlagMoreComing = 1,




  kCFNetServiceFlagIsDomain = 2,




  kCFNetServiceFlagIsDefault = 4,




  kCFNetServiceFlagIsRegistrationDomain __attribute__((availability(ios,introduced=2_0,deprecated=2_0,message="" ))) = 4,




  kCFNetServiceFlagRemove = 8
};
struct CFNetServiceClientContext {






  CFIndex version;





  void * _Nullable info;
  CFAllocatorRetainCallBack _Nullable retain;





  CFAllocatorReleaseCallBack _Nullable release;







  CFAllocatorCopyDescriptionCallBack _Nullable copyDescription;
};
typedef struct CFNetServiceClientContext CFNetServiceClientContext;
typedef void ( * CFNetServiceClientCallBack)(CFNetServiceRef theService, CFStreamError * _Nullable error, void * _Nullable info);
typedef void ( * CFNetServiceMonitorClientCallBack)(CFNetServiceMonitorRef theMonitor, CFNetServiceRef _Nullable theService, CFNetServiceMonitorType typeInfo, CFDataRef _Nullable rdata, CFStreamError * _Nullable error, void * _Nullable info);
typedef void ( * CFNetServiceBrowserClientCallBack)(CFNetServiceBrowserRef browser, CFOptionFlags flags, CFTypeRef _Nullable domainOrService, CFStreamError * _Nullable error, void * _Nullable info);
extern CFTypeID
CFNetServiceGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFTypeID
CFNetServiceMonitorGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFTypeID
CFNetServiceBrowserGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFNetServiceRef
CFNetServiceCreate(CFAllocatorRef _Nullable alloc, CFStringRef domain, CFStringRef serviceType, CFStringRef name, SInt32 port) __attribute__((availability(ios,introduced=2_0)));
extern CFNetServiceRef
CFNetServiceCreateCopy(CFAllocatorRef _Nullable alloc, CFNetServiceRef service) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFNetServiceGetDomain(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFNetServiceGetType(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFNetServiceGetName(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceRegisterWithOptions(CFNetServiceRef theService, CFOptionFlags options, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceResolveWithTimeout(CFNetServiceRef theService, CFTimeInterval timeout, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceCancel(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFStringRef
CFNetServiceGetTargetHost(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern SInt32
CFNetServiceGetPortNumber(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFArrayRef
CFNetServiceGetAddressing(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDataRef
CFNetServiceGetTXTData(CFNetServiceRef theService) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceSetTXTData(CFNetServiceRef theService, CFDataRef txtRecord) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDictionaryRef
CFNetServiceCreateDictionaryWithTXTData(CFAllocatorRef _Nullable alloc, CFDataRef txtRecord) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDataRef
CFNetServiceCreateTXTDataWithDictionary(CFAllocatorRef _Nullable alloc, CFDictionaryRef keyValuePairs) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceSetClient(CFNetServiceRef theService, CFNetServiceClientCallBack _Nullable clientCB, CFNetServiceClientContext * _Nullable clientContext) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceScheduleWithRunLoop(CFNetServiceRef theService, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceUnscheduleFromRunLoop(CFNetServiceRef theService, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern CFNetServiceMonitorRef
CFNetServiceMonitorCreate(
  CFAllocatorRef _Nullable alloc,
  CFNetServiceRef theService,
  CFNetServiceMonitorClientCallBack clientCB,
  CFNetServiceClientContext * clientContext) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceMonitorInvalidate(CFNetServiceMonitorRef monitor) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceMonitorStart(CFNetServiceMonitorRef monitor, CFNetServiceMonitorType recordType, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceMonitorStop(CFNetServiceMonitorRef monitor, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceMonitorScheduleWithRunLoop(CFNetServiceMonitorRef monitor, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceMonitorUnscheduleFromRunLoop(CFNetServiceMonitorRef monitor, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern CFNetServiceBrowserRef
CFNetServiceBrowserCreate(CFAllocatorRef _Nullable alloc, CFNetServiceBrowserClientCallBack clientCB, CFNetServiceClientContext *clientContext) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceBrowserInvalidate(CFNetServiceBrowserRef browser) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceBrowserSearchForDomains(CFNetServiceBrowserRef browser, Boolean registrationDomains, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceBrowserSearchForServices(CFNetServiceBrowserRef browser, CFStringRef domain, CFStringRef serviceType, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceBrowserStopSearch(CFNetServiceBrowserRef browser, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceBrowserScheduleWithRunLoop(CFNetServiceBrowserRef browser, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern void
CFNetServiceBrowserUnscheduleFromRunLoop(CFNetServiceBrowserRef browser, CFRunLoopRef runLoop, CFStringRef runLoopMode) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFNetServiceRegister(CFNetServiceRef theService, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=NA,deprecated=NA,message="" )));
extern Boolean
CFNetServiceResolve(CFNetServiceRef theService, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=NA,deprecated=NA,message="" )));





#pragma pack(pop)
#pragma clang assume_nonnull end

}








extern "C" {
#pragma clang assume_nonnull begin
extern const CFStringRef kCFStreamPropertySSLContext __attribute__((availability(ios,introduced=5_0)));
extern const CFStringRef kCFStreamPropertySSLPeerTrust __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamSSLValidatesCertificateChain __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertySSLSettings __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamSSLLevel __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamSSLPeerName __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamSSLCertificates __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamSSLIsServer __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamNetworkServiceType __attribute__((availability(ios,introduced=4_0)));


extern const CFStringRef kCFStreamNetworkServiceTypeVideo __attribute__((availability(ios,introduced=5_0)));
extern const CFStringRef kCFStreamNetworkServiceTypeVoice __attribute__((availability(ios,introduced=5_0)));
extern const CFStringRef kCFStreamNetworkServiceTypeBackground __attribute__((availability(ios,introduced=5_0)));
extern const CFStringRef kCFStreamNetworkServiceTypeResponsiveData __attribute__((availability(ios,introduced=6.0)));
extern const CFStringRef kCFStreamNetworkServiceTypeCallSignaling __attribute__((availability(ios,introduced=10_0)));
extern const CFStringRef kCFStreamNetworkServiceTypeAVStreaming __attribute__((availability(ios,introduced=6.0)));
extern const CFStringRef kCFStreamNetworkServiceTypeResponsiveAV __attribute__((availability(ios,introduced=6.0)));


extern const CFStringRef kCFStreamNetworkServiceTypeVoIP __attribute__((availability(ios,introduced=4_0,deprecated=9_0,message="" "use PushKit for VoIP control purposes")));
extern const CFStringRef kCFStreamPropertyNoCellular __attribute__((availability(ios,introduced=5_0)));
extern const CFStringRef kCFStreamPropertyConnectionIsCellular __attribute__((availability(ios,introduced=6_0)));
extern const CFStringRef kCFStreamPropertyAllowExpensiveNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));
extern const CFStringRef kCFStreamPropertyConnectionIsExpensive __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));
extern const CFStringRef kCFStreamPropertyAllowConstrainedNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));
extern const CFIndex kCFStreamErrorDomainWinSock __attribute__((availability(ios,introduced=2_0)));

static __inline__ __attribute__((always_inline))
SInt32 CFSocketStreamSOCKSGetErrorSubdomain(const CFStreamError* error) {
 return ((error->error >> 16) & 0x0000FFFF);
}

static __inline__ __attribute__((always_inline))
SInt32 CFSocketStreamSOCKSGetError(const CFStreamError* error) {
 return (error->error & 0x0000FFFF);
}

enum {
  kCFStreamErrorSOCKSSubDomainNone = 0,
  kCFStreamErrorSOCKSSubDomainVersionCode = 1,
  kCFStreamErrorSOCKS4SubDomainResponse = 2,
  kCFStreamErrorSOCKS5SubDomainUserPass = 3,
  kCFStreamErrorSOCKS5SubDomainMethod = 4,
  kCFStreamErrorSOCKS5SubDomainResponse = 5
};



enum {
  kCFStreamErrorSOCKS5BadResponseAddr = 1,
  kCFStreamErrorSOCKS5BadState = 2,
  kCFStreamErrorSOCKSUnknownClientVersion = 3
};


enum {
  kCFStreamErrorSOCKS4RequestFailed = 91,
  kCFStreamErrorSOCKS4IdentdFailed = 92,
  kCFStreamErrorSOCKS4IdConflict = 93
};


enum {
  kSOCKS5NoAcceptableMethod = 0xFF
};
extern const CFStringRef kCFStreamPropertyProxyLocalBypass __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertySocketRemoteHost __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertySocketRemoteNetService __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertySocketExtendedBackgroundIdleMode __attribute__((availability(ios,introduced=9_0)));
extern void
CFStreamCreatePairWithSocketToCFHost(
  CFAllocatorRef _Nullable alloc,
  CFHostRef host,
  SInt32 port,
  CFReadStreamRef _Nullable * _Nullable readStream,
  CFWriteStreamRef _Nullable * _Nullable writeStream) __attribute__((availability(ios,introduced=2_0)));
extern void
CFStreamCreatePairWithSocketToNetService(
  CFAllocatorRef _Nullable alloc,
  CFNetServiceRef service,
  CFReadStreamRef _Nullable * _Nullable readStream,
  CFWriteStreamRef _Nullable * _Nullable writeStream) __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertySSLPeerCertificates __attribute__((availability(ios,introduced=2_0,deprecated=4_0,message="" )));
extern const CFStringRef kCFStreamSSLAllowsExpiredCertificates __attribute__((availability(ios,introduced=2_0,deprecated=4_0,message="" )));
extern const CFStringRef kCFStreamSSLAllowsExpiredRoots __attribute__((availability(ios,introduced=2_0,deprecated=4_0,message="" )));
extern const CFStringRef kCFStreamSSLAllowsAnyRoot __attribute__((availability(ios,introduced=2_0,deprecated=4_0,message="" )));
#pragma clang assume_nonnull end






}



extern "C" {
#pragma clang assume_nonnull begin








extern const SInt32 kCFStreamErrorDomainFTP __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFStreamPropertyFTPUserName __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPPassword __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPUsePassiveMode __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPResourceSize __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPFetchResourceInfo __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPFileTransferOffset __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPAttemptPersistentConnection __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPProxy __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPProxyHost __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFStreamPropertyFTPProxyPort __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));





extern const CFStringRef kCFStreamPropertyFTPProxyUser __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));





extern const CFStringRef kCFStreamPropertyFTPProxyPassword __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceMode __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceName __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceOwner __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceGroup __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceLink __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceSize __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceType __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern const CFStringRef kCFFTPResourceModDate __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern CFReadStreamRef
CFReadStreamCreateWithFTPURL(CFAllocatorRef _Nullable alloc, CFURLRef ftpURL) __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern CFIndex
CFFTPCreateParsedResourceListing(CFAllocatorRef _Nullable alloc, const UInt8 *buffer, CFIndex bufferLength, CFDictionaryRef _Nullable * _Nullable parsed) __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
extern CFWriteStreamRef
CFWriteStreamCreateWithFTPURL(CFAllocatorRef _Nullable alloc, CFURLRef ftpURL) __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSessionAPI for ftp requests")));
#pragma clang assume_nonnull end


}







extern "C" {
#pragma clang assume_nonnull begin








extern const CFStringRef kCFHTTPVersion1_0 __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPVersion1_1 __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPVersion2_0 __attribute__((availability(ios,introduced=8_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeBasic __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeDigest __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeNTLM __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeKerberos __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeNegotiate __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeNegotiate2 __attribute__((availability(ios,introduced=3_0)));
extern const CFStringRef kCFHTTPAuthenticationSchemeXMobileMeAuthToken __attribute__((availability(ios,introduced=4_3)));
typedef struct __CFHTTPMessage* CFHTTPMessageRef;
extern CFTypeID
CFHTTPMessageGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFHTTPMessageRef
CFHTTPMessageCreateRequest(CFAllocatorRef _Nullable alloc, CFStringRef requestMethod, CFURLRef url, CFStringRef httpVersion) __attribute__((availability(ios,introduced=2_0)));
extern CFHTTPMessageRef
CFHTTPMessageCreateResponse(
  CFAllocatorRef _Nullable alloc,
  CFIndex statusCode,
  CFStringRef _Nullable statusDescription,
  CFStringRef httpVersion) __attribute__((availability(ios,introduced=2_0)));
extern CFHTTPMessageRef
CFHTTPMessageCreateEmpty(CFAllocatorRef _Nullable alloc, Boolean isRequest) __attribute__((availability(ios,introduced=2_0)));
extern CFHTTPMessageRef
CFHTTPMessageCreateCopy(CFAllocatorRef _Nullable alloc, CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageIsRequest(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFHTTPMessageCopyVersion(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDataRef
CFHTTPMessageCopyBody(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern void
CFHTTPMessageSetBody(CFHTTPMessageRef message, CFDataRef bodyData) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFStringRef
CFHTTPMessageCopyHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDictionaryRef
CFHTTPMessageCopyAllHeaderFields(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern void
CFHTTPMessageSetHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField, CFStringRef _Nullable value) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageAppendBytes(CFHTTPMessageRef message, const UInt8 *newBytes, CFIndex numBytes) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageIsHeaderComplete(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFDataRef
CFHTTPMessageCopySerializedMessage(CFHTTPMessageRef message) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFURLRef
CFHTTPMessageCopyRequestURL(CFHTTPMessageRef request) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFStringRef
CFHTTPMessageCopyRequestMethod(CFHTTPMessageRef request) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageAddAuthentication(
  CFHTTPMessageRef request,
  CFHTTPMessageRef _Nullable authenticationFailureResponse,
  CFStringRef username,
  CFStringRef password,
  CFStringRef _Nullable authenticationScheme,
  Boolean forProxy) __attribute__((availability(ios,introduced=2_0)));
extern CFIndex
CFHTTPMessageGetResponseStatusCode(CFHTTPMessageRef response) __attribute__((availability(ios,introduced=2_0)));
extern _Nullable CFStringRef
CFHTTPMessageCopyResponseStatusLine(CFHTTPMessageRef response) __attribute__((availability(ios,introduced=2_0)));
#pragma clang assume_nonnull end



}



extern "C" {
#pragma clang assume_nonnull begin
extern const SInt32 kCFStreamErrorDomainHTTP __attribute__((availability(ios,introduced=2_0)));







typedef int CFStreamErrorHTTP; enum {




  kCFStreamErrorHTTPParseFailure = -1,




  kCFStreamErrorHTTPRedirectionLoop = -2,




  kCFStreamErrorHTTPBadURL = -3
};
extern const CFStringRef kCFStreamPropertyHTTPResponseHeader __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPFinalURL __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPFinalRequest __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPProxy __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPProxyHost __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPProxyPort __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPSProxyHost __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPSProxyPort __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPShouldAutoredirect __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPAttemptPersistentConnection __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern const CFStringRef kCFStreamPropertyHTTPRequestBytesWrittenCount __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern CFReadStreamRef
CFReadStreamCreateForHTTPRequest(CFAllocatorRef _Nullable alloc, CFHTTPMessageRef request) __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
extern CFReadStreamRef
CFReadStreamCreateForStreamedHTTPRequest(CFAllocatorRef _Nullable alloc, CFHTTPMessageRef requestHeaders, CFReadStreamRef requestBody) __attribute__((availability(ios,introduced=2_0,deprecated=9_0,message="" "Use NSURLSession API for http requests")));
#pragma clang assume_nonnull end





}



extern "C" {
#pragma clang assume_nonnull begin








typedef struct _CFHTTPAuthentication* CFHTTPAuthenticationRef;
typedef int CFStreamErrorHTTPAuthentication; enum {





  kCFStreamErrorHTTPAuthenticationTypeUnsupported = -1000,





  kCFStreamErrorHTTPAuthenticationBadUserName = -1001,





  kCFStreamErrorHTTPAuthenticationBadPassword = -1002
};
extern const CFStringRef kCFHTTPAuthenticationUsername __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationPassword __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFHTTPAuthenticationAccountDomain __attribute__((availability(ios,introduced=2_0)));
extern CFTypeID
CFHTTPAuthenticationGetTypeID(void) __attribute__((availability(ios,introduced=2_0)));
extern CFHTTPAuthenticationRef
CFHTTPAuthenticationCreateFromResponse(CFAllocatorRef _Nullable alloc, CFHTTPMessageRef response) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPAuthenticationIsValid(CFHTTPAuthenticationRef auth, CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPAuthenticationAppliesToRequest(CFHTTPAuthenticationRef auth, CFHTTPMessageRef request) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPAuthenticationRequiresOrderedRequests(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageApplyCredentials(
  CFHTTPMessageRef request,
  CFHTTPAuthenticationRef auth,
  CFStringRef _Nullable username,
  CFStringRef _Nullable password,
  CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPMessageApplyCredentialDictionary(
  CFHTTPMessageRef request,
  CFHTTPAuthenticationRef auth,
  CFDictionaryRef dict,
  CFStreamError * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFHTTPAuthenticationCopyRealm(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
extern CFArrayRef
CFHTTPAuthenticationCopyDomains(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
extern CFStringRef
CFHTTPAuthenticationCopyMethod(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPAuthenticationRequiresUserNameAndPassword(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
extern Boolean
CFHTTPAuthenticationRequiresAccountDomain(CFHTTPAuthenticationRef auth) __attribute__((availability(ios,introduced=2_0)));
#pragma clang assume_nonnull end



}



extern "C" {
#pragma clang assume_nonnull begin








typedef struct __CFNetDiagnostic* CFNetDiagnosticRef;







typedef int CFNetDiagnosticStatusValues; enum {




  kCFNetDiagnosticNoErr = 0,




  kCFNetDiagnosticErr = -66560L,




  kCFNetDiagnosticConnectionUp = -66559L,
  kCFNetDiagnosticConnectionIndeterminate = -66558L,




  kCFNetDiagnosticConnectionDown = -66557L

} __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
typedef CFIndex CFNetDiagnosticStatus __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
extern CFNetDiagnosticRef
CFNetDiagnosticCreateWithStreams(CFAllocatorRef _Nullable alloc, CFReadStreamRef _Nullable readStream, CFWriteStreamRef _Nullable writeStream) __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
extern CFNetDiagnosticRef
CFNetDiagnosticCreateWithURL(CFAllocatorRef alloc, CFURLRef url) __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
extern void
CFNetDiagnosticSetName(CFNetDiagnosticRef details, CFStringRef name) __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
extern CFNetDiagnosticStatus
CFNetDiagnosticDiagnoseProblemInteractively(CFNetDiagnosticRef details) __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
extern CFNetDiagnosticStatus
CFNetDiagnosticCopyNetworkStatusPassively(CFNetDiagnosticRef details, CFStringRef _Nullable * _Nullable description) __attribute__((availability(ios,introduced=2_0,deprecated=11_0,message="" )));
#pragma clang assume_nonnull end



}







extern "C" {
#pragma clang assume_nonnull begin
extern _Nullable CFDictionaryRef
CFNetworkCopySystemProxySettings(void) __attribute__((availability(ios,introduced=2_0)));
extern CFArrayRef
CFNetworkCopyProxiesForURL(CFURLRef url, CFDictionaryRef proxySettings) __attribute__((availability(ios,introduced=2_0)));
typedef void ( * CFProxyAutoConfigurationResultCallback)(void *client, CFArrayRef proxyList, CFErrorRef _Nullable error);
extern _Nullable CFArrayRef
CFNetworkCopyProxiesForAutoConfigurationScript(CFStringRef proxyAutoConfigurationScript, CFURLRef targetURL, CFErrorRef * _Nullable error) __attribute__((availability(ios,introduced=2_0)));
extern CFRunLoopSourceRef
CFNetworkExecuteProxyAutoConfigurationScript(
  CFStringRef proxyAutoConfigurationScript,
  CFURLRef targetURL,
  CFProxyAutoConfigurationResultCallback cb,
  CFStreamClientContext * clientContext) __attribute__((availability(ios,introduced=2_0)));
extern CFRunLoopSourceRef
CFNetworkExecuteProxyAutoConfigurationURL(
  CFURLRef proxyAutoConfigURL,
  CFURLRef targetURL,
  CFProxyAutoConfigurationResultCallback cb,
  CFStreamClientContext * clientContext) __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyTypeKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyHostNameKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyPortNumberKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyAutoConfigurationURLKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyAutoConfigurationJavaScriptKey __attribute__((availability(ios,introduced=3_0)));
extern const CFStringRef kCFProxyUsernameKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyPasswordKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFProxyTypeNone __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeHTTP __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeHTTPS __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeSOCKS __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeFTP __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeAutoConfigurationURL __attribute__((availability(ios,introduced=2_0)));





extern const CFStringRef kCFProxyTypeAutoConfigurationJavaScript __attribute__((availability(ios,introduced=3_0)));





extern const CFStringRef kCFProxyAutoConfigurationHTTPResponseKey __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesExceptionsList __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesExcludeSimpleHostnames __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesFTPEnable __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesFTPPassive __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesFTPPort __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesFTPProxy __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesGopherEnable __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesGopherPort __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesGopherProxy __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesHTTPEnable __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesHTTPPort __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesHTTPProxy __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesHTTPSEnable __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesHTTPSPort __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesHTTPSProxy __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesRTSPEnable __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesRTSPPort __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesRTSPProxy __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesSOCKSEnable __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesSOCKSPort __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesSOCKSProxy __attribute__((availability(ios,introduced=NA)));
extern const CFStringRef kCFNetworkProxiesProxyAutoConfigEnable __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesProxyAutoConfigURLString __attribute__((availability(ios,introduced=2_0)));
extern const CFStringRef kCFNetworkProxiesProxyAutoConfigJavaScript __attribute__((availability(ios,introduced=3_0)));
extern const CFStringRef kCFNetworkProxiesProxyAutoDiscoveryEnable __attribute__((availability(ios,introduced=NA)));
#pragma clang assume_nonnull end


}








// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin





extern "C" NSErrorDomain const NSURLErrorDomain;





extern "C" NSString * const NSURLErrorFailingURLErrorKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






extern "C" NSString * const NSURLErrorFailingURLStringErrorKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






extern "C" NSString * const NSErrorFailingURLStringKey __attribute__((availability(macos,introduced=10.0,deprecated=10.6,message="Use NSURLErrorFailingURLStringErrorKey instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=4.0,message="Use NSURLErrorFailingURLStringErrorKey instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use NSURLErrorFailingURLStringErrorKey instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use NSURLErrorFailingURLStringErrorKey instead")));





extern "C" NSString * const NSURLErrorFailingURLPeerTrustErrorKey __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






extern "C" NSString * const NSURLErrorBackgroundTaskCancelledReasonKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






enum
{
    NSURLErrorCancelledReasonUserForceQuitApplication = 0,
    NSURLErrorCancelledReasonBackgroundUpdatesDisabled = 1,
    NSURLErrorCancelledReasonInsufficientSystemResources __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 2,

} __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





extern "C" NSErrorUserInfoKey const NSURLErrorNetworkUnavailableReasonKey __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));







typedef NSInteger NSURLErrorNetworkUnavailableReason; enum
{
    NSURLErrorNetworkUnavailableReasonCellular = 0,
    NSURLErrorNetworkUnavailableReasonExpensive = 1,
    NSURLErrorNetworkUnavailableReasonConstrained = 2,
} __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));





enum
{
    NSURLErrorUnknown = -1,
    NSURLErrorCancelled = -999,
    NSURLErrorBadURL = -1000,
    NSURLErrorTimedOut = -1001,
    NSURLErrorUnsupportedURL = -1002,
    NSURLErrorCannotFindHost = -1003,
    NSURLErrorCannotConnectToHost = -1004,
    NSURLErrorNetworkConnectionLost = -1005,
    NSURLErrorDNSLookupFailed = -1006,
    NSURLErrorHTTPTooManyRedirects = -1007,
    NSURLErrorResourceUnavailable = -1008,
    NSURLErrorNotConnectedToInternet = -1009,
    NSURLErrorRedirectToNonExistentLocation = -1010,
    NSURLErrorBadServerResponse = -1011,
    NSURLErrorUserCancelledAuthentication = -1012,
    NSURLErrorUserAuthenticationRequired = -1013,
    NSURLErrorZeroByteResource = -1014,
    NSURLErrorCannotDecodeRawData = -1015,
    NSURLErrorCannotDecodeContentData = -1016,
    NSURLErrorCannotParseResponse = -1017,
    NSURLErrorAppTransportSecurityRequiresSecureConnection __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1022,
    NSURLErrorFileDoesNotExist = -1100,
    NSURLErrorFileIsDirectory = -1101,
    NSURLErrorNoPermissionsToReadFile = -1102,
    NSURLErrorDataLengthExceedsMaximum __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1103,
    NSURLErrorFileOutsideSafeArea __attribute__((availability(macos,introduced=10.12.4))) __attribute__((availability(ios,introduced=10.3))) __attribute__((availability(watchos,introduced=3.2))) __attribute__((availability(tvos,introduced=10.2))) = -1104,


    NSURLErrorSecureConnectionFailed = -1200,
    NSURLErrorServerCertificateHasBadDate = -1201,
    NSURLErrorServerCertificateUntrusted = -1202,
    NSURLErrorServerCertificateHasUnknownRoot = -1203,
    NSURLErrorServerCertificateNotYetValid = -1204,
    NSURLErrorClientCertificateRejected = -1205,
    NSURLErrorClientCertificateRequired = -1206,
    NSURLErrorCannotLoadFromNetwork = -2000,


    NSURLErrorCannotCreateFile = -3000,
    NSURLErrorCannotOpenFile = -3001,
    NSURLErrorCannotCloseFile = -3002,
    NSURLErrorCannotWriteToFile = -3003,
    NSURLErrorCannotRemoveFile = -3004,
    NSURLErrorCannotMoveFile = -3005,
    NSURLErrorDownloadDecodingFailedMidStream = -3006,
    NSURLErrorDownloadDecodingFailedToComplete =-3007,

    NSURLErrorInternationalRoamingOff __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1018,
    NSURLErrorCallIsActive __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1019,
    NSURLErrorDataNotAllowed __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1020,
    NSURLErrorRequestBodyStreamExhausted __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -1021,

    NSURLErrorBackgroundSessionRequiresSharedContainer __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -995,
    NSURLErrorBackgroundSessionInUseByAnotherProcess __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = -996,
    NSURLErrorBackgroundSessionWasDisconnected __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))= -997,
};
#pragma clang assume_nonnull end

// @class NSCachedURLResponse;
#ifndef _REWRITER_typedef_NSCachedURLResponse
#define _REWRITER_typedef_NSCachedURLResponse
typedef struct objc_object NSCachedURLResponse;
typedef struct {} _objc_exc_NSCachedURLResponse;
#endif

// @class NSError;
#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

// @class NSMutableURLRequest;
#ifndef _REWRITER_typedef_NSMutableURLRequest
#define _REWRITER_typedef_NSMutableURLRequest
typedef struct objc_object NSMutableURLRequest;
typedef struct {} _objc_exc_NSMutableURLRequest;
#endif

// @class NSURLAuthenticationChallenge;
#ifndef _REWRITER_typedef_NSURLAuthenticationChallenge
#define _REWRITER_typedef_NSURLAuthenticationChallenge
typedef struct objc_object NSURLAuthenticationChallenge;
typedef struct {} _objc_exc_NSURLAuthenticationChallenge;
#endif

// @class NSURLConnection;
#ifndef _REWRITER_typedef_NSURLConnection
#define _REWRITER_typedef_NSURLConnection
typedef struct objc_object NSURLConnection;
typedef struct {} _objc_exc_NSURLConnection;
#endif

// @class NSURLProtocol;
#ifndef _REWRITER_typedef_NSURLProtocol
#define _REWRITER_typedef_NSURLProtocol
typedef struct objc_object NSURLProtocol;
typedef struct {} _objc_exc_NSURLProtocol;
#endif

// @class NSURLProtocolInternal;
#ifndef _REWRITER_typedef_NSURLProtocolInternal
#define _REWRITER_typedef_NSURLProtocolInternal
typedef struct objc_object NSURLProtocolInternal;
typedef struct {} _objc_exc_NSURLProtocolInternal;
#endif

// @class NSURLRequest;
#ifndef _REWRITER_typedef_NSURLRequest
#define _REWRITER_typedef_NSURLRequest
typedef struct objc_object NSURLRequest;
typedef struct {} _objc_exc_NSURLRequest;
#endif

// @class NSURLResponse;
#ifndef _REWRITER_typedef_NSURLResponse
#define _REWRITER_typedef_NSURLResponse
typedef struct objc_object NSURLResponse;
typedef struct {} _objc_exc_NSURLResponse;
#endif

// @class NSURLSessionTask;
#ifndef _REWRITER_typedef_NSURLSessionTask
#define _REWRITER_typedef_NSURLSessionTask
typedef struct objc_object NSURLSessionTask;
typedef struct {} _objc_exc_NSURLSessionTask;
#endif


#pragma clang assume_nonnull begin
// @protocol NSURLProtocolClient <NSObject>
// - (void)URLProtocol:(NSURLProtocol *)protocol wasRedirectedToRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;
// - (void)URLProtocol:(NSURLProtocol *)protocol cachedResponseIsValid:(NSCachedURLResponse *)cachedResponse;
// - (void)URLProtocol:(NSURLProtocol *)protocol didReceiveResponse:(NSURLResponse *)response cacheStoragePolicy:(NSURLCacheStoragePolicy)policy;
// - (void)URLProtocol:(NSURLProtocol *)protocol didLoadData:(NSData *)data;







// - (void)URLProtocolDidFinishLoading:(NSURLProtocol *)protocol;
// - (void)URLProtocol:(NSURLProtocol *)protocol didFailWithError:(NSError *)error;
// - (void)URLProtocol:(NSURLProtocol *)protocol didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;







// - (void)URLProtocol:(NSURLProtocol *)protocol didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/* @end */


#ifndef _REWRITER_typedef_NSURLProtocol
#define _REWRITER_typedef_NSURLProtocol
typedef struct objc_object NSURLProtocol;
typedef struct {} _objc_exc_NSURLProtocol;
#endif

struct NSURLProtocol_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLProtocolInternal *_internal;
};

// - (instancetype)initWithRequest:(NSURLRequest *)request cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client __attribute__((objc_designated_initializer));





// @property (nullable, readonly, retain) id <NSURLProtocolClient> client;





// @property (readonly, copy) NSURLRequest *request;





// @property (nullable, readonly, copy) NSCachedURLResponse *cachedResponse;
// + (BOOL)canInitWithRequest:(NSURLRequest *)request;
// + (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;
// + (BOOL)requestIsCacheEquivalent:(NSURLRequest *)a toRequest:(NSURLRequest *)b;







// - (void)startLoading;
// - (void)stopLoading;
// + (nullable id)propertyForKey:(NSString *)key inRequest:(NSURLRequest *)request;
// + (void)setProperty:(id)value forKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;
// + (void)removePropertyForKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;
// + (BOOL)registerClass:(Class)protocolClass;
// + (void)unregisterClass:(Class)protocolClass;

/* @end */



// @interface NSURLProtocol (NSURLSessionTaskAdditions)
// + (BOOL)canInitWithTask:(NSURLSessionTask *)task __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (instancetype)initWithTask:(NSURLSessionTask *)task cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, readonly, copy) NSURLSessionTask *task __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */

#pragma clang assume_nonnull end
// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

// @class NSDictionary;
#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

// @class NSInputStream;
#ifndef _REWRITER_typedef_NSInputStream
#define _REWRITER_typedef_NSInputStream
typedef struct objc_object NSInputStream;
typedef struct {} _objc_exc_NSInputStream;
#endif

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSURL;
#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif

// @class NSURLRequestInternal;
#ifndef _REWRITER_typedef_NSURLRequestInternal
#define _REWRITER_typedef_NSURLRequestInternal
typedef struct objc_object NSURLRequestInternal;
typedef struct {} _objc_exc_NSURLRequestInternal;
#endif


#pragma clang assume_nonnull begin
typedef NSUInteger NSURLRequestCachePolicy; enum
{
    NSURLRequestUseProtocolCachePolicy = 0,

    NSURLRequestReloadIgnoringLocalCacheData = 1,
    NSURLRequestReloadIgnoringLocalAndRemoteCacheData = 4,
    NSURLRequestReloadIgnoringCacheData = NSURLRequestReloadIgnoringLocalCacheData,

    NSURLRequestReturnCacheDataElseLoad = 2,
    NSURLRequestReturnCacheDataDontLoad = 3,

    NSURLRequestReloadRevalidatingCacheData = 5,
};
typedef NSUInteger NSURLRequestNetworkServiceType; enum
{
    NSURLNetworkServiceTypeDefault = 0,
    NSURLNetworkServiceTypeVoIP __attribute__((availability(macos,introduced=10.7,deprecated=10.15,message="Use PushKit for VoIP control purposes"))) __attribute__((availability(ios,introduced=4.0,deprecated=13.0,message="Use PushKit for VoIP control purposes"))) __attribute__((availability(watchos,introduced=2.0,deprecated=6.0,message="Use PushKit for VoIP control purposes"))) __attribute__((availability(tvos,introduced=9.0,deprecated=13.0,message="Use PushKit for VoIP control purposes"))) = 1,
    NSURLNetworkServiceTypeVideo = 2,
    NSURLNetworkServiceTypeBackground = 3,
    NSURLNetworkServiceTypeVoice = 4,
    NSURLNetworkServiceTypeResponsiveData = 6,
    NSURLNetworkServiceTypeAVStreaming __attribute__((availability(macosx,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 8 ,
    NSURLNetworkServiceTypeResponsiveAV __attribute__((availability(macosx,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 9,
    NSURLNetworkServiceTypeCallSignaling __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0))) = 11,
};

#ifndef _REWRITER_typedef_NSURLRequest
#define _REWRITER_typedef_NSURLRequest
typedef struct objc_object NSURLRequest;
typedef struct {} _objc_exc_NSURLRequest;
#endif

struct NSURLRequest_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLRequestInternal *_internal;
};

// + (instancetype)requestWithURL:(NSURL *)URL;






@property (class, readonly) BOOL supportsSecureCoding;
// + (instancetype)requestWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval;
// - (instancetype)initWithURL:(NSURL *)URL;
// - (instancetype)initWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval __attribute__((objc_designated_initializer));





// @property (nullable, readonly, copy) NSURL *URL;





// @property (readonly) NSURLRequestCachePolicy cachePolicy;
// @property (readonly) NSTimeInterval timeoutInterval;
// @property (nullable, readonly, copy) NSURL *mainDocumentURL;







// @property (readonly) NSURLRequestNetworkServiceType networkServiceType __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));







// @property (readonly) BOOL allowsCellularAccess __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));







// @property (readonly) BOOL allowsExpensiveNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));







// @property (readonly) BOOL allowsConstrainedNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

/* @end */


#ifndef _REWRITER_typedef_NSMutableURLRequest
#define _REWRITER_typedef_NSMutableURLRequest
typedef struct objc_object NSMutableURLRequest;
typedef struct {} _objc_exc_NSMutableURLRequest;
#endif

struct NSMutableURLRequest_IMPL {
	struct NSURLRequest_IMPL NSURLRequest_IVARS;
};





// @property (nullable, copy) NSURL *URL;




// @property NSURLRequestCachePolicy cachePolicy;
// @property NSTimeInterval timeoutInterval;
// @property (nullable, copy) NSURL *mainDocumentURL;






// @property NSURLRequestNetworkServiceType networkServiceType __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));







// @property BOOL allowsCellularAccess __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));







// @property BOOL allowsExpensiveNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));







// @property BOOL allowsConstrainedNetworkAccess __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

/* @end */

// @interface NSURLRequest (NSHTTPURLRequest)





// @property (nullable, readonly, copy) NSString *HTTPMethod;







// @property (nullable, readonly, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;
// - (nullable NSString *)valueForHTTPHeaderField:(NSString *)field;







// @property (nullable, readonly, copy) NSData *HTTPBody;
// @property (nullable, readonly, retain) NSInputStream *HTTPBodyStream;
// @property (readonly) BOOL HTTPShouldHandleCookies;
// @property (readonly) BOOL HTTPShouldUsePipelining __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

// @interface NSMutableURLRequest (NSMutableHTTPURLRequest)




// @property (copy) NSString *HTTPMethod;
// @property (nullable, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;
// - (void)setValue:(nullable NSString *)value forHTTPHeaderField:(NSString *)field;
// - (void)addValue:(NSString *)value forHTTPHeaderField:(NSString *)field;






// @property (nullable, copy) NSData *HTTPBody;
// @property (nullable, retain) NSInputStream *HTTPBodyStream;
// @property BOOL HTTPShouldHandleCookies;
// @property BOOL HTTPShouldUsePipelining __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end
// @class NSDictionary;
#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSURL;
#ifndef _REWRITER_typedef_NSURL
#define _REWRITER_typedef_NSURL
typedef struct objc_object NSURL;
typedef struct {} _objc_exc_NSURL;
#endif

// @class NSURLRequest;
#ifndef _REWRITER_typedef_NSURLRequest
#define _REWRITER_typedef_NSURLRequest
typedef struct objc_object NSURLRequest;
typedef struct {} _objc_exc_NSURLRequest;
#endif

// @class NSURLResponseInternal;
#ifndef _REWRITER_typedef_NSURLResponseInternal
#define _REWRITER_typedef_NSURLResponseInternal
typedef struct objc_object NSURLResponseInternal;
typedef struct {} _objc_exc_NSURLResponseInternal;
#endif


#pragma clang assume_nonnull begin

#ifndef _REWRITER_typedef_NSURLResponse
#define _REWRITER_typedef_NSURLResponse
typedef struct objc_object NSURLResponse;
typedef struct {} _objc_exc_NSURLResponse;
#endif

struct NSURLResponse_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURLResponseInternal *_internal;
};

// - (instancetype)initWithURL:(NSURL *)URL MIMEType:(nullable NSString *)MIMEType expectedContentLength:(NSInteger)length textEncodingName:(nullable NSString *)name __attribute__((objc_designated_initializer));





// @property (nullable, readonly, copy) NSURL *URL;
// @property (nullable, readonly, copy) NSString *MIMEType;
// @property (readonly) long long expectedContentLength;
// @property (nullable, readonly, copy) NSString *textEncodingName;
// @property (nullable, readonly, copy) NSString *suggestedFilename;

/* @end */




// @class NSHTTPURLResponseInternal;
#ifndef _REWRITER_typedef_NSHTTPURLResponseInternal
#define _REWRITER_typedef_NSHTTPURLResponseInternal
typedef struct objc_object NSHTTPURLResponseInternal;
typedef struct {} _objc_exc_NSHTTPURLResponseInternal;
#endif


#ifndef _REWRITER_typedef_NSHTTPURLResponse
#define _REWRITER_typedef_NSHTTPURLResponse
typedef struct objc_object NSHTTPURLResponse;
typedef struct {} _objc_exc_NSHTTPURLResponse;
#endif

struct NSHTTPURLResponse_IMPL {
	struct NSURLResponse_IMPL NSURLResponse_IVARS;
	NSHTTPURLResponseInternal *_httpInternal;
};

// - (nullable instancetype)initWithURL:(NSURL *)url statusCode:(NSInteger)statusCode HTTPVersion:(nullable NSString *)HTTPVersion headerFields:(nullable NSDictionary<NSString *, NSString *> *)headerFields __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// @property (readonly) NSInteger statusCode;
// @property (readonly, copy) NSDictionary *allHeaderFields;
// - (nullable NSString *)valueForHTTPHeaderField:(NSString *)field __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));
// + (NSString *)localizedStringForStatusCode:(NSInteger)statusCode;

/* @end */

#pragma clang assume_nonnull end







// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSMutableDictionary
#define _REWRITER_typedef_NSMutableDictionary
typedef struct objc_object NSMutableDictionary;
typedef struct {} _objc_exc_NSMutableDictionary;
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


extern "C" NSString * const NSGlobalDomain;

extern "C" NSString * const NSArgumentDomain;

extern "C" NSString * const NSRegistrationDomain;

#ifndef _REWRITER_typedef_NSUserDefaults
#define _REWRITER_typedef_NSUserDefaults
typedef struct objc_object NSUserDefaults;
typedef struct {} _objc_exc_NSUserDefaults;
#endif

struct NSUserDefaults_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _kvo_;
	CFStringRef _identifier_;
	CFStringRef _container_;
	void *_reserved[2];
};





@property (class, readonly, strong) NSUserDefaults *standardUserDefaults;


// + (void)resetStandardUserDefaults;


// - (instancetype)init;


// - (nullable instancetype)initWithSuiteName:(nullable NSString *)suitename __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((objc_designated_initializer));


// - (nullable id)initWithUser:(NSString *)username __attribute__((availability(macos,introduced=10.0,deprecated=10.9,message="Use -init instead"))) __attribute__((availability(ios,introduced=2.0,deprecated=7.0,message="Use -init instead"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Use -init instead"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Use -init instead")));




// - (nullable id)objectForKey:(NSString *)defaultName;




// - (void)setObject:(nullable id)value forKey:(NSString *)defaultName;


// - (void)removeObjectForKey:(NSString *)defaultName;


// - (nullable NSString *)stringForKey:(NSString *)defaultName;


// - (nullable NSArray *)arrayForKey:(NSString *)defaultName;

// - (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)defaultName;

// - (nullable NSData *)dataForKey:(NSString *)defaultName;

// - (nullable NSArray<NSString *> *)stringArrayForKey:(NSString *)defaultName;



// - (NSInteger)integerForKey:(NSString *)defaultName;

// - (float)floatForKey:(NSString *)defaultName;

// - (double)doubleForKey:(NSString *)defaultName;




// - (BOOL)boolForKey:(NSString *)defaultName;



// - (nullable NSURL *)URLForKey:(NSString *)defaultName __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// - (void)setInteger:(NSInteger)value forKey:(NSString *)defaultName;

// - (void)setFloat:(float)value forKey:(NSString *)defaultName;

// - (void)setDouble:(double)value forKey:(NSString *)defaultName;

// - (void)setBool:(BOOL)value forKey:(NSString *)defaultName;

// - (void)setURL:(nullable NSURL *)url forKey:(NSString *)defaultName __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






// - (void)registerDefaults:(NSDictionary<NSString *, id> *)registrationDictionary;




// - (void)addSuiteNamed:(NSString *)suiteName;



// - (void)removeSuiteNamed:(NSString *)suiteName;




// - (NSDictionary<NSString *, id> *)dictionaryRepresentation;




// @property (readonly, copy) NSArray<NSString *> *volatileDomainNames;
// - (NSDictionary<NSString *, id> *)volatileDomainForName:(NSString *)domainName;
// - (void)setVolatileDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;
// - (void)removeVolatileDomainForName:(NSString *)domainName;


// - (NSArray *)persistentDomainNames __attribute__((availability(macos,introduced=10.0,deprecated=10.9,message="Not recommended"))) __attribute__((availability(ios,introduced=2.0,deprecated=7.0,message="Not recommended"))) __attribute__((availability(watchos,introduced=2.0,deprecated=2.0,message="Not recommended"))) __attribute__((availability(tvos,introduced=9.0,deprecated=9.0,message="Not recommended")));


// - (nullable NSDictionary<NSString *, id> *)persistentDomainForName:(NSString *)domainName;

// - (void)setPersistentDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;

// - (void)removePersistentDomainForName:(NSString *)domainName;
// - (BOOL)synchronize;


// - (BOOL)objectIsForcedForKey:(NSString *)key;


// - (BOOL)objectIsForcedForKey:(NSString *)key inDomain:(NSString *)domain;

/* @end */





extern "C" NSNotificationName const NSUserDefaultsSizeLimitExceededNotification __attribute__((availability(ios,introduced=9.3))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));






extern "C" NSNotificationName const NSUbiquitousUserDefaultsNoCloudAccountNotification __attribute__((availability(ios,introduced=9.3))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));




extern "C" NSNotificationName const NSUbiquitousUserDefaultsDidChangeAccountsNotification __attribute__((availability(ios,introduced=9.3))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));




extern "C" NSNotificationName const NSUbiquitousUserDefaultsCompletedInitialSyncNotification __attribute__((availability(ios,introduced=9.3))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));




extern "C" NSNotificationName const NSUserDefaultsDidChangeNotification;
#pragma clang assume_nonnull end







// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin

typedef NSString *NSValueTransformerName __attribute__((swift_wrapper(struct)));

extern "C" NSValueTransformerName const NSNegateBooleanTransformerName __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSValueTransformerName const NSIsNilTransformerName __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSValueTransformerName const NSIsNotNilTransformerName __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

extern "C" NSValueTransformerName const NSUnarchiveFromDataTransformerName __attribute__((availability(macos,introduced=10.3,deprecated=10.14,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(ios,introduced=3.0,deprecated=12.0,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(watchos,introduced=2.0,deprecated=5.0,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(tvos,introduced=9.0,deprecated=12.0,replacement="NSSecureUnarchiveFromDataTransformerName")));
extern "C" NSValueTransformerName const NSKeyedUnarchiveFromDataTransformerName __attribute__((availability(macos,introduced=10.3,deprecated=10.14,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(ios,introduced=3.0,deprecated=12.0,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(watchos,introduced=2.0,deprecated=5.0,replacement="NSSecureUnarchiveFromDataTransformerName"))) __attribute__((availability(tvos,introduced=9.0,deprecated=12.0,replacement="NSSecureUnarchiveFromDataTransformerName")));
extern "C" NSValueTransformerName const NSSecureUnarchiveFromDataTransformerName __attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)));

__attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSValueTransformer
#define _REWRITER_typedef_NSValueTransformer
typedef struct objc_object NSValueTransformer;
typedef struct {} _objc_exc_NSValueTransformer;
#endif

struct NSValueTransformer_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};




// + (void)setValueTransformer:(nullable NSValueTransformer *)transformer forName:(NSValueTransformerName)name;
// + (nullable NSValueTransformer *)valueTransformerForName:(NSValueTransformerName)name;
// + (NSArray<NSValueTransformerName> *)valueTransformerNames;


// + (Class)transformedValueClass;
// + (BOOL)allowsReverseTransformation;

// - (nullable id)transformedValue:(nullable id)value;
// - (nullable id)reverseTransformedValue:(nullable id)value;

/* @end */



__attribute__((availability(macos,introduced=10.14))) __attribute__((availability(ios,introduced=12.0))) __attribute__((availability(watchos,introduced=5.0))) __attribute__((availability(tvos,introduced=12.0)))

#ifndef _REWRITER_typedef_NSSecureUnarchiveFromDataTransformer
#define _REWRITER_typedef_NSSecureUnarchiveFromDataTransformer
typedef struct objc_object NSSecureUnarchiveFromDataTransformer;
typedef struct {} _objc_exc_NSSecureUnarchiveFromDataTransformer;
#endif

struct NSSecureUnarchiveFromDataTransformer_IMPL {
	struct NSValueTransformer_IMPL NSValueTransformer_IVARS;
};







@property (class, readonly, copy) NSArray<Class> *allowedTopLevelClasses;

/* @end */

#pragma clang assume_nonnull end







// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
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

#ifndef _REWRITER_typedef_NSInputStream
#define _REWRITER_typedef_NSInputStream
typedef struct objc_object NSInputStream;
typedef struct {} _objc_exc_NSInputStream;
#endif

#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif

// @protocol NSXMLParserDelegate;

#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
typedef NSUInteger NSXMLParserExternalEntityResolvingPolicy; enum {
    NSXMLParserResolveExternalEntitiesNever = 0,
    NSXMLParserResolveExternalEntitiesNoNetwork,
    NSXMLParserResolveExternalEntitiesSameOriginOnly,
    NSXMLParserResolveExternalEntitiesAlways
};


#ifndef _REWRITER_typedef_NSXMLParser
#define _REWRITER_typedef_NSXMLParser
typedef struct objc_object NSXMLParser;
typedef struct {} _objc_exc_NSXMLParser;
#endif

struct NSXMLParser_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _reserved0;
	id _delegate;
	id _reserved1;
	id _reserved2;
	id _reserved3;
};

// - (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
// - (instancetype)initWithData:(NSData *)data __attribute__((objc_designated_initializer));
// - (instancetype)initWithStream:(NSInputStream *)stream __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// @property (nullable, assign) id <NSXMLParserDelegate> delegate;

// @property BOOL shouldProcessNamespaces;
// @property BOOL shouldReportNamespacePrefixes;


// @property NSXMLParserExternalEntityResolvingPolicy externalEntityResolvingPolicy __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (nullable, copy) NSSet<NSURL *> *allowedExternalEntityURLs __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (BOOL)parse;
// - (void)abortParsing;

// @property (nullable, readonly, copy) NSError *parserError;



// @property BOOL shouldResolveExternalEntities;

/* @end */



// @interface NSXMLParser (NSXMLParserLocatorAdditions)
// @property (nullable, readonly, copy) NSString *publicID;
// @property (nullable, readonly, copy) NSString *systemID;
// @property (readonly) NSInteger lineNumber;
// @property (readonly) NSInteger columnNumber;

/* @end */

// @protocol NSXMLParserDelegate <NSObject>
/* @optional */


// - (void)parserDidStartDocument:(NSXMLParser *)parser;

// - (void)parserDidEndDocument:(NSXMLParser *)parser;



// - (void)parser:(NSXMLParser *)parser foundNotationDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

// - (void)parser:(NSXMLParser *)parser foundUnparsedEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID notationName:(nullable NSString *)notationName;

// - (void)parser:(NSXMLParser *)parser foundAttributeDeclarationWithName:(NSString *)attributeName forElement:(NSString *)elementName type:(nullable NSString *)type defaultValue:(nullable NSString *)defaultValue;

// - (void)parser:(NSXMLParser *)parser foundElementDeclarationWithName:(NSString *)elementName model:(NSString *)model;

// - (void)parser:(NSXMLParser *)parser foundInternalEntityDeclarationWithName:(NSString *)name value:(nullable NSString *)value;

// - (void)parser:(NSXMLParser *)parser foundExternalEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

// - (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName attributes:(NSDictionary<NSString *, NSString *> *)attributeDict;







// - (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName;


// - (void)parser:(NSXMLParser *)parser didStartMappingPrefix:(NSString *)prefix toURI:(NSString *)namespaceURI;




// - (void)parser:(NSXMLParser *)parser didEndMappingPrefix:(NSString *)prefix;


// - (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;


// - (void)parser:(NSXMLParser *)parser foundIgnorableWhitespace:(NSString *)whitespaceString;


// - (void)parser:(NSXMLParser *)parser foundProcessingInstructionWithTarget:(NSString *)target data:(nullable NSString *)data;


// - (void)parser:(NSXMLParser *)parser foundComment:(NSString *)comment;


// - (void)parser:(NSXMLParser *)parser foundCDATA:(NSData *)CDATABlock;


// - (nullable NSData *)parser:(NSXMLParser *)parser resolveExternalEntityName:(NSString *)name systemID:(nullable NSString *)systemID;


// - (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError;


// - (void)parser:(NSXMLParser *)parser validationErrorOccurred:(NSError *)validationError;

/* @end */


extern "C" NSErrorDomain const NSXMLParserErrorDomain __attribute__((availability(macos,introduced=10.3))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


typedef NSInteger NSXMLParserError; enum {
    NSXMLParserInternalError = 1,
    NSXMLParserOutOfMemoryError = 2,
    NSXMLParserDocumentStartError = 3,
    NSXMLParserEmptyDocumentError = 4,
    NSXMLParserPrematureDocumentEndError = 5,
    NSXMLParserInvalidHexCharacterRefError = 6,
    NSXMLParserInvalidDecimalCharacterRefError = 7,
    NSXMLParserInvalidCharacterRefError = 8,
    NSXMLParserInvalidCharacterError = 9,
    NSXMLParserCharacterRefAtEOFError = 10,
    NSXMLParserCharacterRefInPrologError = 11,
    NSXMLParserCharacterRefInEpilogError = 12,
    NSXMLParserCharacterRefInDTDError = 13,
    NSXMLParserEntityRefAtEOFError = 14,
    NSXMLParserEntityRefInPrologError = 15,
    NSXMLParserEntityRefInEpilogError = 16,
    NSXMLParserEntityRefInDTDError = 17,
    NSXMLParserParsedEntityRefAtEOFError = 18,
    NSXMLParserParsedEntityRefInPrologError = 19,
    NSXMLParserParsedEntityRefInEpilogError = 20,
    NSXMLParserParsedEntityRefInInternalSubsetError = 21,
    NSXMLParserEntityReferenceWithoutNameError = 22,
    NSXMLParserEntityReferenceMissingSemiError = 23,
    NSXMLParserParsedEntityRefNoNameError = 24,
    NSXMLParserParsedEntityRefMissingSemiError = 25,
    NSXMLParserUndeclaredEntityError = 26,
    NSXMLParserUnparsedEntityError = 28,
    NSXMLParserEntityIsExternalError = 29,
    NSXMLParserEntityIsParameterError = 30,
    NSXMLParserUnknownEncodingError = 31,
    NSXMLParserEncodingNotSupportedError = 32,
    NSXMLParserStringNotStartedError = 33,
    NSXMLParserStringNotClosedError = 34,
    NSXMLParserNamespaceDeclarationError = 35,
    NSXMLParserEntityNotStartedError = 36,
    NSXMLParserEntityNotFinishedError = 37,
    NSXMLParserLessThanSymbolInAttributeError = 38,
    NSXMLParserAttributeNotStartedError = 39,
    NSXMLParserAttributeNotFinishedError = 40,
    NSXMLParserAttributeHasNoValueError = 41,
    NSXMLParserAttributeRedefinedError = 42,
    NSXMLParserLiteralNotStartedError = 43,
    NSXMLParserLiteralNotFinishedError = 44,
    NSXMLParserCommentNotFinishedError = 45,
    NSXMLParserProcessingInstructionNotStartedError = 46,
    NSXMLParserProcessingInstructionNotFinishedError = 47,
    NSXMLParserNotationNotStartedError = 48,
    NSXMLParserNotationNotFinishedError = 49,
    NSXMLParserAttributeListNotStartedError = 50,
    NSXMLParserAttributeListNotFinishedError = 51,
    NSXMLParserMixedContentDeclNotStartedError = 52,
    NSXMLParserMixedContentDeclNotFinishedError = 53,
    NSXMLParserElementContentDeclNotStartedError = 54,
    NSXMLParserElementContentDeclNotFinishedError = 55,
    NSXMLParserXMLDeclNotStartedError = 56,
    NSXMLParserXMLDeclNotFinishedError = 57,
    NSXMLParserConditionalSectionNotStartedError = 58,
    NSXMLParserConditionalSectionNotFinishedError = 59,
    NSXMLParserExternalSubsetNotFinishedError = 60,
    NSXMLParserDOCTYPEDeclNotFinishedError = 61,
    NSXMLParserMisplacedCDATAEndStringError = 62,
    NSXMLParserCDATANotFinishedError = 63,
    NSXMLParserMisplacedXMLDeclarationError = 64,
    NSXMLParserSpaceRequiredError = 65,
    NSXMLParserSeparatorRequiredError = 66,
    NSXMLParserNMTOKENRequiredError = 67,
    NSXMLParserNAMERequiredError = 68,
    NSXMLParserPCDATARequiredError = 69,
    NSXMLParserURIRequiredError = 70,
    NSXMLParserPublicIdentifierRequiredError = 71,
    NSXMLParserLTRequiredError = 72,
    NSXMLParserGTRequiredError = 73,
    NSXMLParserLTSlashRequiredError = 74,
    NSXMLParserEqualExpectedError = 75,
    NSXMLParserTagNameMismatchError = 76,
    NSXMLParserUnfinishedTagError = 77,
    NSXMLParserStandaloneValueError = 78,
    NSXMLParserInvalidEncodingNameError = 79,
    NSXMLParserCommentContainsDoubleHyphenError = 80,
    NSXMLParserInvalidEncodingError = 81,
    NSXMLParserExternalStandaloneEntityError = 82,
    NSXMLParserInvalidConditionalSectionError = 83,
    NSXMLParserEntityValueRequiredError = 84,
    NSXMLParserNotWellBalancedError = 85,
    NSXMLParserExtraContentError = 86,
    NSXMLParserInvalidCharacterInEntityError = 87,
    NSXMLParserParsedEntityRefInInternalError = 88,
    NSXMLParserEntityRefLoopError = 89,
    NSXMLParserEntityBoundaryError = 90,
    NSXMLParserInvalidURIError = 91,
    NSXMLParserURIFragmentError = 92,
    NSXMLParserNoDTDError = 94,
    NSXMLParserDelegateAbortedParseError = 512
};
#pragma clang assume_nonnull end





extern "C" {

typedef uid_t au_id_t;
typedef pid_t au_asid_t;
typedef u_int16_t au_event_t;
typedef u_int16_t au_emod_t;
typedef u_int32_t au_class_t;
typedef u_int64_t au_asflgs_t __attribute__ ((aligned(8)));
typedef unsigned char au_ctlmode_t;

struct au_tid {
 dev_t port;
 u_int32_t machine;
};
typedef struct au_tid au_tid_t;

struct au_tid_addr {
 dev_t at_port;
 u_int32_t at_type;
 u_int32_t at_addr[4];
};
typedef struct au_tid_addr au_tid_addr_t;

struct au_mask {
 unsigned int am_success;
 unsigned int am_failure;
};
typedef struct au_mask au_mask_t;

struct auditinfo {
 au_id_t ai_auid;
 au_mask_t ai_mask;
 au_tid_t ai_termid;
 au_asid_t ai_asid;
};
typedef struct auditinfo auditinfo_t;

struct auditinfo_addr {
 au_id_t ai_auid;
 au_mask_t ai_mask;
 au_tid_addr_t ai_termid;
 au_asid_t ai_asid;
 au_asflgs_t ai_flags;
};
typedef struct auditinfo_addr auditinfo_addr_t;

struct auditpinfo {
 pid_t ap_pid;
 au_id_t ap_auid;
 au_mask_t ap_mask;
 au_tid_t ap_termid;
 au_asid_t ap_asid;
};
typedef struct auditpinfo auditpinfo_t;

struct auditpinfo_addr {
 pid_t ap_pid;
 au_id_t ap_auid;
 au_mask_t ap_mask;
 au_tid_addr_t ap_termid;
 au_asid_t ap_asid;
 au_asflgs_t ap_flags;
};
typedef struct auditpinfo_addr auditpinfo_addr_t;

struct au_session {
 auditinfo_addr_t *as_aia_p;
 au_mask_t as_mask;
};
typedef struct au_session au_session_t;

struct au_expire_after {
 time_t age;
 size_t size;
 unsigned char op_type;
};
typedef struct au_expire_after au_expire_after_t;




typedef struct au_token token_t;
struct au_qctrl {
 int aq_hiwater;


 int aq_lowater;


 int aq_bufsz;
 int aq_delay;
 int aq_minfree;
};
typedef struct au_qctrl au_qctrl_t;




struct audit_stat {
 unsigned int as_version;
 unsigned int as_numevent;
 int as_generated;
 int as_nonattrib;
 int as_kernel;
 int as_audit;
 int as_auditctl;
 int as_enqueue;
 int as_written;
 int as_wblocked;
 int as_rblocked;
 int as_dropped;
 int as_totalsize;
 unsigned int as_memused;
};
typedef struct audit_stat au_stat_t;




struct audit_fstat {
 u_int64_t af_filesz;
 u_int64_t af_currsz;
};
typedef struct audit_fstat au_fstat_t;




struct au_evclass_map {
 au_event_t ec_number;
 au_class_t ec_class;
};
typedef struct au_evclass_map au_evclass_map_t;





int audit(const void *, int);
int auditon(int, void *, int);
int auditctl(const char *);
int getauid(au_id_t *);
int setauid(const au_id_t *);
int getaudit_addr(struct auditinfo_addr *, int);
int setaudit_addr(const struct auditinfo_addr *, int);
int getaudit(struct auditinfo *)
__attribute__((availability(ios,introduced=2.0,deprecated=6.0)));

int setaudit(const struct auditinfo *)
__attribute__((availability(ios,introduced=2.0,deprecated=6.0)));
mach_port_name_t audit_session_self(void);
au_asid_t audit_session_join(mach_port_name_t port);
int audit_session_port(au_asid_t asid, mach_port_name_t *portname);




}
// @class NSMutableDictionary;
#ifndef _REWRITER_typedef_NSMutableDictionary
#define _REWRITER_typedef_NSMutableDictionary
typedef struct objc_object NSMutableDictionary;
typedef struct {} _objc_exc_NSMutableDictionary;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

#ifndef _REWRITER_typedef_NSOperationQueue
#define _REWRITER_typedef_NSOperationQueue
typedef struct objc_object NSOperationQueue;
typedef struct {} _objc_exc_NSOperationQueue;
#endif

#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif

#ifndef _REWRITER_typedef_NSLock
#define _REWRITER_typedef_NSLock
typedef struct objc_object NSLock;
typedef struct {} _objc_exc_NSLock;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

// @class NSXPCConnection;
#ifndef _REWRITER_typedef_NSXPCConnection
#define _REWRITER_typedef_NSXPCConnection
typedef struct objc_object NSXPCConnection;
typedef struct {} _objc_exc_NSXPCConnection;
#endif

#ifndef _REWRITER_typedef_NSXPCListener
#define _REWRITER_typedef_NSXPCListener
typedef struct objc_object NSXPCListener;
typedef struct {} _objc_exc_NSXPCListener;
#endif

#ifndef _REWRITER_typedef_NSXPCInterface
#define _REWRITER_typedef_NSXPCInterface
typedef struct objc_object NSXPCInterface;
typedef struct {} _objc_exc_NSXPCInterface;
#endif

#ifndef _REWRITER_typedef_NSXPCListenerEndpoint
#define _REWRITER_typedef_NSXPCListenerEndpoint
typedef struct objc_object NSXPCListenerEndpoint;
typedef struct {} _objc_exc_NSXPCListenerEndpoint;
#endif

// @protocol NSXPCListenerDelegate;

#pragma clang assume_nonnull begin


// @protocol NSXPCProxyCreating


// - (id)remoteObjectProxy;


// - (id)remoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler;

/* @optional */


// - (id)synchronousRemoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */





typedef NSUInteger NSXPCConnectionOptions; enum {

    NSXPCConnectionPrivileged = (1 << 12UL)
} __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSXPCConnection
#define _REWRITER_typedef_NSXPCConnection
typedef struct objc_object NSXPCConnection;
typedef struct {} _objc_exc_NSXPCConnection;
#endif

struct NSXPCConnection_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	void *_xconnection;
	id _repliesExpected;
	dispatch_queue_t _userQueue;
	uint32_t _state;
	uint32_t _state2;
	void (*_interruptionHandler)();
	void (*_invalidationHandler)();
	id _exportInfo;
	id _repliesRequested;
	id _importInfo;
	id _otherInfo;
	id _reserved1;
	NSXPCInterface *_remoteObjectInterface;
	NSString *_serviceName;
	NSXPCListenerEndpoint *_endpoint;
	id _eCache;
	id _dCache;
};



// - (instancetype)initWithServiceName:(NSString *)serviceName __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));
// @property (nullable, readonly, copy) NSString *serviceName;


// - (instancetype)initWithMachServiceName:(NSString *)name options:(NSXPCConnectionOptions)options __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));


// - (instancetype)initWithListenerEndpoint:(NSXPCListenerEndpoint *)endpoint;
// @property (readonly, retain) NSXPCListenerEndpoint *endpoint;


// @property (nullable, retain) NSXPCInterface *exportedInterface;


// @property (nullable, retain) id exportedObject;


// @property (nullable, retain) NSXPCInterface *remoteObjectInterface;


// @property (readonly, retain) id remoteObjectProxy;

// - (id)remoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler;


// - (id)synchronousRemoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// @property (nullable, copy) void (^interruptionHandler)(void);




// @property (nullable, copy) void (^invalidationHandler)(void);


// - (void)resume;


// - (void)suspend;


// - (void)invalidate;


// @property (readonly) au_asid_t auditSessionIdentifier;
// @property (readonly) pid_t processIdentifier;
// @property (readonly) uid_t effectiveUserIdentifier;
// @property (readonly) gid_t effectiveGroupIdentifier;


// + (nullable NSXPCConnection *)currentConnection __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// - (void)scheduleSendBarrierBlock:(void (^)(void))block __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0)));

/* @end */




__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSXPCListener
#define _REWRITER_typedef_NSXPCListener
typedef struct objc_object NSXPCListener;
typedef struct {} _objc_exc_NSXPCListener;
#endif

struct NSXPCListener_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	void *_xconnection;
	dispatch_queue_t _userQueue;
	void *reserved0;
	id _delegate;
	NSString *_serviceName;
	uint64_t _state;
	id _reserved1;
	id _reserved2;
};



// + (NSXPCListener *)serviceListener;


// + (NSXPCListener *)anonymousListener;


// - (instancetype)initWithMachServiceName:(NSString *)name __attribute__((objc_designated_initializer)) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));


// @property (nullable, weak) id <NSXPCListenerDelegate> delegate;


// @property (readonly, retain) NSXPCListenerEndpoint *endpoint;


// - (void)resume;


// - (void)suspend;


// - (void)invalidate;

/* @end */


// @protocol NSXPCListenerDelegate <NSObject>
/* @optional */

// - (BOOL)listener:(NSXPCListener *)listener shouldAcceptNewConnection:(NSXPCConnection *)newConnection;

/* @end */





__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSXPCInterface
#define _REWRITER_typedef_NSXPCInterface
typedef struct objc_object NSXPCInterface;
typedef struct {} _objc_exc_NSXPCInterface;
#endif

struct NSXPCInterface_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	Protocol *_protocol;
	void *_reserved2;
	id _reserved1;
};



// + (NSXPCInterface *)interfaceWithProtocol:(Protocol *)protocol;


// @property (assign) Protocol *protocol;



// - (void)setClasses:(NSSet<Class> *)classes forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
// - (NSSet<Class> *)classesForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;


// - (void)setInterface:(NSXPCInterface *)ifc forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
// - (nullable NSXPCInterface *)interfaceForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;






/* @end */





__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSXPCListenerEndpoint
#define _REWRITER_typedef_NSXPCListenerEndpoint
typedef struct objc_object NSXPCListenerEndpoint;
typedef struct {} _objc_exc_NSXPCListenerEndpoint;
#endif

struct NSXPCListenerEndpoint_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	void *_internal;
};

/* @end */





__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSXPCCoder
#define _REWRITER_typedef_NSXPCCoder
typedef struct objc_object NSXPCCoder;
typedef struct {} _objc_exc_NSXPCCoder;
#endif

struct NSXPCCoder_IMPL {
	struct NSCoder_IMPL NSCoder_IVARS;
	id _userInfo;
	id _reserved1;
};

// @property (nullable, retain) id <NSObject> userInfo;


// @property (nullable, readonly, strong) NSXPCConnection *connection __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0)));

/* @end */

#pragma clang assume_nonnull end


enum {

    NSFileNoSuchFileError = 4,
    NSFileLockingError = 255,
    NSFileReadUnknownError = 256,
    NSFileReadNoPermissionError = 257,
    NSFileReadInvalidFileNameError = 258,
    NSFileReadCorruptFileError = 259,
    NSFileReadNoSuchFileError = 260,
    NSFileReadInapplicableStringEncodingError = 261,
    NSFileReadUnsupportedSchemeError = 262,
    NSFileReadTooLargeError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 263,
    NSFileReadUnknownStringEncodingError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 264,
    NSFileWriteUnknownError = 512,
    NSFileWriteNoPermissionError = 513,
    NSFileWriteInvalidFileNameError = 514,
    NSFileWriteFileExistsError __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 516,
    NSFileWriteInapplicableStringEncodingError = 517,
    NSFileWriteUnsupportedSchemeError = 518,
    NSFileWriteOutOfSpaceError = 640,
    NSFileWriteVolumeReadOnlyError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 642,


    NSFileManagerUnmountUnknownError __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 768,
    NSFileManagerUnmountBusyError __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 769,


    NSKeyValueValidationError = 1024,
    NSFormattingError = 2048,
    NSUserCancelledError = 3072,
    NSFeatureUnsupportedError __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3328,


    NSExecutableNotLoadableError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3584,
    NSExecutableArchitectureMismatchError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3585,
    NSExecutableRuntimeMismatchError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3586,
    NSExecutableLoadError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3587,
    NSExecutableLinkError __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3588,


    NSFileErrorMinimum = 0,
    NSFileErrorMaximum = 1023,

    NSValidationErrorMinimum = 1024,
    NSValidationErrorMaximum = 2047,

    NSExecutableErrorMinimum __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3584,
    NSExecutableErrorMaximum __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=2.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3839,

    NSFormattingErrorMinimum = 2048,
    NSFormattingErrorMaximum = 2559,

    NSPropertyListReadCorruptError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3840,
    NSPropertyListReadUnknownVersionError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3841,
    NSPropertyListReadStreamError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3842,
    NSPropertyListWriteStreamError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3851,
    NSPropertyListWriteInvalidError __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3852,

    NSPropertyListErrorMinimum __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 3840,
    NSPropertyListErrorMaximum __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4095,

    NSXPCConnectionInterrupted __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4097,
    NSXPCConnectionInvalid __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4099,
    NSXPCConnectionReplyInvalid __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4101,

    NSXPCConnectionErrorMinimum __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4096,
    NSXPCConnectionErrorMaximum __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4224,

    NSUbiquitousFileUnavailableError __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4353,
    NSUbiquitousFileNotUploadedDueToQuotaError __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4354,
    NSUbiquitousFileUbiquityServerNotAvailable __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4355,

    NSUbiquitousFileErrorMinimum __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4352,
    NSUbiquitousFileErrorMaximum __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4607,

    NSUserActivityHandoffFailedError __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4608,
    NSUserActivityConnectionUnavailableError __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4609,
    NSUserActivityRemoteApplicationTimedOutError __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4610,
    NSUserActivityHandoffUserInfoTooLargeError __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4611,

    NSUserActivityErrorMinimum __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4608,
    NSUserActivityErrorMaximum __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4863,

    NSCoderReadCorruptError __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4864,
    NSCoderValueNotFoundError __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4865,
    NSCoderInvalidValueError __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0))) = 4866,
    NSCoderErrorMinimum __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4864,
    NSCoderErrorMaximum __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4991,

    NSBundleErrorMinimum __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 4992,
    NSBundleErrorMaximum __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 5119,

    NSBundleOnDemandResourceOutOfSpaceError __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable))) = 4992,
    NSBundleOnDemandResourceExceededMaximumSizeError __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable))) = 4993,
    NSBundleOnDemandResourceInvalidTagError __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable))) = 4994,

    NSCloudSharingNetworkFailureError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5120,
    NSCloudSharingQuotaExceededError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5121,
    NSCloudSharingTooManyParticipantsError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5122,
    NSCloudSharingConflictError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5123,
    NSCloudSharingNoPermissionError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5124,
    NSCloudSharingOtherError __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5375,

    NSCloudSharingErrorMinimum __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5120,
    NSCloudSharingErrorMaximum __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable))) = 5375,

    NSCompressionFailedError __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0))) = 5376,
    NSDecompressionFailedError __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0))) = 5377,

    NSCompressionErrorMinimum __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0))) = 5376,
    NSCompressionErrorMaximum __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0))) __attribute__((availability(tvos,introduced=13.0))) = 5503,

};











#pragma clang assume_nonnull begin

typedef NSUInteger NSByteCountFormatterUnits; enum {

    NSByteCountFormatterUseDefault = 0,

    NSByteCountFormatterUseBytes = 1UL << 0,
    NSByteCountFormatterUseKB = 1UL << 1,
    NSByteCountFormatterUseMB = 1UL << 2,
    NSByteCountFormatterUseGB = 1UL << 3,
    NSByteCountFormatterUseTB = 1UL << 4,
    NSByteCountFormatterUsePB = 1UL << 5,
    NSByteCountFormatterUseEB = 1UL << 6,
    NSByteCountFormatterUseZB = 1UL << 7,
    NSByteCountFormatterUseYBOrHigher = 0x0FFUL << 8,

    NSByteCountFormatterUseAll = 0x0FFFFUL
};

typedef NSInteger NSByteCountFormatterCountStyle; enum {

    NSByteCountFormatterCountStyleFile = 0,

    NSByteCountFormatterCountStyleMemory = 1,

    NSByteCountFormatterCountStyleDecimal = 2,
    NSByteCountFormatterCountStyleBinary = 3
};


__attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSByteCountFormatter
#define _REWRITER_typedef_NSByteCountFormatter
typedef struct objc_object NSByteCountFormatter;
typedef struct {} _objc_exc_NSByteCountFormatter;
#endif

struct NSByteCountFormatter_IMPL {
	struct NSFormatter_IMPL NSFormatter_IVARS;
	unsigned int _allowedUnits;
	char _countStyle;
	BOOL _allowsNonnumericFormatting;
	BOOL _includesUnit;
	BOOL _includesCount;
	BOOL _includesActualByteCount;
	BOOL _adaptive;
	BOOL _zeroPadsFractionDigits;
	int _formattingContext;
	int _reserved[5];
};




// + (NSString *)stringFromByteCount:(long long)byteCount countStyle:(NSByteCountFormatterCountStyle)countStyle;



// - (NSString *)stringFromByteCount:(long long)byteCount;





// + (NSString *)stringFromMeasurement:(NSMeasurement<NSUnitInformationStorage *> *)measurement countStyle:(NSByteCountFormatterCountStyle)countStyle __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));






// - (NSString *)stringFromMeasurement:(NSMeasurement<NSUnitInformationStorage *> *)measurement __attribute__((availability(macos,introduced=10.15))) __attribute__((availability(ios,introduced=13.0))) __attribute__((availability(tvos,introduced=13.0))) __attribute__((availability(watchos,introduced=6.0)));






// - (nullable NSString *)stringForObjectValue:(nullable id)obj;



// @property NSByteCountFormatterUnits allowedUnits;



// @property NSByteCountFormatterCountStyle countStyle;



// @property BOOL allowsNonnumericFormatting;



// @property BOOL includesUnit;
// @property BOOL includesCount;



// @property BOOL includesActualByteCount;



// @property (getter=isAdaptive) BOOL adaptive;



// @property BOOL zeroPadsFractionDigits;



// @property NSFormattingContext formattingContext __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end






// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @protocol NSCacheDelegate;

#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSCache
#define _REWRITER_typedef_NSCache
typedef struct objc_object NSCache;
typedef struct {} _objc_exc_NSCache;
#endif

struct NSCache_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _delegate;
	void *_private[5];
	void *_reserved;
};


// @property (copy) NSString *name;

// @property (nullable, assign) id<NSCacheDelegate> delegate;

// - (nullable ObjectType)objectForKey:(KeyType)key;
// - (void)setObject:(ObjectType)obj forKey:(KeyType)key;
// - (void)setObject:(ObjectType)obj forKey:(KeyType)key cost:(NSUInteger)g;
// - (void)removeObjectForKey:(KeyType)key;

// - (void)removeAllObjects;

// @property NSUInteger totalCostLimit;
// @property NSUInteger countLimit;
// @property BOOL evictsObjectsWithDiscardedContent;

/* @end */


// @protocol NSCacheDelegate <NSObject>
/* @optional */
// - (void)cache:(NSCache *)cache willEvictObject:(id)obj;
/* @end */

#pragma clang assume_nonnull end




// @class NSDictionary;
#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin



__attribute__((availability(macos,introduced=10.4))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSPredicate
#define _REWRITER_typedef_NSPredicate
typedef struct objc_object NSPredicate;
typedef struct {} _objc_exc_NSPredicate;
#endif

	struct _predicateFlags {
	unsigned int _evaluationBlocked : 1;
	unsigned int _reservedPredicateFlags : 31;
	} ;
struct NSPredicate_IMPL {
	struct NSObject_IMPL NSObject_IVARS;

	struct _predicateFlags _predicateFlags;
	uint32_t reserved;
};



// + (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat argumentArray:(nullable NSArray *)arguments;
// + (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat, ...;
// + (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat arguments:(va_list)argList;

// + (nullable NSPredicate *)predicateFromMetadataQueryString:(NSString *)queryString __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));

// + (NSPredicate *)predicateWithValue:(BOOL)value;

// + (NSPredicate*)predicateWithBlock:(BOOL (^)(id _Nullable evaluatedObject, NSDictionary<NSString *, id> * _Nullable bindings))block __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) NSString *predicateFormat;

// - (instancetype)predicateWithSubstitutionVariables:(NSDictionary<NSString *, id> *)variables;

// - (BOOL)evaluateWithObject:(nullable id)object;

// - (BOOL)evaluateWithObject:(nullable id)object substitutionVariables:(nullable NSDictionary<NSString *, id> *)bindings __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (void)allowEvaluation __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSArray<ObjectType> (NSPredicateSupport)
// - (NSArray<ObjectType> *)filteredArrayUsingPredicate:(NSPredicate *)predicate;
/* @end */


// @interface NSMutableArray<ObjectType> (NSPredicateSupport)
// - (void)filterUsingPredicate:(NSPredicate *)predicate;
/* @end */



// @interface NSSet<ObjectType> (NSPredicateSupport)
// - (NSSet<ObjectType> *)filteredSetUsingPredicate:(NSPredicate *)predicate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */


// @interface NSMutableSet<ObjectType> (NSPredicateSupport)
// - (void)filterUsingPredicate:(NSPredicate *)predicate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
/* @end */


// @interface NSOrderedSet<ObjectType> (NSPredicateSupport)

// - (NSOrderedSet<ObjectType> *)filteredOrderedSetUsingPredicate:(NSPredicate *)p __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSMutableOrderedSet<ObjectType> (NSPredicateSupport)

// - (void)filterUsingPredicate:(NSPredicate *)p __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end

#pragma clang assume_nonnull begin


typedef NSUInteger NSComparisonPredicateOptions; enum {
    NSCaseInsensitivePredicateOption = 0x01,
    NSDiacriticInsensitivePredicateOption = 0x02,
    NSNormalizedPredicateOption __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 0x04,
};


typedef NSUInteger NSComparisonPredicateModifier; enum {
    NSDirectPredicateModifier = 0,
    NSAllPredicateModifier,
    NSAnyPredicateModifier
};



typedef NSUInteger NSPredicateOperatorType; enum {
    NSLessThanPredicateOperatorType = 0,
    NSLessThanOrEqualToPredicateOperatorType,
    NSGreaterThanPredicateOperatorType,
    NSGreaterThanOrEqualToPredicateOperatorType,
    NSEqualToPredicateOperatorType,
    NSNotEqualToPredicateOperatorType,
    NSMatchesPredicateOperatorType,
    NSLikePredicateOperatorType,
    NSBeginsWithPredicateOperatorType,
    NSEndsWithPredicateOperatorType,
    NSInPredicateOperatorType,
    NSCustomSelectorPredicateOperatorType,
    NSContainsPredicateOperatorType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 99,
    NSBetweenPredicateOperatorType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
};

// @class NSPredicateOperator;
#ifndef _REWRITER_typedef_NSPredicateOperator
#define _REWRITER_typedef_NSPredicateOperator
typedef struct objc_object NSPredicateOperator;
typedef struct {} _objc_exc_NSPredicateOperator;
#endif

// @class NSExpression;
#ifndef _REWRITER_typedef_NSExpression
#define _REWRITER_typedef_NSExpression
typedef struct objc_object NSExpression;
typedef struct {} _objc_exc_NSExpression;
#endif




__attribute__((availability(macos,introduced=10.4))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSComparisonPredicate
#define _REWRITER_typedef_NSComparisonPredicate
typedef struct objc_object NSComparisonPredicate;
typedef struct {} _objc_exc_NSComparisonPredicate;
#endif

struct NSComparisonPredicate_IMPL {
	struct NSPredicate_IMPL NSPredicate_IVARS;
	void *_reserved2;
	NSPredicateOperator *_predicateOperator;
	NSExpression *_lhs;
	NSExpression *_rhs;
};


// + (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options;
// + (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector;

// - (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options __attribute__((objc_designated_initializer));
// - (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

// @property (readonly) NSPredicateOperatorType predicateOperatorType;
// @property (readonly) NSComparisonPredicateModifier comparisonPredicateModifier;
// @property (readonly, retain) NSExpression *leftExpression;
// @property (readonly, retain) NSExpression *rightExpression;
// @property (nullable, readonly) SEL customSelector;
// @property (readonly) NSComparisonPredicateOptions options;

/* @end */

#pragma clang assume_nonnull end






// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif


#pragma clang assume_nonnull begin



typedef NSUInteger NSCompoundPredicateType; enum {
    NSNotPredicateType = 0,
    NSAndPredicateType,
    NSOrPredicateType,
};

__attribute__((availability(macos,introduced=10.4))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSCompoundPredicate
#define _REWRITER_typedef_NSCompoundPredicate
typedef struct objc_object NSCompoundPredicate;
typedef struct {} _objc_exc_NSCompoundPredicate;
#endif

struct NSCompoundPredicate_IMPL {
	struct NSPredicate_IMPL NSPredicate_IVARS;
	void *_reserved2;
	NSUInteger _type;
	NSArray *_subpredicates;
};


// - (instancetype)initWithType:(NSCompoundPredicateType)type subpredicates:(NSArray<NSPredicate *> *)subpredicates __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));

// @property (readonly) NSCompoundPredicateType compoundPredicateType;
// @property (readonly, copy) NSArray *subpredicates;


// + (NSCompoundPredicate *)andPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates __attribute__((swift_name("init(andPredicateWithSubpredicates:)")));
// + (NSCompoundPredicate *)orPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates __attribute__((swift_name("init(orPredicateWithSubpredicates:)")));
// + (NSCompoundPredicate *)notPredicateWithSubpredicate:(NSPredicate *)predicate __attribute__((swift_name("init(notPredicateWithSubpredicate:)")));

/* @end */

#pragma clang assume_nonnull end








#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
typedef NSInteger NSDateComponentsFormatterUnitsStyle; enum {
    NSDateComponentsFormatterUnitsStylePositional = 0,
    NSDateComponentsFormatterUnitsStyleAbbreviated,
    NSDateComponentsFormatterUnitsStyleShort,
    NSDateComponentsFormatterUnitsStyleFull,
    NSDateComponentsFormatterUnitsStyleSpellOut,
    NSDateComponentsFormatterUnitsStyleBrief __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,introduced=3.0))) __attribute__((availability(tvos,introduced=10.0)))
};

__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
typedef NSUInteger NSDateComponentsFormatterZeroFormattingBehavior; enum {
    NSDateComponentsFormatterZeroFormattingBehaviorNone = (0),
    NSDateComponentsFormatterZeroFormattingBehaviorDefault = (1 << 0),

    NSDateComponentsFormatterZeroFormattingBehaviorDropLeading = (1 << 1),
    NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle = (1 << 2),
    NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing = (1 << 3),
    NSDateComponentsFormatterZeroFormattingBehaviorDropAll = (NSDateComponentsFormatterZeroFormattingBehaviorDropLeading | NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle | NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing),

    NSDateComponentsFormatterZeroFormattingBehaviorPad = (1 << 16),
};



__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSDateComponentsFormatter
#define _REWRITER_typedef_NSDateComponentsFormatter
typedef struct objc_object NSDateComponentsFormatter;
typedef struct {} _objc_exc_NSDateComponentsFormatter;
#endif

struct NSDateComponentsFormatter_IMPL {
	struct NSFormatter_IMPL NSFormatter_IVARS;
	pthread_mutex_t _lock;
	void *_fmt;
	void *_unused;
	NSString *_fmtLocaleIdent;
	NSCalendar *_calendar;
	NSDate *_referenceDate;
	NSNumberFormatter *_unitFormatter;
	NSCalendarUnit _allowedUnits;
	NSFormattingContext _formattingContext;
	NSDateComponentsFormatterUnitsStyle _unitsStyle;
	NSDateComponentsFormatterZeroFormattingBehavior _zeroFormattingBehavior;
	NSInteger _maximumUnitCount;
	BOOL _allowsFractionalUnits;
	BOOL _collapsesLargestUnit;
	BOOL _includesApproximationPhrase;
	BOOL _includesTimeRemainingPhrase;
	void *_reserved;
};




// - (nullable NSString *)stringForObjectValue:(nullable id)obj;



// - (nullable NSString *)stringFromDateComponents:(NSDateComponents *)components;







// - (nullable NSString *)stringFromDate:(NSDate *)startDate toDate:(NSDate *)endDate;



// - (nullable NSString *)stringFromTimeInterval:(NSTimeInterval)ti;


// + (nullable NSString *)localizedStringFromDateComponents:(NSDateComponents *)components unitsStyle:(NSDateComponentsFormatterUnitsStyle) unitsStyle;



// @property NSDateComponentsFormatterUnitsStyle unitsStyle;
// @property NSCalendarUnit allowedUnits;





// @property NSDateComponentsFormatterZeroFormattingBehavior zeroFormattingBehavior;



// @property (nullable, copy) NSCalendar *calendar;



// @property (nullable, copy) NSDate *referenceDate __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// @property BOOL allowsFractionalUnits;
// @property NSInteger maximumUnitCount;



// @property BOOL collapsesLargestUnit;



// @property BOOL includesApproximationPhrase;



// @property BOOL includesTimeRemainingPhrase;




// @property NSFormattingContext formattingContext;



// - (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;

/* @end */

#pragma clang assume_nonnull end






// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif

// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

// @class NSMutableDictionary;
#ifndef _REWRITER_typedef_NSMutableDictionary
#define _REWRITER_typedef_NSMutableDictionary
typedef struct objc_object NSMutableDictionary;
typedef struct {} _objc_exc_NSMutableDictionary;
#endif

// @class NSPredicate;
#ifndef _REWRITER_typedef_NSPredicate
#define _REWRITER_typedef_NSPredicate
typedef struct objc_object NSPredicate;
typedef struct {} _objc_exc_NSPredicate;
#endif


#pragma clang assume_nonnull begin



typedef NSUInteger NSExpressionType; enum {
    NSConstantValueExpressionType = 0,
    NSEvaluatedObjectExpressionType,
    NSVariableExpressionType,
    NSKeyPathExpressionType,
    NSFunctionExpressionType,
    NSUnionSetExpressionType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSIntersectSetExpressionType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSMinusSetExpressionType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSSubqueryExpressionType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 13,
    NSAggregateExpressionType __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 14,
    NSAnyKeyExpressionType __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 15,
    NSBlockExpressionType = 19,
    NSConditionalExpressionType __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 20

};

__attribute__((availability(macos,introduced=10.4))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSExpression
#define _REWRITER_typedef_NSExpression
typedef struct objc_object NSExpression;
typedef struct {} _objc_exc_NSExpression;
#endif

	struct _expressionFlags {
	unsigned int _evaluationBlocked : 1;
	unsigned int _reservedExpressionFlags : 31;
	} ;
struct NSExpression_IMPL {
	struct NSObject_IMPL NSObject_IVARS;

	struct _expressionFlags _expressionFlags;
	uint32_t reserved;
	NSExpressionType _expressionType;
};


// + (NSExpression *)expressionWithFormat:(NSString *)expressionFormat argumentArray:(NSArray *)arguments __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionWithFormat:(NSString *)expressionFormat, ... __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionWithFormat:(NSString *)expressionFormat arguments:(va_list)argList __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// + (NSExpression *)expressionForConstantValue:(nullable id)obj;
// + (NSExpression *)expressionForEvaluatedObject;
// + (NSExpression *)expressionForVariable:(NSString *)string;
// + (NSExpression *)expressionForKeyPath:(NSString *)keyPath;
// + (NSExpression *)expressionForFunction:(NSString *)name arguments:(NSArray *)parameters;
// + (NSExpression *)expressionForAggregate:(NSArray<NSExpression *> *)subexpressions __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForUnionSet:(NSExpression *)left with:(NSExpression *)right __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForIntersectSet:(NSExpression *)left with:(NSExpression *)right __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForMinusSet:(NSExpression *)left with:(NSExpression *)right __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForSubquery:(NSExpression *)expression usingIteratorVariable:(NSString *)variable predicate:(NSPredicate *)predicate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForFunction:(NSExpression *)target selectorName:(NSString *)name arguments:(nullable NSArray *)parameters __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForAnyKey __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForBlock:(id (^)(id _Nullable evaluatedObject, NSArray<NSExpression *> *expressions, NSMutableDictionary * _Nullable context))block arguments:(nullable NSArray<NSExpression *> *)arguments __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// + (NSExpression *)expressionForConditional:(NSPredicate *)predicate trueExpression:(NSExpression *)trueExpression falseExpression:(NSExpression *)falseExpression __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// - (instancetype)initWithExpressionType:(NSExpressionType)type __attribute__((objc_designated_initializer));
// - (nullable instancetype)initWithCoder:(NSCoder *)coder __attribute__((objc_designated_initializer));


// @property (readonly) NSExpressionType expressionType;
// @property (nullable, readonly, retain) id constantValue;
// @property (readonly, copy) NSString *keyPath;
// @property (readonly, copy) NSString *function;
// @property (readonly, copy) NSString *variable;
// @property (readonly, copy) NSExpression *operand;
// @property (nullable, readonly, copy) NSArray<NSExpression *> *arguments;

// @property (readonly, retain) id collection __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSPredicate *predicate __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSExpression *leftExpression __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSExpression *rightExpression __attribute__((availability(macos,introduced=10.5))) __attribute__((availability(ios,introduced=3.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// @property (readonly, copy) NSExpression *trueExpression __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (readonly, copy) NSExpression *falseExpression __attribute__((availability(macos,introduced=10.11))) __attribute__((availability(ios,introduced=9.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) id (^expressionBlock)(id _Nullable, NSArray<NSExpression *> *, NSMutableDictionary * _Nullable) __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


// - (nullable id)expressionValueWithObject:(nullable id)object context:(nullable NSMutableDictionary *)context;

// - (void)allowEvaluation __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end
#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSExtensionContext
#define _REWRITER_typedef_NSExtensionContext
typedef struct objc_object NSExtensionContext;
typedef struct {} _objc_exc_NSExtensionContext;
#endif

struct NSExtensionContext_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};



// @property(readonly, copy, nonatomic) NSArray *inputItems;


// - (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler;


// - (void)cancelRequestWithError:(NSError *)error;


// - (void)openURL:(NSURL *)URL completionHandler:(void (^ _Nullable)(BOOL success))completionHandler;

/* @end */



extern "C" NSString * _Null_unspecified const NSExtensionItemsAndErrorsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSString * _Null_unspecified const NSExtensionHostWillEnterForegroundNotification __attribute__((availability(ios,introduced=8.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));


extern "C" NSString * _Null_unspecified const NSExtensionHostDidEnterBackgroundNotification __attribute__((availability(ios,introduced=8.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));


extern "C" NSString * _Null_unspecified const NSExtensionHostWillResignActiveNotification __attribute__((availability(ios,introduced=8.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));


extern "C" NSString * _Null_unspecified const NSExtensionHostDidBecomeActiveNotification __attribute__((availability(ios,introduced=8.2))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(macos,unavailable)));
#pragma clang assume_nonnull end
#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSExtensionItem
#define _REWRITER_typedef_NSExtensionItem
typedef struct objc_object NSExtensionItem;
typedef struct {} _objc_exc_NSExtensionItem;
#endif

struct NSExtensionItem_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};



// @property(nullable, copy, nonatomic) NSAttributedString *attributedTitle;


// @property(nullable, copy, nonatomic) NSAttributedString *attributedContentText;


// @property(nullable, copy, nonatomic) NSArray<NSItemProvider *> *attachments;


// @property(nullable, copy, nonatomic) NSDictionary *userInfo;

/* @end */



extern "C" NSString * _Null_unspecified const NSExtensionItemAttributedTitleKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSString * _Null_unspecified const NSExtensionItemAttributedContentTextKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSString * _Null_unspecified const NSExtensionItemAttachmentsKey __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
#pragma clang assume_nonnull end







#pragma clang assume_nonnull begin

// @class NSExtensionContext;
#ifndef _REWRITER_typedef_NSExtensionContext
#define _REWRITER_typedef_NSExtensionContext
typedef struct objc_object NSExtensionContext;
typedef struct {} _objc_exc_NSExtensionContext;
#endif



// @protocol NSExtensionRequestHandling <NSObject>

/* @required */


// - (void)beginRequestWithExtensionContext:(NSExtensionContext *)context;

/* @end */

#pragma clang assume_nonnull end
// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

#ifndef _REWRITER_typedef_NSMutableDictionary
#define _REWRITER_typedef_NSMutableDictionary
typedef struct objc_object NSMutableDictionary;
typedef struct {} _objc_exc_NSMutableDictionary;
#endif

#ifndef _REWRITER_typedef_NSOperationQueue
#define _REWRITER_typedef_NSOperationQueue
typedef struct objc_object NSOperationQueue;
typedef struct {} _objc_exc_NSOperationQueue;
#endif

#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif


// @protocol NSFilePresenter;

#pragma clang assume_nonnull begin

typedef NSUInteger NSFileCoordinatorReadingOptions; enum {



    NSFileCoordinatorReadingWithoutChanges = 1 << 0,



    NSFileCoordinatorReadingResolvesSymbolicLink = 1 << 1,



    NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1 << 2,





    NSFileCoordinatorReadingForUploading __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1 << 3,

};

typedef NSUInteger NSFileCoordinatorWritingOptions; enum {
    NSFileCoordinatorWritingForDeleting = 1 << 0,





    NSFileCoordinatorWritingForMoving = 1 << 1,



    NSFileCoordinatorWritingForMerging = 1 << 2,







    NSFileCoordinatorWritingForReplacing = 1 << 3,



    NSFileCoordinatorWritingContentIndependentMetadataOnly __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))) = 1 << 4

};


__attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSFileAccessIntent
#define _REWRITER_typedef_NSFileAccessIntent
typedef struct objc_object NSFileAccessIntent;
typedef struct {} _objc_exc_NSFileAccessIntent;
#endif

struct NSFileAccessIntent_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURL *_url;
	BOOL _isRead;
	NSInteger _options;
};

// + (instancetype)readingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options;
// + (instancetype)writingIntentWithURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options;
// @property (readonly, copy) NSURL *URL;
/* @end */



__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSFileCoordinator
#define _REWRITER_typedef_NSFileCoordinator
typedef struct objc_object NSFileCoordinator;
typedef struct {} _objc_exc_NSFileCoordinator;
#endif

struct NSFileCoordinator_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _accessArbiter;
	id _fileReactor;
	id _purposeID;
	NSURL *_recentFilePresenterURL;
	id _accessClaimIDOrIDs;
	BOOL _isCancelled;
	NSMutableDictionary *_movedItems;
};








// + (void)addFilePresenter:(id<NSFilePresenter>)filePresenter;
// + (void)removeFilePresenter:(id<NSFilePresenter>)filePresenter;
@property (class, readonly, copy) NSArray<id<NSFilePresenter>> *filePresenters;
// - (instancetype)initWithFilePresenter:(nullable id<NSFilePresenter>)filePresenterOrNil __attribute__((objc_designated_initializer));
// @property (copy) NSString *purposeIdentifier __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)coordinateAccessWithIntents:(NSArray<NSFileAccessIntent *> *)intents queue:(NSOperationQueue *)queue byAccessor:(void (^)(NSError * _Nullable error))accessor __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)coordinateReadingItemAtURL:(NSURL *)url options:(NSFileCoordinatorReadingOptions)options error:(NSError **)outError byAccessor:(void (__attribute__((noescape)) ^)(NSURL *newURL))reader;
// - (void)coordinateWritingItemAtURL:(NSURL *)url options:(NSFileCoordinatorWritingOptions)options error:(NSError **)outError byAccessor:(void (__attribute__((noescape)) ^)(NSURL *newURL))writer;
// - (void)coordinateReadingItemAtURL:(NSURL *)readingURL options:(NSFileCoordinatorReadingOptions)readingOptions writingItemAtURL:(NSURL *)writingURL options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (__attribute__((noescape)) ^)(NSURL *newReadingURL, NSURL *newWritingURL))readerWriter;
// - (void)coordinateWritingItemAtURL:(NSURL *)url1 options:(NSFileCoordinatorWritingOptions)options1 writingItemAtURL:(NSURL *)url2 options:(NSFileCoordinatorWritingOptions)options2 error:(NSError **)outError byAccessor:(void (__attribute__((noescape)) ^)(NSURL *newURL1, NSURL *newURL2))writer;
// - (void)prepareForReadingItemsAtURLs:(NSArray<NSURL *> *)readingURLs options:(NSFileCoordinatorReadingOptions)readingOptions writingItemsAtURLs:(NSArray<NSURL *> *)writingURLs options:(NSFileCoordinatorWritingOptions)writingOptions error:(NSError **)outError byAccessor:(void (__attribute__((noescape)) ^)(void (^completionHandler)(void)))batchAccessor;
// - (void)itemAtURL:(NSURL *)oldURL willMoveToURL:(NSURL *)newURL __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)itemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;







// - (void)itemAtURL:(NSURL *)url didChangeUbiquityAttributes:(NSSet <NSURLResourceKey> *)attributes __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));







// - (void)cancel;

/* @end */

#pragma clang assume_nonnull end
// @class NSError;
#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
#endif

#ifndef _REWRITER_typedef_NSFileVersion
#define _REWRITER_typedef_NSFileVersion
typedef struct objc_object NSFileVersion;
typedef struct {} _objc_exc_NSFileVersion;
#endif

#ifndef _REWRITER_typedef_NSOperationQueue
#define _REWRITER_typedef_NSOperationQueue
typedef struct objc_object NSOperationQueue;
typedef struct {} _objc_exc_NSOperationQueue;
#endif

#ifndef _REWRITER_typedef_NSSet
#define _REWRITER_typedef_NSSet
typedef struct objc_object NSSet;
typedef struct {} _objc_exc_NSSet;
#endif


#pragma clang assume_nonnull begin







// @protocol NSFilePresenter<NSObject>

/* @required */





// @property (nullable, readonly, copy) NSURL *presentedItemURL;





// @property (readonly, retain) NSOperationQueue *presentedItemOperationQueue;

/* @optional */



// @property (nullable, readonly, copy) NSURL *primaryPresentedItemURL __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));





// - (void)relinquishPresentedItemToReader:(void (^)(void (^ _Nullable reacquirer)(void)))reader;





// - (void)relinquishPresentedItemToWriter:(void (^)(void (^ _Nullable reacquirer)(void)))writer;







// - (void)savePresentedItemChangesWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler;







// - (void)accommodatePresentedItemDeletionWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler;
// - (void)presentedItemDidMoveToURL:(NSURL *)newURL;
// - (void)presentedItemDidChange;





// - (void)presentedItemDidChangeUbiquityAttributes:(NSSet<NSURLResourceKey> *)attributes __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));







// @property (readonly, strong) NSSet<NSURLResourceKey> *observedPresentedItemUbiquityAttributes __attribute__((availability(macos,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));





// - (void)presentedItemDidGainVersion:(NSFileVersion *)version;
// - (void)presentedItemDidLoseVersion:(NSFileVersion *)version;
// - (void)presentedItemDidResolveConflictVersion:(NSFileVersion *)version;
// - (void)accommodatePresentedSubitemDeletionAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler;





// - (void)presentedSubitemDidAppearAtURL:(NSURL *)url;





// - (void)presentedSubitemAtURL:(NSURL *)oldURL didMoveToURL:(NSURL *)newURL;





// - (void)presentedSubitemDidChangeAtURL:(NSURL *)url;



// - (void)presentedSubitemAtURL:(NSURL *)url didGainVersion:(NSFileVersion *)version;
// - (void)presentedSubitemAtURL:(NSURL *)url didLoseVersion:(NSFileVersion *)version;
// - (void)presentedSubitemAtURL:(NSURL *)url didResolveConflictVersion:(NSFileVersion *)version;

/* @end */

#pragma clang assume_nonnull end








// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSDate
#define _REWRITER_typedef_NSDate
typedef struct objc_object NSDate;
typedef struct {} _objc_exc_NSDate;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
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

#ifndef _REWRITER_typedef_NSPersonNameComponents
#define _REWRITER_typedef_NSPersonNameComponents
typedef struct objc_object NSPersonNameComponents;
typedef struct {} _objc_exc_NSPersonNameComponents;
#endif


#pragma clang assume_nonnull begin

typedef NSUInteger NSFileVersionAddingOptions; enum {



    NSFileVersionAddingByMoving = 1 << 0

};

typedef NSUInteger NSFileVersionReplacingOptions; enum {



    NSFileVersionReplacingByMoving = 1 << 0

};



__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSFileVersion
#define _REWRITER_typedef_NSFileVersion
typedef struct objc_object NSFileVersion;
typedef struct {} _objc_exc_NSFileVersion;
#endif

struct NSFileVersion_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSURL *_fileURL;
	id _addition;
	id _deadVersionIdentifier;
	id _nonLocalVersion;
	NSURL *_contentsURL;
	BOOL _isBackup;
	NSString *_localizedName;
	NSString *_localizedComputerName;
	NSDate *_modificationDate;
	BOOL _isResolved;
	BOOL _contentsURLIsAccessed;
	id _reserved;
	NSString *_name;
};




// + (nullable NSFileVersion *)currentVersionOfItemAtURL:(NSURL *)url;



// + (nullable NSArray<NSFileVersion *> *)otherVersionsOfItemAtURL:(NSURL *)url;



// + (nullable NSArray<NSFileVersion *> *)unresolvedConflictVersionsOfItemAtURL:(NSURL *)url;







// + (void)getNonlocalVersionsOfItemAtURL:(NSURL *)url completionHandler:(void (^)(NSArray<NSFileVersion *> * _Nullable nonlocalFileVersions, NSError * _Nullable error))completionHandler __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// + (nullable NSFileVersion *)versionOfItemAtURL:(NSURL *)url forPersistentIdentifier:(id)persistentIdentifier;







// + (nullable NSFileVersion *)addVersionOfItemAtURL:(NSURL *)url withContentsOfURL:(NSURL *)contentsURL options:(NSFileVersionAddingOptions)options error:(NSError **)outError __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));



// + (NSURL *)temporaryDirectoryURLForNewVersionOfItemAtURL:(NSURL *)url __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));



// @property (readonly, copy) NSURL *URL;



// @property (nullable, readonly, copy) NSString *localizedName;



// @property (nullable, readonly, copy) NSString *localizedNameOfSavingComputer;



// @property (nullable, readonly, copy) NSPersonNameComponents *originatorNameComponents __attribute__((availability(macosx,introduced=10.12))) __attribute__((availability(ios,introduced=10.0))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));



// @property (nullable, readonly, copy) NSDate *modificationDate;



// @property (readonly, retain) id<NSCoding> persistentIdentifier;



// @property (readonly, getter=isConflict) BOOL conflict;







// @property (getter=isResolved) BOOL resolved;
// @property (getter=isDiscardable) BOOL discardable __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,unavailable))) __attribute__((availability(watchos,unavailable))) __attribute__((availability(tvos,unavailable)));



// @property (readonly) BOOL hasLocalContents __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// @property (readonly) BOOL hasThumbnail __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=8.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// - (nullable NSURL *)replaceItemAtURL:(NSURL *)url options:(NSFileVersionReplacingOptions)options error:(NSError **)error;







// - (BOOL)removeAndReturnError:(NSError **)outError;





// + (BOOL)removeOtherVersionsOfItemAtURL:(NSURL *)url error:(NSError **)outError;

/* @end */

#pragma clang assume_nonnull end







// @class NSData;
#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSDictionary
#define _REWRITER_typedef_NSDictionary
typedef struct objc_object NSDictionary;
typedef struct {} _objc_exc_NSDictionary;
#endif

#ifndef _REWRITER_typedef_NSError
#define _REWRITER_typedef_NSError
typedef struct objc_object NSError;
typedef struct {} _objc_exc_NSError;
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

typedef NSUInteger NSFileWrapperReadingOptions; enum {



    NSFileWrapperReadingImmediate = 1 << 0,



    NSFileWrapperReadingWithoutMapping = 1 << 1

} __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSUInteger NSFileWrapperWritingOptions; enum {



    NSFileWrapperWritingAtomic = 1 << 0,



    NSFileWrapperWritingWithNameUpdating = 1 << 1

} __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

__attribute__((availability(macos,introduced=10.0))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSFileWrapper
#define _REWRITER_typedef_NSFileWrapper
typedef struct objc_object NSFileWrapper;
typedef struct {} _objc_exc_NSFileWrapper;
#endif

struct NSFileWrapper_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSDictionary *_fileAttributes;
	NSString *_preferredFileName;
	NSString *_fileName;
	id _contents;
	id _icon;
	id _moreVars;
};






// - (nullable instancetype)initWithURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError __attribute__((objc_designated_initializer)) __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (instancetype)initDirectoryWithFileWrappers:(NSDictionary<NSString *, NSFileWrapper *> *)childrenByPreferredName __attribute__((objc_designated_initializer));



// - (instancetype)initRegularFileWithContents:(NSData *)contents __attribute__((objc_designated_initializer));



// - (instancetype)initSymbolicLinkWithDestinationURL:(NSURL *)url __attribute__((objc_designated_initializer)) __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (nullable instancetype)initWithSerializedRepresentation:(NSData *)serializeRepresentation __attribute__((objc_designated_initializer));

// - (nullable instancetype)initWithCoder:(NSCoder *)inCoder __attribute__((objc_designated_initializer));





// @property (readonly, getter=isDirectory) BOOL directory;
// @property (readonly, getter=isRegularFile) BOOL regularFile;
// @property (readonly, getter=isSymbolicLink) BOOL symbolicLink;





// @property (nullable, copy) NSString *preferredFilename;



// @property (nullable, copy) NSString *filename;



// @property (copy) NSDictionary<NSString *, id> *fileAttributes;
// - (BOOL)matchesContentsOfURL:(NSURL *)url __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (BOOL)readFromURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// - (BOOL)writeToURL:(NSURL *)url options:(NSFileWrapperWritingOptions)options originalContentsURL:(nullable NSURL *)originalContentsURL error:(NSError **)outError __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));





// @property (nullable, readonly, copy) NSData *serializedRepresentation;







// - (NSString *)addFileWrapper:(NSFileWrapper *)child;



// - (NSString *)addRegularFileWithContents:(NSData *)data preferredFilename:(NSString *)fileName;



// - (void)removeFileWrapper:(NSFileWrapper *)child;



// @property (nullable, readonly, copy) NSDictionary<NSString *, NSFileWrapper *> *fileWrappers;



// - (nullable NSString *)keyForFileWrapper:(NSFileWrapper *)child;







// @property (nullable, readonly, copy) NSData *regularFileContents;







// @property (nullable, readonly, copy) NSURL *symbolicLinkDestinationURL __attribute__((availability(macos,introduced=10.6))) __attribute__((availability(ios,introduced=4.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end








// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

#ifndef _REWRITER_typedef_NSOrthography
#define _REWRITER_typedef_NSOrthography
typedef struct objc_object NSOrthography;
typedef struct {} _objc_exc_NSOrthography;
#endif

#ifndef _REWRITER_typedef_NSValue
#define _REWRITER_typedef_NSValue
typedef struct objc_object NSValue;
typedef struct {} _objc_exc_NSValue;
#endif


#pragma clang assume_nonnull begin





typedef NSString *NSLinguisticTagScheme __attribute__((swift_wrapper(struct)));

extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeTokenType __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeLexicalClass __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeNameType __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeNameTypeOrLexicalClass __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeLemma __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeLanguage __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTagScheme const NSLinguisticTagSchemeScript __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

typedef NSString *NSLinguisticTag __attribute__((swift_wrapper(struct)));


extern "C" NSLinguisticTag const NSLinguisticTagWord __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagPunctuation __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagWhitespace __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOther __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSLinguisticTag const NSLinguisticTagNoun __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagVerb __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagAdjective __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagAdverb __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagPronoun __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagDeterminer __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagParticle __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagPreposition __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagNumber __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagConjunction __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagInterjection __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagClassifier __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagIdiom __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOtherWord __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagSentenceTerminator __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOpenQuote __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagCloseQuote __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOpenParenthesis __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagCloseParenthesis __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagWordJoiner __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagDash __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOtherPunctuation __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagParagraphBreak __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOtherWhitespace __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));


extern "C" NSLinguisticTag const NSLinguisticTagPersonalName __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagPlaceName __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSLinguisticTag const NSLinguisticTagOrganizationName __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));






typedef NSInteger NSLinguisticTaggerUnit; enum {
    NSLinguisticTaggerUnitWord,
    NSLinguisticTaggerUnitSentence,
    NSLinguisticTaggerUnitParagraph,
    NSLinguisticTaggerUnitDocument
};


typedef NSUInteger NSLinguisticTaggerOptions; enum {
    NSLinguisticTaggerOmitWords = 1 << 0,
    NSLinguisticTaggerOmitPunctuation = 1 << 1,
    NSLinguisticTaggerOmitWhitespace = 1 << 2,
    NSLinguisticTaggerOmitOther = 1 << 3,
    NSLinguisticTaggerJoinNames = 1 << 4
};


__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))

#ifndef _REWRITER_typedef_NSLinguisticTagger
#define _REWRITER_typedef_NSLinguisticTagger
typedef struct objc_object NSLinguisticTagger;
typedef struct {} _objc_exc_NSLinguisticTagger;
#endif

struct NSLinguisticTagger_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	NSArray *_schemes;
	NSUInteger _options;
	NSString *_string;
	id _orthographyArray;
	id _tokenArray;
	void *_reserved;
};




// - (instancetype)initWithTagSchemes:(NSArray<NSLinguisticTagScheme> *)tagSchemes options:(NSUInteger)opts __attribute__((objc_designated_initializer)) __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

// @property (readonly, copy) NSArray<NSLinguisticTagScheme> *tagSchemes __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// @property (nullable, retain) NSString *string __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// + (NSArray<NSLinguisticTagScheme> *)availableTagSchemesForUnit:(NSLinguisticTaggerUnit)unit language:(NSString *)language __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// + (NSArray<NSLinguisticTagScheme> *)availableTagSchemesForLanguage:(NSString *)language __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (void)setOrthography:(nullable NSOrthography *)orthography range:(NSRange)range __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (nullable NSOrthography *)orthographyAtIndex:(NSUInteger)charIndex effectiveRange:(nullable NSRangePointer)effectiveRange __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (void)stringEditedInRange:(NSRange)newRange changeInLength:(NSInteger)delta __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (NSRange)tokenRangeAtIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// - (NSRange)sentenceRangeForRange:(NSRange)range __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (void)enumerateTagsInRange:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options usingBlock:(void (__attribute__((noescape)) ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, BOOL *stop))block __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// - (nullable NSLinguisticTag)tagAtIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// - (NSArray<NSLinguisticTag> *)tagsInRange:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// - (void)enumerateTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)tagScheme options:(NSLinguisticTaggerOptions)opts usingBlock:(void (__attribute__((noescape)) ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (nullable NSLinguisticTag)tagAtIndex:(NSUInteger)charIndex scheme:(NSLinguisticTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (NSArray<NSString *> *)tagsInRange:(NSRange)range scheme:(NSString *)tagScheme options:(NSLinguisticTaggerOptions)opts tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// @property (nullable, readonly, copy) NSString *dominantLanguage __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// + (nullable NSString *)dominantLanguageForString:(NSString *)string __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// + (nullable NSLinguisticTag)tagForString:(NSString *)string atIndex:(NSUInteger)charIndex unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme orthography:(nullable NSOrthography *)orthography tokenRange:(nullable NSRangePointer)tokenRange __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// + (NSArray<NSLinguisticTag> *)tagsForString:(NSString *)string range:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));
// + (void)enumerateTagsForString:(NSString *)string range:(NSRange)range unit:(NSLinguisticTaggerUnit)unit scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography usingBlock:(void (__attribute__((noescape)) ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, BOOL *stop))block __attribute__((availability(macosx,introduced=10.13))) __attribute__((availability(ios,introduced=11.0))) __attribute__((availability(watchos,introduced=4.0))) __attribute__((availability(tvos,introduced=11.0)));



// - (nullable NSArray<NSString *> *)possibleTagsAtIndex:(NSUInteger)charIndex scheme:(NSString *)tagScheme tokenRange:(nullable NSRangePointer)tokenRange sentenceRange:(nullable NSRangePointer)sentenceRange scores:(NSArray<NSValue *> * _Nullable * _Nullable)scores __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */


// @interface NSString (NSLinguisticAnalysis)



// - (NSArray<NSLinguisticTag> *)linguisticTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
// - (void)enumerateLinguisticTagsInRange:(NSRange)range scheme:(NSLinguisticTagScheme)scheme options:(NSLinguisticTaggerOptions)options orthography:(nullable NSOrthography *)orthography usingBlock:(void (__attribute__((noescape)) ^)(NSLinguisticTag _Nullable tag, NSRange tokenRange, NSRange sentenceRange, BOOL *stop))block __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */

#pragma clang assume_nonnull end










// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin




// - (instancetype)init;



// @property (nullable, assign) id <NSNetServiceBrowserDelegate> delegate;



// @property BOOL includesPeerToPeer __attribute__((availability(macos,introduced=10.10))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));



// - (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;
// - (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;



// - (void)searchForBrowsableDomains;



// - (void)searchForRegistrationDomains;



// - (void)searchForServicesOfType:(NSString *)type inDomain:(NSString *)domainString;



// - (void)stop;

/* @end */




__attribute__((availability(watchos,unavailable)))
// @protocol NSNetServiceDelegate <NSObject>
/* @optional */



// - (void)netServiceWillPublish:(NSNetService *)sender;



// - (void)netServiceDidPublish:(NSNetService *)sender;



// - (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary<NSString *, NSNumber *> *)errorDict;



// - (void)netServiceWillResolve:(NSNetService *)sender;



// - (void)netServiceDidResolveAddress:(NSNetService *)sender;



// - (void)netService:(NSNetService *)sender didNotResolve:(NSDictionary<NSString *, NSNumber *> *)errorDict;



// - (void)netServiceDidStop:(NSNetService *)sender;



// - (void)netService:(NSNetService *)sender didUpdateTXTRecordData:(NSData *)data;
// - (void)netService:(NSNetService *)sender didAcceptConnectionWithInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream __attribute__((availability(macos,introduced=10.9))) __attribute__((availability(ios,introduced=7.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

/* @end */




__attribute__((availability(watchos,unavailable)))
// @protocol NSNetServiceBrowserDelegate <NSObject>
/* @optional */



// - (void)netServiceBrowserWillSearch:(NSNetServiceBrowser *)browser;



// - (void)netServiceBrowserDidStopSearch:(NSNetServiceBrowser *)browser;



// - (void)netServiceBrowser:(NSNetServiceBrowser *)browser didNotSearch:(NSDictionary<NSString *, NSNumber *> *)errorDict;



// - (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindDomain:(NSString *)domainString moreComing:(BOOL)moreComing;



// - (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing;



// - (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveDomain:(NSString *)domainString moreComing:(BOOL)moreComing;



// - (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveService:(NSNetService *)service moreComing:(BOOL)moreComing;

/* @end */

#pragma clang assume_nonnull end









// @class NSArray;
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

#ifndef _REWRITER_typedef_NSData
#define _REWRITER_typedef_NSData
typedef struct objc_object NSData;
typedef struct {} _objc_exc_NSData;
#endif

#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin

__attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(tvos,introduced=9.0))) __attribute__((availability(watchos,unavailable)))

#ifndef _REWRITER_typedef_NSUbiquitousKeyValueStore
#define _REWRITER_typedef_NSUbiquitousKeyValueStore
typedef struct objc_object NSUbiquitousKeyValueStore;
typedef struct {} _objc_exc_NSUbiquitousKeyValueStore;
#endif

struct NSUbiquitousKeyValueStore_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	id _private1;
	id _private2;
	id _private3;
	void *_private4;
	void *_reserved[3];
	int _daemonWakeToken;
};


@property (class, readonly, strong) NSUbiquitousKeyValueStore *defaultStore;

// - (nullable id)objectForKey:(NSString *)aKey;
// - (void)setObject:(nullable id)anObject forKey:(NSString *)aKey;
// - (void)removeObjectForKey:(NSString *)aKey;

// - (nullable NSString *)stringForKey:(NSString *)aKey;
// - (nullable NSArray *)arrayForKey:(NSString *)aKey;
// - (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)aKey;
// - (nullable NSData *)dataForKey:(NSString *)aKey;
// - (long long)longLongForKey:(NSString *)aKey;
// - (double)doubleForKey:(NSString *)aKey;
// - (BOOL)boolForKey:(NSString *)aKey;

// - (void)setString:(nullable NSString *)aString forKey:(NSString *)aKey;
// - (void)setData:(nullable NSData *)aData forKey:(NSString *)aKey;
// - (void)setArray:(nullable NSArray *)anArray forKey:(NSString *)aKey;
// - (void)setDictionary:(nullable NSDictionary<NSString *, id> *)aDictionary forKey:(NSString *)aKey;
// - (void)setLongLong:(long long)value forKey:(NSString *)aKey;
// - (void)setDouble:(double)value forKey:(NSString *)aKey;
// - (void)setBool:(BOOL)value forKey:(NSString *)aKey;

// @property (readonly, copy) NSDictionary<NSString *, id> *dictionaryRepresentation;

// - (BOOL)synchronize;

/* @end */


extern "C" NSNotificationName const NSUbiquitousKeyValueStoreDidChangeExternallyNotification __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSString * const NSUbiquitousKeyValueStoreChangeReasonKey __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));
extern "C" NSString * const NSUbiquitousKeyValueStoreChangedKeysKey __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)));

enum {
    NSUbiquitousKeyValueStoreServerChange __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSUbiquitousKeyValueStoreInitialSyncChange __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSUbiquitousKeyValueStoreQuotaViolationChange __attribute__((availability(macos,introduced=10.7))) __attribute__((availability(ios,introduced=5.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0))),
    NSUbiquitousKeyValueStoreAccountChange __attribute__((availability(macos,introduced=10.8))) __attribute__((availability(ios,introduced=6.0))) __attribute__((availability(watchos,introduced=2.0))) __attribute__((availability(tvos,introduced=9.0)))
};
#pragma clang assume_nonnull end
// @class NSArray;
#ifndef _REWRITER_typedef_NSArray
#define _REWRITER_typedef_NSArray
typedef struct objc_object NSArray;
typedef struct {} _objc_exc_NSArray;
#endif

// @class NSString;
#ifndef _REWRITER_typedef_NSString
#define _REWRITER_typedef_NSString
typedef struct objc_object NSString;
typedef struct {} _objc_exc_NSString;
#endif


#pragma clang assume_nonnull begin




#pragma clang assume_nonnull begin


#ifndef _REWRITER_typedef_DecodeString_OC
#define _REWRITER_typedef_DecodeString_OC
typedef struct objc_object DecodeString_OC;
typedef struct {} _objc_exc_DecodeString_OC;
#endif

struct DecodeString_OC_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
};


// @property (nonatomic, copy) NSString *string;
// - (NSString*)decode:(NSString*)string;

/* @end */

#pragma clang assume_nonnull end

#pragma clang assume_nonnull begin

// @interface DecodeString_OC (Ex)

// - (void)log;

/* @end */

#pragma clang assume_nonnull end

// @implementation DecodeString_OC (Ex)


static void _I_DecodeString_OC_Ex_log(DecodeString_OC * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_DecodeString_OC_Ex_e9f331_mi_0,((NSString *(*)(id, SEL))(void *)objc_msgSend)((id)self, sel_registerName("string")));
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
	unsigned int instanceStart;
	unsigned int instanceSize;
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

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CATEGORY_INSTANCE_METHODS_DecodeString_OC_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"log", "v16@0:8", (void *)_I_DecodeString_OC_Ex_log}}
};

extern "C" __declspec(dllimport) struct _class_t OBJC_CLASS_$_DecodeString_OC;

//分类也是一个对象，他是_category_t 的实例，
static struct _category_t _OBJC_$_CATEGORY_DecodeString_OC_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = 
{
	"DecodeString_OC",
	0, // &OBJC_CLASS_$_DecodeString_OC,
	(const struct _method_list_t *)&_OBJC_$_CATEGORY_INSTANCE_METHODS_DecodeString_OC_$_Ex,
	0,
	0,
	0,
};
//初始化分类的方法，在方法中将分类对应的类指向对应的类对象地址
static void OBJC_CATEGORY_SETUP_$_DecodeString_OC_$_Ex(void ) {
	_OBJC_$_CATEGORY_DecodeString_OC_$_Ex.cls = &OBJC_CLASS_$_DecodeString_OC;
}
#pragma section(".objc_inithooks$B", long, read, write)
__declspec(allocate(".objc_inithooks$B")) static void *OBJC_CATEGORY_SETUP[] = {
	(void *)&OBJC_CATEGORY_SETUP_$_DecodeString_OC_$_Ex,
};
// 存放分类的数组，保存到数据段中的__objc_catlist
static struct _category_t *L_OBJC_LABEL_CATEGORY_$ [1] __attribute__((used, section ("__DATA, __objc_catlist,regular,no_dead_strip")))= {
	&_OBJC_$_CATEGORY_DecodeString_OC_$_Ex,
};
static struct IMAGE_INFO { unsigned version; unsigned flag; } _OBJC_IMAGE_INFO = { 0, 2 };
