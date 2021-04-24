##Class
####编译阶段：

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
    Class superclass;
    cache_t cache;             // formerly cache pointer and vtable
    /**
     * 存放对象相关数据的地方，比如成员变量
     */
    class_data_bits_t bits;    // class_rw_t * plus custom rr/alloc flags
};

```
