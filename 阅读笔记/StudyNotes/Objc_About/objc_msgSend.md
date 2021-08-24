#  objc_msgSend

> 从编译后的CPP文件开始

```
        Man * msgMan = [[Man alloc]init];
===>
        Man *msgMan = ((Man *(*)(id, SEL))(void *)objc_msgSend)((id)
        ((Man *(*)(id, SEL))(void *)objc_msgSend)
        ((id)objc_getClass("Man"), sel_registerName("alloc")), 
        sel_registerName("init"));
简化一下
===>
	id classMan = ((Man *(*)(id, SEL))(void *)objc_msgSend)
	((id)objc_getClass("Man"), sel_registerName("alloc"))
	
	Man *msgMan = 
    
    
    执行IMP void (*func)(id, SEL, id) = (void *)imp;  func(self, methodName,param);

    注意分析：如果方法没有传入参数时：void (*func)(id, SEL) = (void *)imp;   func(self, methodName);

    如果方法传入一个参数时：void (*func)(id, SEL,id) = (void *)imp;   func(self, methodName,param);

    如果方法传入俩个参数时：void (*func)(id, SEL,id,id) = (void *)imp;   func(self, methodName,param1,param2);

