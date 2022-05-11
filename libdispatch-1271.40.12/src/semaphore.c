/*
 * Copyright (c) 2008-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

#include "internal.h"

DISPATCH_WEAK // rdar://problem/8503746
intptr_t _dispatch_semaphore_signal_slow(dispatch_semaphore_t dsema);

#pragma mark -
#pragma mark dispatch_semaphore_t

dispatch_semaphore_t
dispatch_semaphore_create(intptr_t value)
{
	dispatch_semaphore_t dsema;

	// If the internal value is negative, then the absolute of the value is
	// 如果内部值为负，则绝对值为
	// equal to the number of waiting threads. Therefore it is bogus to
	// 等于等待线程的数量。因此，它是虚假的
	// initialize the semaphore with a negative value.
	// 用负值初始化信号量。
	
	if (value < 0) {
		return DISPATCH_BAD_INPUT;
	}

	dsema = _dispatch_object_alloc(DISPATCH_VTABLE(semaphore),
			sizeof(struct dispatch_semaphore_s));
	//可以理解为链表的结尾标记
	dsema->do_next = DISPATCH_OBJECT_LISTLESS;
	// 目标队列
	dsema->do_targetq = _dispatch_get_default_queue(false);
	// 信号值
	dsema->dsema_value = value;
	_dispatch_sema4_init(&dsema->dsema_sema, _DSEMA4_POLICY_FIFO);
	dsema->dsema_orig = value;
	return dsema;
}

void
_dispatch_semaphore_dispose(dispatch_object_t dou,
		DISPATCH_UNUSED bool *allow_free)
{
	dispatch_semaphore_t dsema = dou._dsema;

	if (dsema->dsema_value < dsema->dsema_orig) {
		DISPATCH_CLIENT_CRASH(dsema->dsema_orig - dsema->dsema_value,
				"Semaphore object deallocated while in use");
	}

	_dispatch_sema4_dispose(&dsema->dsema_sema, _DSEMA4_POLICY_FIFO);
}

size_t
_dispatch_semaphore_debug(dispatch_object_t dou, char *buf, size_t bufsiz)
{
	dispatch_semaphore_t dsema = dou._dsema;

	size_t offset = 0;
	offset += dsnprintf(&buf[offset], bufsiz - offset, "%s[%p] = { ",
			_dispatch_object_class_name(dsema), dsema);
	offset += _dispatch_object_debug_attr(dsema, &buf[offset], bufsiz - offset);
#if USE_MACH_SEM
	offset += dsnprintf(&buf[offset], bufsiz - offset, "port = 0x%x, ",
			dsema->dsema_sema);
#endif
	offset += dsnprintf(&buf[offset], bufsiz - offset,
			"value = %" PRIdPTR ", orig = %" PRIdPTR " }", dsema->dsema_value, dsema->dsema_orig);
	return offset;
}

DISPATCH_NOINLINE
intptr_t
_dispatch_semaphore_signal_slow(dispatch_semaphore_t dsema)
{
	//调用内核接口
	_dispatch_sema4_create(&dsema->dsema_sema, _DSEMA4_POLICY_FIFO);
	_dispatch_sema4_signal(&dsema->dsema_sema, 1);
	return 1;
}

intptr_t
dispatch_semaphore_signal(dispatch_semaphore_t dsema)
{
	/*
	 dsema->dsema_value = dsema->dsema_value + 1
	 return dsema->dsema_value
	 也就是对信号量dispatch_semaphore_t 中的计数器属性dsema_value进行+1 操作，返回+1后的结果
	 */
	long value = os_atomic_inc2o(dsema, dsema_value, release);
	if (likely(value > 0)) {
		//如果dsema->dsema_value进行+1后的值大于0 则直接返回
		return 0;
	}
	if (unlikely(value == LONG_MIN)) {
		DISPATCH_CLIENT_CRASH(value,
				"Unbalanced call to dispatch_semaphore_signal()");
	}
	return _dispatch_semaphore_signal_slow(dsema);
}

