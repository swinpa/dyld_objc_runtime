

#ifndef _REWRITER_typedef_Singer
#define _REWRITER_typedef_Singer
typedef struct objc_object Singer;
typedef struct {} _objc_exc_Singer;
#endif

extern "C" unsigned long OBJC_IVAR_$_Singer$_name;
extern "C" unsigned long OBJC_IVAR_$_Singer$_age;
struct Singer_IMPL {
    struct NSObject_IMPL NSObject_IVARS;
    NSString * _Nonnull _name;
    int * _Nonnull _age;
};

// @property (nonatomic,copy)NSString *name;
// @property (nonatomic,assign)int *age;
/* @end */



#ifndef _REWRITER_typedef_Eason
#define _REWRITER_typedef_Eason
typedef struct objc_object Eason;
typedef struct {} _objc_exc_Eason;
#endif

extern "C" unsigned long OBJC_IVAR_$_Eason$_musicAblums;
struct Eason_IMPL {
    struct Singer_IMPL Singer_IVARS;
    NSMutableArray * _Nonnull _musicAblums;
};

// @property (nonatomic,strong)NSMutableArray *musicAblums;
/* @end */

#pragma clang assume_nonnull end

// @implementation Singer

static void _C_Singer_load(Class self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_w__fpzqhmrd08dczx4bdjqly8040000gn_T_Singer_2e3388_mi_0);
}

static void _I_Singer_instanceFunction(Singer * self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_w__fpzqhmrd08dczx4bdjqly8040000gn_T_Singer_2e3388_mi_1,__func__);
}

static void _C_Singer_classFunction(Class self, SEL _cmd) {
    NSLog((NSString *)&__NSConstantStringImpl__var_folders_w__fpzqhmrd08dczx4bdjqly8040000gn_T_Singer_2e3388_mi_2);
}

static NSString * _Nonnull _I_Singer_name(Singer * self, SEL _cmd) { return (*(NSString * _Nonnull *)((char *)self + OBJC_IVAR_$_Singer$_name)); }
extern "C" __declspec(dllimport) void objc_setProperty (id, SEL, long, id, bool, bool);

static void _I_Singer_setName_(Singer * self, SEL _cmd, NSString * _Nonnull name) { objc_setProperty (self, _cmd, __OFFSETOFIVAR__(struct Singer, _name), (id)name, 0, 1); }

static int * _Nonnull _I_Singer_age(Singer * self, SEL _cmd) { return (*(int * _Nonnull *)((char *)self + OBJC_IVAR_$_Singer$_age)); }
static void _I_Singer_setAge_(Singer * self, SEL _cmd, int * _Nonnull age) { (*(int * _Nonnull *)((char *)self + OBJC_IVAR_$_Singer$_age)) = age; }
// @end


// @implementation Eason


static NSMutableArray * _Nonnull _I_Eason_musicAblums(Eason * self, SEL _cmd) { return (*(NSMutableArray * _Nonnull *)((char *)self + OBJC_IVAR_$_Eason$_musicAblums)); }
static void _I_Eason_setMusicAblums_(Eason * self, SEL _cmd, NSMutableArray * _Nonnull musicAblums) { (*(NSMutableArray * _Nonnull *)((char *)self + OBJC_IVAR_$_Eason$_musicAblums)) = musicAblums; }
// @end

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

extern "C" unsigned long int OBJC_IVAR_$_Singer$_name __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Singer, _name);
extern "C" unsigned long int OBJC_IVAR_$_Singer$_age __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Singer, _age);

static struct /*_ivar_list_t*/ {
    unsigned int entsize;  // sizeof(struct _prop_t)
    unsigned int count;
    struct _ivar_t ivar_list[2];
} _OBJC_$_INSTANCE_VARIABLES_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_ivar_t),
    2,
    {{(unsigned long int *)&OBJC_IVAR_$_Singer$_name, "_name", "@\"NSString\"", 3, 8},
     {(unsigned long int *)&OBJC_IVAR_$_Singer$_age, "_age", "^i", 3, 8}}
};

