#  自我提问 

## iOS内存管理方式
iOS内存管理方式，引用计数的方式 有自动引用计数ARC和手动引用计数MRC。日常使用自动引用计数，编译器和Runtime协作在我们代码恰当的位置 加入retain release。runtime会维护一个散列表也就是SideTables 里面有引用计数表和弱引用计数表 对象被引用 指针指向时候加一 对象不再指向或者引用之后减一 一个引用对象在引用计数为0的时候被释放掉，回收内存。     
可能引发点 说说弱引用的实现？  说说引用计数表的实现？  autoreleasePush你了解过吗？ 内存泄漏问题？

## runtime源码 是怎么看的 总结一下你理解的？
*  

## load和initialize 调用时机
* 先说结论 load 在main方法之前调用 具体来说的话 就是在_objc_init()中注册runtime回调是调用的load_images 在mach-o 读取的关于非懒加载的类列表取出类方法load 加入到
load类列表中 加载顺序 层次加载 先父类再子类  然后到分类也差不多 一样 加载到load分类列表 最后逐个调用 顺序如插入全局列表一样 先父类 子类 分类
* initialize 的话 就是第一次发送消息的时候 就会调用（这里牵涉到消息发送内容）。 
可能引发点  

## 消息机制
*  

## 关于KVO的理解
* 主要涉及到isa混写技术 创建一个关于被监听对象类的一个子类NSKVOnNotifying_Singer 然后把该对象的isa指向这个生成的子类
其中重写setter方法 涉及到willchangevalueforkey 和 did changevalueforkey 然后就会通知外部的观察者   
* 同时重写它的class 方法 返回其父类 欺骗外部调用者 暂未改变
* SDMagicHook 就是基于这个思想来开发的 把待hook的方法 selector 的 函数调用地址 IMP 直接替换为_objc_msgForword 接着远方法肯定会走消息转发 自己实现消息转发 （修改Selector对应的IMP --- 不知道怎么描述好点）调用自己准备好的hook实现方法/如果要自己调用原方法  里面用到fishhook 去把这个_objc_setClass这个方法进行hook 因为自己加了一个类似月SDMagicHook的前缀 如果需要修改其objc的class 也就是对象的isa的时候 对应着来修改

## MVC模式和MVVM模式区别
* 对于MVC来说 M是model V是View视图 C是Controller，模型负责处理存储数据 View负责展示数据 C Controller负责协调两者之间的关系 从模型中获取数据 之后更新到view之中去 view中变化更新 也及时存在模型之中去。iOS中传统的三者关系的联动 分别是 view通过代理和（target-action）或者数据源跟C进行联动 C配合View的要求提供对应的数据。因为不断的发展 也许后面就会出现很多复杂的数据不再是简单的读取，涉及到数据逻辑的处理 或者解析 就也许融合进了C里去 造成越来越复杂的C 就需要一个新的方案来处理那就是MVVM。

* MVVM  M还是model，V是view（或者说VC也在） VM 是viewModel 那么C去哪里了 其实他还在只不过被弱化了感觉而已 因为现在数据解析或者说 数据怎么处理都是有VM来取代  VM协调者的角色 去双向绑定VIew 和 Model （ View获取数据 正向绑定，Model 更新数据 反向绑定）

补充知识：https://cloud.tencent.com/developer/article/1336232