DISPATCH_NOINLINE
static intptr_t
_dispatch_semaphore_wait_slow(dispatch_semaphore_t dsema, dispatch_time_t timeout)
{
	//等到FIFO队列中信号量的到来，直到timeout为止。
	long orig;

	_dispatch_sema4_create(&dsema->dsema_sema, _DSEMA4_POLICY_FIFO);
	switch (timeout) {
		default:
			if (!_dispatch_sema4_timedwait(&dsema->dsema_sema, timeout)) {
				break;
			}
			// Fall through and try to undo what the fast path did to
			// dsema->dsema_value
		case DISPATCH_TIME_NOW:
			orig = dsema->dsema_value;
			//死循环比较
			while (orig < 0) {
				
				/*
				 //参考https://juejin.cn/post/6902346229868019719
				 os_atomic_cmpxchgv2o 宏定义中 f 是 &(p) 的成员变量，比较 &(p)->f 和 e 的值，如果相等则用 &(p)->f 的值替换 v 的值，如果不相等，则把 &(p)->f 的值存入 e 中。
				 #define os_atomic_cmpxchgv2o(p, f, e, v, g, m) \
						 os_atomic_cmpxchgv(&(p)->f, (e), (v), (g), m)
				 
				 #define os_atomic_cmpxchgv(p, e, v, g, m) \
						 ({
							_os_atomic_basetypeof(p) _r = (e);
							//参考https://docs.microsoft.com/en-us/cpp/standard-library/atomic-functions?view=msvc-170#atomic_compare_exchange_strong_explicit
							//https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
							_Bool _b = atomic_compare_exchange_strong_explicit(_os_atomic_c11_atomic(p),
																				&_r,
																				v,
																				memory_order_##m,
																				memory_order_relaxed);
							*(g) = _r;
							_b;
						})

				 #define _os_atomic_basetypeof(p) \
						 __typeof__(atomic_load_explicit(_os_atomic_c11_atomic(p), memory_order_relaxed))
				 
				 
				 //将obj 跟 expected 比较，如果相等，那么将desired的值 内存覆盖obj指向的内存(也就是更新obj的值为desired)
				 //如果不相等，那么就将obj内存的值加载到expected所指向的内存(也就是expected的值更新为obj的值)
				 _Bool atomic_compare_exchange_strong_explicit( volatile A* obj,
																C* expected,
																C desired,
																memory_order succ,
																memory_order fail );
				 
				 所以这里的解释就是
				 比较dsema->dsema_value 跟 orig(也就是dsema->dsema_value)的值
				 如果相等，那用orig + 1更新dsema->dsema_value的值
				 如果不相等，那用dsema->dsema_value的值赋值给第5参数&orig
				 
				 */
				//desired == orig + 1
				//第二个参数(dsema_value)是用来指定第一个参数(dsema) 中的成员变量
				
				if (os_atomic_cmpxchgv2o(dsema, dsema_value, orig, orig + 1,
						&orig, relaxed))
				{
					return _DSEMA4_TIMEOUT();
				}
			}
			// Another thread called semaphore_signal().
			// Fall through and drain the wakeup.
		case DISPATCH_TIME_FOREVER:
			/*
			 也不知道这文章对不对得上Apple的实现：http://www.cs.fsu.edu/~baker/opsys/notes/semaphores.html
			 */
			_dispatch_sema4_wait(&dsema->dsema_sema);
			break;
	}
	return 0;
}

/*
 [参考](http://lingyuncxb.com/2018/02/08/GCD%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%905%20%E2%80%94%E2%80%94%20dispatch-semaphore%E7%AF%87/)
 DISPATCH_DECL(dispatch_semaphore);

 #define DISPATCH_DECL(name) typedef struct name##_s *name##_t;

 struct dispatch_semaphore_s {
	 DISPATCH_STRUCT_HEADER(dispatch_semaphore_s, dispatch_semaphore_vtable_s);
	 long dsema_value;   // 当前信号值，当这个值小于0时无法访问加锁资源
	 long dsema_orig;    // 初始化信号值，限制了同时访问资源的线程数量
	 
	 size_t dsema_sent_ksignals; //由于mach信号可能会被意外唤醒，通过原子操作来避免虚假信号
	 
	 semaphore_t dsema_port;
	 semaphore_t dsema_waiter_port;
	 size_t dsema_group_waiters;
	 struct dispatch_sema_notify_s *dsema_notify_head;
	 struct dispatch_sema_notify_s *dsema_notify_tail;
 };
 */

