##KVO[官方文档](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueObserving/Articles/KVOImplementation.html)

```
@interface LWPerson:NSObject
@property (nonatomic, assign) int age;
@end

@implementation LWPerson
@end

LWPerson *p = [[LWPerson alloc] init];
NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
[p addObserver:self forKeyPath:@"age" options:options context:nil];
p.age = 100;

```

###4步走
1. 创建NSKVONotifying_LWPerson 子类
2.   将对象的isa 指向NSKVONotifying_LWPerson
	
	* 这目的应该是在消息查找时，可以查找到子类NSKVONotifying_LWPerson 中的setter方法
3.   处理setter方法（用来在setter方法中添加willchangevalueforkey, didchangevalueforkey等代码来通知外部observer，具体是重写setter方法还是进行消息转发呢）
	
	* 从GNUSTep源码来看，在overrideSetterFor: 方法中会将子类的setter方法通过class_addMethod(replacement, sel, imp, [sig methodType]) 将其指向GSKVOSetter 对应类型的setter方法，比如setterInt:
	* 这就是为什么在断点的时候能看到NSSetIntValueAndNotify：这样的调用栈
4.   重写NSKVONotifying_LWPerson 的class方法，让其返回父类，用来欺骗外部调用者，因为当isa指向NSKVONotifying_LWPerson后，如果外部使用[p class]， 如果不重写class，那么此时返回的是NSKVONotifying_LWPerson

	这样做的目的：
	1. 用来欺骗外部，对象的class没有变
	2. 在setterInt: 方法中，通过[self class] 能拿到原本的LWPerson类，再通过[LWPerson instanceMethodForSelector: _cmd]; 能获取LWPerson 原本的setter方法 setAge:从而使用setAge进行赋值，也就是NSKVONotifying_LWPerson 中setAge:对应的IMP为setterInt: 的IMP，LWPerson 对应的仍是原本的setAge:的IMP


###GNUSTep 中overrideSetterFor: (NSString*)aKey 逻辑

1. 获取方法签名
2. 根据签名中的参数类型获取GSKVOSetter类 对应的方法IMP
3. 通过class_addMethod(replacement, sel, imp, [sig methodType])将子类对应的setter 绑定对对应的IMP上
	
	比如setAge:(Int)age，这会绑定到GSKVOSetter  中的setterInt:，而在setterInt:中会有willchangeValueForKey didChangeValueForKey的调用

###KVO思想延伸出来的一些开源库
1. Aspects -- 轻量级的hook现有方法的库，可以hook类方法，实例方法
2. SDMagicHook

###KVO在MVVM模式中扮演的角色
