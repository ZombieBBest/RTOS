#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "context.h"


#define OS_Start()													\
	__asm volatile(													\
		"str %[f_task], [%[s_task]] \n\t"							\
		"mov r0, %[source]			\n\t"							\
		"cpsie i					\n\t"							\
		"svc #0						\n\t"							\
		: 															\
		: [f_task] "r" (&os_context.task_context[0]),				\
		  [s_task] "r" (&os_context.current_run_task),				\
		  [source] "r" (os_context.task_context[0].stack_pointer)	\
		: "r0", "memory"											\
	)

typedef void* OS_TaskHandle_t;

typedef enum {
	OS_EXIT_ERROR,
	OS_EXIT_SUCCESS,
} OS_Return_t;

void OS_Initialization(void);

OS_TaskHandle_t* OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t OS_DeleteTask(OS_TaskHandle_t* handle);

static inline void OS_Yield(void) {
	__asm volatile("" : : : "memory");
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}

#endif
