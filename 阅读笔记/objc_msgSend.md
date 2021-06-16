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

