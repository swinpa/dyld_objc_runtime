#  loadAllCategories
加载所有的分类
> 新版objc 把加载分类的方法延迟到了    
> 完成_dyld_objc_notify_register调用之后   
> 旧版在map_images时候 就已经统一加载了    

全局header_info List 遍历一遍 调用 在mapImages时机存有
load_categories_nolock(hi);
## load_categories_nolock
    processCatlist(hi->catlist(&count));
    processCatlist(hi->catlist2(&count));
    两个匿名函数调用
如果分类中有类方法还是实例方法，协议，或者属性/是否有类属性，  
走如下流程

```
///class_t->data is class_rw_t, not class_ro_t.    
1、cls->isRealized() 说明已经经过realizeClassWithoutSwift
//将分类的方法添加到rw中的methods中去
调用attachCategories(cls, &lc, 1, ATTACH_EXISTING)；

2、如果没有realizeClassWithoutSwift
将其加入到全局的map ExplicitInitDenseMap<Class, category_list> 当中去
map class为key  cat_list 为value
cat_list ==>是一个经过优化locstamped_category_t数组

struct locstamped_category_t {
    category_t *cat;
    struct header_info *hi;
};
class category_list : nocopy_t {
    union {
        locstamped_category_t lc;
        struct {
            locstamped_category_t *array;
            // this aliases with locstamped_category_t::hi
            // which is an aliased pointer
            uint32_t is_array :  1;
            uint32_t count    : 31;
            uint32_t size     : 32;
        };
    } _u;
    ...
```

## attachCategories
 在旧版本中 先进行malloc 
 `    method_list_t **mlists = (method_list_t **)
        malloc(cats->count * sizeof(*mlists));
`
接着倒序遍历
新版本818以上   
Only a few classes have more than 64 categories during launch. This uses a little stack, and avoids malloc.  
做了如此优化 启动时候 极少数的分类大于64 个 避免malloc
大于64的先提前attachlists 把个数重置为0

    其中有一句  auto rwe = cls->data()->extAllocIfNeeded();
    获取分配空间的rwe 如果没有分配 会进行分配 也就是把ro的 迁移到rw
旧版中是倒序遍历 到了新版本 如何处理呢？    
mlists[ATTACH_BUFSIZ - ++mcount] 数组的最大值开始往回写入  
最终处理   
`   rwe->methods.attachLists(mlists + ATTACH_BUFSIZ - mcount, mcount);`  
指针数组的起始位置为 倒数第(mcount个数)个
### methods.attachLists
内部维护这一个list_array_tt 类型的  
` list_array_tt<method_t, method_list_t, method_list_t_authed_ptr>`

```
for (int i = oldCount - 1; i >= 0; i--)
                newArray->lists[i + addedCount] = array()->lists[i];
            for (unsigned i = 0; i < addedCount; i++)
                newArray->lists[i] = addedLists[i];
```
把前面的分类方法的数组添加到前面去 （所以这里就会在方法查找的时候 宿主类为什么痛同名方法被覆盖的原因）
