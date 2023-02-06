##分类定义

分类是Objective-C 2.0之后添加的语言特性。它的主要作用是为已经存在的类添加方法。

可以把分类的实现分开放在几个不同的文件里面。这样的做好处有：

可以减少单个文件的体积
可以把不同的功能组织到不同的category里
可以由多个开发者共同完成一个类（注意，一个类的多个分类中有重复的方法时，最后编译的分类中的方法才会被调用，分类中的方法会覆盖原有类的方法）
可以按需加载想要的category（分类）
声明私有方法

##category中添加属性的问题
* 分类中可以添加属性，但编译器不会为分类中的属性自动生成setter，getter 方法，也没有对应的成员变量生成
* 我们可以手动的给分类的属性添加setter，getter 方法，并在方法中通过运行时为其关联变量
- 关联方法如下
	* objc_setAssociatedObject(id _Nonnull object, const void * _Nonnull key,
                         id _Nullable value, objc_AssociationPolicy policy),底层调用了runtime的_object_set_associative_reference 方法，该方法在objc_references.mm中定义
	* objc_getAssociatedObject(id _Nonnull object, const void * _Nonnull key)
* 关联的大致原理如下
	* runtime中有一个名叫AssociationsManager 关联管理类，里面有一个static（静态）hashMap（static AssociationsHashMap *_map;）该哈希表存放着所有关联过属性的对象关联表，数据结构大致如下
	
	```
    typedef DenseMap<const void *, ObjcAssociation> ObjectAssociationMap;   
	AssociationsHashMap = [
		ObjectAssociationMap1 = [ //根据对象地址找到对应的ObjectAssociationMap
			ObjcAssociation,//在ObjectAssociationMap 中根据key找到对应的ObjcAssociation
			ObjcAssociation
		],
		ObjectAssociationMap2 = [
			ObjcAssociation,
			ObjcAssociation
		],
		ObjectAssociationMap3 = [
			ObjcAssociation,
			ObjcAssociation
		],
	]
	```
	```
	class ObjcAssociation {
		uintptr_t _policy;
		id _value;
    public:
    	ObjcAssociation(uintptr_t policy, id value) : _policy(policy), _value(value) {}
     	ObjcAssociation() : _policy(0), _value(nil) {}
     	uintptr_t policy() const { return _policy; }	
     	id value() const { return _value; }	
     	bool hasValue() { return _value != nil; }
   
    };

	```
	
* 关联时，根据当前对象地址，从AssociationsHashMap中找到对象对应的ObjectAssociationMap，然后再根据key，在
ObjectAssociationMap 中找到关联信息

### 如何把framework的私有方法公开？
* 在分类中定义一个方法跟私有方法同名的就可以了
### 如何把framework的私有属性（在扩展里面定义的属性）公开？
* 在分类中定义一个与私有属性同名的属性就可以了

###分类为什么不可以添加属性(成员变量)？
要回答这个问题，个人觉得应该从以下两个点回答

* 1，分类的本质(category_t)以及类的成员变量怎么存储，何时存储
*  2，分类设计的目的

第一点：分类的本质以及类成员变量的存储

* 分类的本质也是一个对象，它是category_t这个结构体的一个变量

编译期

```
struct _category_t {
	const char *name;
	struct _class_t *cls;
	const struct _method_list_t *instance_methods;
	const struct _method_list_t *class_methods;
	const struct _protocol_list_t *protocols;
	const struct _prop_list_t *properties;
};
```
运行时

```
struct category_t {
    const char *name;
    classref_t cls;
    struct method_list_t *instanceMethods;
    struct method_list_t *classMethods;
    struct protocol_list_t *protocols;
    struct property_list_t *instanceProperties;
    // Fields below this point are not always present on disk.
    struct property_list_t *_classProperties;
};

```
* 从这个两个阶段的分类结构体可以看出，苹果在设计分类时，并没有给分类添加存储变量的列表，只设计了存储实例方法的instanceMethods列表，存储类方法的classMethods列表，存储协议的protocols列表，存储属性的instanceProperties等
* 在编译的时候，编译器会把我们的分类转成一个静态的_category_t类型的一个全局变量

```
将分类中的方法转成静态的函数
static void _I_NSString_Ex_log(NSString * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_ NSString_Ex_e9f331_mi_0,((NSString *(*)(id, SEL))(void *)objc_msgSend)((id)self, sel_registerName("string")));
}
定义一个静态的存放方法的列表，列表元素指向静态函数地址
static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CATEGORY_INSTANCE_METHODS_NSString_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"log", "v16@0:8", (void *)_I_NSString_Ex_log}}
};
//分类是_category_t 的实例，
static struct _category_t _OBJC_$_CATEGORY_NSString_$_Ex __attribute__ ((used, section ("__DATA,__objc_const"))) = 
{
	"NSString",
	0, // &OBJC_CLASS_$_NSString,
	//分类中的instance_methods 指向了静态的存放分类方法的列表
	(const struct _method_list_t *)&_OBJC_$_CATEGORY_INSTANCE_METHODS_NSString_$_Ex,//
	0,
	0,
	0,
};
```
再说说类成员变量的存储

* 类成员变量是存储在类的rw->ro->ivar_list_t 这个列表中，而ro 是在编译器已经确定了的
编译期类信息

