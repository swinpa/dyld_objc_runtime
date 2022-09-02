#我是这样子理解Mach-O
####[mach-o官方文档](https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/MachOTopics/0-Introduction/introduction.html)
mach-o 是mac/iOS上可执行文件的文件格式，当然他还是目标文件，动态库文件等的文件格式

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
