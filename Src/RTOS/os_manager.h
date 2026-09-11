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

// ==================== TYPES_DEFINITION ====================

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

// =================== FUNCTIONS_PROTOTYPES==================

void OS_Initialization(void);

void OS_Start(void);

OS_TaskHandle_t OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle);

void OS_FPU_Settings(OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n, OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r);

// ================= PUBLIC_STATIC_FUNCTIONS ================

static inline void OS_Yield(void) {
	_port_PendSV_enter();
}

#endif
