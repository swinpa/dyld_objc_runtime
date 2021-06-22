##KVO

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
3.   处理setter方法（用来在setter方法中添加willchangevalueforkey, didchangevalueforkey等代码来通知外部observer，具体是重写setter方法还是进行消息转发呢）
4.   重写NSKVONotifying_LWPerson 的class方法，让其返回父类，用来欺骗外部调用者，因为当isa指向NSKVONotifying_LWPerson后，如果外部使用[p class]， 如果不重写class，那么此时返回的是NSKVONotifying_LWPerson（用来欺骗外部，对象的class没有变）