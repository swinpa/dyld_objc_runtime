/*
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 2011 Apple Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/********************************************************************
 * 
 *  objc-msg-arm64.s - ARM64 code to support objc messaging
 *
 ********************************************************************/

#ifdef __arm64__

#include <arm/arch.h>
#include "isa.h"
#include "arm64-asm.h"

.data

// _objc_entryPoints and _objc_exitPoints are used by method dispatch
// caching code to figure out whether any threads are actively 
// in the cache for dispatching.  The labels surround the asm code
// that do cache lookups.  The tables are zero-terminated.

.align 4
.private_extern _objc_entryPoints
_objc_entryPoints:
	PTR   _cache_getImp
	PTR   _objc_msgSend
	PTR   _objc_msgSendSuper
	PTR   _objc_msgSendSuper2
	PTR   _objc_msgLookup
	PTR   _objc_msgLookupSuper2
	PTR   0

.private_extern _objc_exitPoints
_objc_exitPoints:
	PTR   LExit_cache_getImp
	PTR   LExit_objc_msgSend
	PTR   LExit_objc_msgSendSuper
	PTR   LExit_objc_msgSendSuper2
	PTR   LExit_objc_msgLookup
	PTR   LExit_objc_msgLookupSuper2
	PTR   0


/* objc_super parameter to sendSuper */
#define RECEIVER         0
#define CLASS            __SIZEOF_POINTER__

/* Selected field offsets in class structure */
#define SUPERCLASS       __SIZEOF_POINTER__
#define CACHE            (2 * __SIZEOF_POINTER__)

/* Selected field offsets in method structure */
#define METHOD_NAME      0
#define METHOD_TYPES     __SIZEOF_POINTER__
#define METHOD_IMP       (2 * __SIZEOF_POINTER__)

#define BUCKET_SIZE      (2 * __SIZEOF_POINTER__)


/********************************************************************
 * GetClassFromIsa_p16 src
 * src is a raw isa field. Sets p16 to the corresponding class pointer.
 * The raw isa might be an indexed isa to be decoded, or a
 * packed isa that needs to be masked.
 *
 * On exit:
 *   $0 is unchanged
 *   p16 is a class pointer
 *   x10 is clobbered
 ********************************************************************/
/*
 汇编中的.globl == C语言中的extern
 .globl _objc_indexed_classes 中的.global，就是声明_objc_indexed_classes为全局变量/标号，可以供其他源文件所访问。
 即汇编器，在编译此汇编代码的时候，会将此变量记下来，知道其是个全局变量，遇到其他文件是用到此变量的的时候，知道是访问这个全局变量的。
 因此，从功能上来说，就相当于C语言用extern去生命一个变量，以实现本文件外部访问此变量。
 */
#if SUPPORT_INDEXED_ISA
	.align 3
//定义一全局变量 _objc_indexed_classes
	.globl _objc_indexed_classes
//定义_objc_indexed_classes标签, 相当于C中定义的标签，其他代码通过该标签可以跳转到这里，比如 goto xxx
_objc_indexed_classes:
	.fill ISA_INDEX_COUNT, PTRSIZE, 0
#endif

//定义宏 GetClassFromIsa_p16 函数
.macro GetClassFromIsa_p16 /* src */

