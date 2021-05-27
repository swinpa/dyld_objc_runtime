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


