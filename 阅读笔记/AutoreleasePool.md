##AutoreleasePool

```
int main(int argc, char * argv[]) {
	@autoreleasepool {
        NSObject *obj0 = [[[NSObject alloc] init] autorelease];
        @autoreleasepool {
            NSObject *obj10 = [[[NSObject alloc] init] autorelease];
            @autoreleasepool {
                NSObject *obj20 = [[[NSObject alloc] init] autorelease];
            }
        }
        NSObject *obj1 = [[[NSObject alloc] init] autorelease];
    }
}
```
##编译器会转变成如下代码

```
extern "C" __declspec(dllimport) void * objc_autoreleasePoolPush(void);
extern "C" __declspec(dllimport) void objc_autoreleasePoolPop(void *);

struct __AtAutoreleasePool {
  void * atautoreleasepoolobj;
  __AtAutoreleasePool() {
  		atautoreleasepoolobj = objc_autoreleasePoolPush();
  }
  ~__AtAutoreleasePool() {
  		objc_autoreleasePoolPop(atautoreleasepoolobj);
  }
};

int main(int argc, char * argv[]) {

    /* @autoreleasepool */
    {
        __AtAutoreleasePool __autoreleasepool;
        NSObject *obj0 = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")), sel_registerName("autorelease"));
        /* @autoreleasepool */
        {
            __AtAutoreleasePool __autoreleasepool;
            NSObject *obj10 = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")), sel_registerName("autorelease"));
            
            /* @autoreleasepool */
            {
                __AtAutoreleasePool __autoreleasepool;
                NSObject *obj20 = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")), sel_registerName("autorelease"));
            }
        }
        NSObject *obj1 = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")), sel_registerName("autorelease"));
    }
    return 0;
}
```

* 可以看出，在代码块前面，在栈中创建了一个pool结构体对象，因为是结构体对象，所以该变量在栈上，在代码块结束后会被释放，而该结构体对象在构造函数中会调用objc_autoreleasePoolPush()创建AutoreleasePoolPage对象，那么代码块中的autorelease对象会被加入到该PoolPage中
* 当代码块结束时，栈中的pool会被释放，那么在pool的析构方法中又会调用objc_autoreleasePoolPop()接口释放PoolPage中的对象

* 当对象发送autorelease消息后（[obj autorelease]），最终经过一些列的调用栈转换，最终会执行AutoreleasePoolPage::autoreleaseFast(id obj); 方法将obj添加到AutoreleasePoolPage的next（id *next） 指针数组中

	```
	|->[obj autorelease]
		|->((id)self)->rootAutorelease();
			|->rootAutorelease2();
				|->AutoreleasePoolPage::autorelease((id)this);
					|->autoreleaseFast(id obj)
	```
* autoreleaseFast(obj)中会通过hotPage()接口拿到当前最近的AutoreleasePoolPage 对象，也就是前面__AtAutoreleasePool结构体在构造时通过atautoreleasepoolobj = objc_autoreleasePoolPush();构造的对象，然后调用atautoreleasepoolobj对象的add(obj)成员方法，将obj添加到atautoreleasepoolobj中
* 其实就是AutoreleasePoolPage中有一个id *next;成员变量(看出指针数组，存放对象obj的指针的数组)，obj对象的指针就保存在该变量中（ *next++ = obj;）
* 当代码块结束时，__AtAutoreleasePool 结构体对象__autoreleasepool会被释放（因为是在栈上），__AtAutoreleasePool 结构体析构方法中会调用objc_autoreleasePoolPop(atautoreleasepoolobj);方法来释放atautoreleasepoolobj中的 atautorelease 对象，也就是释放AutoreleasePoolPage中的next中保存的对象

	```
	objc_autoreleasePoolPop(atautoreleasepoolobj)
		|->AutoreleasePoolPage::pop(atautoreleasepoolobj);
			|->page->releaseUntil(atautoreleasepoolobj);
	```
* 在releaseUntil(atautoreleasepoolobj)中会遍历*next 中所保存的所以对象，然后给这些对象发送一条release消息id obj = *--page->next; objc_release(obj);以达到释放对象的目的

### 上面是手动@autoreleasepool {} 将对象添加到释放池时，对象释放的时机，而如果使用默认的autoreleasepool（也就是主线程中的pool）时，则该pool中对象释放时机则是：
* 是

