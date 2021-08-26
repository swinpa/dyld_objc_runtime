#  objc_msgSend
在开始objc_msgSend方法的学习时候，以及对平常使用的oc代码进行 消息发送的本质 底层方法是具体如何去理解，调用的进行总结。

现在开始真正对这个方法进行学习。    
在objc/Source里可以看到 objc-msg-XXX.s（），说明这个方法和__dyld_start一样用汇编语言进行实现的。原因：提高消息发送的过程，使用汇编节省高级语言翻译过程，编译成机器码就可以了。      
一开始我觉得看不懂汇编，看着里面的内容发现 汇编那么多个内容 你不懂我也不懂 那肯定要有注释 不然谁看懂 整挺好 源码内部真的有注释

```
objc-msg-simulator-x86_64.sobjc-msg-arm.sobjc-msg-arm64.sobjc-msg-i386.sobjc-msg-simulator-i386.sobjc-msg-x86_64.s
```

针对看objc-msg-arm64.s 相关的。   
找到其入口_objc_msgSend 还有一些别后缀的 直接搜索定位

```
	ENTRY _objc_msgSend
	UNWIND _objc_msgSend, NoFrame
	//第一个为信息接受者 判断是否为0 如果是直接返回LReturnZero
	cmp	 p0, #0			// nil check and tagged pointer check
#if SUPPORT_TAGGED_POINTERS
	b.le    LNilOrTagged		//  (MSB tagged pointer looks negative)
#else
	b.eq 	LReturnZero
#endif
	ldr	p13, [x0]		// p13 = isa 拿第一个的地址 也就是isa 
	GetClassFromIsa_p16 p13, 1, x0	// p16 = class 获取它的类 存在 p16里面
LGetIsaDone: //名如其目的 get完isa done 往下走
	// calls imp or objc_msgSend_uncached
	//查询缓存 模式？NORMAL Function当前调用的方法 MissLabelDynamic 估计是miss 没命中之后的动态调用？
	CacheLookup NORMAL, _objc_msgSend, __objc_msgSend_uncached 

```
接下来进入 CacheLookup 关于缓存查找

```
#if defined(__arm64__) && __LP64__
#if TARGET_OS_OSX || TARGET_OS_SIMULATOR
#define CACHE_MASK_STORAGE CACHE_MASK_STORAGE_HIGH_16_BIG_ADDRS
#else
#define CACHE_MASK_STORAGE CACHE_MASK_STORAGE_HIGH_16
#endif
#elif defined(__arm64__) && !__LP64__
#define CACHE_MASK_STORAGE CACHE_MASK_STORAGE_LOW_4
#else
#define CACHE_MASK_STORAGE CACHE_MASK_STORAGE_OUTLINED
#endif
```
去看新版的源码的时候 有点吓人 新旧变化那么多？
我删除一些暂为用到的 我考虑的是 arm64的

```
.macro CacheLookup Mode, Function, MissLabelDynamic, MissLabelConstant
	mov	x15, x16			// stash the original isa
LLookupStart\Function:
	// p1 = SEL, p16 = isa
...
#elif CACHE_MASK_STORAGE == CACHE_MASK_STORAGE_HIGH_16
	ldr	p11, [x16, #CACHE]			// p11 = mask|buckets
#if CONFIG_USE_PREOPT_CACHES
#if __has_feature(ptrauth_calls)
	tbnz	p11, #0, LLookupPreopt\Function
	and	p10, p11, #0x0000ffffffffffff	// p10 = buckets
#else
	and	p10, p11, #0x0000fffffffffffe	// p10 = buckets
	tbnz	p11, #0, LLookupPreopt\Function
#endif
	eor	p12, p1, p1, LSR #7
	and	p12, p12, p11, LSR #48		// x12 = (_cmd ^ (_cmd >> 7)) & mask
#else
	and	p10, p11, #0x0000ffffffffffff	// p10 = buckets
	and	p12, p1, p11, LSR #48		// x12 = _cmd & mask
#endif // CONFIG_USE_PREOPT_CACHES
#elif CACHE_MASK_STORAGE == CACHE_MASK_STORAGE_LOW_4
...
#else
#error Unsupported cache mask storage for ARM64.
#endif

	add	p13, p10, p12, LSL #(1+PTRSHIFT)
						// p13 = buckets + ((_cmd & mask) << (1+PTRSHIFT))

						// do {
1:	ldp	p17, p9, [x13], #-BUCKET_SIZE	//     {imp, sel} = *bucket--
	cmp	p9, p1				//     if (sel != _cmd) {
	b.ne	3f				//         scan more
						//     } else {
2:	CacheHit \Mode				// hit:    call or return imp
						//     }
3:	cbz	p9, \MissLabelDynamic		//     if (sel == 0) goto Miss;
	cmp	p13, p10			// } while (bucket >= buckets)
	b.hs	1b

	// wrap-around:
	//   p10 = first bucket
	//   p11 = mask (and maybe other bits on LP64)
	//   p12 = _cmd & mask
	//
	// A full cache can happen with CACHE_ALLOW_FULL_UTILIZATION.
	// So stop when we circle back to the first probed bucket
	// rather than when hitting the first bucket again.
	//
	// Note that we might probe the initial bucket twice
	// when the first probed slot is the last entry.


#if CACHE_MASK_STORAGE == CACHE_MASK_STORAGE_HIGH_16_BIG_ADDRS
...
#elif CACHE_MASK_STORAGE == CACHE_MASK_STORAGE_HIGH_16
	add	p13, p10, p11, LSR #(48 - (1+PTRSHIFT))
						// p13 = buckets + (mask << 1+PTRSHIFT)
						// see comment about maskZeroBits
#elif CACHE_MASK_STORAGE == CACHE_MASK_STORAGE_LOW_4
...
#else
#error Unsupported cache mask storage for ARM64.
#endif
	add	p12, p10, p12, LSL #(1+PTRSHIFT)
						// p12 = first probed bucket

						// do {
4:	ldp	p17, p9, [x13], #-BUCKET_SIZE	//     {imp, sel} = *bucket--
	cmp	p9, p1				//     if (sel == _cmd)
	b.eq	2b				//         goto hit
	cmp	p9, #0				// } while (sel != 0 &&
	ccmp	p13, p12, #0, ne		//     bucket > first_probed)
	b.hi	4b
//__has_feature(ptrauth_calls): 是判断编译器是否支持指针身份验证功能
//ptrauth_calls 指针身份验证，针对arm64e架构；使用Apple A12或更高版本A系列处理器的设备
//（如iPhone XS、iPhone XS Max和iPhone XR或更新的设备）支持arm64e架构
```

