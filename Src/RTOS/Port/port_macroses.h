#ifndef RTOS_PORT_PORT_MACROSES_H_
#define RTOS_PORT_PORT_MACROSES_H_

#define INITIAL_EXC_RETURN   	(0xFFFFFFED)

#define _PORT_OS_RUN(svc_n, first_task_stack_pointer)												\
	__asm volatile(																					\
			"mov r0, %[source]			\n\t"														\
			"cpsie i					\n\t"														\
			"cpsie f              		\n\t"														\
			"dsb	              		\n\t"														\
			"svc %[svc_num]				\n\t"														\
			:																						\
			: [svc_num] "i" (svc_n),																\
			  [source] "r" (first_task_stack_pointer)												\
			: "r0", "r1", "r2", "r3", "r12", "lr", "memory"											\
		)

#define _PORT_ENTER_SVC_1_ARGS_AND_RETURN(svc_num, argument_0)				\
	({																		\
		register uint32_t 	result __asm("r0");								\
		register uint32_t 	arg0 __asm("r0") = (uint32_t)argument_0;		\
																			\
		__asm volatile(														\
			"svc %[svc_n]		\n\t"										\
			: "+r" (result)													\
			: [svc_n] "i" (svc_num),										\
			  "r" (arg0)													\
			: "r12", "lr", "memory"											\
		);																	\
																			\
		result;																\
	})

#define _PORT_ENTER_SVC_3_ARGS_AND_RETURN(svc_num, argument_0, argument_1, argument_2)	\
	({																					\
		register uint32_t 	result __asm("r0");											\
		register uint32_t 	arg0 __asm("r0") = (uint32_t)argument_0;					\
		register uint32_t 	arg1 __asm("r1") = (uint32_t)argument_1;					\
		register uint32_t 	arg2 __asm("r2") = (uint32_t)argument_2;					\
																						\
		__asm volatile(																	\
			"svc %[svc_n]		\n\t"													\
			: "+r" (result)																\
			: [svc_n] "i" (svc_num),													\
			  "r" (arg0), "r" (arg1), "r" (arg2)										\
			: "r12", "lr", "memory"														\
		);																				\
																						\
		result;																			\
	})

#define _PORT_ENTER_SVC_4_ARGS_AND_RETURN(svc_num, argument_0, argument_1, argument_2, argument_3)	\
	({																								\
		register uint32_t 	result __asm("r0");														\
		register uint32_t 	arg0 __asm("r0") = (uint32_t)argument_0;								\
		register uint32_t 	arg1 __asm("r1") = (uint32_t)argument_1;								\
		register uint32_t 	arg2 __asm("r2") = (uint32_t)argument_2;								\
		register uint32_t 	arg3 __asm("r3") = (uint32_t)argument_3;								\
																									\
		__asm volatile(																				\
			"svc %[svc_n]		\n\t"																\
			: "+r" (result)																			\
			: [svc_n] "i" (svc_num),																\
			  "r" (arg0), "r" (arg1), "r" (arg2), "r" (arg3)										\
			: "r12", "lr", "memory"																	\
		);																							\
																									\
		result;																						\
	})

#define _PORT_IS_INSIDE_SYSCALL()		(__get_IPSR() == ((uint32_t)(SVCall_IRQn + 16)))


#endif
