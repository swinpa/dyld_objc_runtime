##objc_msgSend(id self, SEL _cmd, ...)


```
struct _class_t {
	struct _class_t *isa;
	struct _class_t *superclass;
	void *cache;
	void *vtable;
	struct _class_ro_t *ro;
};
	
@interface NSObject <NSObject> {
    objc_class *isa;
}

```
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
* 在objc_msgSend(id self, SEL _cmd, ...)内部，会获取第一个参数self的isa里面的methods

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

