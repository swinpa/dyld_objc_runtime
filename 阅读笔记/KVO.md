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
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context; 定义在foundation/NSKeyValueObserving.h
- GNUSTep中有对应的实现

1. 创建NSKVONotifying_LWPerson 子类
2.   将对象的isa 指向NSKVONotifying_LWPerson
	
	* 这目的应该是在消息查找时，可以查找到子类NSKVONotifying_LWPerson 中的setter方法
3.   处理setter方法（用来在setter方法中添加willchangevalueforkey, didchangevalueforkey等代码来通知外部observer，具体是重写setter方法还是进行消息转发呢）

	```
 
    @interface    GSKVOSetter : NSObject
    - (void) setter: (void*)val;
    - (void) setterChar: (unsigned char)val;
    - (void) setterDouble: (double)val;
    - (void) setterFloat: (float)val;
    - (void) setterInt: (unsigned int)val;
    - (void) setterLong: (unsigned long)val;
    #ifdef  _C_LNG_LNG
    - (void) setterLongLong: (unsigned long long)val;
    #endif
    - (void) setterShort: (unsigned short)val;
    - (void) setterRange: (NSRange)val;
    - (void) setterPoint: (NSPoint)val;
    - (void) setterSize: (NSSize)val;
    - (void) setterRect: (NSRect)rect;
    @end

	这里我用了“处理setter”这种说法，而不像网上很多的文章的说法“重写setter”是因为我个人的理解是：
	KVO是发生在运行时的，运行时没有重写这概念了，只可以通过运行时方式将setter重新指向别的已有的IMP中
	那么在GNUSTep的KVO源码中可以看到在完成第二步后会调用overrideSetterFor的方法将setter方法关联到
	GSKVOSetter中对应的类型方法中，比如setter的参数类型是double，那么就关联到setterDouble中，那么在
	GSKVOSetter 的 setterDouble方法内就会在赋值前调用willChangeValueForKey,赋值后调用
	didChangeValueForKey,
	```
	
	* 从GNUSTep源码来看，在overrideSetterFor: 方法中会将子类的setter方法通过class_addMethod(replacement, sel, imp, [sig methodType]) 将其指向GSKVOSetter 对应类型的setter方法，比如setterDouble:
	* 这就是为什么在断点的时候能看到NSSetIntValueAndNotify：这样的调用栈

4.   重写NSKVONotifying_LWPerson 的class方法，让其返回父类，用来欺骗外部调用者，因为当isa指向NSKVONotifying_LWPerson后，如果外部使用[p class]， 如果不重写class，那么此时返回的是NSKVONotifying_LWPerson

	这样做的目的：
	1. 用来欺骗外部，对象的class没有变
	2. 在setterInt: 方法中，通过[self class] 能拿到原本的LWPerson类，再通过[LWPerson instanceMethodForSelector: _cmd]; 能获取LWPerson 原本的setter方法 setAge:从而使用setAge进行赋值，也就是NSKVONotifying_LWPerson 中setAge:对应的IMP为setterInt: 的IMP，LWPerson 对应的仍是原本的setAge:的IMP

    第二点才是重写class的根本目的吧

###GNUSTep 中overrideSetterFor: (NSString*)aKey 逻辑

1. 获取方法签名
2. 根据签名中的参数类型获取GSKVOSetter类 对应的方法IMP
3. 通过class_addMethod(replacement, sel, imp, [sig methodType])将子类对应的setter 绑定对对应的IMP上
	
	比如setAge:(Int)age，这会绑定到GSKVOSetter  中的setterInt:，而在setterInt:中会有willchangeValueForKey didChangeValueForKey的调用

###KVO思想延伸出来的一些开源库
1. Aspects -- 轻量级的hook现有方法的库，可以hook类方法，实例方法
2. SDMagicHook

###KVO在MVVM模式中扮演的角色

###KVO使用过程中需要注意的点
1. KVO 添加次数和移除次数不匹配:
	
	* 移除了未注册的观察者，导致崩溃。
	* 重复移除多次，移除次数多于添加次数，导致崩溃。
	* 重复添加多次，虽然不会崩溃，但是发生改变时，也同时会被观察多次。
	
2. 被观察者提前被释放，被观察者在 dealloc 时仍然注册着 KVO，导致崩溃
3. 添加了观察者，但未实现 observeValueForKeyPath:ofObject:change:context: 方法，导致崩溃
4. 添加或者移除时 keypath == nil，导致崩溃

[参考1](https://www.jianshu.com/p/c9d9c6e4dab8)
[iOS 开发：『Crash 防护系统』（二）KVO 防护](https://www.jianshu.com/p/e3713d309283)