intptr_t
dispatch_semaphore_wait(dispatch_semaphore_t dsema, dispatch_time_t timeout)
{
	 /*
	  dsema->dsema_value = dsema->dsema_value - 1
	  return dsema->dsema_value
	  也就是对信号量dispatch_semaphore_t 中的计数器属性dsema_value进行-1 操作，返回-1后的结果
	  */
	 
	long value = os_atomic_dec2o(dsema, dsema_value, acquire);
	if (likely(value >= 0)) {
		return 0;
	}
	return _dispatch_semaphore_wait_slow(dsema, timeout);
}

#pragma mark -
#pragma mark dispatch_group_t

DISPATCH_ALWAYS_INLINE
static inline dispatch_group_t
_dispatch_group_create_with_count(uint32_t n)
{
	dispatch_group_t dg = _dispatch_object_alloc(DISPATCH_VTABLE(group),
			sizeof(struct dispatch_group_s));
	dg->do_next = DISPATCH_OBJECT_LISTLESS;
	dg->do_targetq = _dispatch_get_default_queue(false);
	if (n) {
		os_atomic_store2o(dg, dg_bits,
				(uint32_t)-n * DISPATCH_GROUP_VALUE_INTERVAL, relaxed);
		os_atomic_store2o(dg, do_ref_cnt, 1, relaxed); // <rdar://22318411>
	}
	return dg;
}

dispatch_group_t
dispatch_group_create(void)
{
	return _dispatch_group_create_with_count(0);
}

dispatch_group_t
_dispatch_group_create_and_enter(void)
{
	return _dispatch_group_create_with_count(1);
}

void
_dispatch_group_dispose(dispatch_object_t dou, DISPATCH_UNUSED bool *allow_free)
{
	uint64_t dg_state = os_atomic_load2o(dou._dg, dg_state, relaxed);

	if (unlikely((uint32_t)dg_state)) {
		DISPATCH_CLIENT_CRASH((uintptr_t)dg_state,
				"Group object deallocated while in use");
	}
}

size_t
_dispatch_group_debug(dispatch_object_t dou, char *buf, size_t bufsiz)
{
	dispatch_group_t dg = dou._dg;
	uint64_t dg_state = os_atomic_load2o(dg, dg_state, relaxed);

	size_t offset = 0;
	offset += dsnprintf(&buf[offset], bufsiz - offset, "%s[%p] = { ",
			_dispatch_object_class_name(dg), dg);
	offset += _dispatch_object_debug_attr(dg, &buf[offset], bufsiz - offset);
	offset += dsnprintf(&buf[offset], bufsiz - offset,
			"count = %u, gen = %d, waiters = %d, notifs = %d }",
			_dg_state_value(dg_state), _dg_state_gen(dg_state),
			(bool)(dg_state & DISPATCH_GROUP_HAS_WAITERS),
			(bool)(dg_state & DISPATCH_GROUP_HAS_NOTIFS));
	return offset;
}

DISPATCH_NOINLINE
static intptr_t
_dispatch_group_wait_slow(dispatch_group_t dg, uint32_t gen,
		dispatch_time_t timeout)
{
	for (;;) {
		int rc = _dispatch_wait_on_address(&dg->dg_gen, gen, timeout, 0);
		if (likely(gen != os_atomic_load2o(dg, dg_gen, acquire))) {
			return 0;
		}
		if (rc == ETIMEDOUT) {
			return _DSEMA4_TIMEOUT();
		}
	}
}

