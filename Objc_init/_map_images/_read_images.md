#  read_images
关于map_images核心的部分
##  gdb_objc_realized_classes
`int namedClassesSize = (isPreoptimized() ?` 
`unoptimizedTotalClasses : totalClasses) * 4 / 3;`
`gdb_objc_realized_classes =
    NXCreateMapTable(NXStrValueMapPrototype, namedClassesSize);`

> 预先优化过的类不会加入到 gdb_objc_realized_classes 这个哈希表中来，
> gdb_objc_realized_classes 哈希表的装载因子为 0.75，这是一个经过验证的效率很高的扩容临界值。
> 除了 gdb_objc_realized_classes 表之外，还有一张表 allocatedClasses :
> 在新版的objc_已经调整到objc_init runtime.init()处理 robjc::allocatedClasses.init();
> 其实 gdb_objc_realized_classes 对 allocatedClasses 是一种包含的关系，一张是类的总表，一张是已经开辟了内存的类表，

## Discover classes 流程
接着还是遍历所有的 Mach-O 的 header 部分，然后通过 mustReadClasses 来判断哪些条件可以跳过读取类这一步骤（预检）非必需readclass就跳过
遍历 _getObjc2ClassList 取出的所有的类
读取 header 是否是 Bundle
读取 header 是否开启了 预优化
通过 readClass 来读取类信息
判断如果不相等并且 readClass 结果不为空，则需要重新为类开辟内存
### readClass 

## Fix up remapped classes 流程
通过 noClassesRemapped 方法判断是否有类引用(_objc_classrefs)需要进行重映射
如果需要，则遍历 EACH_HEADER
通过 _getObjc2ClassRefs 和 _getObjc2SuperRefs 取出当前遍历到的 Mach-O 的类引用和父类引用，然后调用 remapClassRef 进行重映射

## Fix up @selector references 流程
然后遍历 EACH_HEADER
如果开启了预优化，contiue 到下一个 Mach-O
通过 _getObjc2SelectorRefs 拿到所有的 SEL 引用
然后对所有的 SEL 引用调用 sel_registerNameNoLock 进行注册
也就是说这一流程最主要的目的就是注册 SEL ，我们注册真正发生的地方: __sel_registerName 
### __sel_registerName 方法的流程：
判断是否要加锁
如果 sel 为空，则返回一个空的 SEL
从 builtins 中搜索，看是否已经注册过，如果找到，直接返回结果
从 namedSelectors 哈希表中查询，找到了就返回结果
如果 namedSelectors 未初始化，则创建一下这个哈希表
如果上面的流程都没有找到，则需要调用 sel_alloc 来创建一下 SEL ，然后把新创建的 SEL 插入哈希表中进行缓存的填充

## Fix up old objc_msgSend_fixup call sites 流程
遍历 EACH_HEADER
通过 _getObjc2MessageRefs 方法来获取当前遍历到的 Mach-O 镜像的所有消息引用
然后遍历这些消息引用，然后调用 fixupMessageRef 进行修正

## Discover protocols 流程
遍历 EACH_HEADER
通过 _getObjc2ProtocolList 方法来获取当前遍历到的 Mach-O 镜像的所有消息引用
然后遍历这些消息引用，然后调用 readProtocol 进行读取

## Fix up @protocol references 流程
对所有的协议做重映射

## Realize non-lazy classes 流程
初始化非懒加载类( **+load** 方法和静态实例)
### realizeClass 新版名realizeClassWithoutSwift
#### methodizeClass 


## Discover categories 流程
处理所有的分类，包括类和元类 在新版本之中加入了didInitialAttachCategories判断 
Whether the initial attachment of categories present at startup has
在此处的 map_images作用不大 暂时忽略深入



引用 https://blog.csdn.net/u011132324/article/details/104501248
