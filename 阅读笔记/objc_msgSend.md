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


