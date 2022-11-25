##GCD

[参考文章1](http://joeleee.github.io/2017/02/21/005.扒了扒libdispatch源码/)
[参考文章2](https://juejin.cn/post/6844904143753052174)
###dispatch_once
####源码如下
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
	//#define DLOCK_ONCE_DONE		(~(uintptr_t)0)
	if (likely(v == DLOCK_ONCE_DONE)) {
		return;
	}
#if DISPATCH_ONCE_USE_QUIESCENT_COUNTER
	if (likely(DISPATCH_ONCE_IS_GEN(v))) {
		return _dispatch_once_mark_done_if_quiesced(l, v);
	}
#endif
#endif
	//类似于尝试加锁
	if (_dispatch_once_gate_tryenter(l)) {
		//加锁成功，调用block，而后释放锁
		return _dispatch_once_callout(l, ctxt, func);
	}
	/*
	如果获取锁失败，那就等待，内部通过for循环不停的查询l->dgo_once的状态是否变成
	DLOCK_ONCE_DONE，直到变成DLOCK_ONCE_DONE后才结束查询返回
	*/
	return _dispatch_once_wait(l);
}

```

####源码说明
1. 在dispatch_once中通过原子操作读取判断token的值是否已经DLOCK_ONCE_DONE过，如果已经DLOCK_ONCE_DONE过说明已经执行过block，所以就直接返回，这可以保证block执行过一次后不会再执行。

2. 另外一点保证代码值执行一次的原因是，如果token没DLOCK_ONCE_DONE过，那么调用_dispatch_once_gate_tryenter(l)类似于尝试加锁，获取到锁，那么就调用block，然后广播释放锁，
如果获取不到锁，那么就通过_dispatch_once_wait(l);等待锁的释放，等到锁释放后返回

####dispatch_once注意事项
1. 通过上面源码可以看到token不能赋值，因为内部token需要跟~0比较，赋值了影响比较
	
	```
	if (likely(v == DLOCK_ONCE_DONE)) {
		return;
	}
	```
2. 需要避免在dispatch_once()的block内部又调用了dispatch_once()，这样会出现死锁的情况
	
    代码以及注释如下
	
	```
	+ (instancetype) sharedInstance {
	    static LWStoreManager *instance;
	    static dispatch_once_t onceToken;
	    //这里获取到锁
	    dispatch_once(&onceToken, ^{
	    	    //这里获取不到锁，所以会等待锁的释放才返回
		    dispatch_once(&onceToken, ^{
		        //xxxxx
		    });
		    //由于上面的dispatch_once一直在等待锁的释放才返回，导致当前的block代码无法
		    完成执行，从而导致锁无法释放
	     });
	    return instance;
	}
	```
3. 同上2一样，dispatch_once中的block内部也不能有dispatch_sync操作

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
#####从以下代码
```
typedef struct dispatch_queue_s *dispatch_queue_t;
```
#####可以看出dispatch_queue_t是dispatch_queue_s类型指针，可以向外部提供方便dispatch_queue_s类型指针变量的定义
1. dispatch_queue_t是一个对象，该对象中有一个struct dispatch_queue_s *_dq; 属性
2. dispatch_queue_s 类型的对象又有一个isa 属性，而该ISA其实就是do_vtable，是一个const struct dispatch_queue_vtable_s 类型
3. do_vtable类型中有一个_os_obj_vtable属性，在_os_obj_vtable 这个属性中有一个dq_push()函数指针，该指针在dispatch_queue_t对象构造的时候会初始化为_dispatch_root_queue_push，



###dispatch\_async(dispatch\_queue\_t dq, dispatch\_block\_t work)

Submits a block for asynchronous execution on a dispatch queue and returns immediately.

也就是提交一个异步执行的block到queue中，并且dispatch_async马上返回

#####底部实现逻辑如下

```
typedef struct dispatch_continuation_s {
	DISPATCH_CONTINUATION_HEADER(continuation);
} *dispatch_continuation_t;

宏展开后得到

typedef struct dispatch_continuation_s {
	 union {
		 const void *__ptrauth_objc_isa_pointer do_vtable;
		 uintptr_t dc_flags;
	 };
	 union {
		 pthread_priority_t dc_priority;
		 int dc_cache_cnt;
		 uintptr_t dc_pad;
	 };
	 struct dispatch_continuation_s *volatile do_next;
	 struct voucher_s *dc_voucher;
	 dispatch_function_t dc_func;
	 void *dc_ctxt; //dispatch_async()中的block参数
	 void *dc_data;
	 void *dc_other
 
 } *dispatch_continuation_t;

1. 在dispatch_async内部调用_dispatch_continuation_init()接口将block封装到dispatch_continuation_t类型的结构体对象中
	1. 调用_dispatch_Block_copy(block);接口将block拷贝到堆上，然后赋值给dispatch_continuation_t对象
		dispatch_continuation_t->dc_ctxt = _dispatch_Block_copy(block)
	2. 设置优先级
		
2. 调用_dispatch_continuation_async()接口将dispatch_continuation_t添加到队列queue中
   其实最终调用了队列对象内的(dqu._dq->do_vtable->_os_obj_vtable)->dq_push(dqu._dq, dc, qos)函数指针实现添加
   dq_push(队列, block, 优先级)
   queue在创建，初始化时设置了该函数指针，如果queue是系统的global_queue，那么dq_push指向	_dispatch_root_queue_push()
   	
   	DISPATCH_VTABLE_SUBCLASS_INSTANCE(queue_global, lane,
		.do_type        = DISPATCH_QUEUE_GLOBAL_ROOT_TYPE,
		.do_dispose     = _dispatch_object_no_dispose,
		.do_debug       = _dispatch_queue_debug,
		.do_invoke      = _dispatch_object_no_invoke,
		.dq_activate    = _dispatch_queue_no_activate,
		.dq_wakeup      = _dispatch_root_queue_wakeup,
		//将block添加到队列queue时需要调用的接口
		.dq_push        = _dispatch_root_queue_push,
	);
	
	在_dispatch_root_queue_push()接口中主要通过_dispatch_root_queue_push_inline()进行入队列操作
		
	在_dispatch_root_queue_push()中先调用os_mpsc_push_list(os_mpsc(dq, dq_items), hd, tl, do_next)进行入队列
	然后调用_dispatch_root_queue_poke(dq, n, 0);唤醒线程池中的线程，或者创建线程，在线程中不断取出任务执行
	
	_dispatch_root_queue_poke中通过调用_dispatch_root_queue_poke_slow(dispatch_queue_global_t dq, int n, int floor)
	来实现执行block效果
	
	_dispatch_root_queue_poke_slow主要的逻辑是先唤醒缓存池的线程，二是创建线程
	
	1. 唤醒线程
		if (likely(pqc->dpq_thread_mediator.do_vtable)) {
			//唤醒remaining条睡眠的线程起来
			while (dispatch_semaphore_signal(&pqc->dpq_thread_mediator)) {
				_dispatch_root_queue_debug("signaled sleeping worker for " "global queue: %p", dq);
				if (!--remaining) {//需要的线程都唤醒后就可以返回了，线程内从队列中获取block执行
					return;
				}
			}
		}
	2. 开辟worker线程，线程内不断从队列中获取block执行
		
		do {
			_dispatch_retain(dq); // released in _dispatch_worker_thread
			//创建线程，  根据remaining大小去创建线程 这里是普通的并发队列创建线程
			while ((r = pthread_create(pthr, attr, _dispatch_worker_thread, dq))) {
				if (r != EAGAIN) {
					(void)dispatch_assume_zero(r);
				}
				_dispatch_temporary_resource_shortage();
			}
		} while (--remaining); 
	3. _dispatch_worker_thread线程主要是不停地从队列中取出任务执行
		
		do {
			_dispatch_trace_runtime_event(worker_unpark, dq, 0);
			// 开始调用_dispatch_root_queue_drain函数，取出任务
			_dispatch_root_queue_drain(dq, pri, DISPATCH_INVOKE_REDIRECTING_DRAIN);
			_dispatch_reset_priority_and_voucher(pp, NULL);
			_dispatch_trace_runtime_event(worker_park, NULL, 0);
		} while (dispatch_semaphore_wait(&pqc->dpq_thread_mediator, dispatch_time(0, timeout)) == 0);
```

###gcd 队列死锁

```
-(void)viewDidLoad {
    dispatch_sync(dispatch_get_main_queue(), ^{
        NSLog(@"%@ 任务:",[NSThread currentThread]);
    });
}
```
抛出死锁异常的代码在

```
_dispatch_sync_f_slow(){
	__DISPATCH_WAIT_FOR_QUEUE__()
}
//等待队列任务执行结束
__DISPATCH_WAIT_FOR_QUEUE__(dispatch_sync_context_t dsc, dispatch_queue_t dq)
{
	uint64_t dq_state = _dispatch_wait_prepare(dq);
	if (unlikely(_dq_state_drain_locked_by(dq_state, dsc->dsc_waiter))) {
		DISPATCH_CLIENT_CRASH((uintptr_t)dq_state,
				"dispatch_sync called on queue "
				"already owned by current thread");
	}
}
```

