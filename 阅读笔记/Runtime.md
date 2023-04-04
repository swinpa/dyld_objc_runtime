###Runtime

##### 调用栈

1. _objc_init() 中通过_dyld_objc_notify_register(&map_images, load_images, unmap_image);
   
   向dyld注册了回调map_images，load_images，unmap_image。这些回调会再dyld执行到对应的阶段，由dyld调用，通知Runtime。Runtime在收到回调后就可以做相应的事情
2. 

##### 初始化过程（map_images）

1. Runtime在收到map_image的回调时实际在map_image中调用map_images_nolock做具体的事情
	map_image() -> map_images_nolock()
2. map_images_nolock()整个过程做了如下事情：
	
	1. 根据mach_header得到header_info（要么从dyld的缓存中获取，要么从mach-o中对应的段中获取）
	2. 得到header_info后通过_read_images()读取image中的类信息
	3. _read_images
		
		1. 通过classref_t *classlist = _getObjc2ClassList(hi, &count);方式读取image中的类列表（从mach-o中的__objc_classlist段中读取）
	4. 
3. 