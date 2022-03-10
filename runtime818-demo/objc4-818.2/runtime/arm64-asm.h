/*
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 2018 Apple Inc.  All Rights Reserved.
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
 *  arm64-asm.h - asm tools for arm64/arm64_32 and ROP/JOP
 *
 ********************************************************************/

#if __arm64__

#include "objc-config.h"

/*
 在64位机器上，如果int是32位，long是64位，pointer也是64位，那么该机器就是LP64的，其中的L表示Long，P表示Pointer，
 64表示Long和Pointer都是64位的。
 由于LP64位下int是32位，因此LP64也叫I32LP64。类似的还有LLP64(Microsoft Window专用)，表示int是32位，long是32位，long long是64位，pointer是64位；ILP64表示int，long，pointer都是64位；SILP64表示short，int，long，pointer都是64位。

 */
#if __LP64__
// true arm64

#define SUPPORT_TAGGED_POINTERS 1
#define PTR .quad
#define PTRSIZE 8
#define PTRSHIFT 3  // 1<<PTRSHIFT == PTRSIZE
// "p" registers are pointer-sized
#define UXTP UXTX
#define p0  x0
#define p1  x1
#define p2  x2
#define p3  x3
#define p4  x4
#define p5  x5
#define p6  x6
#define p7  x7
#define p8  x8
#define p9  x9
#define p10 x10
#define p11 x11
#define p12 x12
#define p13 x13
#define p14 x14
#define p15 x15
#define p16 x16
#define p17 x17

/*
 r0 - r30 是31个通用整形寄存器
 当使用 x0 - x30访问时，它就是一个64位的数。当使用 w0 - w30访问时，访问的是这些寄存器的低32位
 r29 又被叫做 fp (frame pointer). r30 又被叫做 lr (link register)
 
 SP
 SP寄存器其实就是 x31，在指令编码中，使用 SP/WSP来进行对SP寄存器的访问。
 PC
 PC寄存器中存的是当前执行的指令的地址。在arm64中，软件是不能改写PC寄存器的。
 V0 – V31
 V0 - V31 是向量寄存器，也可以说是浮点型寄存器。它的特点是每个寄存器的大小是 128 位的。 分别可以用Bn Hn Sn Dn Qn的方式来访问不同的位数
 Bn: 一个Byte的大小
 Hn: half word. 就是16位
 Sn: single word. 32位
 Dn: double word. 64位
 Qn: quad word. 128位
 
 SPRs
 SPRs是状态寄存器，用于存放程序运行中一些状态标识。不同于编程语言里面的
 if else.在汇编中就需要根据状态寄存器中的一些状态来控制分支的执行。
 状态寄存器又分为 The Current Program Status Register (CPSR) 和 The Saved Program Status Registers (SPSRs)。
 一般都是使用CPSR， 当发生异常时， CPSR会存入SPSR。当异常恢复，再拷贝回CPSR。
 还有一些系统寄存器，如 FPSR FPCR是浮点型运算时的状态寄存器等。
 
 */

// true arm64
#else
// arm64_32

#define SUPPORT_TAGGED_POINTERS 0
#define PTR .long
#define PTRSIZE 4
#define PTRSHIFT 2  // 1<<PTRSHIFT == PTRSIZE
// "p" registers are pointer-sized
#define UXTP UXTW
#define p0  w0
#define p1  w1
#define p2  w2
#define p3  w3
#define p4  w4
#define p5  w5
#define p6  w6
#define p7  w7
#define p8  w8
#define p9  w9
#define p10 w10
#define p11 w11
#define p12 w12
#define p13 w13
#define p14 w14
#define p15 w15
#define p16 w16
#define p17 w17

// arm64_32
#endif


#if __has_feature(ptrauth_returns)
// ROP
#   define SignLR pacibsp
#   define AuthenticateLR autibsp
#else
// not ROP
#   define SignLR
#   define AuthenticateLR
#endif

#if __has_feature(ptrauth_calls)
// JOP

.macro TailCallFunctionPointer
	// $0 = function pointer value
	braaz	$0
.endmacro

.macro TailCallCachedImp
	// $0 = cached imp, $1 = address of cached imp, $2 = SEL, $3 = isa
	eor	$1, $1, $2	// mix SEL into ptrauth modifier
	eor	$1, $1, $3  // mix isa into ptrauth modifier
	brab	$0, $1
.endmacro

.macro TailCallMethodListImp
	// $0 = method list imp, $1 = address of method list imp
	braa	$0, $1
.endmacro

.macro TailCallBlockInvoke
	// $0 = invoke function, $1 = address of invoke function
	braa	$0, $1
.endmacro

.macro AuthAndResignAsIMP
	// $0 = cached imp, $1 = address of cached imp, $2 = SEL, $3 = isa
	// note: assumes the imp is not nil
	eor	$1, $1, $2	// mix SEL into ptrauth modifier
	eor	$1, $1, $3  // mix isa into ptrauth modifier
	autib	$0, $1	// authenticate cached imp
	ldr	xzr, [$0]	// crash if authentication failed
	paciza	$0		// resign cached imp as IMP
.endmacro

.macro ExtractISA
	and	$0, $1, #ISA_MASK
#if ISA_SIGNING_AUTH_MODE == ISA_SIGNING_STRIP
	xpacd	$0
#elif ISA_SIGNING_AUTH_MODE == ISA_SIGNING_AUTH
	mov	x10, $2
	movk	x10, #ISA_SIGNING_DISCRIMINATOR, LSL #48
	autda	$0, x10
#endif
.endmacro

.macro AuthISASuper dst, addr_mutable, discriminator
#if ISA_SIGNING_AUTH_MODE == ISA_SIGNING_AUTH
	movk	\addr_mutable, #\discriminator, LSL #48
	autda	\dst, \addr_mutable
#elif ISA_SIGNING_AUTH_MODE == ISA_SIGNING_STRIP
	xpacd	\dst
#endif
.endmacro

.macro SignAsImp
	paciza	$0
.endmacro

// JOP
#else
// not JOP

.macro TailCallFunctionPointer
	// $0 = function pointer value
	br	$0
.endmacro

.macro TailCallCachedImp
	// $0 = cached imp, $1 = address of cached imp, $2 = SEL, $3 = isa
	eor	$0, $0, $3
	br	$0
.endmacro

.macro TailCallMethodListImp
	// $0 = method list imp, $1 = address of method list imp
	br	$0
.endmacro

.macro TailCallBlockInvoke
	// $0 = invoke function, $1 = address of invoke function
	br	$0
.endmacro

.macro AuthAndResignAsIMP
	// $0 = cached imp, $1 = address of cached imp, $2 = SEL
	eor	$0, $0, $3
.endmacro

.macro SignAsImp
.endmacro

.macro ExtractISA
	and    $0, $1, #ISA_MASK
.endmacro

// not JOP
#endif

#define TailCallBlockInvoke TailCallMethodListImp


// __arm64__
#endif
