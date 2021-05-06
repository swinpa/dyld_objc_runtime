##Class
####编译阶段：

```
//属性
struct _prop_t {
	const char *name;
	const char *attributes;
};
struct _protocol_t;
//方法
struct _objc_method {
	struct objc_selector * _cmd;
	const char *method_type;
	void  *_imp;
};
//协议
struct _protocol_t {
	void * isa;  // NULL
	const char *protocol_name;
	const struct _protocol_list_t * protocol_list; // super protocols
	const struct method_list_t *instance_methods;
	const struct method_list_t *class_methods;
	const struct method_list_t *optionalInstanceMethods;
	const struct method_list_t *optionalClassMethods;
	const struct _prop_list_t * properties;
	const unsigned int size;  // sizeof(struct _protocol_t)
	const unsigned int flags;  // = 0
	const char ** extendedMethodTypes;
};
//变量
struct _ivar_t {
	unsigned long int *offset;  // pointer to ivar offset location
	const char *name;
	const char *type;
	unsigned int alignment;
	unsigned int  size;
};
//类方法，成员变量信息
struct _class_ro_t {
	unsigned int flags;
    //-----------确定了成员变量的地址空间----------------
	unsigned int instanceStart;
	unsigned int instanceSize;
    //---------------------------
	const unsigned char *ivarLayout;
	const char *name;
	const struct _method_list_t *baseMethods;
	const struct _objc_protocol_list *baseProtocols;
	const struct _ivar_list_t *ivars;
	const unsigned char *weakIvarLayout;
	const struct _prop_list_t *properties;
};
//类信息-保存类的类型isa，指向的父类，缓存，以及保存了类其他信息的ro
struct _class_t {
	struct _class_t *isa;
	struct _class_t *superclass;
	void *cache;
	void *vtable;
	struct _class_ro_t *ro;
};
//分类
struct _category_t {
	const char *name;
	struct _class_t *cls;
	const struct _method_list_t *instance_methods;
	const struct _method_list_t *class_methods;
	const struct _protocol_list_t *protocols;
	const struct _prop_list_t *properties;
};
```

####运行时阶段：

```
typedef struct objc_class *Class;

struct objc_class {
    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;

#if !__OBJC2__
    Class _Nullable super_class                              OBJC2_UNAVAILABLE;
    const char * _Nonnull name                               OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list * _Nullable ivars                  OBJC2_UNAVAILABLE;
    struct objc_method_list * _Nullable * _Nullable methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache * _Nonnull cache                       OBJC2_UNAVAILABLE;
    struct objc_protocol_list * _Nullable protocols          OBJC2_UNAVAILABLE;
#endif

} OBJC2_UNAVAILABLE;


```
```
struct objc_object {
    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;
};

typedef struct objc_object *id;

```
```
@interface NSObject <NSObject> {
    Class isa  OBJC_ISA_AVAILABILITY;
}
```

####从这可以看出NSObject的对象大小就是一个isa (objc_class *) 指针大小（32位为4 byte，64位为8 byte）


```
struct objc_object {
private:
    isa_t isa;
};
```
```
typedef struct objc_class *Class;

struct objc_class : objc_object {
    // Class ISA;
    Class superclass; // 相当于 objc_class * superclass;
    cache_t cache;             // formerly cache pointer and vtable
    /*
     存放对象相关数据的地方，比如成员变量
     	   struct class_data_bits_t {
		    uintptr_t bits;
		    class_rw_t* data() {
		        return (class_rw_t *)(bits & FAST_DATA_MASK);
		    }
	   }
     */
    class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
};

```
#### 所以NSObject 其实就是
```
@interface NSObject <NSObject> {
    objc_class *isa;
}
```
#### 一个只有一个objc_class 类型的指针变量isa的类

* NSObject 中只有一个objc_class 类型的指针变量isa
* objc_class又是objc_object的子类，而在objc_class中有一个objc_class类型的用来指向父类的 指针变量superclass，还有一个cache变量以及一个class_data_bits_t bits变量
### 其中的 class_data_bits_t bits 成员变量很重要，存放了类信息相关的数据如class_rw_t，class_ro_t

```
struct class_rw_t {
    // Be warned that Symbolication knows the layout of this structure.
    /*
     标志位，根据该变量与不同的标志位进行 & 操作判断 是否为元类，是否为跟类，是否为ARC
     class is a metaclass 等
     RO_META，RW_INITIALIZED
     */
    uint32_t flags;
    uint32_t version;
    const class_ro_t *ro;
    //类realize后(realizeClass()执行后)，所有的实例方法都放在该变量中，包括分类中定义的
    method_array_t methods;
    property_array_t properties;
    protocol_array_t protocols;
    Class firstSubclass;
    //Sibling: 兄弟姊妹；同胞
    Class nextSiblingClass;
    char *demangledName;
 };
```
```
struct class_ro_t {
    /*
     标志位，根据该变量与不同的标志位进行 & 操作判断 是否为元类，是否为跟类，是否为ARC
     class is a metaclass 等
     RO_META，RW_INITIALIZED
     */
    uint32_t flags;
    /// 成员变量开始的首地址，这里是以第一个成员变量为开始
    uint32_t instanceStart;
    /// 所有成员变量所占用内存空间大小
    uint32_t instanceSize;
    const uint8_t * ivarLayout;// <- 记录了哪些是 strong 的 ivar
    const char * name;
    method_list_t * baseMethodList;
    protocol_list_t * baseProtocols;
    /// 存放的是成员变量相对于对象首地址的偏移量
    const ivar_list_t * ivars;
    const uint8_t * weakIvarLayout;// <- 记录了哪些是 weak 的 ivar
    property_list_t *baseProperties;
};
```

###运行时class_rw_t保存了类的方法，协议，属性相关信息，而class_ro_t则保存这类的成员变量相关信息（如所有的成员变量占用的内存空间大小instanceSize，访问这些成员变量需要用到的成员变量信息ivars）

* 在objc_class  的父类 objc_object 中只有一个成员变量 isa_t isa，isa_t是一个联合体union，isa_t中有一个Class cls;变量，在alloc 一个对象后，会将这个cls 指向对应的类

```
比如

[[Person alloc] init] 这样子创建一个对象，对象alloc 后会将对象中的isa_t isa 变量中的cls 指向了Person（Person 其实也是一个对象）

```