intptr_t
dispatch_group_wait(dispatch_group_t dg, dispatch_time_t timeout)
{
	uint64_t old_state, new_state;

	os_atomic_rmw_loop2o(dg, dg_state, old_state, new_state, relaxed, {
		if ((old_state & DISPATCH_GROUP_VALUE_MASK) == 0) {
			os_atomic_rmw_loop_give_up_with_fence(acquire, return 0);
		}
		if (unlikely(timeout == 0)) {
			os_atomic_rmw_loop_give_up(return _DSEMA4_TIMEOUT());
		}
		new_state = old_state | DISPATCH_GROUP_HAS_WAITERS;
		if (unlikely(old_state & DISPATCH_GROUP_HAS_WAITERS)) {
			os_atomic_rmw_loop_give_up(break);
		}
	});

	return _dispatch_group_wait_slow(dg, _dg_state_gen(new_state), timeout);
}

DISPATCH_NOINLINE
static void
_dispatch_group_wake(dispatch_group_t dg, uint64_t dg_state, bool needs_release)
{
	uint16_t refs = needs_release ? 1 : 0; // <rdar://problem/22318411>

	if (dg_state & DISPATCH_GROUP_HAS_NOTIFS) {
		dispatch_continuation_t dc, next_dc, tail;

		// Snapshot before anything is notified/woken <rdar://problem/8554546>
		dc = os_mpsc_capture_snapshot(os_mpsc(dg, dg_notify), &tail);
		do {
			dispatch_queue_t dsn_queue = (dispatch_queue_t)dc->dc_data;
			next_dc = os_mpsc_pop_snapshot_head(dc, tail, do_next);
			_dispatch_continuation_async(dsn_queue, dc,
					_dispatch_qos_from_pp(dc->dc_priority), dc->dc_flags);
			_dispatch_release(dsn_queue);
		} while ((dc = next_dc));

		refs++;
	}

	if (dg_state & DISPATCH_GROUP_HAS_WAITERS) {
		_dispatch_wake_by_address(&dg->dg_gen);
	}

	if (refs) _dispatch_release_n(dg, refs);
}

/**
 
 struct dispatch_group_s {
	 DISPATCH_OBJECT_HEADER(group);
	 DISPATCH_UNION_LE(uint64_t volatile dg_state,
			 uint32_t dg_bits,
			 uint32_t dg_gen
	 ) DISPATCH_ATOMIC64_ALIGN;
	 struct dispatch_continuation_s *volatile dg_notify_head;
	 struct dispatch_continuation_s *volatile dg_notify_tail;
 };

 
 dispatch_group_t 中有一个dg_state 遍历
 每次dispatch_group_leave 都会对这个值进行原子+1 操作
 每次dispatch_group_enter 都会对这个值进行原子-1 操作
 */
void
dispatch_group_leave(dispatch_group_t dg)
{
	// The value is incremented on a 64bits wide atomic so that the carry for
	// the -1 -> 0 transition increments the generation atomically.
	uint64_t new_state, old_state = os_atomic_add_orig2o(dg, dg_state,
			DISPATCH_GROUP_VALUE_INTERVAL, release);
	uint32_t old_value = (uint32_t)(old_state & DISPATCH_GROUP_VALUE_MASK);

	if (unlikely(old_value == DISPATCH_GROUP_VALUE_1)) {
		old_state += DISPATCH_GROUP_VALUE_INTERVAL;
		do {
			new_state = old_state;
			if ((old_state & DISPATCH_GROUP_VALUE_MASK) == 0) {
				new_state &= ~DISPATCH_GROUP_HAS_WAITERS;
				new_state &= ~DISPATCH_GROUP_HAS_NOTIFS;
			} else {
				// If the group was entered again since the atomic_add above,
				// we can't clear the waiters bit anymore as we don't know for
				// which generation the waiters are for
				new_state &= ~DISPATCH_GROUP_HAS_NOTIFS;
			}
			if (old_state == new_state) break;
		} while (unlikely(!os_atomic_cmpxchgv2o(dg, dg_state,
				old_state, new_state, &old_state, relaxed)));
		return _dispatch_group_wake(dg, old_state, true);
	}

	if (unlikely(old_value == 0)) {
		DISPATCH_CLIENT_CRASH((uintptr_t)old_value,
				"Unbalanced call to dispatch_group_leave()");
	}
}

