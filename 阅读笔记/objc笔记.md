
美团面试问题：为什么Objective-C中有Class和MetaClass这种设计？去掉是否可以？

* C++中通过虚函数表来实现类似的功能

* 在Objective-C 中，普通的对象是类的实例，而类也是一个对象，他是_class_t的一个实例，元类(MetaClass)也是一个对象，也是_class_t的一个实例
* 我们通常认识的，对象的isa 指向类，类的isa 指向其元类，元类的isa指向根元类，那么具体指向（也就是赋值）是在什么时候发生的呢？

	* 普通对象在对象创建时(也就是alloc时)将isa 指向类
	*  类是一个对象，那类这个对象又是什么时候创建的呢？ 而类的初始化，在编译期间，编译器将类声明一个静态的

Objective-C 是一门动态语音，他的动态特性之一就是对象在发送消息时，最终确定调用哪个方法体的是通过判断对象是属于什么类（class），然后去
去对应的方法列表中查找对应的方法实现，也就是对象的方法列表存储在类中

* Class
	* |---> \class\_data\_bits\_t
		* ---> class\_rw\_t
			* ---> method_array\_t

* 对象在alloc 时，在申请完空间后，会调用initInstanceIsa()方法将对象的isa 指向他所属的类

* |-->alloc()
	* |-->\_objc_rootAlloc(Class cls) 
		* |--> callAlloc(Class cls, bool checkNil, bool allocWithZone=false)
			* 1 直接使用底层接口申请空间
				* 通过id obj = (id)calloc(1, cls->bits.fastInstanceSize());申请空间
				* 然后通过obj->initInstanceIsa(cls, dtor);设置ISA值
			* 2
				* + (id)allocWithZone:(struct _NSZone *)zone
					* objc_rootAllocWithZone(Class cls, malloc_zone_t *zone)
						* class_createInstanceFromZone(Class cls, size_t extraBytes, void *zone, bool cxxConstruct = true,  size_t *outAllocatedSize = nil) 
						* 最终还是会通过id obj = (id)calloc(1, cls->bits.fastInstanceSize());申请空间，然后通过obj->initInstanceIsa(cls, dtor);设置ISA值
