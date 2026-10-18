#ifndef RTOS_CORE_CORE_SYS_FUNCTIONS_H_
#define RTOS_CORE_CORE_HANDLERS_H_

#include "../Drivers/GPIO/gpio_stm32f4.h"
#include "core_context.h"
#include "core_manager.h"

// =================== FUNCTIONS_PROTOTYPES ==================

OS_TaskHandle_t _core_create_task_handler(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t _core_delete_task_handler(OS_TaskHandle_t handle);

OS_Return_t _core_task_suicide_handler(void);

OS_Return_t _core_fpu_settings_handler(uint32_t* sp, OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n,
									OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r);

void _core_task_context_reset_handler(void);

#endif
