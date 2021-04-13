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

* 可以看出，在代码块前面，在栈中创建了一个pool结构体对象，而该结构体对象在构造函数中会调用objc_autoreleasePoolPush()创建AutoreleasePoolPage对象，那么代码块中的autorelease对象会被加入到该PoolPage中
* 当代码块结束时，栈中的pool会被释放，那么在pool的析构方法中又会调用objc_autoreleasePoolPop()接口释放PoolPage中的对象