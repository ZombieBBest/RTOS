#include "context_switch_logic.h"

#include <stm32f4xx.h>
#include "Port/port_mpu.h"
#include "config.h"
#include "context.h"

// ====================== SCHEDULER_API =====================

void* _scheduler_switch_logic(void* current_task_stack_pointer) {
	os_context.current_run_task->stack_pointer = current_task_stack_pointer;

	uint32_t max_ready_priority = 31 - __builtin_clz(os_context.priority_bitmap);

	OS_TCB_t* chosen_task = (OS_TCB_t*)os_context.task_ready_list[max_ready_priority];

	_port_mpu_set_task_stack_region(chosen_task->mpu_sr.rbar, chosen_task->mpu_sr.rasr);


	uint32_t current_run_task_priority = os_context.current_run_task->priority;

	os_context.task_ready_list[current_run_task_priority] = os_context.task_ready_list[current_run_task_priority]->next_node_ptr;

	os_context.current_run_task = chosen_task;

	return chosen_task->stack_pointer;
}
