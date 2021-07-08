##objc_msgSend(id self, SEL _cmd, ...)


```
struct _class_t {
	struct _class_t *isa;
	struct _class_t *superclass;
	void *cache;
	void *vtable;
	struct _class_ro_t *ro;
};

```
```
@interface NSObject <NSObject> {
    objc_class *isa;
}
```

```
typedef struct objc_class *Class;

struct objc_object {
	private:
	    isa_t isa;
}
struct objc_class : objc_object {
    // Class ISA;
    Class superclass;
    cache_t cache;             // formerly cache pointer and vtable
    /**
     * 存放对象相关数据的地方，比如成员变量
     */
    class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags

    class_rw_t *data() { 
        return bits.data();
    }
    void setData(class_rw_t *newData) {
        bits.setData(newData);
    }
}
```
####所以对象的ISA指向的是objc_class类型，objc_class中的class_data_bits_t类型的成员变量bits 存储了class_rw_t类型的数据

```

struct class_data_bits_t {
    uintptr_t bits;
    class_rw_t* data() {
        /*
         #define FAST_DATA_MASK          0x00007ffffffffff8UL
         通过bits & FAST_DATA_MASK进行与操作，拿到类的class_rw_t 这个结构体的数据
         也就是类的class_rw_t 结构体数据存放在bits 中的从第3到47 位中，总共31位
         */
        return (class_rw_t *)(bits & FAST_DATA_MASK);
    }
};

struct class_rw_t {
    const class_ro_t *ro;
    //类realize后(realizeClass()执行后)，所有的实例方法都放在该变量中，包括分类中定义的
    method_array_t methods;
    property_array_t properties;
    protocol_array_t protocols;
}
```
####class_rw_t中保存了方法methods

```
[Person drive];
Person *obj = [[Person alloc] init];
[obj doJob];
```
```
类方法调用
objc_msgSend((id)objc_getClass("Person"), sel_registerName("drive"));

Person *obj = (Person *)objc_msgSend((id)objc_getClass("Person"), sel_registerName("alloc")), sel_registerName("init"));

成员方法调用
objc_msgSend((id)obj, sel_registerName("doJob"));

```

* 从上面可以看出，
	
	1. 实例方法调用objc_msgSend(id self, SEL _cmd, ...)时，第一个参数传的是对象obj
	2. 类方法调用objc_msgSend(id self, SEL _cmd, ...)时第一个参数传的是类对象(id)objc_getClass("Person")
* 在objc_msgSend(id self, SEL _cmd, ...)函数内部，会获取第一个参数self(外部传进来的obj对象)的isa里面的methods

####类与元类，跟元类都是objc_class类型的对象

	```
	isa === objc_class
	
	objc_class {
		class_rw_t *data()
	}
	class_rw_t {
		method_array_t methods;
	}
	
	isa -> data() -> methods
	
	```

	* obj 的isa 是objc_class类型，objc_class类型中保存了class_rw_t类型的数据，class_rw_t中保存了方法列表methods，
	* 对象的isa 指向的是类对象，也就是方法查找时查找的是类对象中的数据（类对象中的methods保存的是成员方法，这是编译期间确定的）
	* 类对象的isa 指向的是元类对象，也就是方法查找时查找的是元类对象中的数据（元类对象中的methods保存的是类方法，这是编译期间确定的）
	
	
	####类
	* _class_t 中有一个保存了类变量信息的_class_ro_t类型的变量ro
	* _class_ro_t中的_ivar_list_t *ivars变量保存了变量相对于对象的地址偏移信息，而这个ivars 的大小在编译期间已经确定了，后续访问变量都是通过该列表找到变量的地址偏移信息进行访问
	
####消息发送过程
	```
	在编译期间，消息发送会被编译器转成调用objc_msgSend方法的，该方法的第一个参数是对象（如果是静态方法，则会调用objc_getClass()
	获取类对象作为第一个参数）第二个参数则是方法名SEL，后面就是其他可变参数
	```

####查找逻辑
* objc_msgSend 查找IMP 是通过调用IMP _class_lookupMethodAndLoadCache3(id obj, SEL sel, Class cls)实现的，传进来的cls 是对象（类对象）的isa
* _class_lookupMethodAndLoadCache3 直接调用IMP lookUpImpOrForward(Class cls, SEL sel, id inst, bool initialize, bool cache, bool resolver)方法
* 具体查找逻辑如下
     1. 从当前类的缓存中查找，找到则返回
     2. 当前类的缓存没有，则去当前类的方法列表( cls->data()->methods)中查找，找到缓存并返回
    		
    			```
    			static method_t * getMethodNoSuper_nolock(Class cls, SEL sel)
			{
			    for (auto mlists = cls->data()->methods.beginLists(), 
			              end = cls->data()->methods.endLists();  mlists != end; ++mlists)
			    {
			        method_t *m = search_method_list(*mlists, sel);
			        if (m) return m;
			    }
			    return nil;
			}
    			```
    		
     3. 当前类的方法列表中没有找到则去父类的缓存查找，找到将其缓存到当前类并返回
     4. 父类的缓存没有则去父类的方法列表中查找，找到将其缓存到当前类并返回
     5. 如果遍历完父类的缓存以及方法列表都没找到，则进行动态方法决议
     		
     		动态方法决议：查询有没有实现resolveInstanceMethod（类对象则是resolveClassMethod）方法，有则执行一次
     		执行完动态方法决议后会通过goto 指令跳转，重新跑一遍查询流程（也就是回到了第一步）
     		
     6. 如果动态方法决议后也没找到方法imp，则进行消息转发
     7. 消息转发失败则崩溃


	
	

