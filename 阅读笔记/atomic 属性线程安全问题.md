##@property (atomic, assign) NSInteger number; atomic 线程安全问题

* 属性访问底层实现


```
static inline void reallySetProperty(id self, SEL _cmd, id newValue, ptrdiff_t offset, bool atomic, bool copy, bool mutableCopy)
{
    if (offset == 0) {
        object_setClass(self, newValue);
        return;
    }
    id oldValue;
    /*
     根据变量与对象的相对偏移量，计算出变量位置
     这里的self是对象，如
     Person *p = [[Person alloc] init];
     p.name = @"xiaoming";
     这时候传进来的self 则就是p
     
     所以根据变量与对象的相对偏移量就可以算出变量的内存地址
     
     */
    id *slot = (id*) ((char*)self + offset);

    if (copy) {
        newValue = [newValue copyWithZone:nil];
    } else if (mutableCopy) {
        newValue = [newValue mutableCopyWithZone:nil];
    } else {
        if (*slot == newValue) return;
        //retain 新对象的引用计数
        newValue = objc_retain(newValue);
    }

    if (!atomic) {
        oldValue = *slot;
        *slot = newValue;
    } else {
        spinlock_t& slotlock = PropertyLocks[slot];
        slotlock.lock();
        oldValue = *slot;
        *slot = newValue;        
        slotlock.unlock();
    }

    //release 旧对象的引用计数
    objc_release(oldValue);
}
```
```
id objc_getProperty(id self, SEL _cmd, ptrdiff_t offset, BOOL atomic) {
    if (offset == 0) {
        return object_getClass(self);
    }

    // Retain release world
    id *slot = (id*) ((char*)self + offset);
    if (!atomic) return *slot;
        
    // Atomic retain release world
    spinlock_t& slotlock = PropertyLocks[slot];
    slotlock.lock();
    id value = objc_retain(*slot);
    slotlock.unlock();
    
    // for performance, we (safely) issue the autorelease OUTSIDE of the spinlock.
    return objc_autoreleaseReturnValue(value);
}
```

* 可以看出atomic 只是针对 setter 和 getter 方法进行加锁
* 如果出现如下情况，则就会有线程安全问题

```
- (void)atomicTest {
    线程A
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 10000; i ++) {
            self.number = self.number + 1;
        }
    });
    线程B
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 10000; i ++) {
            self.number = self.number + 1;
        }
    });
}

假如《线程A》执行到 = 右边的getter 方法返回后还没进行赋值就切换到了下面《线程B》执行，
那么当下面的《线程B》执行完赋值操作，又切换到《线程A》进行赋值操作，那么这时候=号右边的值
并不是下面《线程B》操作后的最新值，这就导致了线程不同步出现数据差异

```

###@synchronized (obj)
* 底层会转变成

```
int objc_sync_enter(id obj)
int objc_sync_exit(id obj)
```
* 底层还有一个全局的hash表（static StripedMap<SyncList> sDataLists;）这里的设计类似弱引用的设计，也是通过hash表 + 列表的方案解决hash冲突
	
	```
	typedef struct alignas(CacheLineSize) SyncData {
	    struct SyncData* nextData;
	    DisguisedPtr<objc_object> object;
	    int32_t threadCount;  // number of THREADS using this block
	    recursive_mutex_t mutex;
	} SyncData;

	struct SyncList {
	    SyncData *data;
	    spinlock_t lock;
	    constexpr SyncList() : data(nil), lock(fork_unsafe_lock) { }
	};
	```
* 每次加解锁（调用objc_sync_enter 或者objc_sync_exit）时都会从线程的快速缓存或者线程缓存中获取SyncData数据，如果缓存中获取不到，那就通过对传进来的object地址进行hash计算得到一个SyncList对象，该对象中保存了一个SyncData类型的列表，而SyncData 则就持有了一个recursive_mutex_t mutex;也就是最终用来加锁的互斥量

####各种锁性能比较[其他锁，看这里](https://juejin.cn/post/6844904088178688008)
* OSSpinLock > dispatch_semaphore > pthread_mutex > NSLock > NSCondition > pthread_mutex(recursive) > NSRecursiveLock > NSConditionLock > synchronized

	1. 因为OSSpinLock 是抢占锁，一直占用CPU获取锁，不需要像mutex 那样挂起线程，所以性能最高
	2. dispatch_semaphore > pthread_mutex 因为其底层也是通过while循环不断进行原子比较获取锁状态，
	3. pthread_mutex > NSLock  是因为NSLock 底层其实也是pthread_mutex
	4. synchronized慢的原因是：1. 需要查找缓存 2. 缓存没有去全局的hash表查找 3. 前两部查找都没找到才创建

####NSThread, GCD, NSOperationQueue
* NSThread 底层基于pthread的封装（基于GNUStep 源码）
* GCD 也是基于pthread的封装
* NSOperationQueue 底层使用了GCD进行线程管理 [基于swift NSOperationQueue源码链接](https://github.com/apple/swift-corelibs-foundation) ，但是基于GNUStep 源码来分析NSOperationQueue底层又用的是NSThread开辟线程
