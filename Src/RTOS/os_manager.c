#include "os_manager.h"

#include <stm32f4xx.h>
#include <string.h>
#include "Port/port_functions.h"
#include "critical.h"
#include "memory.h"
#include "context.h"
#include "config.h"


// ======================== INTERNAL ========================

static inline void _context_initialization(void) {
	memset((void*)&os_context, 0, sizeof(OS_Context_t));

	for (uint32_t i = 0; i < CONFIG_NUM_OF_TASKS - 1; i++) {
		os_context.task_context[i].next_node_ptr = (OS_TCB_t*)&os_context.task_context[i + 1];
		os_context.task_context[i + 1].prev_node_ptr = (OS_TCB_t*)&os_context.task_context[i];
	}

	os_context.free_TCB_ptr = (OS_TCB_t*)&os_context.task_context[0];
}

void _idle_task(void) {
	while (1) {
		__WFI();
	}
}

// ======================= PUBLIC_API =======================

OS_CREATE_STACK(_idle_stack_handle, 256);

void OS_Initialization(void) {
	__disable_irq();
	_port_fpu_apply_settings();

	NVIC_SetPriority(SVCall_IRQn, 13);
	NVIC_SetPriority(SysTick_IRQn, 14);
	NVIC_SetPriority(PendSV_IRQn, 15);

	_context_initialization();
	_port_sys_SysTick_initialization(CONFIG_F_CPU_HZ, CONFIG_TICK_RATE_HZ);
	__enable_irq();

	OS_CreateTaskStatic(_idle_task, _idle_stack_handle, 0);
}

OS_TaskHandle_t OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	register OS_TaskHandle_t result 		__asm("r0");

	register void(*arg0)(void)  	 		__asm("r0") = task_ptr;
	register OS_StackHandle_t 	arg1 		__asm("r1") = handle;
	register uint32_t 			arg2 		__asm("r2") = priority;

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "=r" (result)
		: [svc_num] "i" (SVC_CREATE_TASK),
		  "r" (arg0), "r" (arg1), "r" (arg2)
		: "r12", "lr", "memory"
	);

	return result;
}

OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle) {
	register OS_Return_t result __asm("r0");

	register uint32_t 	arg0 	__asm("r0") = (uint32_t)handle;

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "=r" (result)
		: [svc_num] "i" (SVC_DELETE_TASK),
		  "r" (arg0)
		: "r12", "lr", "memory"
	);

	return result;
}

void OS_FPU_Settings(OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n, OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r) {
	register uint32_t arg0 __asm("r0") = h;
	register uint32_t arg1 __asm("r1") = n;
	register uint32_t arg2 __asm("r2") = f;
	register uint32_t arg3 __asm("r3") = r;

	__asm volatile(
		"svc %[svc_num]		\n\t"
		:
		: [svc_num] "i" (SVC_SET_FPSCR),
		  "r"(arg0), "r"(arg1), "r"(arg2), "r"(arg3)
		: "r12", "lr", "memory"
	);
}
