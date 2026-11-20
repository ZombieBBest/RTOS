#include "core_task_handlers.h"

#include "../Port/port_functions.h"
#include "../Port/port_macroses.h"
#include "../Port/port_mpu.h"
#include "core_supervisor_dispatcher.h"
#include "core_mutex.h"

// ========================= EXTERN =========================

extern uint8_t __core_mutexes_start__[];
extern uint8_t __core_mutexes_end__[];

// ===================== INTERNAL_STATIC ====================

static inline void _add_to_ready_list(OS_TCB_t* task_ptr, uint32_t priority) {
	task_ptr->state = OS_STATE_READY;
	task_ptr->priority = priority;
	task_ptr->base_priority = priority;

	os_context.priority_bitmap |= (1 << priority);

	OS_TCB_t* head = os_context.task_ready_list[priority];

	if (!head) {
		task_ptr->next_node_ptr = task_ptr;
		task_ptr->prev_node_ptr = task_ptr;
		os_context.task_ready_list[priority] = task_ptr;
	}
	else {
		OS_TCB_t* tail = head->prev_node_ptr;

		task_ptr->next_node_ptr = head;
		task_ptr->prev_node_ptr = tail;

		tail->next_node_ptr = task_ptr;
		head->prev_node_ptr = task_ptr;
	}
}

static inline void _remove_from_ready_list(OS_TCB_t* task_ptr, OS_TaskStates_t state) {
	uint32_t priority = task_ptr->priority;

	if (task_ptr->next_node_ptr == task_ptr) {
		os_context.priority_bitmap &= ~(1 << priority);

		os_context.task_ready_list[priority] = NULL;
	}
	else {
		OS_TCB_t* prev = task_ptr->prev_node_ptr;
		OS_TCB_t* next = task_ptr->next_node_ptr;

		prev->next_node_ptr = next;
		next->prev_node_ptr = prev;

		if (os_context.task_ready_list[priority] == task_ptr) {
			os_context.task_ready_list[priority] = next;
		}
	}

	task_ptr->next_node_ptr = NULL;
	task_ptr->prev_node_ptr = NULL;

	task_ptr->state = state;
}

static inline OS_TCB_t* _get_free_TCB(void) {
	OS_TCB_t* head = os_context.free_TCB_ptr;

	if (head && head->state == OS_STATE_FREE) {
		os_context.free_TCB_ptr = os_context.free_TCB_ptr->next_node_ptr;

		if (os_context.free_TCB_ptr) {
			os_context.free_TCB_ptr->prev_node_ptr = NULL;
		}

		head->next_node_ptr = NULL;
	}
	else {
		head = NULL;
	}

	return head;
}

static inline void _add_free_TCB(OS_TCB_t* task_ptr) {
	OS_TCB_t* head = os_context.free_TCB_ptr;

	if (head) {
		task_ptr->next_node_ptr = head;
		head->prev_node_ptr = task_ptr;
	}

	os_context.free_TCB_ptr = task_ptr;
	task_ptr->state = OS_STATE_FREE;
}

// ======================== INTERNAL ========================

void _task_suicide(void) {
	_PORT_PRIVATE_SYSCALL_0_RET(SVC_SUICIDE_TASK);
}

// ====================== ISR_HANDLES =======================

OS_TaskHandle_t _core_create_task_handler(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	OS_TCB_t* free_TCB = NULL;
	OS_StackDescriptor_t* desc = (OS_StackDescriptor_t*)handle;

	if (!_PORT_IS_INSIDE_CORE_ISR()) {
		return NULL;
	}

	free_TCB = _get_free_TCB();
	if (free_TCB) {
		if (desc && !desc->is_taken && priority < CONFIG_NUM_OF_PRIORITIES) {
			free_TCB->state = OS_STATE_RESERVED;
			desc->is_taken = 1;
		}
		else {
			free_TCB = NULL;
		}
	}

	if (free_TCB) {
		free_TCB->stack_descriptor = desc;

		free_TCB->task_function_ptr = task_ptr;
		free_TCB->mpu_sr = _port_mpu_prepare_task_stack_region(free_TCB->stack_descriptor->stack_ptr, free_TCB->stack_descriptor->stack_size);
		free_TCB->stack_pointer = _port_stack_init(task_ptr, _task_suicide, free_TCB->stack_descriptor->stack_ptr,
														free_TCB->stack_descriptor->stack_size);

		_add_to_ready_list(free_TCB, priority);
	}

	return (OS_TaskHandle_t*)free_TCB;
}

OS_Return_t _core_delete_task_handler(OS_TaskHandle_t handle) {
	OS_TCB_t* task_ptr = (OS_TCB_t*)handle;

	if (!_PORT_IS_INSIDE_CORE_ISR()) {
		return OS_EXIT_ERROR_NOT_FROM_SYSCALL;
	}

	if (task_ptr) {
		task_ptr->stack_descriptor->is_taken = 0;

		_remove_from_ready_list(task_ptr, OS_STATE_RESERVED);

		_add_free_TCB(task_ptr);

		OS_TCB_t* current_run_task = (OS_TCB_t*)os_context.current_run_task;

		if (task_ptr == current_run_task) {
			_port_yield();
		}

		return OS_EXIT_SUCCESS;
	}
	else {
		return OS_EXIT_ERROR_INVALID_ARGUMENT;
	}
}

OS_Return_t _core_task_suicide_handler(void) {
	OS_TCB_t* c = os_context.current_run_task;
	return _core_delete_task_handler(c);
}

OS_Return_t _core_fpu_settings_handler(uint32_t* sp, OS_FPU_HALFPRECISION_t h, OS_FPU_NaN_MODE_t n,
									OS_FPU_FLASH_TO_ZERO_t f, OS_FPU_ROUNDING_t r) {

	if (!_PORT_IS_INSIDE_CORE_ISR()) {
		return OS_EXIT_ERROR_NOT_FROM_SYSCALL;
	}

	_port_fpu_mode_settings(sp, (uint32_t)h, (uint32_t)n, (uint32_t)f, (uint32_t)r);

	return OS_EXIT_SUCCESS;
}

OS_Return_t _core_mutex_take_handler(OS_Mutex_t* mutex) {
	OS_TCB_t* task_ptr = os_context.current_run_task;

	if (!_PORT_IS_INSIDE_CORE_ISR()) {
		return OS_EXIT_ERROR_NOT_FROM_SYSCALL;
	}

	if ((uintptr_t)__core_mutexes_start__ > (uintptr_t)mutex ||
		(uintptr_t)__core_mutexes_end__ <= (uintptr_t)mutex  ||
		((uintptr_t)mutex - (uintptr_t)__core_mutexes_start__) % sizeof(OS_Mutex_t) != 0
	) {
		return OS_MUTEX_INVALID_HANDLE;
	}

	if (task_ptr->priority > mutex->priority_ceiling) {
		return OS_MUTEX_INVALID_PRIORITY;
	}

	if (mutex->is_free) {
		mutex->is_free = 0;
		mutex->owner_ptr = task_ptr;

		task_ptr->priority = mutex->priority_ceiling;
	}
	else {
		_remove_from_ready_list(task_ptr, OS_STATE_WAITING);

		mutex->priority_bitmap |= (1 << task_ptr->priority);

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

		_port_yield();
	}

	return OS_EXIT_SUCCESS;
}
