#include "os_manager.h"

#include <string.h>
#include "../Port/port_functions.h"
#include "../Port/port_macroses.h"
#include "../Port/port_mpu.h"
#include "../Port/port_sys_timer.h"
#include "supervisor_call.h"
#include "../Drivers/GPIO/gpio_stm32f4.h"
#include "context.h"
#include "config.h"
#include "sys_core_functions.h"

// ===================== INTERNAL_STATIC ====================

static inline void _context_initialization(void) {
	memset((void*)&os_context, 0, sizeof(OS_Context_t));

	for (uint32_t i = 0; i < CONFIG_NUM_OF_TASKS - 1; i++) {
		os_context.task_context[i].next_node_ptr = (OS_TCB_t*)&os_context.task_context[i + 1];
		os_context.task_context[i + 1].prev_node_ptr = (OS_TCB_t*)&os_context.task_context[i];
	}

	os_context.free_TCB_ptr = (OS_TCB_t*)&os_context.task_context[0];
}

static inline OS_TCB_t* _get_most_priority_task(void) {
	uint32_t max_ready_priority = 31 - __builtin_clz(os_context.priority_bitmap);

	return os_context.task_ready_list[max_ready_priority];
}

// ======================== INTERNAL ========================

OS_CREATE_STACK(_idle_stack_handle, 256);

void _idle_task(void) {
	while (1) {
		__WFI();
	}
}

// ======================= PUBLIC_API =======================

void OS_Initialization(void) {
	__disable_irq();
	_port_fpu_start_settings();

	_port_ISR_settings_apply();

	_context_initialization();
	_port_sys_SysTick_initialization(CONFIG_F_CPU_HZ, CONFIG_TICK_RATE_HZ);

	_port_mpu_initialization();
	_port_mpu_register_stacking_error_callback((void(*)(void))_sys_task_suicide_handle);

	__enable_irq();

	OS_CreateTaskStatic(_idle_task, _idle_stack_handle, 0);
}

void OS_Start(void) {
	_port_sys_SysTick_start();
	OS_TCB_t* most_priority_task = _get_most_priority_task();
	os_context.current_run_task = most_priority_task;

	_PORT_OS_RUN(SVC_START_OS, most_priority_task->stack_pointer);
}

OS_TaskHandle_t OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	return (OS_TaskHandle_t)_PORT_ENTER_SVC_3_ARGS_AND_RETURN(SVC_CREATE_TASK, task_ptr, handle, priority);
}

OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle) {
	return (OS_Return_t)_PORT_ENTER_SVC_1_ARGS_AND_RETURN(SVC_DELETE_TASK, (uint32_t)handle);
}

OS_Return_t OS_FPU_Settings(OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n, OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r) {
	return (OS_Return_t)_PORT_ENTER_SVC_4_ARGS_AND_RETURN(SVC_SET_FPSCR, h, n, f, r);
}

/*OS_Return_t OS_GPIO_PIN_Request(Drivers_GPIO_PortsEnum_t gpio, uint16_t pin) {
	register OS_Return_t 				result 	__asm("r0");

	register Drivers_GPIO_PortsEnum_t	arg0	__asm("r0") = gpio;
	register uint16_t 					arg1 	__asm("r1") = pin;

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "=r" (result)
		: [svc_num] "i" (SVC_GPIO_PIN_REQUEST),
		  "r" (arg0), "r" (arg1)
		: "r12", "lr", "memory"
	);

	return result;
}

OS_Return_t OS_GPIO_PIN_Free(Drivers_GPIO_PortsEnum_t gpio, uint16_t pin) {
	register OS_Return_t 				result 	__asm("r0");

	register Drivers_GPIO_PortsEnum_t	arg0	__asm("r0") = gpio;
	register uint16_t 					arg1 	__asm("r1") = pin;

	__asm volatile(
		"svc %[svc_num]		\n\t"
		: "=r" (result)
		: [svc_num] "i" (SVC_GPIO_PIN_FREE),
		  "r" (arg0), "r" (arg1)
		: "r12", "lr", "memory"
	);

	return result;
}*/
