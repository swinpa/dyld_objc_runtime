##GCD

###dispatch_once
```
dispatch_once(dispatch_once_t *val, dispatch_block_t block)
{
	dispatch_once_f(val, block, _dispatch_Block_invoke(block));
}
```

```
dispatch_once_f(dispatch_once_t *val, void *ctxt, dispatch_function_t func)
{
	dispatch_once_gate_t l = (dispatch_once_gate_t)val;

#if !DISPATCH_ONCE_INLINE_FASTPATH || DISPATCH_ONCE_USE_QUIESCENT_COUNTER
	uintptr_t v = os_atomic_load(&l->dgo_once, acquire);
	if (likely(v == DLOCK_ONCE_DONE)) {
		return;
	}
#if DISPATCH_ONCE_USE_QUIESCENT_COUNTER
	if (likely(DISPATCH_ONCE_IS_GEN(v))) {
		return _dispatch_once_mark_done_if_quiesced(l, v);
	}
#endif
#endif
	if (_dispatch_once_gate_tryenter(l)) {
		return _dispatch_once_callout(l, ctxt, func);
	}
	return _dispatch_once_wait(l);
}

```
###dispatch_once 源码解析
![参考文章](https://juejin.cn/post/6844904143753052174)

##dispatch_once实现单列可能会出现的问题
1. 一不注意可能会引起循环引用问题
	
	```
	+ (instancetype) sharedInstance {
	    static LWStoreManager *instance;
	    static dispatch_once_t onceToken;
	    dispatch_once(&onceToken, ^{
	        instance = [[LWStoreManager alloc] init];
	        //xxxxx
	        [instance otherFunc];
	    });
	    return instance;
	}
	
	- (void) otherFunc {
		[LWStoreManager sharedInstance];
	}
	```
也就是在dispatch_once的block内部直接或间接又调用了sharedInstance，这就导致了第一次dispatch_once的block内部等待第二次的sharedInstance返回，然而由于第一次dispatch_once占用着oncetoken，导致第二次的dispatch_once等待这个oncetoken释放迟迟未能退出，这就造成了死锁

2.  static dispatch_once_t token; 不能初始化token的值
   


###queue(粗糙版理解)

1. 在libdispatch 的 init.c 中有一个全局的_dispatch_root_queues[] 数组，该数组保存了各种(12种)各优先级的queue_entry（其实应该就是一个对象，一个结构体实例），其中就包含了global_queue, main_queue
2. 当调用dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)去获取queue时，其实就是根据优先级参数，计算得到_dispatch_root_queues[]数组中的下标，去_dispatch_root_queues[]数组中相应的位置拿去对应的queue_entry（是一个对象），其实拿到的就是_dispatch_root_queues[6] 这个节点
3. _dispatch_root_queues[6] 队列的节点应该是以下类型的结构体（对象）

```
DISPATCH_VTABLE_SUBCLASS_INSTANCE(queue_global, lane,
	 .do_type        = DISPATCH_QUEUE_GLOBAL_ROOT_TYPE,
	 .do_dispose     = _dispatch_object_no_dispose,
	 .do_debug       = _dispatch_queue_debug,
	 .do_invoke      = _dispatch_object_no_invoke,

	 .dq_activate    = _dispatch_queue_no_activate,
	 .dq_wakeup      = _dispatch_root_queue_wakeup,
	 .dq_push        = _dispatch_root_queue_push,//用来将block 添加到队列中
 );
```



```
struct dispatch_queue_s {
	DISPATCH_QUEUE_CLASS_HEADER(queue, void *__dq_opaque1);
	/* 32bit hole on LP64 */
} __attribute__((aligned(8)));
```

```

struct dispatch_queue_s {
	
	//第一部分：DISPATCH_STRUCT_HEADER(dispatch_queue_s, dispatch_queue_vtable_s)
    const struct dispatch_queue_vtable_s *do_vtable;  //dispatch_queue_s的操作函数:dispatch_queue_vtable_s类型的结构体
    struct dispatch_queue_s *volatile do_next;  //链表的next
    unsigned int do_ref_cnt;    //引用计数
    unsigned int do_xref_cnt;  //外部引用计数
    unsigned int do_suspend_cnt;  //暂停标志，比如延时处理中，在任务到时后，计时器处理将会将该标志位修改，然后唤醒队列调度
    struct dispatch_queue_s *do_targetq;  //目标队列，GCD允许我们将一个队列放在另一个队列里执行任务
    void *do_ctxt;  //上下文，用来存储线程池相关数据，比如用于线程挂起和唤醒的信号量、线程池尺寸等
    void *do_finalizer;
    
    //第二部分：DISPATCH_QUEUE_HEADER
    uint32_t volatile dq_running;  //是否运行中
    uint32_t dq_width;  //最大并发数：主线程/串行中这个值为1
    struct dispatch_object_s *volatile dq_items_tail;  //链表尾节点
    struct dispatch_object_s *volatile dq_items_head;  //链表头节点
    unsigned long dq_serialnum;  //队列的序列号
    dispatch_queue_t dq_specific_q; //specific队列
    
    //其他：
    char dq_label[DISPATCH_QUEUE_MIN_LABEL_SIZE]; // must be last 说明队列的名字要少于64个字符
    char _dq_pad[DISPATCH_QUEUE_CACHELINE_PAD]; // for static queues only
	
	/* 32bit hole on LP64 */
} __attribute__((aligned(8)));



```

* dispatch_queue_t == dispatch_queue_class_t

	```
	dispatch_queue_class_t {
		struct dispatch_queue_s *_dq;
	}
	struct dispatch_queue_s {
		isa//   const struct dispatch_queue_vtable_s *__ptrauth_objc_isa_pointer do_vtable;
	}
	```
###queue总结
1. dispatch_queue_t是一个对象，该对象中有一个struct dispatch_queue_s *_dq; 属性
2. dispatch_queue_s 类型的对象又有一个isa 属性，而该ISA其实就是do_vtable，是一个const struct dispatch_queue_vtable_s 类型
3. do_vtable类型中有一个_os_obj_vtable属性，在_os_obj_vtable 这个属性中有一个dq_push()函数指针，该指针在dispatch_queue_t对象构造的时候会初始化为_dispatch_root_queue_push，
4. 在调用dispatch_async(dispatch_queue_t dq, dispatch_block_t work)进行异步操作时，内部逻辑如下：
	
	1. 将block封装到dispatch_continuation_t类型的结构体对象中（dispatch_continuation_t = block;）
	2. 调用_dispatch_continuation_async() 方法（其实内部是调用了dispatch_queue_t对象的dq_push函数指针，也就是_dispatch_root_queue_push函数），将






