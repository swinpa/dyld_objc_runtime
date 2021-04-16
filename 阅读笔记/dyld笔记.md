#dyld
##_main()逻辑
1. 全局的参数变量设置setContext(mainExecutableMH, argc, argv, envp, apple)
2. 执行权限检查（签名相关）
3.  检查环境变量（checkEnvironmentVariables）(依赖的动态库数量在这阶段得知)
	
		该阶段获取DYLD_FRAMEWORK_PATH，DYLD_INSERT_LIBRARIES(所有依赖的动态库的数量)
4. 初始化一些容器（sAllImages，sImageRoots）用来存放应用的image 以及所依赖的动态库的image
5. 根据应用的mach-o实例化成ImageLoader对象sMainExecutable（其实就是获取mach-o文件中的load command中的内容，然后用这些内容实例化ImageLoader），
     并添加到sAllImages中
6.  将所有依赖的动态库实例化成ImageLoader，并添加到sAllImages中（其实就是获取mach-o文件中的load command中的内容，然后用这些内容实例化ImageLoader）
7. 开始主程序sMainExecutable链接（link） 

		实际做的事情是如下两点：
		旧地址 + 偏移量 = 最终《实际地址》，《因为iOS系统有个随机地址偏移量？？？》
		this->recursiveRebase(context);
			  
		《占位地址》转成《实际地址》，
		（编译阶段，调用方使用外部符号时，无法知道外部符号地址，故只能先给个临时的占位地址，在加载的时候才能确定地址）
		this->recursiveBind(context, forceLazysBound, neverUnload);

8. 动态库链接
	
		遍历sAllImages中所有的动态库，并调用的他的link方法 image->link(gLinkContext, forceLazysBound, false, neverUnload, loaderRPaths);
		实际做的事情是如下两点：
		旧地址 + 偏移量 = 最终《实际地址》，《因为iOS系统有个随机地址偏移量？？？》
		this->recursiveRebase(context);
			  
		《占位地址》转成《实际地址》，
		（编译阶段，调用方使用外部符号时，无法知道外部符号地址，故只能先给个临时的占位地址，在加载的时候才能确定地址）
		this->recursiveBind(context, forceLazysBound, neverUnload);


9. 执行initializeMainExecutable(); 在initializeMainExecutable中遍历sImageRoots容器中所有image，并且执行image的runInitializers初始化函数
	* runInitializers() ->processInitializers()->recursiveInitialization()->doInitialization()->doModInitFunctions()
	* doModInitFunctions()中获取loadcommand段标记为S_MOD_INIT_FUNC_POINTERS的段（存储的是函数指针）进行函数调用。在libSystem.dylib ，该函数指针对应_libSystem_initializer
	* libSystem_initializer()->libdispatch_init()->_os_object_init()->_objc_init(),到此完成了运行时的回调注册_dyld_objc_notify_register(&map_images, load_images, unmap_image);



##Rebasing([参考文章](http://yulingtianxia.com/blog/2016/10/30/Optimizing-App-Startup-Time/))
在过去，会把 dylib 加载到指定地址，所有指针和数据对于代码来说都是对的，dyld 就无需做任何 fix-up 了。如今用了 ASLR 后会将 dylib 加载到新的随机地址(actual_address)，这个随机的地址跟代码和数据指向的旧地址(preferred_address)会有偏差，dyld 需要修正这个偏差(slide)，做法就是将 dylib 内部的指针地址都加上这个偏移量，偏移量的计算方法如下：

Slide = actual_address - preferred_address

然后就是重复不断地对 __DATA 段中需要 rebase 的指针加上这个偏移量。这就又涉及到 page fault 和 COW。这可能会产生 I/O 瓶颈，但因为 rebase 的顺序是按地址排列的，所以从内核的角度来看这是个有次序的任务，它会预先读入数据，减少 I/O 消耗。

##Binding
Binding 是处理那些指向 dylib 外部的指针，它们实际上被符号（symbol）名称绑定，也就是个字符串。之前提到 __LINKEDIT 段中也存储了需要 bind 的指针，以及指针需要指向的符号。dyld 需要找到 symbol 对应的实现，这需要很多计算，去符号表里查找。找到后会将内容存储到 __DATA 段中的那个指针中。Binding 看起来计算量比 Rebasing 更大，但其实需要的 I/O 操作很少，因为之前 Rebasing 已经替 Binding 做过了。