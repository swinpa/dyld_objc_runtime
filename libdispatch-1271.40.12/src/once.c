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

#undef dispatch_once
#undef dispatch_once_f


#ifdef __BLOCKS__
void
dispatch_once(dispatch_once_t *val, dispatch_block_t block)
{
	dispatch_once_f(val, block, _dispatch_Block_invoke(block));
}
#endif

#if DISPATCH_ONCE_INLINE_FASTPATH
#define DISPATCH_ONCE_SLOW_INLINE inline DISPATCH_ALWAYS_INLINE
#else
#define DISPATCH_ONCE_SLOW_INLINE DISPATCH_NOINLINE
#endif // DISPATCH_ONCE_INLINE_FASTPATH

DISPATCH_NOINLINE
static void
_dispatch_once_callout(dispatch_once_gate_t l, void *ctxt,
		dispatch_function_t func)
{
	//执行block回调
	_dispatch_client_callout(ctxt, func);
	//广播锁已经释放了
	_dispatch_once_gate_broadcast(l);
}

DISPATCH_NOINLINE
//									token
void dispatch_once_f(dispatch_once_t *val, void *ctxt, dispatch_function_t func)
{
	/*
	 可参考文章：https://xiaozhuanlan.com/topic/7916538240
	 
	 typedef struct dispatch_gate_s {
		 dispatch_lock dgl_lock;
	 } dispatch_gate_s, *dispatch_gate_t;

	 typedef struct dispatch_once_gate_s {
		 union {
			 dispatch_gate_s dgo_gate;
			 uintptr_t dgo_once;
		 };
	 } dispatch_once_gate_s, *dispatch_once_gate_t;
	 
	 */
	dispatch_once_gate_t l = (dispatch_once_gate_t)val;

#if !DISPATCH_ONCE_INLINE_FASTPATH || DISPATCH_ONCE_USE_QUIESCENT_COUNTER
	
	/*
	 #define _os_atomic_c11_atomic(p) \
			 ((__typeof__(*(p)) _Atomic *)(p))
	 
	 #define os_atomic_load(p, m) \
			 atomic_load_explicit(_os_atomic_c11_atomic(p), memory_order_##m)
	 
	 所以展开得到
	 
	 atomic_load_explicit(_os_atomic_c11_atomic(l->dgo_once), memory_order_acquire)
	 
	 */
	
	uintptr_t v = os_atomic_load(&l->dgo_once, acquire);
	
	//likely表示更大可能成立，unlikely表示更大可能不成立。
	/*
	 ~ 取反运算符参考https://www.runoob.com/cplusplus/cpp-operators.html
	 #define DLOCK_ONCE_DONE		(~(uintptr_t)0) 相当于~0=-1;
	 */
	
	if (likely(v == DLOCK_ONCE_DONE)) {
		/*
		 如果token的值为DLOCK_ONCE_DONE 说明token的值已经被设置过(在执行block后会把token的值置成DLOCK_ONCE_DONE)，
		 所以直接返回（也就是block已经被执行过了，单例已经纯在了）
		 */
		return;
	}
	
	#if DISPATCH_ONCE_USE_QUIESCENT_COUNTER
		if (likely(DISPATCH_ONCE_IS_GEN(v))) {
			return _dispatch_once_mark_done_if_quiesced(l, v);
		}
	#endif
	
#endif
	//尝试加锁，加上了锁，就进入调用block，调用完block后就广播锁释放，通知正在等待锁的线程返回
	if (_dispatch_once_gate_tryenter(l)) {
		//调用block
		return _dispatch_once_callout(l, ctxt, func);
	}
	/*
	 等待锁，通过for循环不停的查询l->dgo_once的状态是否变成DLOCK_ONCE_DONE，直到变成DLOCK_ONCE_DONE后才结束查询返回
	 */
	return _dispatch_once_wait(l);
}