```
struct _ivar_t {
	unsigned long int *offset;  // pointer to ivar offset location
	const char *name;
	const char *type;
	unsigned int alignment;
	unsigned int  size;
};

struct _class_ro_t {
	unsigned int flags;
	unsigned int instanceStart;
	unsigned int instanceSize;
	const unsigned char *ivarLayout;
	const char *name;
	const struct _method_list_t *baseMethods;
	const struct _objc_protocol_list *baseProtocols;
	const struct _ivar_list_t *ivars;
	const unsigned char *weakIvarLayout;
	const struct _prop_list_t *properties;
};

struct _class_t {
	struct _class_t *isa;
	struct _class_t *superclass;
	void *cache;
	void *vtable;
	struct _class_ro_t *ro;
};
//为属性生成两个静态的变量

extern "C" unsigned long int OBJC_IVAR_$_Animal$_pAge __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Animal, _pAge);
extern "C" unsigned long int OBJC_IVAR_$_Animal$_name __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Animal, _name);

/*
 从这里可以看出类扩展的属性会存放到类的变量量表中
 同时也可以看出，类的成员变量在编译期就已经确定了，会存放在rw->ro->ivar_list 中
 生成一个存放变量信息的列表，里面的元素指向属性对应的静态变量
 */
static struct /*_ivar_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count;
	//由此可见，存放类成员变量的列表是一个数组，他的大小在编译期间已经确定了，
	//故在运行期间无法再向其中添加元素
	struct _ivar_t ivar_list[2];
} _OBJC_$_INSTANCE_VARIABLES_Animal __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_ivar_t),
	2,
	{{(unsigned long int *)&OBJC_IVAR_$_Animal$_pAge, "_pAge", "i", 2, 4},
	 {(unsigned long int *)&OBJC_IVAR_$_Animal$_name, "_name", "@\"NSString\"", 3, 8}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[10];
} _OBJC_$_INSTANCE_METHODS_Animal __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	10,
	{{(struct objc_selector *)"name", "@16@0:8", (void *)_I_Animal_name},
	{(struct objc_selector *)"setName:", "v24@0:8@16", (void *)_I_Animal_setName_},
	{(struct objc_selector *)"pAge", "i16@0:8", (void *)_I_Animal_pAge},
	{(struct objc_selector *)"setPAge:", "v20@0:8i16", (void *)_I_Animal_setPAge_}}
};
static struct _class_ro_t _OBJC_METACLASS_RO_$_Animal __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	1, sizeof(struct _class_t), sizeof(struct _class_t), 
	0, 
	"Animal",
	0, 
	0, 
	0, 
	0, 
	0, 
};
//类的ro数据
static struct _class_ro_t _OBJC_CLASS_RO_$_Animal __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	0, __OFFSETOFIVAR__(struct Animal, _pAge), sizeof(struct Animal_IMPL), 
	0, 
	"Animal",
	(const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Animal,
	0, 
	//将ro中的ivar_list指向静态的存放属性对应变量的列表
	(const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Animal,
	0, 
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Animal,
};
//创建一个类（类是一个对象，从这里就可以看出，而且还是一个单例）
extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Animal __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_Animal,
	0, // &OBJC_CLASS_$_NSObject,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	//将类的ro段指向静态的_class_ro_t 类型的变量
	&_OBJC_CLASS_RO_$_Animal,
};
static void OBJC_CLASS_SETUP_$_Animal(void ) {
	OBJC_METACLASS_$_Animal.isa = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Animal.superclass = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Animal.cache = &_objc_empty_cache;
	OBJC_CLASS_$_Animal.isa = &OBJC_METACLASS_$_Animal;
	OBJC_CLASS_$_Animal.superclass = &OBJC_CLASS_$_NSObject;
	OBJC_CLASS_$_Animal.cache = &_objc_empty_cache;
}
从这里就可以看出，对象的isa指向对象，类的isa指向元类，元类的isa 执行根元类，
```
第二点

* 分类设计的目的是把类的实现按不同的功能分散在不同的文件里面。从而可以减少单个文件的体积 ，也可以由多个开发者共同完成一个类 。
* 如果分类可以添加属性，那跟类就一样了，这点可以通过继承的方式扩展已有类的成员。明显的，苹果是不想这样设计 

// MRC
xcrun -sdk iphoneos clang -arch arm64 -rewrite-objc main.m

// ARC
xcrun -sdk iphoneos clang -arch arm64 -rewrite-objc -fobjc-arc -fobjc-runtime=ios-8.0.0 main.m
这会生成main.cpp

### 调用顺序

* 在运行时，mapImage阶段，分类中的方法，协议，属性会被添加到类中方法，协议，属性列表中，添加顺序是倒序的，所以后编译的会在列表前面，
另一个就是分类列表会在类的方法列表的前面，这就是为什么同名方法会先调用后编译的分类方法，或者说分类方法会比类方法先被调用。

### +load方法调用顺序

* 在调用+load方法前，会将类的+load方法添加到一个列表中， 分类的+load方法添加到另一个列表中

    类的+load方法
    在prepare类的+load方法时，是通过递归的方式，所以父类的+load方法会在列表的前面，因此，调用顺序是
    
    父类+load -> 当前类+load -> 先编译的分类+load -> 后编译的分类+load

### 分类跟主类都有同名方法，那怎么才能调用到主类方法而非分类方法？

* 通过运行时方法class_copyMethodList获取到方法列表，然后想调哪个就调哪个