void
dispatch_group_enter(dispatch_group_t dg)
{
	// The value is decremented on a 32bits wide atomic so that the carry
	// for the 0 -> -1 transition is not propagated to the upper 32bits.
	uint32_t old_bits = os_atomic_sub_orig2o(dg, dg_bits,
			DISPATCH_GROUP_VALUE_INTERVAL, acquire);
	uint32_t old_value = old_bits & DISPATCH_GROUP_VALUE_MASK;
	if (unlikely(old_value == 0)) {
		_dispatch_retain(dg); // <rdar://problem/22318411>
	}
	if (unlikely(old_value == DISPATCH_GROUP_VALUE_MAX)) {
		DISPATCH_CLIENT_CRASH(old_bits,
				"Too many nested calls to dispatch_group_enter()");
	}
}

DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_group_notify(dispatch_group_t dg, dispatch_queue_t dq,
		dispatch_continuation_t dsn)
{
	uint64_t old_state, new_state;
	dispatch_continuation_t prev;

	dsn->dc_data = dq;
	_dispatch_retain(dq);

	prev = os_mpsc_push_update_tail(os_mpsc(dg, dg_notify), dsn, do_next);
	if (os_mpsc_push_was_empty(prev)) _dispatch_retain(dg);
	os_mpsc_push_update_prev(os_mpsc(dg, dg_notify), prev, dsn, do_next);
	if (os_mpsc_push_was_empty(prev)) {
		os_atomic_rmw_loop2o(dg, dg_state, old_state, new_state, release, {
			new_state = old_state | DISPATCH_GROUP_HAS_NOTIFS;
			if ((uint32_t)old_state == 0) {
				os_atomic_rmw_loop_give_up({
					return _dispatch_group_wake(dg, new_state, false);
				});
			}
		});
	}
}

DISPATCH_NOINLINE
void
dispatch_group_notify_f(dispatch_group_t dg, dispatch_queue_t dq, void *ctxt,
		dispatch_function_t func)
{
	dispatch_continuation_t dsn = _dispatch_continuation_alloc();
	_dispatch_continuation_init_f(dsn, dq, ctxt, func, 0, DC_FLAG_CONSUME);
	_dispatch_group_notify(dg, dq, dsn);
}

#ifdef __BLOCKS__
void
dispatch_group_notify(dispatch_group_t dg, dispatch_queue_t dq,
		dispatch_block_t db)
{
	dispatch_continuation_t dsn = _dispatch_continuation_alloc();
	_dispatch_continuation_init(dsn, dq, db, 0, DC_FLAG_CONSUME);
	_dispatch_group_notify(dg, dq, dsn);
}
#endif

DISPATCH_ALWAYS_INLINE
static inline void
_dispatch_continuation_group_async(dispatch_group_t dg, dispatch_queue_t dq,
		dispatch_continuation_t dc, dispatch_qos_t qos)
{
	dispatch_group_enter(dg);
	dc->dc_data = dg;
	_dispatch_continuation_async(dq, dc, qos, dc->dc_flags);
}

DISPATCH_NOINLINE
void
dispatch_group_async_f(dispatch_group_t dg, dispatch_queue_t dq, void *ctxt,
		dispatch_function_t func)
{
	dispatch_continuation_t dc = _dispatch_continuation_alloc();
	uintptr_t dc_flags = DC_FLAG_CONSUME | DC_FLAG_GROUP_ASYNC;
	dispatch_qos_t qos;

	qos = _dispatch_continuation_init_f(dc, dq, ctxt, func, 0, dc_flags);
	_dispatch_continuation_group_async(dg, dq, dc, qos);
}

#ifdef __BLOCKS__
void
dispatch_group_async(dispatch_group_t dg, dispatch_queue_t dq,
		dispatch_block_t db)
{
	dispatch_continuation_t dc = _dispatch_continuation_alloc();
	uintptr_t dc_flags = DC_FLAG_CONSUME | DC_FLAG_GROUP_ASYNC;
	dispatch_qos_t qos;

	qos = _dispatch_continuation_init(dc, dq, db, 0, dc_flags);
	_dispatch_continuation_group_async(dg, dq, dc, qos);
}
#endif
