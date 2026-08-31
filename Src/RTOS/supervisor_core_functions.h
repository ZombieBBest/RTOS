#ifndef RTOS_SUPERVISOR_CORE_FUNCTIONS_H_
#define RTOS_SUPERVISOR_CORE_FUNCTIONS_H_

#include "os_manager.h"


OS_TaskHandle_t OS_CreateTaskStatic_SVC_Handle(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t OS_DeleteTask_SVC_Handle(OS_TaskHandle_t handle);

void OS_FPU_Settings_SVC_Handle(uint32_t* sp, OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n,
									OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r);


#endif