static struct /*_method_list_t*/ {
    unsigned int entsize;  // sizeof(struct _objc_method)
    unsigned int method_count;
    struct _objc_method method_list[9];
} _OBJC_$_INSTANCE_METHODS_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_objc_method),
    9,
    {{(struct objc_selector *)"instanceFunction", "v16@0:8", (void *)_I_Singer_instanceFunction},
    {(struct objc_selector *)"name", "@16@0:8", (void *)_I_Singer_name},
    {(struct objc_selector *)"setName:", "v24@0:8@16", (void *)_I_Singer_setName_},
    {(struct objc_selector *)"age", "^i16@0:8", (void *)_I_Singer_age},
    {(struct objc_selector *)"setAge:", "v24@0:8^i16", (void *)_I_Singer_setAge_},
    {(struct objc_selector *)"name", "@16@0:8", (void *)_I_Singer_name},
    {(struct objc_selector *)"setName:", "v24@0:8@16", (void *)_I_Singer_setName_},
    {(struct objc_selector *)"age", "^i16@0:8", (void *)_I_Singer_age},
    {(struct objc_selector *)"setAge:", "v24@0:8^i16", (void *)_I_Singer_setAge_}}
};

static struct /*_method_list_t*/ {
    unsigned int entsize;  // sizeof(struct _objc_method)
    unsigned int method_count;
    struct _objc_method method_list[2];
} _OBJC_$_CLASS_METHODS_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_objc_method),
    2,
    {{(struct objc_selector *)"load", "v16@0:8", (void *)_C_Singer_load},
    {(struct objc_selector *)"classFunction", "v16@0:8", (void *)_C_Singer_classFunction}}
};

static struct /*_prop_list_t*/ {
    unsigned int entsize;  // sizeof(struct _prop_t)
    unsigned int count_of_properties;
    struct _prop_t prop_list[2];
} _OBJC_$_PROP_LIST_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_prop_t),
    2,
    {{"name","T@\"NSString\",C,N,V_name"},
    {"age","T^i,N,V_age"}}
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    1, sizeof(struct _class_t), sizeof(struct _class_t),
    0,
    "Singer",
    (const struct _method_list_t *)&_OBJC_$_CLASS_METHODS_Singer,
    0,
    0,
    0,
    0,
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Singer __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    0, __OFFSETOFIVAR__(struct Singer, _name), sizeof(struct Singer_IMPL),
    0,
    "Singer",
    (const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Singer,
    0,
    (const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Singer,
    0,
    (const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Singer,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Singer __attribute__ ((used, section ("__DATA,__objc_data"))) = {
    0, // &OBJC_METACLASS_$_NSObject,
    0, // &OBJC_METACLASS_$_NSObject,
    0, // (void *)&_objc_empty_cache,
    0, // unused, was (void *)&_objc_empty_vtable,
    &_OBJC_METACLASS_RO_$_Singer,
};

extern "C" __declspec(dllimport) struct _class_t OBJC_CLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Singer __attribute__ ((used, section ("__DATA,__objc_data"))) = {
    0, // &OBJC_METACLASS_$_Singer,
    0, // &OBJC_CLASS_$_NSObject,
    0, // (void *)&_objc_empty_cache,
    0, // unused, was (void *)&_objc_empty_vtable,
    &_OBJC_CLASS_RO_$_Singer,
};
static void OBJC_CLASS_SETUP_$_Singer(void ) {
    OBJC_METACLASS_$_Singer.isa = &OBJC_METACLASS_$_NSObject;
    OBJC_METACLASS_$_Singer.superclass = &OBJC_METACLASS_$_NSObject;
    OBJC_METACLASS_$_Singer.cache = &_objc_empty_cache;
    OBJC_CLASS_$_Singer.isa = &OBJC_METACLASS_$_Singer;
    OBJC_CLASS_$_Singer.superclass = &OBJC_CLASS_$_NSObject;
    OBJC_CLASS_$_Singer.cache = &_objc_empty_cache;
}

extern "C" unsigned long int OBJC_IVAR_$_Eason$_musicAblums __attribute__ ((used, section ("__DATA,__objc_ivar"))) = __OFFSETOFIVAR__(struct Eason, _musicAblums);

static struct /*_ivar_list_t*/ {
    unsigned int entsize;  // sizeof(struct _prop_t)
    unsigned int count;
    struct _ivar_t ivar_list[1];
} _OBJC_$_INSTANCE_VARIABLES_Eason __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_ivar_t),
    1,
    {{(unsigned long int *)&OBJC_IVAR_$_Eason$_musicAblums, "_musicAblums", "@\"NSMutableArray\"", 3, 8}}
};

static struct /*_method_list_t*/ {
    unsigned int entsize;  // sizeof(struct _objc_method)
    unsigned int method_count;
    struct _objc_method method_list[4];
} _OBJC_$_INSTANCE_METHODS_Eason __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_objc_method),
    4,
    {{(struct objc_selector *)"musicAblums", "@16@0:8", (void *)_I_Eason_musicAblums},
    {(struct objc_selector *)"setMusicAblums:", "v24@0:8@16", (void *)_I_Eason_setMusicAblums_},
    {(struct objc_selector *)"musicAblums", "@16@0:8", (void *)_I_Eason_musicAblums},
    {(struct objc_selector *)"setMusicAblums:", "v24@0:8@16", (void *)_I_Eason_setMusicAblums_}}
};

