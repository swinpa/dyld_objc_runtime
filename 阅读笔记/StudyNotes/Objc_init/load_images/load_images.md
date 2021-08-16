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
  


