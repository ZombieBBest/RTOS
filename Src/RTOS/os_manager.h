#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>
#include "sys_timer.h"
#include "supervisor_call.h"
#include "memory.h"
#include "context.h"

typedef void* OS_TaskHandle_t;

typedef enum {
	OS_EXIT_ERROR,
	OS_EXIT_SUCCESS,
} OS_Return_t;


void OS_Initialization(void);


static inline void OS_Start(void) {
	Sys_SysTick_Start();
	__asm volatile(
		"str %[f_task], [%[s_task]] \n\t"
		"mov r0, %[source]			\n\t"
		"cpsie i					\n\t"
		"svc %[svc_num]				\n\t"
		:
		: [svc_num] "i" (SVC_START_OS),
		  [f_task] "r" (&os_context.task_context[0]),
		  [s_task] "r" (&os_context.current_run_task),
		  [source] "r" (os_context.task_context[0].stack_pointer)
		: "r1", "r2", "r3", "r12", "lr", "memory"
	);
}

static inline void OS_Yield(void) {
	__asm volatile("" : : : "memory");
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}

//Attention! Stack uses 68 bytes for switch
static inline OS_TaskHandle_t OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	register OS_TaskHandle_t r0_result __asm("r0");

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "+r" (r0_result)
		: [svc_num] "i" (SVC_CREATE_TASK)
		: "r12", "lr", "memory"
	);

	return r0_result;
}

static inline OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle) {
	register OS_Return_t r0_result __asm("r0");

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "+r" (r0_result)
		: [svc_num] "i" (SVC_DELETE_TASK)
		: "r12", "lr", "memory"
	);

	return r0_result;
}

#endif
