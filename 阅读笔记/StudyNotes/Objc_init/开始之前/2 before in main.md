#  iOS 程序 main 函数之前发生了什么


## dyld
dyld（the dynamic link editor），Apple 的动态链接器，系统 kernel 做好启动程序的初始准备后，交给 dyld 负责，援引并翻译《 Mike Ash 这篇 blog 》对 dyld 作用顺序的概括：

从 kernel 留下的原始调用栈引导和启动自己
将程序依赖的动态链接库递归加载进内存，当然这里有缓存机制
non-lazy 符号立即 link 到可执行文件，lazy 的存表里
Runs static initializers for the executable
找到可执行文件的 main 函数，准备参数并调用
程序执行中负责绑定 lazy 符号、提供 runtime dynamic loading services、提供调试器接口
程序main函数 return 后执行 static terminator
某些场景下 main 函数结束后调 libSystem 的 _exit 函数

## ImageLoader
当然这个 image 不是图片的意思，它大概表示一个二进制文件（可执行文件或 so 文件），里面是被编译过的符号、代码等，所以 ImageLoader 作用是将这些文件加载进内存，且每一个文件对应一个ImageLoader实例来负责加载。

两步走：
在程序运行时它先将动态链接的 image 递归加载 （也就是上面测试栈中一串的递归调用的时刻）
再从可执行文件 image 递归加载所有符号
当然所有这些都发生在我们真正的main函数执行前。

## runtime 与 +load
由 libSystem_initializer 逐步调用到了  ** _objc_init ** ，这里就是 objc 和 runtime 的初始化入口。
 dyld 担当了 runtime 和 ImageLoader 中间的协调者，当新 image 加载进来后交由 runtime 大厨去解析这个二进制文件的符号表和代码。
 
 整个调用栈和顺序：
1、 dyld 开始将程序二进制文件初始化
2、 交由 ImageLoader 读取 image，其中包含了我们的类、方法等各种符号
3、由于 runtime 向 dyld 绑定了回调，当 image 加载到内存后，dyld 会通知 runtime 进行处理
4、 runtime 接手后调用 map_images 做解析和处理，接下来 load_images 中调用 call_load_methods 方法，遍历所有加载进来的 Class，按继承层级依次调用 Class 的 +load 方法和其 Category 的 +load 方法
 至此，可执行文件中和动态库所有的符号（Class，Protocol，Selector，IMP，…）都已经按格式成功加载到内存中，被 runtime 所管理，再这之后，runtime 的那些方法（动态添加 Class、swizzle 等等才能生效）
 *****
## 关于 +load 方法的几个 QA

Q: 重载自己 Class 的 +load 方法时需不需要调父类？
A: runtime 负责按继承顺序递归调用，所以我们不能调 super

Q: 在自己 Class 的 +load 方法时能不能替换系统 framework（比如 UIKit）中的某个类的方法实现
A: 可以，因为动态链接过程中，所有依赖库的类是先于自己的类加载的

Q: 重载 +load 时需要手动添加 @autoreleasepool 么？
A: 不需要，在 runtime 调用 +load 方法前后是加了 objc_autoreleasePoolPush() 和 objc_autoreleasePoolPop() 的。

Q: 想让一个类的 +load 方法被调用是否需要在某个地方 import 这个文件
A: 不需要，只要这个类的符号被编译到最后的可执行文件中，+load 方法就会被调用（Reveal SDK 就是利用这一点，只要引入到工程中就能工作）

*****
整个事件由 dyld 主导，完成运行环境的初始化后，配合 ImageLoader 将二进制文件按格式加载到内存，
动态链接依赖库，并由 runtime 负责加载成 objc 定义的结构，所有初始化工作结束后，dyld 调用真正的 main 函数。
值得说明的是，这个过程远比写出来的要复杂，这里只提到了 runtime 这个分支，还有像 GCD、XPC 等重头的系统库初始化分支没有提及（当然，有缓存机制在，它们也不会玩命初始化），总结起来就是 main 函数执行之前，系统做了茫茫多的加载和初始化工作，但都被很好的隐藏了，我们无需关心。

当这一切都结束时，dyld 会清理现场，将调用栈回归 只剩下：孤独的 main 函数，看上去是程序的开始，确是一段精彩的终结 

出处
>>> http://blog.sunnyxx.com/2014/08/30/objc-pre-main/
