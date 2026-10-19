#include "core_manager.h"

#include <string.h>
#include "../Port/port_functions.h"
#include "../Port/port_macroses.h"
#include "../Port/port_mpu.h"
#include "../Port/port_sys_timer.h"
#include "../Drivers/GPIO/gpio_stm32f4.h"
#include "core_config.h"
#include "core_context.h"
#include "core_supervisor_dispatcher.h"
#include "core_handlers.h"

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
	_port_sys_SysTick_initialization(CONFIG_F_CPU_HZ, CONFIG_TICK_RATE_PER_SEC_HZ);

	_port_mpu_initialization();

	_port_mpu_register_stacking_error_callback((void(*)(void))_core_task_context_reset_handler);

	__enable_irq();

	OS_StackHandle_t _idle_stack_handle = OS_CREATE_STACK(256);

	OS_CreateTask(_idle_task, _idle_stack_handle, 0);
}

void OS_Start(void) {
	_port_sys_SysTick_start();
	OS_TCB_t* most_priority_task = _get_most_priority_task();
	os_context.current_run_task = most_priority_task;

	_PORT_OS_RUN(SVC_START_OS, most_priority_task->stack_pointer);
}

OS_TaskHandle_t OS_CreateTask(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	return (OS_TaskHandle_t)_PORT_PRIVATE_SYSCALL_3_RET(SVC_CREATE_TASK, (uint32_t)task_ptr, (uint32_t)handle, priority);
}

OS_Return_t OS_DeleteTask(OS_TaskHandle_t handle) {
	return (OS_Return_t)_PORT_PRIVATE_SYSCALL_1_RET(SVC_DELETE_TASK, (uint32_t)handle);
}

OS_Return_t OS_FPU_Settings(OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n, OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r) {
	return (OS_Return_t)_PORT_PRIVATE_SYSCALL_4_RET(SVC_SET_FPSCR, h, n, f, r);
}

void OS_RestartTask(void) {
	_PORT_PRIVATE_SYSCALL_0_RET(SVC_RESTART_TASK);
}

void OS_Yield(void) {
	_PORT_PRIVATE_SYSCALL_0_RET(SVC_YIELD);
}

void OS_DriverTake() {

}
