##runtime初始化以及类分类初始化过程
####主要做了两件事：
	1. 注册类(类完整性处理：将分类信息合并到类中，将类的ro移到rw中)
	2. 执行+load方法

####过程大致如下：
* 在dyld完成链接后会执行可执行文件的初始化方法（initializeMainExecutable）
* 在initializeMainExecutable()过程中会先遍历sImageRoots容器中所有动态库image，并且执行image的runInitializers初始化函数
	* runInitializers() ->processInitializers()->recursiveInitialization()->doInitialization()->doModInitFunctions()
	* doModInitFunctions()中获取load command段标记为S_MOD_INIT_FUNC_POINTERS的段（存储的是函数指针）进行函数调用。在	   libSystem.dylib ，该函数指针对应_libSystem_initializer()
	* libSystem_initializer()->libdispatch_init()->_os_object_init()->_objc_init(),层层的调用，最终调用到了runtime的初始化方法_objc_init()，因此完成了运行时的回调注册_dyld_objc_notify_register(&map_images, load_images, unmap_image);
	* 在image的runInitializers过程中一定会确保libSystem.dylib会最先执行他的初始化方法libSystem_initializer()
* 在可执行文件跑完Initializers后会回调通知runtime，让他执行_dyld_objc_notify_register(&map_images, load_images, unmap_image);注册的map_images以及load_images方法，这样就能让runtime有机会对所有的类进行一些类完整性处理（比如将分类添加到类的方法列表中，构建rw,并且把ro信息付给rw，执行+load方法等等）

####类完整性处理(map_images)
```
map_images()
	-> map_images_nolock()
		-> _read_images()
			-> realizeClass(cls)
				-> reconcileInstanceVariables(cls, supercls, ro)//修正成员变量的offset(因为插入了父类的成员变量的offset)
				-> methodizeClass(cls)
```
调用栈大致如上，比较重要的几步就是realizeClass(cls)，reconcileInstanceVariables(cls, supercls, ro)，methodizeClass(cls)

* realizeClass(cls)阶段会设置类的class_rw_t数据，其实就是 alloc 一份class_rw_t，然后 将编译阶段确定好的类信息ro(class_ro_t)赋值给class_rw_t中的ro,然后将class_data_bits_t bits 指向片申请的class_rw_t内存空间
* 完成class_rw_t内存空间申请并赋值给类(objc_class)中的class_data_bits_t bits后，需要修正ro中当前类的成员变量的offset，因为在编译期间ro中只保存了当前类的成员变量的offset，并没有父类的成员变量的offset，所以需要在运行时，将父类的成员变量的offset放在当前类的成员变量的offset前面，所以这时就调用了reconcileInstanceVariables修正ro中成员变量的offset
* realizeClass(cls)中第二步需要做的就是，将分类中的方法，协议，属性添加到类中方法，协议，属性列表，添加顺序是倒序的，所以后编译的会在列表前面，另一个就是分类列表会在类的方法列表的前面，这就是为什么同名方法会先调用后编译的分类方法，或者说分类方法会比类方法先被调用。
* realizeClass(cls)过程中会
	* 遍历分类的实例方法，并将其添加到类(类对象)的methods列表中
	* 遍历分类的类方法，并将其添加到类的isa的methods列表中
	* 《也就是说，实例方法保存在类中，类方法保存在元类中》

##### class_rw_t以及class_ro_t中并没有类方法列表，只有methods，baseMethodList，所以类方法不存在类对象中，存在于元类的对象(也就是类，类也是一个对象)中的methods，baseMethodList，这个在编译期间已经确定的
