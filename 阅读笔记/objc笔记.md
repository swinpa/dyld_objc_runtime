
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

## 类单例声明，元类等源码
### 声明两个类
```
@interface Person:NSObject
@property(nonatomic, assign) int age;
-(void)instanceFunc;
+(void)clsFunc;
@end

@implementation Person
-(void)instanceFunc {
    NSLog(@"hello class");
}
+(void)clsFunc {
    NSLog(@"hello instance");
}
@end

@interface Man:Person
@property(nonatomic, copy) NSString* name;
-(void)m_instanceFunc;
+(void)m_clsFunc;
@end

@implementation Man
-(void)m_instanceFunc {
    NSLog(@"hello Man instance");
}
+(void)m_clsFunc {
    NSLog(@"hello Man class");
}
@end
```
### 最终编译器转化成如下(xcrun --sdk iphoneos clang -arch arm64 -rewrite-objc main.m -o main.cpp)
```
#ifndef _REWRITER_typedef_Person
#define _REWRITER_typedef_Person
typedef struct objc_object Person;
typedef struct {} _objc_exc_Person;
#endif

extern "C" unsigned long OBJC_IVAR_$_Person$_age;
struct Person_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	int _age;
};

// @property(nonatomic, assign) int age;
// -(void)instanceFunc;
// +(void)clsFunc;

/* @end */
// @implementation Person


static void _I_Person_instanceFunc(Person * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_main_812e86_mi_0);
}

static void _C_Person_clsFunc(Class self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_main_812e86_mi_1);
}

static int _I_Person_age(Person * self, SEL _cmd) { return (*(int *)((char *)self + OBJC_IVAR_$_Person$_age)); }
static void _I_Person_setAge_(Person * self, SEL _cmd, int age) { (*(int *)((char *)self + OBJC_IVAR_$_Person$_age)) = age; }
// @end

#ifndef _REWRITER_typedef_Man
#define _REWRITER_typedef_Man
typedef struct objc_object Man;
typedef struct {} _objc_exc_Man;
#endif

extern "C" unsigned long OBJC_IVAR_$_Man$_name;
struct Man_IMPL {
	struct Person_IMPL Person_IVARS;
	NSString *_name;
};

// @property(nonatomic, copy) NSString* name;
// -(void)m_instanceFunc;
// +(void)m_clsFunc;
/* @end */

// @implementation Man

static void _I_Man_m_instanceFunc(Man * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_main_812e86_mi_2);
}
static void _C_Man_m_clsFunc(Class self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_2c_54s_9yqd2ts63jncfvr4k10c0000gn_T_main_812e86_mi_3);
}
static NSString * _I_Man_name(Man * self, SEL _cmd) { return (*(NSString **)((char *)self + OBJC_IVAR_$_Man$_name)); }
extern "C" __declspec(dllimport) void objc_setProperty (id, SEL, long, id, bool, bool);

static void _I_Man_setName_(Man * self, SEL _cmd, NSString *name) { 
    objc_setProperty (self, _cmd, __OFFSETOFIVAR__(struct Man, _name), (id)name, 0, 1); 
}
// @end

int main(int argc, const char * argv[]) {

    Person *p1 = ((Person *(*)(id, SEL))(void *)objc_msgSend)((id)((Person *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("Person"), sel_registerName("alloc")), sel_registerName("init"));
    ((void (*)(id, SEL))(void *)objc_msgSend)((id)p1, sel_registerName("instanceFunc"));
    ((void (*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("Person"), sel_registerName("clsFunc"));
    return 0;
}

struct _prop_t {
	const char *name;
	const char *attributes;
};

struct _protocol_t;

struct _objc_method {
	struct objc_selector * _cmd;
	const char *method_type;
	void  *_imp;
};

struct _protocol_t {
	void * isa;  // NULL
	const char *protocol_name;
	const struct _protocol_list_t * protocol_list; // super protocols
	const struct method_list_t *instance_methods;
	const struct method_list_t *class_methods;
	const struct method_list_t *optionalInstanceMethods;
	const struct method_list_t *optionalClassMethods;
	const struct _prop_list_t * properties;
	const unsigned int size;  // sizeof(struct _protocol_t)
	const unsigned int flags;  // = 0
	const char ** extendedMethodTypes;
};

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

struct _category_t {
	const char *name;
	struct _class_t *cls;
	const struct _method_list_t *instance_methods;
	const struct _method_list_t *class_methods;
	const struct _protocol_list_t *protocols;
	const struct _prop_list_t *properties;
};
extern "C" __declspec(dllimport) struct objc_cache _objc_empty_cache;
#pragma warning(disable:4273)

extern "C" unsigned long int OBJC_IVAR_$_Person$_age __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Person, _age);

static struct /*_ivar_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count;
	struct _ivar_t ivar_list[1];
} _OBJC_$_INSTANCE_VARIABLES_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_ivar_t),
	1,
	{{(unsigned long int *)&OBJC_IVAR_$_Person$_age, "_age", "i", 2, 4}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[3];
} _OBJC_$_INSTANCE_METHODS_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	3,
	{{(struct objc_selector *)"instanceFunc", "v16@0:8", (void *)_I_Person_instanceFunc},
	{(struct objc_selector *)"age", "i16@0:8", (void *)_I_Person_age},
	{(struct objc_selector *)"setAge:", "v20@0:8i16", (void *)_I_Person_setAge_}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CLASS_METHODS_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"clsFunc", "v16@0:8", (void *)_C_Person_clsFunc}}
};

static struct /*_prop_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count_of_properties;
	struct _prop_t prop_list[1];
} _OBJC_$_PROP_LIST_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_prop_t),
	1,
	{{"age","Ti,N,V_age"}}
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	1, sizeof(struct _class_t), sizeof(struct _class_t), 0, 
	"Person",
	(const struct _method_list_t *)&_OBJC_$_CLASS_METHODS_Person,
	0, 0, 0, 0, 
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Person __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	0, __OFFSETOFIVAR__(struct Person, _age), sizeof(struct Person_IMPL), 
	0, 
	"Person",
	(const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Person,
	0, 
	(const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Person,
	0, 
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Person,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Person __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_NSObject,
	0, // &OBJC_METACLASS_$_NSObject,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_METACLASS_RO_$_Person,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_CLASS_$_NSObject;

/*
 1, extern "C"后，会指示编译器这部分代码按C语言的进行编译，而不是C++的
 2, 用__declspec(align(#))精确控制用户自定数据的对齐方式 ，#是对齐值。
 3, __attribute__是一个编译器指令，用于在C、C++、Objective-C中修饰变量、函数、参数、方法、类等。
 这里表示将_class_t 类型的 OBJC_CLASS_$_Person 变量放到指定的段中（也就是放在数据段中的__objc_data 段中）
 同时，这也表明了，类是一个对象，是一个单例对象，他存储在数据段中的__objc_data 段中
 
 Functions or Data marked with __attribute__((used)) are tagged in the object file to avoid removal by linker unused section removal.
 指示编译器在对象文件中保留静态函数or变量，即使将该函数or变量没有被引用也是如此。

 
 
 */
extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Person __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_Person,
	0, // &OBJC_CLASS_$_NSObject,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_CLASS_RO_$_Person,
};
static void OBJC_CLASS_SETUP_$_Person(void ) {
	OBJC_METACLASS_$_Person.isa = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Person.superclass = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Person.cache = &_objc_empty_cache;
	
    OBJC_CLASS_$_Person.isa = &OBJC_METACLASS_$_Person;
	OBJC_CLASS_$_Person.superclass = &OBJC_CLASS_$_NSObject;
	OBJC_CLASS_$_Person.cache = &_objc_empty_cache;
}

extern "C" unsigned long int OBJC_IVAR_$_Man$_name __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Man, _name);

static struct /*_ivar_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count;
	struct _ivar_t ivar_list[1];
} _OBJC_$_INSTANCE_VARIABLES_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_ivar_t),
	1,
	{{(unsigned long int *)&OBJC_IVAR_$_Man$_name, "_name", "@\"NSString\"", 3, 8}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[3];
} _OBJC_$_INSTANCE_METHODS_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	3,
	{{(struct objc_selector *)"m_instanceFunc", "v16@0:8", (void *)_I_Man_m_instanceFunc},
	{(struct objc_selector *)"name", "@16@0:8", (void *)_I_Man_name},
	{(struct objc_selector *)"setName:", "v24@0:8@16", (void *)_I_Man_setName_}}
};

static struct /*_method_list_t*/ {
	unsigned int entsize;  // sizeof(struct _objc_method)
	unsigned int method_count;
	struct _objc_method method_list[1];
} _OBJC_$_CLASS_METHODS_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_objc_method),
	1,
	{{(struct objc_selector *)"m_clsFunc", "v16@0:8", (void *)_C_Man_m_clsFunc}}
};

static struct /*_prop_list_t*/ {
	unsigned int entsize;  // sizeof(struct _prop_t)
	unsigned int count_of_properties;
	struct _prop_t prop_list[1];
} _OBJC_$_PROP_LIST_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	sizeof(_prop_t),
	1,
	{{"name","T@\"NSString\",C,N,V_name"}}//猜想解读attributes T?type后面加上类型, C copy? V_name === V原因是在于非关联对象_加上名字 
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	1, sizeof(struct _class_t), sizeof(struct _class_t), 
	0, 
	"Man",
	(const struct _method_list_t *)&_OBJC_$_CLASS_METHODS_Man,
	0, 
	0, 
	0, 
	0, 
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Man __attribute__ ((used, section ("__DATA,__objc_const"))) = {
	0, __OFFSETOFIVAR__(struct Man, _name), sizeof(struct Man_IMPL), 
	0, 
	"Man",
	(const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Man,
	0, 
	(const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Man,
	0, 
	(const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Man,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Person;
extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Man __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_NSObject,
	0, // &OBJC_METACLASS_$_Person,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_METACLASS_RO_$_Man,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Person;

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Man __attribute__ ((used, section ("__DATA,__objc_data"))) = {
	0, // &OBJC_METACLASS_$_Man,
	0, // &OBJC_CLASS_$_Person,
	0, // (void *)&_objc_empty_cache,
	0, // unused, was (void *)&_objc_empty_vtable,
	&_OBJC_CLASS_RO_$_Man,
};
static void OBJC_CLASS_SETUP_$_Man(void ) {
	OBJC_METACLASS_$_Man.isa = &OBJC_METACLASS_$_NSObject;
	OBJC_METACLASS_$_Man.superclass = &OBJC_METACLASS_$_Person;
	OBJC_METACLASS_$_Man.cache = &_objc_empty_cache;
	OBJC_CLASS_$_Man.isa = &OBJC_METACLASS_$_Man;
	OBJC_CLASS_$_Man.superclass = &OBJC_CLASS_$_Person;
	OBJC_CLASS_$_Man.cache = &_objc_empty_cache;
}
#pragma section(".objc_inithooks$B", long, read, write) 猜想由hooks名字可知 会在objc_init中的某个时刻调用这个函数指针 $B或许还有$A 暂且留下思考
///OBJC_CLASS_SETUP[] 为存放函数指针的数组
__declspec(allocate(".objc_inithooks$B")) static void *OBJC_CLASS_SETUP[] = {
	(void *)&OBJC_CLASS_SETUP_$_Person,
	(void *)&OBJC_CLASS_SETUP_$_Man,
};
static struct _class_t *L_OBJC_LABEL_CLASS_$ [2] __attribute__((used, section ("__DATA, __objc_classlist,regular,no_dead_strip")))= {
	&OBJC_CLASS_$_Person,
	&OBJC_CLASS_$_Man,
};
static struct IMAGE_INFO { unsigned version; unsigned flag; } _OBJC_IMAGE_INFO = { 0, 2 };

```

__declspec(allocate("segname")) 告诉编译器分配一个名字为segname的段
在实际使用时，还需要#pragma section事先告诉编译器，我们要使用的段名