这一大段 emmm 太难受了 但是通过其他办法来理解 对比新旧代码 以及在cache_t里面的插入缓存方法
在旧版中 还存在 这个find方法 在新版中已经没有了 集合合在insert里了。

```
    bucket_t *b = buckets();
    mask_t m = capacity - 1;
    mask_t begin = cache_hash(sel, m);
    mask_t i = begin;

    // Scan for the first unused slot and insert there.
    // There is guaranteed to be an empty slot.
    do {
        if (fastpath(b[i].sel() == 0)) {
            incrementOccupied();
            b[i].set<Atomic, Encoded>(b, sel, imp, cls());
            return;
        }
        if (b[i].sel() == sel) {
            // The entry was added to the cache by some other thread
            // before we grabbed the cacheUpdateLock.
            return;
        }
    } while (fastpath((i = cache_next(i, m)) != begin));
```

对比来学习 也就是说      
在此查询的目的就是 在汇编的角度来拿出它的buckets 接着key值为：`(mask_t)(value & mask); //value 相当sel `  拿到之后进行遍历（mast转一圈又回到原处 来结束）这里查到到直接return 不插入 如果在查找过程 找到了 就应该调用 `CacheHit \Mode              // hit:    call or return imp`现在是insert过程 所以是return    
找到了是0那就说明是空的插入set 但是在我们查找过程 为0就应该miss `3:  cbz p9, \MissLabelDynamic       //     if (sel == 0) goto Miss;`
再回去一字一字的去看 汇编 发现 简单如斯

接着没命中（这才能继续往下走）MissLabelDynamic 还记得当初传进来的是啥？ __objc_msgSend_uncached！！！ 对的 定位到这个地方（在Mac 上用commonLine 断点调试 也可以看到这个）

```
STATIC_ENTRY __objc_msgSend_uncached
	UNWIND __objc_msgSend_uncached, FrameWithNoSaves

	// THIS IS NOT A CALLABLE C FUNCTION
	// Out-of-band p15 is the class to search
	
	MethodTableLookup //这个是一个不可调用的？C函数？可能后期改为C?
	TailCallFunctionPointer x17

	END_ENTRY __objc_msgSend_uncached
	
.macro MethodTableLookup
	
	SAVE_REGS MSGSEND

	// lookUpImpOrForward(obj, sel, cls, LOOKUP_INITIALIZE | LOOKUP_RESOLVER)
	// receiver and selector already in x0 and x1
	mov	x2, x16 //应该给我们准备 cls 以及后面的传入参数
	mov	x3, #3 
	bl	_lookUpImpOrForward //接着调用这个_lookUpImpOrForward

	// IMP in x0
	mov	 x17, x0

	RESTORE_REGS MSGSEND

.endmacro
```
简单看一下上面的源码 其实最终就调用到了.  
 `IMP lookUpImpOrForward(id inst, SEL sel, Class cls, int behavior)`      
checkIsKnowClass // 防止不是class类的？ CFI 控制流完整性（Control Flow Integrity, CFI）的防御机制
`    cls = realizeAndInitializeIfNeeded_locked(inst, cls, behavior & LOOKUP_INITIALIZE);`
这就是调用我们的常用的initialize方法之处 盲猜 必须要标志位调一次而已  （cls->isInitialized）.  
 接下来就进入到了 类和父类的方法列表查找了（旧版本很清晰 新版本 维护了一个for 无退出条件的循环 需要break）     
1.  先是判断有没有支持缓存优化 有的话就查询cache中缓存 `cache_getImp(curClass, sel)` 接着从`curClass->cache.preoptFallbackClass`再拿缓存。奇怪 如果这里一直拿不到 怎么出来到我的方法中拿呢？猜测是`cache.preoptFallbackClass `移动回来得到的不会进入这个缓存优化。   
2. `Method meth = getMethodNoSuper_nolock(curClass, sel);`获取目前class的方法列表 通过SEL查找对应的方法,查询到跳转done    
3. 在2中拿不到就 把curClass 设置为父类 接着查询父类的缓存，接着就是第二个循环里面 查询当前类（第一次的父类）的方法列表 继续循环下去 
4. 知道找到 缓存起来 `log_and_fill_cache(cls, imp, sel, inst, curClass);` 并且返回imp   或者 没找到break 跳出循环 走动态方法决议。 


