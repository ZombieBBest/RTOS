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


#endif
