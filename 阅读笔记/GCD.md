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

###queue(粗糙版理解)

1. 在libdispatch 的 init.c 中有一个全局的_dispatch_root_queues[] 数组，该数组保存了各种(12种)各优先级的queue_entry，其中就包含了global_queue, main_queue
2. 当调用dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)去获取queue时，其实就是去_dispatch_root_queues[] 这个数组中相应的位置拿去对应的queue_entry，其实拿到的就是_dispatch_root_queues[6] 这个节点
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