#CFRunLoop
https://rimson.top/2020/05/21/yyasynclayer/
* NSRunLoop 并没有向外提供创建runloop对象的接口，只提供了currentRunLoop 这个类属性，在通过该属性获取runloop时，底层应该会调用CFRunLoopGetCurrent(void) 这个接口获取，而这个接口会先从当前线程的STD数据中查询有没有runloop 对象，有就返回，没有则再调用_CFRunLoopGet0(pthread_t t)这个接口获取指定线程的runloop
