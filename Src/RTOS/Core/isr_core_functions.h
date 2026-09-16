#ifndef RTOS_ISR_CORE_FUNCTIONS_H_
#define RTOS_ISR_CORE_FUNCTIONS_H_

#include "os_manager.h"
#include "../Drivers/GPIO/gpio_stm32f4.h"

// =================== FUNCTIONS_PROTOTYPES ==================

OS_TaskHandle_t _isr_create_task_static_handle(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);

OS_Return_t _isr_delete_task_handle(OS_TaskHandle_t handle);

void _isr_task_suicide_handle(void);

void _isr_fpu_settings_handle(uint32_t* sp, OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n,
									OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r);

OS_Return_t _isr_gpio_pin_request(Drivers_GPIO_PortsEnum_t gpio, uint16_t pins_mask);

OS_Return_t _isr_gpio_pin_free(Drivers_GPIO_PortsEnum_t gpio, uint16_t pins_mask);

#endif
