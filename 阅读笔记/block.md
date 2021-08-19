##block 中捕获使用__weak 变量
```
typedef void(^blk_t)(id obj);
int main(int argc, const char * argv[]) {
    blk_t block;
    {
        id array = [[NSMutableArray alloc] init];
        id __weak array2= array;
        block = [^(id obj) {
            [array2 addObject:obj];
        } copy];
    }
    block([[NSObject alloc] init]);
    return 0;
}
```
##经过clang 转换后

```
struct __block_impl {
  void *isa;
  int Flags;
  int Reserved;
  void *FuncPtr;
};

typedef void(*blk_t)(id obj);

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  __weak id array2;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, __weak id _array2, int flags=0) : array2(_array2) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

static void __main_block_func_0(struct __main_block_impl_0 *__cself, __strong id obj) {
  __weak id array2 = __cself->array2; // bound by copy
  ((void (*)(id, SEL, ObjectType  _Nonnull __strong))(void *)objc_msgSend)((id)array2, sel_registerName("addObject:"), (id)obj);
}

static void __main_block_copy_0(struct __main_block_impl_0*dst, struct __main_block_impl_0*src) {_Block_object_assign((void*)&dst->array2, (void*)src->array2, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static void __main_block_dispose_0(struct __main_block_impl_0*src) {_Block_object_dispose((void*)src->array2, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
  void (*copy)(struct __main_block_impl_0*, struct __main_block_impl_0*);
  void (*dispose)(struct __main_block_impl_0*);
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0), __main_block_copy_0, __main_block_dispose_0};


int main(int argc, const char * argv[]) 
{
    blk_t block;
    {
        id array = ((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSMutableArray"), sel_registerName("alloc")), sel_registerName("init"));
        id __attribute__((objc_ownership(weak))) array2= array;
        block = (blk_t)((id (*)(id, SEL))(void *)objc_msgSend)((id)((void (*)(__strong id))&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA, array2, 570425344)), sel_registerName("copy"));
    }

    ((void (*)(__block_impl *, __strong id))((__block_impl *)block)->FuncPtr)((__block_impl *)block, ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")));
    return 0;
}

```
##block中捕获使用_strong 修饰的对象

```

typedef void(^blk_t)(id obj);

int main(int argc, const char * argv[]) 
{  
    blk_t block;
    {
        id __strong array = [[NSMutableArray alloc] init];
        block = [^(id obj) {
            [array addObject:obj];
        } copy];
    }
    block([[NSObject alloc] init]);
    return 0;
}


```
##经过clang 转换后
```
typedef void(*blk_t)(id obj);

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  id array;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, id _array, int flags=0) : array(_array) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};
static void __main_block_func_0(struct __main_block_impl_0 *__cself, id obj) {
  id array = __cself->array; // bound by copy

            ((void (*)(id, SEL, ObjectType _Nonnull))(void *)objc_msgSend)((id)array, sel_registerName("addObject:"), (id)obj);
        }
static void __main_block_copy_0(struct __main_block_impl_0*dst, struct __main_block_impl_0*src) {_Block_object_assign((void*)&dst->array, (void*)src->array, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static void __main_block_dispose_0(struct __main_block_impl_0*src) {_Block_object_dispose((void*)src->array, 3/*BLOCK_FIELD_IS_OBJECT*/);}

static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
  void (*copy)(struct __main_block_impl_0*, struct __main_block_impl_0*);
  void (*dispose)(struct __main_block_impl_0*);
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0), __main_block_copy_0, __main_block_dispose_0};

int main(int argc, const char * argv[]) {
    blk_t block;
    {
        id __attribute__((objc_ownership(strong))) array = ((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSMutableArray"), sel_registerName("alloc")), sel_registerName("init"));

        block = (blk_t)((id (*)(id, SEL))(void *)objc_msgSend)((id)((void (*)(id))&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA, array, 570425344)), sel_registerName("copy"));
    }

    ((void (*)(__block_impl *, id))((__block_impl *)block)->FuncPtr)((__block_impl *)block, ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")));
    return 0;
}
```

##__block修饰对象

```

typedef void(^blk_t)(id obj);

int main(int argc, const char * argv[]) 
{  
    blk_t block;
    {
        __block id __strong array = [[NSMutableArray alloc] init];
        block = [^(id obj) {
            [array addObject:obj];
        } copy];
    }
    block([[NSObject alloc] init]);
    return 0;
}


```
##经过clang 转换后
```

typedef void(*blk_t)(id obj);

struct __Block_byref_array_0 {
  void *__isa;
__Block_byref_array_0 *__forwarding;
 int __flags;
 int __size;
 void (*__Block_byref_id_object_copy)(void*, void*);
 void (*__Block_byref_id_object_dispose)(void*);
 id array;
};

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  __Block_byref_array_0 *array; // by ref
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, __Block_byref_array_0 *_array, int flags=0) : array(_array->__forwarding) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};
static void __main_block_func_0(struct __main_block_impl_0 *__cself, id obj) {
  __Block_byref_array_0 *array = __cself->array; // bound by ref

            ((void (*)(id, SEL, ObjectType _Nonnull))(void *)objc_msgSend)((id)(array->__forwarding->array), sel_registerName("addObject:"), (id)obj);
        }
static void __main_block_copy_0(struct __main_block_impl_0*dst, struct __main_block_impl_0*src) {_Block_object_assign((void*)&dst->array, (void*)src->array, 8/*BLOCK_FIELD_IS_BYREF*/);}

static void __main_block_dispose_0(struct __main_block_impl_0*src) {_Block_object_dispose((void*)src->array, 8/*BLOCK_FIELD_IS_BYREF*/);}

static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
  void (*copy)(struct __main_block_impl_0*, struct __main_block_impl_0*);
  void (*dispose)(struct __main_block_impl_0*);
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0), __main_block_copy_0, __main_block_dispose_0};
int main(int argc, const char * argv[]) {
    blk_t block;
    {
        __attribute__((__blocks__(byref))) __Block_byref_array_0 array = {(void*)0,(__Block_byref_array_0 *)&array, 33554432, sizeof(__Block_byref_array_0), __Block_byref_id_object_copy_131, __Block_byref_id_object_dispose_131, ((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)((NSMutableArray *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSMutableArray"), sel_registerName("alloc")), sel_registerName("init"))};

        block = (blk_t)((id (*)(id, SEL))(void *)objc_msgSend)((id)((void (*)(id))&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA, (__Block_byref_array_0 *)&array, 570425344)), sel_registerName("copy"));
    }

    ((void (*)(__block_impl *, id))((__block_impl *)block)->FuncPtr)((__block_impl *)block, ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init")));
    return 0;
}
```

##从中可以看出
* block 中捕获对象，外部定义的是什么就是什么，外部是weak，那么block中就是weak，外部是strong，那么block则就是strong
* 使用__block 修饰后，则可以在block中改变对象（也就是说可以在block中赋值新对象，如：可在block中array = [[NSMutableArray alloc] init];如果没__block修饰则不可以）