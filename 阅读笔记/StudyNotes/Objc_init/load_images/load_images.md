#  load_images
load_image 会对每个image进行加载 多次调用
``` 
if (!didInitialAttachCategories && didCallDyldNotifyRegister) {
        didInitialAttachCategories = true;
        loadAllCategories();
    }
```
> 新版objc 把加载分类的方法延迟到了    
> 完成_dyld_objc_notify_register调用之后   
> 旧版在map_images时候 就已经统一加载了    
> 所以本章节 要对loadAllCategories 进行分析

```
// Return without taking locks if there are no +load methods here.
if (!hasLoadMethods((const headerType *)mh))
	return;
```
> 判断没有load 方法直接return  
> _getObjc2NonlazyClassList 快速获取 来判断 
> _getObjc2NonlazyCategoryList

## prepare_load_methods
准备加载load相关方法    
1、加载非懒加载类的load方法。  
> 递归加载父类load方法  
> 把cls加入全局+load的类列表

2、加载分类的load方法。
> 取出分类的宿主类  
> realize宿主类（分类的宿主类不一定实现了load方法 因为 未实现的load的类在mapImages阶段 并不会realize）  
> 把cat加入全局+load的分类列表
> 
```
加入全局的load列表两者方式类似 
取出类方法 load是类方法 遍历selName == load即可
类 ==> ISA()->data()->ro()->baseMethods()
分类 ==>直接取出类列表 
```

## call_load_methods
> 先执行类的load方法
> 在执行分类的load方法





