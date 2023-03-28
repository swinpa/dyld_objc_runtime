#我是这样子理解Mach-O
####[mach-o官方文档](https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/MachOTopics/0-Introduction/introduction.html)
mach-o 是mac/iOS上可执行文件的文件格式，当然他还是目标文件，动态库文件等的文件格式

__PAGEZERO段，[参考文章](https://juejin.cn/post/6844903968875757575)

mach-o文件的文件内容分为3大部分，分别是
	
	1、header
	2、load command
	3、Raw Segment Data(存放了所有段(segment)的原始数据) 
		
		segment（段）比如：
        代码段(__TEXT)，
        数据段(__DATA，__DATA_CONST),这两个段从学习汇编时就开始听说了，
        __PAGEZERO段，[参考文章](https://juejin.cn/post/6844903968875757575)
        			
        		__PAGEZERO是Mach-O加载进内存之后附加的一块区域，它不可读，不可写，
        		主要用来捕捉NULL指针的引用。如果访问__PAGEZERO段，会引起程序崩溃
        		
        		Mach-O文件本身是不存在__PAGEZERO的，在Mach-O文件被加载到虚拟内存之后，
        		系统会给Mach-O文件分配一个__PAGEZERO，它的开始位置是0x000000000，
        		结束位置是0x100000000。并且它的大小是固定的
        			
        __LINKEDIT段(link editor在链接时候创建生成,包含了符号表(symtab)、间接符号表(dysymtab)、字符串表(string table)等)（这个段为动态链接做准备的）
        
        
        每个segment(段)中跟据内容的不同又可以细分成不同的section，比如：
            
            代码段
            Section64(__TEXT,__text)
            Section64(__TEXT,__stubs)
            Section64(__TEXT,__stub_helper)
            
            数据段
            Section64(__DATA,__got)
            Section64(__DATA,__mod_init_func)
            Section64(__DATA,__objc_classlist)
            Section64(__DATA,__la_symbol_ptr)
        
我们可以把mach-o的文件内容想象成一本书的内容
	
	1、封面
	2、目录
	3、具体章节内容

mach-o文件内容跟书内容可以这样对应
	
	1、header			->	封面
	2、load command		->	目录
	3、segment			->	具体章节内容

所以我们可以通过load command（目录） 快速定位到segment（具体章节内容）部分

一本书里面有很多章节内容，比如金庸的笑傲江湖里面就有很多有趣的章节，而我们的mach-o 里面也有很多section
	
	1、Section64(__TEXT)
		1. __text					-> 这一看就像是代码
		2. __stubs					-> 这是桩代码，跟动态加载绑定有关
		3. __stubs_helper			-> 这也跟动态加载绑定有关
		4. __objc_classname			-> 这不是类名吗
		5. __gcc_except_tab
		6. __objc_methname			-> 这不就是方法名吗
		
	2、Section64(__DATA)
	
####load command
	描述了对应的section 在那里，有多大等信息，不同的load command 描述的信息会不同，比如：
		1. LC_SYMTAB 这个load command，他就描述了符号表(Symbol Table)的位置（offset），符号数量
		2. LC_SEGMENT_64(__DATA_CONST).SectionHeader(__got)，这个load command 就描述了
####符号表
符号表(Symbol Table) 又描述了所有符号的相关信息，比如符号名称，符号来源于那个模块(哪个动态库)，符号对应的地址，
符号在哪个section中等等信息，每个符号又有一个唯一的索引index
####间接符号表
间接符号表(Indirect Symbols) 中保存了符号在符号表中的位置(index)
####动态链接
链接：将符号与符号地址绑定的过程
	
	符号又分为
	
	
符号表



####clang 命令
	1. 编译动态库 
		clang -shared say.c -o say.dylib
	2. 编译
		clang -c main.c -o main.o
	3. 链接 
		clang main.o -o a.out -L . login.dylib pay.dylib say.dylib


####MachOView解析mach-o

MachOView 从Document.mm 中的

```
- (BOOL)readFromURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError

```

开始读入macho文件，以NSData的方式读入

```
dataController.fileData = [NSMutableData dataWithContentsOfURL:absoluteURL 
                                                         options:NSDataReadingMappedIfSafe 
                                                           error:outError];
```

NSData读取到macho文件后，通过

```
- (void)createLayouts:(MVNode *)parent
             location:(uint32_t)location
               length:(uint32_t)length
```
开始解析macho，解析当然是根据macho的文件格式进行解析

```
macho {
	header,
	load_command,
	segment
}
1. 根据固定大小读取到mach_header
2. 根据mach_header的描述读取load_command
3. 根据load_command的描述读取segment
```




1. 首先可以肯定的是mach_header长度是固定的，可以通过以下方式获取

		
		struct mach_header_64 {
			用来判断当前macho是fat_header，还是mach_header，还是mach_header_64
			uint32_t	magic;		/* mach magic number identifier */
			cpu_type_t	cputype;	/* cpu specifier */
			cpu_subtype_t	cpusubtype;	/* machine specifier */
			uint32_t	filetype;	/* type of file */
			uint32_t	ncmds;		/* number of load commands */
			uint32_t	sizeofcmds;	/* the size of all the load commands */
			/*
			一些标志位，如下
				#define MH_NOUNDEFS 0x1     // 目前没有未定义的符号，不存在链接依赖
				#define    MH_DYLDLINK  0x4     // 该文件是dyld的输入文件，无法被再次静态链接
				#define MH_PIE 0x200000     // 加载程序在随机的地址空间，只在 MH_EXECUTE中使用
				#define    MH_TWOLEVEL  0x80    // 两级名称空间
			*/
			uint32_t	flags;		/* flags */
			uint32_t	reserved;	/* reserved */
		};
		
		sizeof(mach_header) 
		或者 
		sizeof(mach_header_64)

2. 通过固定长度读取到mach_header后，根据mach\_header的内容就可以得知接下来的load\_command的数量以及所有load\_command内容所占用的长度

	machoview中是在DataController中调用
	
	```
	-(void)createMachO64Layout:(MVNode *)node
        mach_header_64:(struct mach_header_64 const *)mach_header_64
	```
	创建MachOLayout对象添加到layouts中
	
	然后再- (void)windowControllerDidLoadNib:(NSWindowController *)aController 中遍历layouts
	执行[layout doMainTasks];开始解析
	
		struct load_command {
			uint32_t cmd;		/* type of load command */
			uint32_t cmdsize;	/* total size of command in bytes */
		};
   
3. 得到load\_command的数量以及大小后，就可以遍历获取到每条load\_command了，因为每条load\_command前面的信息都是固定的，它指定了该条load_command的类型以及该条load_command占用长度是多少。

	所以遍历过程都是先读取load_command的内容，然后根据load_command指定的类型以及内容长度，读入对应类型的command内容，segment_command是其中的一种load_comnand
	
		struct segment_command { /* for 32-bit architectures */
			uint32_t	cmd;		/* LC_SEGMENT */
			uint32_t	cmdsize;	/* includes sizeof section structs */
			char		segname[16];	/* segment name */
			uint32_t	vmaddr;		/* memory address of this segment */
			uint32_t	vmsize;		/* memory size of this segment */
			/*
			表示在macho文件中的偏移量
			根据这个就可以读取segment内的所有的section，根据section的描述
			则可以读取所有的section内容
			*/
			uint32_t	fileoff;	/* file offset of this segment */
			uint32_t	filesize;	/* amount to map from the file */
			vm_prot_t	maxprot;	/* maximum VM protection */
			vm_prot_t	initprot;	/* initial VM protection */
			uint32_t	nsects;		/* number of sections in segment */
			uint32_t	flags;		/* flags */
		};
		
		struct section { /* for 32-bit architectures */
			char		sectname[16];	/* name of this section */
			char		segname[16];	/* segment this section goes in */
			uint32_t	addr;		/* memory address of this section */
			//section 该section内容的大小
			uint32_t	size;		/* size in bytes of this section */
			//该section内容相对于macho文件的偏移量
			uint32_t	offset;		/* file offset of this section */
			uint32_t	align;		/* section alignment (power of 2) */
			uint32_t	reloff;		/* file offset of relocation entries */
			uint32_t	nreloc;		/* number of relocation entries */
			uint32_t	flags;		/* flags (section type and attributes)*/
			uint32_t	reserved1;	/* reserved (for offset or index) */
			uint32_t	reserved2;	/* reserved (for count or sizeof) */
		};

4. 在遍历解析load_command的过程中，如果load_command是segment_command的，那么在segment_command内部
     
     描述了该segment有多少section，然后循环读取section内容，因为section大小是固定的，所以可通过
     
     ```
    uint32_t sectionloc = location + sizeof(struct segment_command) + nsect * sizeof(struct section);
     
     ```
     就可以得到每个section开始的位置，然后读入sizeof(struct section)大小的section内容

####58基于macho分析无用类

1. 读取mach_header

	```
	mach_header_64 mhHeader;
	[fileData getBytes:&mhHeader range:NSMakeRange(0, sizeof(mach_header_64))];
	```

2. 根据mach_header_64中描述的load_command数量以及大小读取load_command

	```
	unsigned long long currentLcLocation = sizeof(mach_header_64);
	for (int i = 0; i < mhHeader.ncmds; i++) {
		load_command *cmd = (load_command *)malloc(sizeof(load_command));
		[fileData getBytes:cmd range:NSMakeRange(currentLcLocation, sizeof(load_command))];
	}
	```

3. 如果load_command是segment_command，那么根据segment_command中描述的section数量读取对应的section

	```
	unsigned long long currentSecLocation = currentLcLocation + sizeof(segment_command_64);
	for (int j = 0; j < segmentCommand.nsects; j++) {
		section_64 sectionHeader;
		[fileData getBytes:&sectionHeader range:NSMakeRange(currentSecLocation, sizeof(section_64))];
		NSString *secName = [[NSString alloc] initWithUTF8String:sectionHeader.sectname];
                    
		//note classlist
		if ([secName isEqualToString:DATA_CLASSLIST_SECTION] ||
		    [secName isEqualToString:CONST_DATA_CLASSLIST_SECTION]) {
		    classList = sectionHeader;
		}
		//note classref
		if ([secName isEqualToString:DATA_CLASSREF_SECTION] ||
		    [secName isEqualToString:CONST_DATA_CLASSREF_SECTION]) {
		    classrefList = sectionHeader;
		}
	}
	```
4. 根据section的描述去读取section的内容


###[fishhook](https://www.jianshu.com/p/9e1f4d771e35)

```
在程序运行时，动态链接的 C 函数dynamic(...)地址记录在DATA segment下的la_symbol_ptr中；
初始时，程序只知道dynamic函数的符号名而不知道函数的实现地址；首次调用时，程序通过TEXT segment
中的stub_helper取得绑定信息，通过dyld_stub_binder来更新la_symbol_ptr中的符号实现地址；
这样，再次调用时，就可以通过la_symbol_ptr直接找到dynamic函数的实现；
如果我们需要替换dynamic函数的实现，只需要修改__la_symbol_ptr即可


是不是可以理解成调用动态库函数dynamic(...)的时候会去la_symbol_ptr中获取函数符号对应的函数地址进行调用
如果首次调用的时候，la_symbol_ptr中还没有函数符号对应的地址，那么就通过stub_helper，dyld_stub_binder
从而查询得到动态库函数的地址，然后调用，并且将其缓存到la_symbol_ptr中，那么下次再调用的时候，在la_symbol_ptr
中就能命中该动态库函数的地址了。fishhook的本质就是替换了la_symbol_ptr中符号对应的函数地址


然而是这样的：
la_symbol_ptr 中存放了符号在indirect symbol table 中的起始下标index，而indirect symbol table又记录了symbol在
符号表（symbol table）中的下标，通过indirect symbol table中记录的下标去符号表（symbol table）对应的位置就能
查询得到符号的信息（符号名，符号对应的地址），然后进行修改吗？

更具体的在QMCMHProject项目中写了部分笔记

```



* 简单来说可能就是

```
1. 通过_dyld_register_func_for_add_image监听image map加载完成，然后替换
```