static struct /*_prop_list_t*/ {
    unsigned int entsize;  // sizeof(struct _prop_t)
    unsigned int count_of_properties;
    struct _prop_t prop_list[1];
} _OBJC_$_PROP_LIST_Eason __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    sizeof(_prop_t),
    1,
    {{"musicAblums","T@\"NSMutableArray\",&,N,V_musicAblums"}}
};

static struct _class_ro_t _OBJC_METACLASS_RO_$_Eason __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    1, sizeof(struct _class_t), sizeof(struct _class_t),
    0,
    "Eason",
    0,
    0,
    0,
    0,
    0,
};

static struct _class_ro_t _OBJC_CLASS_RO_$_Eason __attribute__ ((used, section ("__DATA,__objc_const"))) = {
    0, __OFFSETOFIVAR__(struct Eason, _musicAblums), sizeof(struct Eason_IMPL),
    0,
    "Eason",
    (const struct _method_list_t *)&_OBJC_$_INSTANCE_METHODS_Eason,
    0,
    (const struct _ivar_list_t *)&_OBJC_$_INSTANCE_VARIABLES_Eason,
    0,
    (const struct _prop_list_t *)&_OBJC_$_PROP_LIST_Eason,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Singer;
extern "C" __declspec(dllimport) struct _class_t OBJC_METACLASS_$_NSObject;

extern "C" __declspec(dllexport) struct _class_t OBJC_METACLASS_$_Eason __attribute__ ((used, section ("__DATA,__objc_data"))) = {
    0, // &OBJC_METACLASS_$_NSObject,
    0, // &OBJC_METACLASS_$_Singer,
    0, // (void *)&_objc_empty_cache,
    0, // unused, was (void *)&_objc_empty_vtable,
    &_OBJC_METACLASS_RO_$_Eason,
};

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Singer;

extern "C" __declspec(dllexport) struct _class_t OBJC_CLASS_$_Eason __attribute__ ((used, section ("__DATA,__objc_data"))) = {
    0, // &OBJC_METACLASS_$_Eason,
    0, // &OBJC_CLASS_$_Singer,
    0, // (void *)&_objc_empty_cache,
    0, // unused, was (void *)&_objc_empty_vtable,
    &_OBJC_CLASS_RO_$_Eason,
};
static void OBJC_CLASS_SETUP_$_Eason(void ) {
    OBJC_METACLASS_$_Eason.isa = &OBJC_METACLASS_$_NSObject;
    OBJC_METACLASS_$_Eason.superclass = &OBJC_METACLASS_$_Singer;
    OBJC_METACLASS_$_Eason.cache = &_objc_empty_cache;
    OBJC_CLASS_$_Eason.isa = &OBJC_METACLASS_$_Eason;
    OBJC_CLASS_$_Eason.superclass = &OBJC_CLASS_$_Singer;
    OBJC_CLASS_$_Eason.cache = &_objc_empty_cache;
}
#pragma section(".objc_inithooks$B", long, read, write)
__declspec(allocate(".objc_inithooks$B")) static void *OBJC_CLASS_SETUP[] = {
    (void *)&OBJC_CLASS_SETUP_$_Singer,
    (void *)&OBJC_CLASS_SETUP_$_Eason,
};
static struct _class_t *L_OBJC_LABEL_CLASS_$ [2] __attribute__((used, section ("__DATA, __objc_classlist,regular,no_dead_strip")))= {
    &OBJC_CLASS_$_Singer,
    &OBJC_CLASS_$_Eason,
};
static struct _class_t *_OBJC_LABEL_NONLAZY_CLASS_$[] = {
        &OBJC_CLASS_$_Singer,
};
static struct IMAGE_INFO { unsigned version; unsigned flag; } _OBJC_IMAGE_INFO = { 0, 2 };
