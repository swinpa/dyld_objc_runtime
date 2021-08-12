#  map_images
第一个点 涉及到mach_header  
struct mach_header { ~~~mach_header_64
    uint32_t    magic;        /* mach magic number identifier */ Mach-O魔数,FAT:0xcafebabeARMv7:0xfeedface,ARM64:0xfeedfacf
    cpu_type_t    cputype;    /* cpu specifier */
    cpu_subtype_t    cpusubtype;    /* machine specifier */
    uint32_t    filetype;    /* type of file */
    uint32_t    ncmds;        /* number of load commands */ 加载命令的数量
    uint32_t    sizeofcmds;    /* the size of all the load commands */ 所有加载命令的大小
    uint32_t    flags;        /* flags */ dyld加载需要的一些标记，有28种宏定义，具体看源码，其中MH_PIE表示启用ASLR地址空间布局随机化
    ~~~     uint32_t    reserved;   /* reserved */ 64位保留字段
}; 
先去了解简单了解一下mach-O
https://www.jianshu.com/p/5a44f69466cc

## map_images_nolock(unsigned mhCount, const char * const mhPaths[],
                  const struct mach_header * const mhdrs[])
### preopt_init 初始化opt准备  共享缓存 
旧版本直接返回nil 新版具体内容翻阅objc_818版本对应位置 

### addHeader 
####  hi = preoptimizedHinfoForHeader(mhdr);
旧版本 的直接返回nil 跟上面preopt_init 呼应 
新版如下 
 objc_headeropt_ro_t *hinfos = opt ? opt->headeropt_ro() : nil;
 if (hinfos) return hinfos->get(mhdr);
 else return nil;
 hinfos = opt->headeropt_ro()  对静态变量 opt 缓存 
 (struct objc_headeropt_ro_t *)((uint8_t *)this + headeropt_ro_offset);进行offset偏移 拿出来headeropt_ro_t 
 hinfos->get(mhdr); 通过mhdr 对比 ro_t中的(start+end)/2 折半查找 进行查询对应的header_info
 ####  header_info存在 则进行 对应的设置读取 否则进行封装
 Locate the __OBJC segment
 getDataSection<objc_image_info>(mhdr, "__objc_imageinfo", 
                                        outBytes, nil);
const uint8_t *objc_segment = getsegmentdata(mhdr,SEG_OBJC,&seg_size);
全局的segment 中 imageinfo和objc_segment  都不存在 就返回空 （可能意味着 headerInfo里面必须要有这两个东西 否则没有意义）
申请空间 setmhdr setinfo setLoaded setAllClassesRealized 
_getObjc2ClassList 获取classlist内总数
#### appendHeader
Add a newly-constructed header_info to the list. 
里面维护着一个 关于 header_info 的链表 把它加入进去 
### sel_init(selrefCount);
namedSelectors.init((unsigned)selrefCount);
全局关于选择器的初始化？
### arr_init()
AutoreleasePoolPage::init(); 自动释放池
SideTablesMap.init();   Side散列表的初始化
_objc_associations_init(); 关联对象管理初始化 
### _read_images    ===>  _read_images.md
将分类的实例方法添加到类的rw中的methods 列表中
将分类的类方法添加到类的isa（元类）的rw中的methods列表中
###  // Call image load funcs after everything is set up.
for (auto func : loadImageFuncs) {
    for (uint32_t i = 0; i < mhCount; i++) {
        func(mhdrs[i]);
    }
}
