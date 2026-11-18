#include "core_mutex.h"


void _core_mutex_take(OS_Mutex_t* mutex) {
	OS_TCB_t* task_ptr = os_context.current_run_task;

	if (mutex->is_free) {
		mutex->is_free = 0;
		mutex->owner_ptr = task_ptr;

		task_ptr->priority = mutex->priority_ceiling;
	}
	else {
		task_ptr->state = OS_STATE_WAITING;
		mutex->priority_bitmup |= (1 << task_ptr->priority);

		OS_TCB_t* head = mutex->queue_wait_list[task_ptr->priority];

		if (!head) {
			task_ptr->next_node_ptr = task_ptr;
			task_ptr->prev_node_ptr = task_ptr;
			mutex->queue_wait_list[task_ptr->priority] = task_ptr;
		}
		else {
			OS_TCB_t* tail = head->prev_node_ptr;

			task_ptr->next_node_ptr = head;
			task_ptr->prev_node_ptr = tail;

			tail->next_node_ptr = task_ptr;
			head->prev_node_ptr = task_ptr;
		}
	}
}
