#include "context_switch_logic.h"

#include <stm32f4xx.h>
#include "config.h"
#include "context.h"


uint8_t* OS_SwitchLogic(uint8_t* current_task_stack_pointer) {
	OS_TCB_t** current_run_task = (OS_TCB_t**)&os_context.current_run_task;

	(*current_run_task)->stack_pointer = current_task_stack_pointer;

	uint32_t max_ready_priority = 31 - __builtin_clz(os_context.priority_bitmap);

	os_context.task_ready_list[max_ready_priority] = os_context.task_ready_list[max_ready_priority]->next_node_ptr;

	OS_TCB_t* chosen_task = (OS_TCB_t*)os_context.task_ready_list[max_ready_priority];

	*current_run_task = chosen_task;

	return chosen_task->stack_pointer;
}
