#  read_images
旧版本：对类 selector_references protocols objc_msgSend引用 进行加载和修正，  
其中获取编译好的类加入一个全局管理的哈希表中，对非懒加载的(有+load实现)的类进行识别，    
最后分类加载添加到对应的宿主类上去。    
新版本：差别在于 在识别阶段旧版本会methodizeClass 现在需要将ro（编译好的内容）中的方法列表、属性、协议等加载到我们rw中去。     
新版此时并不会将 ro这些内容进行处理 只会跟旧版本一样把ro复制到rw->ro中去。！！！如果这个类 没有load方法 没有分类     是不会存在rwx（rw->ext()）也就是跟旧版本区别点 rw中没有一份重复的 跟ro内容一样的，因为 rw中也有ro 所以他们做了优化是 无load 无分类       到时候需要用到列表、属性、协议直接去ro里面获取 （后面专门一篇文章进行讲述）

##  gdb_objc_realized_classes
```
int namedClassesSize = (isPreoptimized() ? unoptimizedTotalClasses : totalClasses) * 4 / 3;
gdb_objc_realized_classes = NXCreateMapTable(NXStrValueMapPrototype, namedClassesSize);
```
> 预先优化过的类不会加入到 gdb_objc_realized_classes 这个哈希表中来，
> gdb_objc_realized_classes 哈希表的装载因子为 0.75，这是一个经过验证的效率很高的扩容临界值。
> 除了 gdb_objc_realized_classes 表之外，还有一张表 allocatedClasses :
> 在新版的objc_已经调整到objc_init runtime.init()处理 robjc::allocatedClasses.init();
> 其实 gdb_objc_realized_classes 对 allocatedClasses 是一种包含的关系，一张是类的总表，一张是已经开辟了内存的类表，

## Discover classes 流程
1. 接着还是遍历所有的 Mach-O 的 header 部分
2. 然后通过 mustReadClasses 来判断哪些条件可以跳过读取类这一步骤（预检）非必需readclass就跳过
3. 遍历 _getObjc2ClassList 取出的所有的类
4. 读取 header 是否是 Bundle
5. 读取 header 是否开启了 预优化
6. 通过 readClass 来读取类信息
7. 判断如果不相等并且 readClass 结果不为空，则需要重新为类开辟内存

### readClass 
`在_read_images里面的readClass missingWeakSuperclass popFutureNamedClass `
`是不会进入 打断点可知 至于何时处理会进入 后期讨论`
> 其中涉及addNamedClass 把我们所有的Class 都存进一个gdb_objc_realized_classes的map中

> addClassTableEntry 已经分配了才进入 在所有类的表中添加一个类。如果addMeta为真，也自动添加类的元类。这里是不会进入的

**对于这个函数而言 封装起来被多处调用 有部分内容 并不是为readImages此方法所设立 **

![readClass_CallHierarchy.png](./../AllImages/readClass_CallHierarchy.png)
## Fix up remapped classes 流程
1. 通过 noClassesRemapped 方法判断是否有类引用(_objc_classrefs)需要进行重映射
2. 如果需要，则遍历 EACH_HEADER
3. 通过 _getObjc2ClassRefs 和 _getObjc2SuperRefs 取出当前遍历到的 Mach-O 的类引用和父类引用，然后调用 remapClassRef 进行重映射

## Fix up @selector references 流程
1. 遍历 EACH_HEADER
2. 如果开启了预优化，contiue 到下一个 Mach-O
3. 通过 _getObjc2SelectorRefs 拿到所有的 SEL 引用
4. 然后对所有的 SEL 引用调用 sel_registerNameNoLock 进行注册
5. 也就是说这一流程最主要的目的就是注册 SEL ，我们注册真正发生的地方: __sel_registerName
 
### __sel_registerName 方法的流程：
1. 判断是否要加锁
2. 如果 sel 为空，则返回一个空的 SEL
3. 从 builtins 中搜索，看是否已经注册过，如果找到，直接返回结果
4. 从 namedSelectors 哈希表中查询，找到了就返回结果
5. 如果 namedSelectors 未初始化，则创建一下这个哈希表
6. 如果上面的流程都没有找到，则需要调用 sel_alloc 来创建一下 SEL ，然后把新创建的 SEL 插入哈希表中进行缓存的填充

## Fix up old objc_msgSend_fixup call sites 流程
1. 遍历 EACH_HEADER
2. 通过 _getObjc2MessageRefs 方法来获取当前遍历到的 Mach-O 镜像的所有消息引用
3. 遍历这些消息引用，调用 fixupMessageRef 进行修正

## Discover protocols 流程
1. 遍历 EACH_HEADER
2. 通过 _getObjc2ProtocolList 方法来获取当前遍历到的 Mach-O 镜像的所有消息引用
3. 遍历这些消息引用，调用 readProtocol 进行读取

## Fix up @protocol references 流程
对所有的协议做重映射

## Realize non-lazy classes 流程
初始化非懒加载类( **+load** 方法和静态实例)

### realizeClass 新版名realizeClassWithoutSwift
`前部分`

1. 判断是否被处理过了 assert 出去了
2. 编译器期间就确认了cls ro 通过cls->data()取出 （内部有个bits 维护着对象相关数据）
3. ro->flags & RO_FUTURE 根据该变量与不同的标志位进行 & 操作判断 是否为元类，是否为根类，是否为ARC 是否为 future class 
4. 申请rw空间 rw中的ro设置为编译期间确认的ro
5. 接下来标识位和一些参数的设置

`后部分`

1. 递归调用realizeClass 为什么？说明下面的方法必须先父类 元类 先做 会对子类有影响
2. SUPPORT_NONPOINTER_ISA 关于这部分目前暂时跳过
3. 设置父类和元类 
4. reconcileInstanceVariables 关于成员变量（reconcile 调节一致）
`取出父类ro对比子类的ro instanceStart是否大于等于父类ro instanceSize`
` 运行到 ManSuperClass ro start = 8 super_ro instanceSize = 8 相同` 
`默认留有一定的空间也就是说 偏移的start 就是8 如果父类中 instanceSize`
`需求空间大于了8 都必须 进行偏移`
5. methodizeClass ro在上面步骤已经处理好了 现在需要将ro（编译好的内容）中的方法列表、属性、协议、分类（需要加入了全局分类map这里是未识别的才做处理 一开始是空的）等加载到我们rw中去。（新版本 还要区分于是否有load 是否分类 后面继续分析） ！！！在map_images阶段不进入分类 打断点可知 因为分类map是空的此时 

> 在新版本的objc中 mapimages中 rw->ext() 分配到才会有 估计时机延后 具体分析学习也进行延后到对应位置 

## Discover categories 流程
处理所有的分类，包括类和元类 
`Whether the initial attachment of categories present at startup has
`
> 在新版本之中加入了didInitialAttachCategories判断

> 在此处的 map_images作用不大 暂时忽略深入 ===》load images 中分析 



引用 https://blog.csdn.net/u011132324/article/details/104501248
