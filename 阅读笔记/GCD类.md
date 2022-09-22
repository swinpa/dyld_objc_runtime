
```


struct dispatch_queue_s {

	DISPATCH_QUEUE_CLASS_HEADER(queue, void *__dq_opaque1);

	DISPATCH_QUEUE_CLASS_HEADER(queue, void *__dq_opaque1);
	
			_DISPATCH_QUEUE_CLASS_HEADER(queue, void *__dq_opaque1); \
			
					DISPATCH_OBJECT_HEADER(queue); \
					
							struct dispatch_object_s _as_do[0]; \
							_DISPATCH_OBJECT_HEADER(queue)
									
									struct _os_object_s _as_os_obj[0]; \
									OS_OBJECT_STRUCT_HEADER(dispatch_queue); \
											
											_OS_OBJECT_HEADER(\
											const struct dispatch_queue_vtable_s *__ptrauth_objc_isa_pointer do_vtable, \
											do_ref_cnt, \
											do_xref_cnt)
											
																								 const struct dispatch_queue_vtable_s *do_vtable
										        int volatile do_ref_cnt; \
										        int volatile do_xref_cnt
									
									
									
									struct dispatch_queue_s *volatile do_next; \
									struct dispatch_queue_s *do_targetq; \
									void *do_ctxt; \
									union { \
										dispatch_function_t DISPATCH_FUNCTION_POINTER do_finalizer; \
										void *do_introspection_ctxt; \
									}
					
					
					void *__dq_opaque1); \
					DISPATCH_UNION_LE(uint64_t volatile dq_state, \
							dispatch_lock dq_state_lock, \
							uint32_t dq_state_bits \
					)
			
			
			/* LP64 global queue cacheline boundary */ \
			unsigned long dq_serialnum; \
			const char *dq_label; \
			DISPATCH_UNION_LE(uint32_t volatile dq_atomic_flags, \
				const uint16_t dq_width, \
				const uint16_t __dq_opaque2 \
			); \
			dispatch_priority_t dq_priority; \
			union { \
				struct dispatch_queue_specific_head_s *dq_specific_head; \
				struct dispatch_source_refs_s *ds_refs; \
				struct dispatch_timer_source_refs_s *ds_timer_refs; \
				struct dispatch_mach_recv_refs_s *dm_recv_refs; \
				struct dispatch_channel_callbacks_s const *dch_callbacks; \
			}; \
			int volatile dq_sref_cnt
	
		
	


} DISPATCH_ATOMIC64_ALIGN;/* 32bit hole on LP64 */

```


```

struct dispatch_queue_s {


	struct dispatch_object_s _as_do[0];
	struct _os_object_s _as_os_obj[0];
	/* must be pointer-sized and use __ptrauth_objc_isa_pointer */
	const struct dispatch_queue_vtable_s *do_vtable;         
   int volatile do_ref_cnt;
   int volatile do_xref_cnt;
	struct dispatch_ queue_s *volatile do_next;
	struct dispatch_queue_s *do_targetq;
	void *do_ctxt;
	union {
		dispatch_function_t DISPATCH_FUNCTION_POINTER do_finalizer;
		void *do_introspection_ctxt;
	}
	void *__dq_opaque1;
	DISPATCH_UNION_LE(uint64_t volatile dq_state,
			dispatch_lock dq_state_lock,
			uint32_t dq_state_bits
	)
	/* LP64 global queue cacheline boundary */
	unsigned long dq_serialnum;
	const char *dq_label;
	DISPATCH_UNION_LE(uint32_t volatile dq_atomic_flags,
		const uint16_t dq_width,
		const uint16_t __dq_opaque2
	); 
	dispatch_priority_t dq_priority;
	union {
		struct dispatch_queue_specific_head_s *dq_specific_head;
		struct dispatch_source_refs_s *ds_refs;
		struct dispatch_timer_source_refs_s *ds_timer_refs;
		struct dispatch_mach_recv_refs_s *dm_recv_refs;
		struct dispatch_channel_callbacks_s const *dch_callbacks;
	};
	int volatile dq_sref_cnt;
}

```




```


struct dispatch_queue_s {

	struct dispatch_object_s _as_do[0];	
	struct _os_object_s _as_os_obj[0];
	const struct dispatch_queue_vtable_s *do_vtable;
	int volatile do_ref_cnt;
	int volatile do_xref_cnt;
	struct dispatch_queue_s *volatile do_next;
	struct dispatch_queue_s *do_targetq;
	void *do_ctxt;
	union {
		dispatch_function_t DISPATCH_FUNCTION_POINTER do_finalizer;
		void *do_introspection_ctxt; 
	}
	void *__dq_opaque1;
	DISPATCH_UNION_LE(uint64_t volatile dq_state,
			dispatch_lock dq_state_lock,
			uint32_t dq_state_bits
	)
	/* LP64 global queue cacheline boundary */ 
	unsigned long dq_serialnum;
	const char *dq_label;
	DISPATCH_UNION_LE(uint32_t volatile dq_atomic_flags,
		const uint16_t dq_width,
		const uint16_t __dq_opaque2
	);
	dispatch_priority_t dq_priority;
	union {
		struct dispatch_queue_specific_head_s *dq_specific_head; \
		struct dispatch_source_refs_s *ds_refs; \
		struct dispatch_timer_source_refs_s *ds_timer_refs; \
		struct dispatch_mach_recv_refs_s *dm_recv_refs; \
		struct dispatch_channel_callbacks_s const *dch_callbacks; \
	};
	int volatile dq_sref_cnt
} DISPATCH_ATOMIC64_ALIGN;/* 32bit hole on LP64 */

```