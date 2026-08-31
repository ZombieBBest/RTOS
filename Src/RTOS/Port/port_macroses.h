#ifndef RTOS_PORT_PORT_MACROSES_H_
#define RTOS_PORT_PORT_MACROSES_H_

#define FPSCR_AHP_Pos				(26U)
#define FPSCR_DN_Pos				(25U)
#define FPSCR_FZ_Pos				(24U)
#define FPSCR_RMODE_Pos				(22U)

#define PORT_FPU_SETTINGS(AHP, DN, FZ, RMODE)																				\
	do {																													\
		sp[24] &= ~((1 << FPSCR_AHP_Pos) | (1 << FPSCR_DN_Pos) | (1 << FPSCR_FZ_Pos) | (3 << FPSCR_RMODE_Pos));				\
		sp[24] |= ((uint32_t)AHP << FPSCR_AHP_Pos) | ((uint32_t)DN << FPSCR_DN_Pos) | 										\
			((uint32_t)FZ << FPSCR_FZ_Pos) | ((uint32_t)RMODE << FPSCR_RMODE_Pos);											\
	} while(0)

#define INITIAL_EXC_RETURN   	0xFFFFFFED

#define PORT_START_SCHEDULER_FROM_SVC()		\
	__asm volatile (						\
		"mov r0, %[task_sp] 	\n\t"		\
		"ldr lr, =%[lr_exc] 	\n\t"		\
		"b OS_Load_Context 		\n\t"		\
		:									\
		: [task_sp] "r" (arg1),				\
		  [lr_exc]  "i" (INITIAL_EXC_RETURN)\
		: "r0", "lr", "memory"				\
	)

#define PORT_OS_RUN(svc_n, first_task_stack_pointer)												\
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
