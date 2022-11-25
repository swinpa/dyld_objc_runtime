#Weak
```
void object_setIvar(id obj, Ivar ivar, id value)
	
	object_setIvar内直接调用_object_setIvar()
	
	|-> void _object_setIvar(id obj, Ivar ivar, id value, bool assumeStrong)
		_object_setIvar内通过_class_lookUpIvar()获取ivar变量在obj中的内存布局类型以及offset
		然后根据id *location = (id *)((char *)obj + offset);获取ivar变量的内存区域
		然后调用objc_storeWeak()进行弱变量赋值
		
		|-> objc_storeWeak(id _Nullable * _Nonnull location, id _Nullable obj) 
		
			|-> static id storeWeak(id *location, objc_object *newObj)
		
```
```

template <HaveOld haveOld, HaveNew haveNew,
          CrashIfDeallocating crashIfDeallocating>
static id 
storeWeak(id *location,//弱引用指针变量weakPtr
          objc_object *newObj)//被弱引用指针指向的对象obj
{
    assert(haveOld  ||  haveNew);//不能同时为false
    if (!haveNew) assert(newObj == nil);

    Class previouslyInitializedClass = nil;
    id oldObj;
    SideTable *oldTable;
    SideTable *newTable;

    // Acquire locks for old and new values.
    // Order by lock address to prevent lock ordering problems. 
    // Retry if the old value changes underneath us.
 retry:
    if (haveOld) {
        /*
         根据对象地址，从全局hash表中获取对象对应的SideTable，SideTable里面包含了弱引用变量列表(弱引用变量列表存储了所有指向该对象的弱引用变量)
         location 为存储对象地址的指针变量
         *location 为取指针变量中存储的值
         例如：
         int a = 10;此时a 的内存地址为0x000000a0
         生命指针变量p指向a
         int *p = &a;此时指针变量p中保存的就是a的地址0x000000a0
         *p 为获取p变量中存储的值0x000000a0
         */
        /*
         根据对象指针，从弱引用hash表中获取对象对应的弱引用变量列表
         */
        oldObj = *location;
        /*
         SideTables() 为 StripedMap类型，在StripedMap重载了[]操作符
         []操作符会会转成array[indexForPointer(p)].value;也就是根据对象地址c转成数组的下标
         */
        oldTable = &SideTables()[oldObj];
    } else {
        oldTable = nil;
    }
    if (haveNew) {
        newTable = &SideTables()[newObj];
    } else {
        newTable = nil;
    }

    SideTable::lockTwo<haveOld, haveNew>(oldTable, newTable);

    if (haveOld  &&  *location != oldObj) {
        SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);
        goto retry;
    }

    // Prevent a deadlock between the weak reference machinery
    // and the +initialize machinery by ensuring that no 
    // weakly-referenced object has an un-+initialized isa.
    if (haveNew  &&  newObj) {
        Class cls = newObj->getIsa();
        if (cls != previouslyInitializedClass  &&  
            !((objc_class *)cls)->isInitialized()) 
        {
            SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);
            _class_initialize(_class_getNonMetaClass(cls, (id)newObj));

            // If this class is finished with +initialize then we're good.
            // If this class is still running +initialize on this thread 
            // (i.e. +initialize called storeWeak on an instance of itself)
            // then we may proceed but it will appear initializing and 
            // not yet initialized to the check above.
            // Instead set previouslyInitializedClass to recognize it on retry.
            previouslyInitializedClass = cls;

            goto retry;
        }
    }

    // Clean up old value, if any.
    if (haveOld) {
        /*
         将指定的弱引用变量设置为nil
         
         NSObject *objA = [[NSObject alloc] init];
         __weak NSObject *weak_ptr1 = objA;
         
         NSObject *objB = [[NSObject alloc] init];
         weak_ptr1 = objB;
         
         应该是在weak_ptr1 = objB; 的时候需要将weak_ptr1的旧值变成nil先;
         
         1，在这里，在weak_table中根据对象ObjA 找到保存了对象ObjA的所有弱引用变量的节点
         (通过遍历列表weak_table，查找节点中的对象成员变量跟ObjA相等的节点)
         2，在节点中的弱引用变量列表中找到跟weak_ptr1一致的弱引用变量，然后将其置成nil
         3，判断节点中的引用变量列表中是否所有的弱引用变量都是nil了，如果是，则删除节点
         
         问题又来了，为什么需要先置nil呢？不做这一步可以吗？？？？？？
         
         */
        //                                              objA   weak_ptr1
        weak_unregister_no_lock(&oldTable->weak_table, oldObj, location);
    }

    // Assign new value, if any.
    if (haveNew) {
        newObj = (objc_object *)
            weak_register_no_lock(&newTable->weak_table, (id)newObj, location, 
                                  crashIfDeallocating);
        // weak_register_no_lock returns nil if weak store should be rejected

        // Set is-weakly-referenced bit in refcount table.
        if (newObj  &&  !newObj->isTaggedPointer()) {
            newObj->setWeaklyReferenced_nolock();
        }

        // Do not set *location anywhere else. That would introduce a race.
        *location = (id)newObj;
    }
    else {
        // No new value. The storage is not changed.
    }
    
    SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);

    return (id)newObj;
}

```

