#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>
#include "Port/port_functions.h"
#include "Port/port_sys_timer.h"
#include "Port/port_macroses.h"
#include "supervisor_call.h"
#include "memory.h"
#include "context.h"
#include "Port/port_sys_timer.h"

typedef void* OS_TaskHandle_t;

typedef enum {
	OS_EXIT_ERROR,
	OS_EXIT_SUCCESS
} OS_Return_t;


typedef enum {
	FPU_IEEE_FORMAT,
	FPU_ALT_FORMAT
} OS_FPU_HALFPRECISION_t;

typedef enum {
	FPU_NaN_PROPAGATION,
	FPU_DEFAULT_NaN
} OS_FPU_NaN_MODE_t;

typedef enum {
	FPU_IEEE_STANDART,
	FPU_FLASH_TO_ZERO_MODE
} OS_FPU_FLASH_TO_ZERO_t;

typedef enum {
	FPU_ROUND_TO_NEAREST,
	FPU_ROUND_PLUS_INFINITY,
	FPU_ROUND_MINUS_INFINITY,
	FPU_ROUND_TO_ZERO
} OS_FPU_ROUNDING_t;


void OS_Initialization(void);

//Attention! Stack uses 68 bytes for switch
OS_TaskHandle_t OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle);

void OS_FPU_Settings(OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n, OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r);

static inline void OS_Start(void) {
	_port_sys_SysTick_start();
	os_context.current_run_task = (OS_TCB_t*)&os_context.task_context[0];
	PORT_OS_RUN(SVC_START_OS, os_context.task_context[0].stack_pointer);
}

static inline void OS_Yield(void) {
	_port_PendSV_enter();
}

#endif
