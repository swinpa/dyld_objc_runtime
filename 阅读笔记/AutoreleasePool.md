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

* 可以看出，在代码块前面，在栈中创建了一个pool结构体对象，因为是结构体对象，所以该变量在栈上，在代码块结束后会被释放，而该结构体对象在构造函数中会调用objc_autoreleasePoolPush()创建或获取AutoreleasePoolPage对象，那么代码块中的autorelease对象会被加入到该PoolPage中
	
	#####经过如下调用栈
	
	```
	|->objc_autoreleasePoolPush()
		|->AutoreleasePoolPage::push()
			|->autoreleaseFast(POOL_BOUNDARY)
	```
	#####objc_autoreleasePoolPush() 最终会通过autoreleaseFast(POOL_BOUNDARY)方法获取到当前的poolPage（AutoreleasePoolPage *page = hotPage();）或者新new 一个poolpage，并在poolpage 中添加一个哨兵（nil）,后续添加的autorelease对象会在这个page的哨兵的后面
		* 哨兵应该是用来分隔每个@autoreleasepool{}代码块内的autorelease 对象的，这样当进行objc_autoreleasePoolPop(atautoreleasepoolobj)时，知道遍历到哪里结束，也就是一个poolpage 可以存放多个@autoreleasepool{}代码块内的autorelease 对象，他们是通过哨兵(nil)进行分隔的


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

### 上面是手动@autoreleasepool {} 将对象添加到释放池时，对象释放的时机（@autoreleasepool {}代码块结束），而如果使用默认的autoreleasepool（也就是主线程中的pool）时，则该pool中对象释放时机则是：
* RunLoop退出时

####autoreleasepool 跟RunLoop有关系，从GNUstep 源码中看，RunLoop在- (BOOL) runMode: (NSString*)mode beforeDate: (NSDate*)date{} 的最前面代码会创建一个NSAutoreleasePool	*arp = [NSAutoreleasePool new];并且在最后面进行[arp drain];(也就是dealloc 掉)


###那线程跟autoreleasepool 有关系吗？如果没开启RunLoop，那线程中的autorelease对象是添加到那个autoreleasepool中的呢？（目前没在GNUstep源码中的NSThread 看到相关的创建autoreleasepool 的代码）其实在没开启runloop的子线程中如果有autorelease对象时，会自动创建一个自动释放池，在创建自动释放池时，会注册线程销毁的回调tls_dealloc，当线程销毁时会回调到tls_deallo函数，tls_deallo中又调用objc_autoreleasePoolPop对自动释放池中的对象进行释放


###对象发送多条autorelease消息，比如多次执行[obj autorelease] 会有问题不？
    
    不会有问题，只是多次添加到autoreleasepool中，当autoreleasepool 释放时同样也能多次拿到进行多次发送release消息

```

App启动后，系统在主线程RunLoop 里注册两个Observser,其回调都是_wrapRunLoopWithAutoreleasePoolHandler()。

第一个 Observer 监视的事件
是 Entry(即将进入Loop)，其回调内会调用 _objc_autoreleasePoolPush() 创建自动释放池。其优先级最高，保证创建释放池发生在其他所有回调之前。

第二个 Observer 监视了两个事件

_BeforeWaiting(准备进入休眠) 时 _
调用_objc_autoreleasePoolPop() 和 _objc_autoreleasePoolPush() 释放旧的池并创建新池；

_Exit(即将退出Loop) 时 _
调用 _objc_autoreleasePoolPop() 来释放自动释放池。这个 Observer 优先级最低，保证其释放池子发生在其他所有回调之后。

在主线程执行的代码，通常是写在诸如事件回调、Timer回调内的。这些回调会被 RunLoop 创建好的 AutoreleasePool 环绕着，所以不会出现内存泄漏，开发者也不必显示创建 Pool 了。

现在我们知道了AutoreleasePool是在RunLoop即将进入RunLoop和准备进入休眠这两种状态的时候被创建和销毁的。

所以AutoreleasePool的释放有如下两种情况。
一是Autorelease对象是在当前的runloop迭代结束时释放的，而它能够释放的原因是系统在每个runloop迭代中都加入了自动释放池Push和Pop。
二是手动调用AutoreleasePool的释放方法（drain方法）来销毁AutoreleasePool



```
