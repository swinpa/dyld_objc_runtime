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
