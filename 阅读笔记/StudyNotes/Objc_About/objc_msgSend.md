#  objc_msgSend

> 从编译后的CPP文件开始

```
        Man * msgMan = [[Man alloc]init];
        
xcrun --sdk iphoneos clang -arch arm64 -rewrite-objc main.m -o main.cpp
===>
        Man *msgMan = ((Man *(*)(id, SEL))(void *)objc_msgSend)((id)
        ((Man *(*)(id, SEL))(void *)objc_msgSend)
        ((id)objc_getClass("Man"), sel_registerName("alloc")), 
        sel_registerName("init"));

简化一下 摸索了一下
===> 其实就是俄罗斯套娃 哈哈 目前使用了 函数指针的形式调用 以前是使用objc_msgSend(id,SEL)这样
    Man *msgMan = ((Man *(*)(id, SEL))(void *)objc_msgSend)
    ((id)((Man *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("Man"), sel_registerName("alloc")), //id
    sel_registerName("init"));//SEL
再简化一下
===>
    id classMan = ((Man *(*)(id, SEL))(void *)objc_msgSend) //id
	((id)objc_getClass("Man"), sel_registerName("alloc")) //SEL
    Man *msgMan =  ((Man *(*)(id, SEL))(void *)objc_msgSend) //id
    (classMan, sel_registerName("init")) //SEL
    
最细解释
===>
	void *msgSendIMP = (void *)objc_msgSend;
    Man *(*funcMsgSend)(id,SEL) = msgSendIMP; //有这里可知 原代码的地方 使用了匿名函数指针(Man *(*)(id, SEL)) 一开始看懵逼到 恍然大悟 
    Man *msgMan = funcMsgSend((id)objc_getClass("Man"),sel_registerName("alloc"));
    由此递推 alloc init 等其他方法
    
    //看不懂看这里
    //看看C++的函数指针相关的内容
    //IMP 相关 
    执行IMP void (*func)(id, SEL, id) = (void *)imp;  func(self, methodName,param);
    注意分析：如果方法没有传入参数时：void (*func)(id, SEL) = (void *)imp;   func(self, methodName);
    如果方法传入一个参数时：void (*func)(id, SEL,id) = (void *)imp;   func(self, methodName,param);
    如果方法传入俩个参数时：void (*func)(id, SEL,id,id) = (void *)imp;   func(self, methodName,param1,param2);

```
