###应用启动过程
1. 内核创建一个进程,分配空间,根据mach-o的LC\_SEGMENT段将mach-o的各段映射到分配的虚
	拟内存空间中，根据LC\_LOAD\_DYLDINKER段中指定的dyld路径(/usr/lib/dyld)调用dyld
	将执行权限转交给dyld,让dyld给主程序链接主程序依赖的动态库，dyld处理完后返回主程序的入口地址，
	从此执行权限转交到主程序，开始运行主程序进入main阶段

	[很好的加载过程文章](https://www.jianshu.com/p/8498cec10a41)

	更具体一点的
	
	```
	1. 系统内核从调用exec_mach_imgact()开始（在kern_exec.c中定义）
		在__mac_execve()中创建image_params，然后调用exec_activate_image(image_params *imgp)
		在exec_activate_image()中通过(*execsw[i].ex_imgact)(imgp);的方式调用到exec_mach_imgact()方法
			struct execsw {
				int(*const ex_imgact)(struct image_params *);
				const char *ex_name;
			}const execsw[] = {
				{ exec_mach_imgact, "Mach-o Binary" },
				{ exec_fat_imgact, "Fat Binary" },
				{ exec_shell_imgact, "Interpreter Script" },
				{ NULL, NULL}
			};
		
			
			
		在exec_mach_imgact中各种判断，magic魔数判断，filetype判断，cputype判断等等
		各种判断通过后通过【创建进程】
		imgp->ip_new_thread = fork_create_child(task,
		    NULL,
		    p,
		    FALSE,
		    (imgp->ip_flags & IMGPF_IS_64BIT_ADDR),
		    (imgp->ip_flags & IMGPF_IS_64BIT_DATA),
		    FALSE)
		 
	2. 内核通过在execoad_machfile()加载macho
		
	   内核加载器只关心几条load command，如LC_SEGMENT，LC_LOAD_DYLDINKER
		
	3. 在load_machfile中进行如下操作
	
		1. 创建虚拟内存空间
		2. 生成aslr需要的随机数
		3. 调用parse_machfile()解析macho中的内核部分的load command
	4. 在parse_machfile执行如下操作
		
		1. 会先将load command映射到内核的内存中
		/*
	 	 * Map the load commands into kernel memory.
	 	 */
		addr = kalloc(alloc_size);
		2. 遍历load command
			
		    1. 根据LC_SEGMENT的描述将各段映射到进程内存空间（虚拟内存空间）
		    	map_segment()
		    
		    2. 根据LC_LOAD_DYLDINKER中描述的dyld路径(/usr/lib/dyld)调用dyld
		   	   将执行权限转交给dyld,让dyld给主程序链接主程序依赖的动态库
		3. dyld处理完后返回主程序的入口地址，从此执行权限转交到主程序
	
	5. 根据dyld返回的主程序入口地址，开始进入主程序执行
	
	```
	[About the app launch sequence](https://developer.apple.com/documentation/uikit/app_and_environment/responding_to_the_launch_of_your_app/about_the_app_launch_sequence/)
2. 进入main后，执行如下步骤
	
		1. 实例化UIApplication，设置代理AppDelegate，开启主线程RunLoop，
		2. 加载info.plist设置的storyboard
		3. 回调代理执行willFinishLaunchingWithOptions，didFinishLaunchingWithOptions:
		4. 在didFinishLaunchingWithOptions中一般会做
			1. SDK注册
			2. 组件注册
			3. 推送注册
			4. 创建window，设置rootViewController，自此进入首页渲染，
			   在首页的viewdidload中进行视图创建，数据加载等操作
			5. 
		5. 
3.  

# dyld
## _main()逻辑
1. 全局的参数变量设置setContext(mainExecutableMH, argc, argv, envp, apple)
2. 执行权限检查（签名相关）
3. 检查环境变量（checkEnvironmentVariables）(依赖的动态库数量在这阶段得知)
	
		该阶段获取DYLD_FRAMEWORK_PATH，DYLD_INSERT_LIBRARIES(所有依赖的动态库的数量)

4. 初始化一些容器（sAllImages，sImageRoots）用来存放应用的image 以及所依赖的动态库的image
5. 根据应用的mach-o实例化成ImageLoader对象sMainExecutable（其实就是获取mach-o文件中的load command中的内容，
	然后用这些内容实例化ImageLoader），并添加到sAllImages中
	
	```
	// instantiate an image
		ImageLoader* image = ImageLoaderMachO::instantiateFromFile(path, fd, firstPage, fileOffset, fileLength, stat_buf, gLinkContext);
	```
	
6.  将所有依赖的动态库实例化成ImageLoader，并添加到sAllImages中（其实就是获取mach-o文件中的load command中的内容，
	然后用这些内容实例化ImageLoader）
	
	```
	// instantiate an image
		ImageLoader* image = ImageLoaderMachO::instantiateFromFile(path, fd, firstPage, fileOffset, fileLength, stat_buf, gLinkContext);
	```
7. 开始主程序sMainExecutable链接（link） 


		实际做的事情是如下两点：
		
		1. rebase
		旧地址 + 偏移量 = 最终《实际地址》，《因为iOS系统有个随机地址偏移量？？？》
		this->recursiveRebase(context);
		ImageLoaderMachO::doRebase(const LinkContext& context)
			-> void ImageLoaderMachOCompressed::rebase(const LinkContext& context)
				-> ImageLoaderMachOCompressed::rebaseAt(const LinkContext& context, uintptr_t addr, uintptr_t slide, uint8_t type)
		
		更确切的说是获取segment_command_64.vmaddr，然后进行修正
		因为vmaddr 是在内核在parse_machfile()阶段将
			  
		2. bind
		《占位地址》转成《实际地址》，
		（编译阶段，调用方使用外部符号时，无法知道外部符号地址，故只能先给个临时的占位地址，在加载的时候才能确定地址）
		this->recursiveBind(context, forceLazysBound, neverUnload);
		
		
		ASLR(Address Space Layout Randomization)地址空间布局随机化，其实就
		是当Mach-O文件载入虚拟内存的时候，起始地址不从0x00000000开始了，而是随
		机增加一段，例如从0x50000开始，后面的函数地址都会增加0x50000

8. 动态库链接
	
		遍历sAllImages中所有的动态库，并调用的他的link方法 image->link(gLinkContext, forceLazysBound, false, neverUnload, loaderRPaths);
		实际做的事情是如下两点：
		1. rebase
		旧地址 + 偏移量 = 最终《实际地址》，《因为iOS系统有个随机地址偏移量？？？》
		this->recursiveRebase(context);
			  
		2. bind《占位地址》转成《实际地址》，
			编译阶段，调用方使用外部符号时，无法知道外部符号地址，故只能先给个临时的占位地址，
			在加载的时候才能确定地址）
			this->recursiveBind(context, forceLazysBound, neverUnload);
			
			为了性能考虑，动态绑定过程绑定的符号是非懒加载的符号(一般是数据)，懒加载符号(一般是函数调用)的绑定发生在
			第一次使用的时候
			因为模块间的数据访问很少（模块间还提供很多全局变量给其它模块用，那耦合度太大了，所以这样的情况很少见），
			所以外部数据地址，都是放到got（也称Non-Lazy Symbol Pointers）数据段，非惰性的，动态链接阶段，
			就寻找好所有数据符号的地址；而模块间函数调用就太频繁了，就用了延迟绑定技术，将外部函数地址都放在
			la_symbol_ptr(Lasy Symbol Pointers)数据段，惰性的，程序第一次调用到这个函数，才寻址函数地址，
			然后将地址写入到这个数据段


9. 执行initializeMainExecutable(); 在initializeMainExecutable中遍历sImageRoots容器中所有image，并且执行image的runInitializers初始化函数
	* runInitializers() ->processInitializers()->recursiveInitialization()->doInitialization()->doModInitFunctions()
	* doModInitFunctions()中获取loadcommand段标记为S_MOD_INIT_FUNC_POINTERS的段（存储的是函数指针）进行函数调用。在libSystem.dylib ，该函数指针对应_libSystem_initializer
	* libSystem_initializer()->libdispatch_init()->_os_object_init()->_objc_init(),到此完成了运行时的回调注册_dyld_objc_notify_register(&map_images, load_images, unmap_image);

* 断点查看+load调用栈如下：

	```
	1. dyldbooststrap::start(macho_header const*, int, char...)
	2. dyld::_main()
	3. dyld::initializeMainExecutable()
	4. ImageLoader::runInitializers()
	5. ImageLoader::recursiveInitialization
	6. dyld::notifySingle()
	7. load_images
	8. call_load_methods
	9. +[xxx load]
	
	```



##Rebasing([参考文章](http://yulingtianxia.com/blog/2016/10/30/Optimizing-App-Startup-Time/))
在过去，会把 dylib 加载到指定地址，所有指针和数据对于代码来说都是对的，dyld 就无需做任何 fix-up 了。如今用了 ASLR 后会将 dylib 加载到新的随机地址(actual_address)，这个随机的地址跟代码和数据指向的旧地址(preferred_address)会有偏差，dyld 需要修正这个偏差(slide)，做法就是将 dylib 内部的指针地址都加上这个偏移量，偏移量的计算方法如下：

Slide = actual_address - preferred_address

然后就是重复不断地对 __DATA 段中需要 rebase 的指针加上这个偏移量。这就又涉及到 page fault 和 COW。这可能会产生 I/O 瓶颈，但因为 rebase 的顺序是按地址排列的，所以从内核的角度来看这是个有次序的任务，它会预先读入数据，减少 I/O 消耗。

##Binding
Binding 是处理那些指向 dylib 外部的指针，它们实际上被符号（symbol）名称绑定，也就是个字符串。之前提到 __LINKEDIT 段中也存储了需要 bind 的指针，以及指针需要指向的符号。dyld 需要找到 symbol 对应的实现，这需要很多计算，去符号表里查找。找到后会将内容存储到 __DATA 段中的那个指针中。Binding 看起来计算量比 Rebasing 更大，但其实需要的 I/O 操作很少，因为之前 Rebasing 已经替 Binding 做过了。

##静态链接
* [参考文章](https://juejin.cn/post/6844903912198127623)
* 链接的目的是将多个目标文件(.o文件)链接成一个可执行文件 
* 编译期间，模块内使用模块外部的符号(函数，变量)时是不知道它的地址的，此时只有先用占位符，等到链接时才确定

##dyld在项目中的应用场景
* 通过_dyld_register_func_for_add_image添加监听回调，监听所有的image ，从而判断是否有未知的第三方动态库被加载进来，破坏应用的完整性 
* 根据ImageLoader 中的bool ImageLoader::containsAddress(const void* addr) const方法可以判断指定地址是不是在某个动态库上
	
		1. 通过获取image的开始地址与结束地址，然后将当前地址跟开始地址与结束地址比较，看它在不在他们之间

* 越狱检测

    ```
    _dyld_image_count返回dyld映射的当前的image数
    _dyld_get_image_name返回image名称，可以通过它来检索dyld的image名称
    ```
    ####可以通过检测目录中是否有MobileSubstrate.dylib来确认是否越狱，代码参考如下
    ```
    void dylibCheck() {
        uint32_t count = _dyld_image_count();
        char *substrate = "/Library/MobileSubstrate/MobileSubstrate.dylib";
        for(uint32_t i = 0; i < count; i++) {
            const char *dyld = _dyld_get_image_name(i);
            if (strcmp(dyld,substrate)==0) { 
                NSLog(@"该设备已越狱"); 
              }
         } 
    }
    ```
    
###关于安全的一点参考文章[应用安全检测](https://hello-sherlock.github.io/2017/03/22/eight-Blog/)

https://blog.csdn.net/A1553225534/article/details/104187054

###[关于DYLD,以及一些mach-o中的一些section的说明](http://www.newosxbook.com/articles/DYLD.html#footnote)

###启动优化的文章

[iOS App 启动优化 - 阿里云云栖号](https://baijiahao.baidu.com/s?id=1716928011037277248&wfr=spider&for=pc)

[bind 过程懒加载符号以及非懒加载符号](https://blog.csdn.net/u011774517/article/details/117088565)

[懒加载符号绑定过程](https://zhuanlan.zhihu.com/p/386785443)

[MachO详解以及使用](https://juejin.cn/post/6844903910537166861)

[iOS程序员的自我修养-MachO文件结构分析](https://juejin.cn/post/6844903912189722637)



###熟悉MachO可以做什么
1. Category的方法覆盖检查
2. 包瘦身,无用代码检查
3. 代码覆盖率静态检查
4. bitcode分析
5. crash符号化
7. 符号模块查找
8. 非OC函数switch
9. 包支持架构分析
10. 常量字符串分析
11. 进程启动速度优化
12. 学习经典的数据结构