#if SUPPORT_INDEXED_ISA
	// Indexed isa
    //$0 为宏函数GetClassFromIsa_p16 的参数
	mov	p16, $0			// optimistically set dst = src
	/*
     tbz: (test branch zero). 测试位为0，则跳转。
     如：tbz w24, #0x6, 0x19307005c ; 即w24第6位，若为0，则跳转到0x19307005c执行
     [指令说明文章][https://www.dongxin.online/assembly/assemblyinstructions.html]
     */
    /*
     #ISA_INDEX_IS_NPI_BIT == #0
     如果p16 第0位为0 则跳转到下面的1: 标签处继续执行，否则执行接下来的adrp    x10, _objc_indexed_classes@PAGE指令
     tbz    p16, #ISA_INDEX_IS_NPI_BIT 判断对象地址是否是Tagged Pointer
     [Tagged Pointer 判断说明好文章][https://www.infoq.cn/article/r5s0budukwyndafrivh4]
     简单说就是拿取地址的第一位判断是否为1，如：0xb000000000000012
     b == 1011 第一位为1（从左到右数），所以为Tagged Pointer
     */
    tbz	p16, #ISA_INDEX_IS_NPI_BIT, 1f	// done if not non-pointer isa，【non-pointer isa：非指针类isa,(地址不是单纯的地址，还有值相关的数据)】
	
    // isa in p16 is indexed，接下来就是non-pointer isa（Tagged Pointer） 情况的处理
    /*
     adr: 作用：小范围的地址读取指令。ADR 指令将基于PC 相对偏移的地址值读取到寄存器中。
     adrp: 以页为单位的大范围的地址读取指令，这里的p就是page的意思。
     通俗来讲，adrp指令就是先进行PC+imm（偏移值）然后找到lable所在的一个4KB的页，然后取得label的基址，再进行偏移去寻址
     */
	adrp	x10, _objc_indexed_classes@PAGE
	add	x10, x10, _objc_indexed_classes@PAGEOFF
	ubfx	p16, p16, #ISA_INDEX_SHIFT, #ISA_INDEX_BITS  // extract index
	//将[x10, p16, UXTP #PTRSHIFT] 指定的内存数据加载到p16 寄存器中
    ldr	p16, [x10, p16, UXTP #PTRSHIFT]	// load class from array
1:

#elif __LP64__
	// 64-bit packed isa
    // 不是 non-pointer isa 的情况下，直接将参数与p16进行与运算并将结果存放在p16中：
	and	p16, $0, #ISA_MASK

#else
	// 32-bit raw isa
	mov	p16, $0

#endif

.endmacro


/********************************************************************
 * ENTRY functionName
 * STATIC_ENTRY functionName
 * END_ENTRY functionName
 ********************************************************************/

// 定义一个汇编宏 ENTRY，表示在 text 段定义一个 32 字节对齐的 global 函数，
// "$0" 同时生产一个函数入口标签。
// 上一节中我们分析 GetClassFromIsa_p16 时，说过 $0 表示宏定义的第一个入参
// (不知道支不支持多个入参例如 $1 $2 啥的...)

/*
 
// .global 关键字用来让一个符号对链接器可见，可以供其他链接对象模块使用，
// 告诉汇编器后续跟的是一个全局可见的名字（可能是变量，也可以是函数名）

// 这里用来指定 $0，$0 代表入参，
// 是不是就是表示 ENTRY 标注的函数都是全局可见的函数

// 00001:
// 00002: .text
// 00003: .global _start
// 00004:
// 00005: _start:

// .global _start 和 _start: 配合，
// 给代码开始地址定义一个全局标记 _start。
// _start 是一个函数的起始地址，也是编译、链接后程序的起始地址。
// 由于程序是通过加载器来加载的，
// 必须要找到 _start 名字的的函数，因此 _start 必须定义成全局的，
// 以便存在于编译后的全局符号表中，
// 供其他程序（如加载器）寻找到。

// .global _start 让 _start 符号成为可见的标示符，
// 这样链接器就知道跳转到程序中的什么地方并开始执行，
// Linux 寻找这个 _start 标签作为程序的默认进入点。

// .extern xxx 说明 xxx 为外部函数，
// 调用的时候可以遍访所有文件找到该函数并且使用它
                  
// 在汇编和 C 混合编程中，在 GNU ARM 编译环境下，
// 汇编程序中要使用 .global 伪操作声明汇编程序为全局的函数，
// 意即可被外部函数调用，
// 同时 C 程序中要使用 extern 声明要被汇编调用的函数。

 [原文链接][https://juejin.cn/post/6880503993798230030]
 
 */

.macro ENTRY /* name */
	.text /* .text 定义一个代码段，处理器开始执行代码的时候，代表后面是代码。这是 GCC 必须的。*/
	.align 5 // 2^5，32 个字节对齐
	.globl    $0
$0:
.endmacro

.macro STATIC_ENTRY /*name*/
	.text
	.align 5
	.private_extern $0//// 这里是 private_extern (私有函数)
$0:
.endmacro

.macro END_ENTRY /* name */
LExit$0: // 只有一个 LExit$0 标签 （以 L 开头的标签叫本地标签，这些标签只能用于函数内部）
.endmacro


/********************************************************************
 * UNWIND name, flags
 * Unwind info generation	(展开信息生成)
 ********************************************************************/
.macro UNWIND
	.section __LD,__compact_unwind,regular,debug
	PTR $0
	.set  LUnwind$0, LExit$0 - $0
	.long LUnwind$0
	.long $1
	PTR 0	 /* no personality */
	PTR 0  /* no LSDA */
	.text
.endmacro

#define NoFrame 0x02000000  // no frame, no SP adjustment
#define FrameWithNoSaves 0x04000000  // frame, no non-volatile saves


/********************************************************************
 *
 * CacheLookup NORMAL|GETIMP|LOOKUP
 * 
 * Locate the implementation for a selector in a class method cache.
 *
 * Takes:
 *	 x1 = selector
 *	 x16 = class to be searched
 *
 * Kills:
 * 	 x9,x10,x11,x12, x17
 *
 * On exit: (found) calls or returns IMP
 *                  with x16 = class, x17 = IMP
 *          (not found) jumps to LCacheMiss
 *
 ********************************************************************/

#define NORMAL 0
#define GETIMP 1
#define LOOKUP 2

// CacheHit: x17 = cached IMP, x12 = address of cached IMP
.macro CacheHit
.if $0 == NORMAL
	TailCallCachedImp x17, x12	// authenticate and call imp
.elseif $0 == GETIMP
	mov	p0, p17
	AuthAndResignAsIMP x0, x12	// authenticate imp and re-sign as IMP
	ret				// return IMP
.elseif $0 == LOOKUP
	AuthAndResignAsIMP x17, x12	// authenticate imp and re-sign as IMP
	ret				// return imp via x17
.else
.abort oops
.endif
.endmacro

.macro CheckMiss
	// miss if bucket->sel == 0
.if $0 == GETIMP
	cbz	p9, LGetImpMiss
.elseif $0 == NORMAL
	cbz	p9, __objc_msgSend_uncached
.elseif $0 == LOOKUP
	cbz	p9, __objc_msgLookup_uncached
.else
.abort oops
.endif
.endmacro

.macro JumpMiss
.if $0 == GETIMP
	b	LGetImpMiss
.elseif $0 == NORMAL
/*
 b
 branch. 无条件跳转。
 例如：b 0x1b6b79cf8 跳转到0x1b6b79cf8处继续执行。
*/
	b	__objc_msgSend_uncached
.elseif $0 == LOOKUP
	b	__objc_msgLookup_uncached
.else
.abort oops
.endif
.endmacro

//定义宏 函数CacheLookup，该函数在objc_msgSend()中获取到isa 后被调用
.macro CacheLookup
	// p1 = SEL, p16 = isa
    /*
     ldp x29, x30, [sp, #0x70] 将内存地址sp+0x70处的数据加载到x29中，再将sp+0x78(Tip1)处的数据加载到x30中。
     #define CACHE            (2 * __SIZEOF_POINTER__)
     */
    ldp	p10, p11, [x16, #CACHE]	// p10 = buckets, p11 = occupied|mask
#if !__LP64__
	and	w11, w11, 0xffff	// p11 = mask
#endif
	and	w12, w1, w11		// x12 = _cmd & mask
	add	p12, p10, p12, LSL #(1+PTRSHIFT)
		             // p12 = buckets + ((_cmd & mask) << (1+PTRSHIFT))

	ldp	p17, p9, [x12]		// {imp, sel} = *bucket

//  这前面主要获取缓存中的数据到p9 中
1:	cmp	p9, p1			// if (bucket->sel != _cmd)
	b.ne	2f			//     scan more
	CacheHit $0			// call or return imp
	
2:	// not hit: p12 = not-hit bucket
	CheckMiss $0			// miss if bucket->sel == 0
	cmp	p12, p10		// wrap if bucket == buckets
	b.eq	3f
	//从内存中加载一个bucket 到p9 中
    //Tip1: 64位下，寄存器大小为8bytes
    //ldp x29, x30, [sp, #0x70] 将内存地址sp+0x70处的数据加载到x29中，再将sp+0x78(Tip1, 在sp+0x70 基础上再偏移8)处的数据加载到x30中。
    ldp	p17, p9, [x12, #-BUCKET_SIZE]!	// {imp, sel} = *--bucket
	b	1b			// loop，重新跳到1标签进行比较

3:	// wrap: p12 = first bucket, w11 = mask
	add	p12, p12, w11, UXTW #(1+PTRSHIFT)
		                        // p12 = buckets + (mask << 1+PTRSHIFT)

	// Clone scanning loop to miss instead of hang when cache is corrupt.
	// The slow path may detect any corruption and halt later.

	ldp	p17, p9, [x12]		// {imp, sel} = *bucket
1:	cmp	p9, p1			// if (bucket->sel != _cmd)
	b.ne	2f			//     scan more
	CacheHit $0			// call or return imp
	
2:	// not hit: p12 = not-hit bucket
	CheckMiss $0			// miss if bucket->sel == 0
	cmp	p12, p10		// wrap if bucket == buckets
	b.eq	3f
	ldp	p17, p9, [x12, #-BUCKET_SIZE]!	// {imp, sel} = *--bucket
	b	1b			// loop

3:	// double wrap
    // 缓存没命中，则调用宏函数JumpMiss
	JumpMiss $0
	
.endmacro


/********************************************************************
 *
 * id objc_msgSend(id self, SEL _cmd, ...);
 * IMP objc_msgLookup(id self, SEL _cmd, ...);
 * 
 * objc_msgLookup ABI:
 * IMP returned in x17   找到的 IMP 保存在 x17 寄存器中
 * x16 reserved for our use but not used     --- x16 寄存器则是保留寄存器
 * [很好的一篇使用汇编阅读的文章][https://juejin.cn/post/6880774335192432647]
 * [https://www.codenong.com/js1972010b88d7/]
 * [http://kmanong.top/kmn/qxw/form/article?id=3197&cate=68]
 * [很好的汇编语法说明][https://www.crifan.com/files/doc/docbook/uboot_starts_analysis/release/htmls/summary_assembly.html]
 ********************************************************************/

#if SUPPORT_TAGGED_POINTERS
	.data   // 数据内容
	.align 3   // 2^3 = 8 字节对齐
	.globl _objc_debug_taggedpointer_classes  // 定义一个全局的标记 _objc_debug_taggedpointer_classes
_objc_debug_taggedpointer_classes:
/*
 .fill repeat, size, value 含义是反复拷贝 size 个字节，重复 repeat 次，
 其中 size 和 value 是可选的，默认值分别是 1 和 0
 全部填充 0
 */
	.fill 16, 8, 0
	.globl _objc_debug_taggedpointer_ext_classes
_objc_debug_taggedpointer_ext_classes:
	.fill 256, 8, 0
#endif

	ENTRY _objc_msgSend
    
    // UNWIND 展开信息生成，无窗口
	UNWIND _objc_msgSend, NoFrame

    /*
     对比p0寄存器是否为空，其中x0-x7是参数，x0可能会是返回值
     按照ARM64的Calling Convention，整形的参数前8个会按顺序放到'x0-x7'寄存器里，超过八个的放到栈上传递
     
     p0 和 空 对比，即判断接收者是否存在，
     其中 p0 是 objc_msgSend 的第一个参数(消息接收者 receiver)
     p0 定义在objc-818/Project Headers/arm64-asm.h
     p0-p15  等同于x0-x15, x0 ~ x31 是通用寄存器
     */
    // p0 - 0 = 0。  状态寄存器标识zero: PSTATE.NZCV.Z = 1
	cmp	p0, #0			// nil check and tagged pointer check
#if SUPPORT_TAGGED_POINTERS
    /*
     
     b：无返回跳转（一般是循环语句，判断语句跳转）（while，if else）
     bl: 有返回跳转(一般是函数跳转)
     b.le   loc_1000068E0 (标号)
     小于判断le是(less than or equal to)
     的意思当结果为小于等于的时候跳转执行loc_1000068E0(标号)地址pc寄存器的程序。（配合CMP做if判断）。
   
     b.ge   loc_1000068D0（标号）
     大于等于判断（great than or equal to）原理同b.le。
     注:le 和 ge 对应的高级代码是反向的即汇编是大于等于那么实际上高级代码是小于两者互补。
    
     b.gt
     比较结果是大于（greater than），执行标号，否则不跳转。
  
     b.lt
     比较结果是大于（less than），执行标号，否则不跳转
    
     b.eq
     比较结果是等于（equal to），执行标号，否则不跳转
     
     b.hi
     比较结果是无符号大于，执行标号，否则不跳转
    
     p0 小于或等于 0 的话，则跳转到 LNilOrTagged 标签处,执行 Taggend Pointer 对象的函数查找及执行
     因为 tagged pointer 在 arm64 下，最高位为 1，作为有符号数 < 0
    */
    //当判断状态寄存器 NZCV.Z == 0, N==V才跳转
	b.le	LNilOrTagged		//  (MSB tagged pointer looks negative)
#else
    /*
     p0 等于 0 的话，则跳转到 LReturnZero 标签处
     置 0 返回 nil 并直接结束 _objc_msgSend 函数
     */
	b.eq	LReturnZero
#endif
    /*
     第一个参数self其实就等于isa,因为
     struct _class_t {struct _class_t *isa;}
     @interface NSObject <NSObject> {objc_class *isa;}
     也就是类，对象的第一个成员都是isa,
     
     
     str和ldr是一对指令，str的全称是store register，即将寄存器的值存储到内存中，
     ldr的全称是load register，即将内存中的值读到寄存器，
     因此他们的第一个参数都是寄存器，第二个参数都是内存地址。[sp,#12] 代表 sp+12 这个地址，
     同理 [sp,#-12] 代表 sp-12 这个地址。注意这里的数字都是以字节为单位的偏移量，
     以 str w0,[sp,#12] 为例，w是4字节的寄存器（word），这个指令代表将w0寄存器的值存储在sp+12这个地址上
     
     ldr 是 Load Register 的缩写，[] 为间接寻址。它表示从 x0 所表示的地址中取出 8 字节数据，放到 x13 中。
     x0 中是 self 的地址，所以这里取出来的数据其实是 isa 的值
     
     */
	ldr	p13, [x0]		/* p13 = isa，根据对象拿出 isa，即从 x0 寄存器指向的地址取出 isa，存入 p13 寄存器  [x0]为第一个参数self这个对象，
        如果外部传进来的self这个对象是一个实例对象，那么它的ISA位于NSObject这个类的第一个成员变量
        此时使用[x0]也可以当成获取实例对象的isa 这个指针，而实例对象的isa 指向的是类对象（在alloc实例对象时会将对象的isa = cls），故去到了类对象的方法列表中查找
        
        如果外部传进来的self这个对象是一个类对象，那么它的ISA位于_class_t这个类的第一个成员变量
        此时使用[x0]也可以当成获取类对象的isa 这个指针，而类对象的isa 指向的是元类对象（编译期间将类对象的isa 指向元类对象），故去到了元类对象的方法列表中查找
    */

    /*
     GetClassFromIsa_p16：从 isa 中获取类指针并存放在通用寄存器 p16 中
     and p16, $0, #ISA_MASK
     在 __LP64__ 下通过 p16 = isa(正是 p13) & ISA_MASK，拿出 shiftcls 信息，得到 class 信息
     GetClassFromIsa_p16 为宏函数，传递的参数为p13
     */
	GetClassFromIsa_p16 p13		// p16 = class
//定义跳转标签
LGetIsaDone:
    //调用宏函数，传入参数值为NORMAL
	CacheLookup NORMAL		// calls imp or objc_msgSend_uncached

#if SUPPORT_TAGGED_POINTERS
LNilOrTagged:
	b.eq	LReturnZero		// nil check

	// tagged
	adrp	x10, _objc_debug_taggedpointer_classes@PAGE
	add	x10, x10, _objc_debug_taggedpointer_classes@PAGEOFF
	ubfx	x11, x0, #60, #4
	ldr	x16, [x10, x11, LSL #3]
	adrp	x10, _OBJC_CLASS_$___NSUnrecognizedTaggedPointer@PAGE
	add	x10, x10, _OBJC_CLASS_$___NSUnrecognizedTaggedPointer@PAGEOFF
	cmp	x10, x16
	b.ne	LGetIsaDone

	// ext tagged
	adrp	x10, _objc_debug_taggedpointer_ext_classes@PAGE
	add	x10, x10, _objc_debug_taggedpointer_ext_classes@PAGEOFF
	ubfx	x11, x0, #52, #8
	ldr	x16, [x10, x11, LSL #3]
	b	LGetIsaDone
// SUPPORT_TAGGED_POINTERS
#endif

LReturnZero:
	// x0 is already zero, 清空，置0
	mov	x1, #0
	movi	d0, #0
	movi	d1, #0
	movi	d2, #0
	movi	d3, #0
    // return 结束执行
	ret

    // LExit 结束 _objc_msgSend 函数执行
	END_ENTRY _objc_msgSend


	ENTRY _objc_msgLookup
	UNWIND _objc_msgLookup, NoFrame
	cmp	p0, #0			// nil check and tagged pointer check
#if SUPPORT_TAGGED_POINTERS
	b.le	LLookup_NilOrTagged	//  (MSB tagged pointer looks negative)
#else
	b.eq	LLookup_Nil
#endif
	ldr	p13, [x0]		// p13 = isa
	GetClassFromIsa_p16 p13		// p16 = class
LLookup_GetIsaDone:
	CacheLookup LOOKUP		// returns imp

#if SUPPORT_TAGGED_POINTERS
LLookup_NilOrTagged:
	b.eq	LLookup_Nil	// nil check

	// tagged
	mov	x10, #0xf000000000000000
	cmp	x0, x10
	b.hs	LLookup_ExtTag
	adrp	x10, _objc_debug_taggedpointer_classes@PAGE
	add	x10, x10, _objc_debug_taggedpointer_classes@PAGEOFF
	ubfx	x11, x0, #60, #4
	ldr	x16, [x10, x11, LSL #3]
	b	LLookup_GetIsaDone

LLookup_ExtTag:	
	adrp	x10, _objc_debug_taggedpointer_ext_classes@PAGE
	add	x10, x10, _objc_debug_taggedpointer_ext_classes@PAGEOFF
	ubfx	x11, x0, #52, #8
	ldr	x16, [x10, x11, LSL #3]
	b	LLookup_GetIsaDone
// SUPPORT_TAGGED_POINTERS
#endif

LLookup_Nil:
	adrp	x17, __objc_msgNil@PAGE
	add	x17, x17, __objc_msgNil@PAGEOFF
	ret

	END_ENTRY _objc_msgLookup

	
	STATIC_ENTRY __objc_msgNil

	// x0 is already zero
	mov	x1, #0
	movi	d0, #0
	movi	d1, #0
	movi	d2, #0
	movi	d3, #0
	ret
	
	END_ENTRY __objc_msgNil


	ENTRY _objc_msgSendSuper
	UNWIND _objc_msgSendSuper, NoFrame

	ldp	p0, p16, [x0]		// p0 = real receiver, p16 = class
	CacheLookup NORMAL		// calls imp or objc_msgSend_uncached

	END_ENTRY _objc_msgSendSuper

	// no _objc_msgLookupSuper

	ENTRY _objc_msgSendSuper2
	UNWIND _objc_msgSendSuper2, NoFrame

	ldp	p0, p16, [x0]		// p0 = real receiver, p16 = class
	ldr	p16, [x16, #SUPERCLASS]	// p16 = class->superclass
	CacheLookup NORMAL

	END_ENTRY _objc_msgSendSuper2

	
	ENTRY _objc_msgLookupSuper2
	UNWIND _objc_msgLookupSuper2, NoFrame

	ldp	p0, p16, [x0]		// p0 = real receiver, p16 = class
	ldr	p16, [x16, #SUPERCLASS]	// p16 = class->superclass
	CacheLookup LOOKUP

	END_ENTRY _objc_msgLookupSuper2


    //准备去obj->isa->data()->methods方法列表中查找
.macro MethodTableLookup
	
	// push frame
	SignLR
    /*
     参考文章 https://juejin.cn/post/6844903816362459144
     stp 入栈指令  stp x29, x30, [sp, #0x10]     ; 将 x29, x30 的值存入 sp 偏移 16 个字节的位置
     sp： (Stack Pointer)，栈顶寄存器，用于保存栈顶地址；
     fp(x29)： (Frame Pointer)为栈基址寄存，用于保存栈底地址；
     lr(x30)： (Link Register) ，保存调用跳转指令 bl 指令的下一条指令的内存地址；
     zr(x31)： (Zero Register)，xzr/wzr分别代表 64/32 位，其作用就是 0，写进去代表丢弃结果，读出来是 0；
     pc： 保存将要执行的指令的地址（有操作系统决定其值，不能改写）。

     */
    //将 fp, lr 入栈到[sp, #-16]处
	stp	fp, lr, [sp, #-16]!
    //保存保存栈顶地址到fp 中，为后面申请栈空间做准备
	mov	fp, sp

	// save parameter registers: x0..x8, q0..q7
    //申请栈空间
	sub	sp, sp, #(10*8 + 8*16)
    //将r0-r8寄存器中的值进行入栈，保留，以便接下来调用的函数结束后进行复原
	stp	q0, q1, [sp, #(0*16)]
	stp	q2, q3, [sp, #(2*16)]
	stp	q4, q5, [sp, #(4*16)]
	stp	q6, q7, [sp, #(6*16)]
	stp	x0, x1, [sp, #(8*16+0*8)]
	stp	x2, x3, [sp, #(8*16+2*8)]
	stp	x4, x5, [sp, #(8*16+4*8)]
	stp	x6, x7, [sp, #(8*16+6*8)]
	str	x8,     [sp, #(8*16+8*8)]

	// receiver and selector already in x0 and x1
    // 将x16 应该是isa 存到x2寄存器中，因为x0 and x1 中已经保存了self,cmd 的参数
	mov	x2, x16
    /*
     如果缓存中未找到，则跳转到 __class_lookupMethodAndLoadCache3（c 函数） 去方法列表中去找函数，
     源码在objc-runtime-new.mm 5024 行 IMP _class_lookupMethodAndLoadCache3(id obj, SEL sel, Class cls)
     bl
     branch with link.
     将下一条指令地址copy到lr中，然后跳转。由于保存了下一条指令地址
     (相对于pc)，所以可实现子程序的返回，而b只能单纯的实现跳转，不能实现子程序返回。
     【原文：https://www.dongxin.online/assembly/assemblyinstructions.html】
     这里是不是将bl    __class_lookupMethodAndLoadCache3 后面的指令 mov    x17, x0 的地址copy到
     lr 中，这能让__class_lookupMethodAndLoadCache3 结束后获取lr 中的地址，跳回到mov    x17, x0 这里继续执行
     
     */
	bl	__class_lookupMethodAndLoadCache3

	// IMP in x0
    /*
     此时x0保存的是__class_lookupMethodAndLoadCache3 的返回值
     mov    x17, x0 将__class_lookupMethodAndLoadCache3 返回值保存到x17 中
     */
	mov	x17, x0
	
	// restore registers and return
    // 恢复跳转__class_lookupMethodAndLoadCache3前各寄存器状态，也就是从栈中恢复，跟上面入栈反着来就行了
	ldp	q0, q1, [sp, #(0*16)]
	ldp	q2, q3, [sp, #(2*16)]
	ldp	q4, q5, [sp, #(4*16)]
	ldp	q6, q7, [sp, #(6*16)]
	ldp	x0, x1, [sp, #(8*16+0*8)]
	ldp	x2, x3, [sp, #(8*16+2*8)]
	ldp	x4, x5, [sp, #(8*16+4*8)]
	ldp	x6, x7, [sp, #(8*16+6*8)]
	ldr	x8,     [sp, #(8*16+8*8)]

	mov	sp, fp
	ldp	fp, lr, [sp], #16
	AuthenticateLR

.endmacro

	STATIC_ENTRY __objc_msgSend_uncached// 进入__objc_msgSend_uncached函数
	UNWIND __objc_msgSend_uncached, FrameWithNoSaves

	// THIS IS NOT A CALLABLE C FUNCTION
	// Out-of-band p16 is the class to search
    /*
     调用宏函数MethodTableLookup (.macro MethodTableLookup)
     该宏函数中在方法列表查找
     */
	MethodTableLookup
	TailCallFunctionPointer x17

	END_ENTRY __objc_msgSend_uncached// 结束__objc_msgSend_uncached函数


	STATIC_ENTRY __objc_msgLookup_uncached
	UNWIND __objc_msgLookup_uncached, FrameWithNoSaves

	// THIS IS NOT A CALLABLE C FUNCTION
	// Out-of-band p16 is the class to search
	
	MethodTableLookup
	ret

	END_ENTRY __objc_msgLookup_uncached


	STATIC_ENTRY _cache_getImp

	GetClassFromIsa_p16 p0
	CacheLookup GETIMP

LGetImpMiss:
	mov	p0, #0
	ret

	END_ENTRY _cache_getImp


/********************************************************************
*
* id _objc_msgForward(id self, SEL _cmd,...);
*
* _objc_msgForward is the externally-callable
*   function returned by things like method_getImplementation().
* _objc_msgForward_impcache is the function pointer actually stored in
*   method caches.
*
********************************************************************/

	STATIC_ENTRY __objc_msgForward_impcache

	// No stret specialization.
	b	__objc_msgForward

	END_ENTRY __objc_msgForward_impcache

	
	ENTRY __objc_msgForward

	adrp	x17, __objc_forward_handler@PAGE
	ldr	p17, [x17, __objc_forward_handler@PAGEOFF]
	TailCallFunctionPointer x17
	
	END_ENTRY __objc_msgForward
	
	
	ENTRY _objc_msgSend_noarg
	b	_objc_msgSend
	END_ENTRY _objc_msgSend_noarg

	ENTRY _objc_msgSend_debug
	b	_objc_msgSend
	END_ENTRY _objc_msgSend_debug

	ENTRY _objc_msgSendSuper2_debug
	b	_objc_msgSendSuper2
	END_ENTRY _objc_msgSendSuper2_debug

	
	ENTRY _method_invoke
	// x1 is method triplet instead of SEL
	add	p16, p1, #METHOD_IMP
	ldr	p17, [x16]
	ldr	p1, [x1, #METHOD_NAME]
	TailCallMethodListImp x17, x16
	END_ENTRY _method_invoke

#endif
