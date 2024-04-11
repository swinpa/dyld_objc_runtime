#CFRunLoop
https://rimson.top/2020/05/21/yyasynclayer/
* NSRunLoop 并没有向外提供创建runloop对象的接口，只提供了currentRunLoop 这个类属性，在通过该属性获取runloop时，底层应该会调用CFRunLoopGetCurrent(void) 这个接口获取，而这个接口会先从当前线程的STD数据中查询有没有runloop 对象，有就返回，没有则再调用_CFRunLoopGet0(pthread_t t)这个接口获取指定线程的runloop


/* Run Loop Observer Activities */
typedef CF_OPTIONS(CFOptionFlags, CFRunLoopActivity) {
    //RunLoop准备启动
    kCFRunLoopEntry = (1UL << 0),
    //RunLoop将要处理一些Timer相关事件
    kCFRunLoopBeforeTimers = (1UL << 1),
    //RunLoop将要处理一些Source事件
    kCFRunLoopBeforeSources = (1UL << 2),
    //RunLoop将要进行休眠状态,即将由用户态切换到内核态
    kCFRunLoopBeforeWaiting = (1UL << 5),
    //RunLoop被唤醒，即从内核态切换到用户态后
    kCFRunLoopAfterWaiting = (1UL << 6),
    //RunLoop退出
    kCFRunLoopExit = (1UL << 7),
    //监听所有状态
    kCFRunLoopAllActivities = 0x0FFFFFFFU
};
