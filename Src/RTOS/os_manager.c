#include "os_manager.h"

#include <stm32f4xx.h>
#include <string.h>
#include "critical.h"
#include "memory.h"
#include "sys_timer.h"
#include "context.h"
#include "config.h"


// ======================== INTERNAL ========================

static inline void _context_initialization(void) {
	memset((void*)&os_context, 0, sizeof(OS_Context_t));

	for (uint32_t i = 0; i < CONFIG_NUM_OF_TASKS - 1; i++) {
		os_context.task_context[i].next_node_ptr = (OS_TCB_t*)&os_context.task_context[i + 1];
		os_context.task_context[i + 1].prev_node_ptr = (OS_TCB_t*)&os_context.task_context[i];
	}

	os_context.free_TCB_ptr = (OS_TCB_t*)&os_context.task_context[0];
}

static inline void _add_to_ready_list(OS_TCB_t* task_ptr, uint32_t priority) {
	task_ptr->state = OS_STATE_READY;
	task_ptr->priority = priority;

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

static inline void _remove_from_ready_list(OS_TCB_t* task_ptr) {
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

	task_ptr->state = OS_STATE_RESERVED;
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
}

static inline void* _stack_init(void(*task_ptr)(void), OS_StackDescriptor_t* desc) {
	uint32_t* stack_ptr = (uint32_t*)((uintptr_t)desc->stack_ptr + desc->stack_size);

	//ЗНАЧЕНИЕ LR И КОЛИЧЕСТВО РЕГИСТРОВ ЗАВИСЯТ ОТ FPU!
	*(--stack_ptr) = (1 << 24);		*(--stack_ptr) = (uint32_t)task_ptr;	//PSR, PC
	*(--stack_ptr) = 0xFFFFFFFD; 	*(--stack_ptr) = 0;						//LR, R12
	*(--stack_ptr) = 0;				*(--stack_ptr) = 0;						//R3, R2
	*(--stack_ptr) = 0; 			*(--stack_ptr) = 0;						//R1, R0

	*(--stack_ptr) = 0; 			*(--stack_ptr) = 0;						//R11...
	*(--stack_ptr) = 0; 			*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 			*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 			*(--stack_ptr) = 0;						//...R4

	return (void*)stack_ptr;
}

void _auto_task_deleter(void) {
	OS_DeleteTask((OS_TaskHandle_t*)os_context.current_run_task->stack_descriptor);
	//Портится os_context.current_run_task
}

void _idle_task(void) {
	while (1) {
		__WFI();
	}
}

OS_CREATE_STACK(_idle_stack_handle, 128);

// ======================= PUBLIC_API =======================

void OS_Initialization(void) {
	uint32_t prev_irq = OS_ENTER_CRITICAL();

	NVIC_SetPriority(SVCall_IRQn, 0);
	NVIC_SetPriority(PendSV_IRQn, 15);
	NVIC_SetPriority(SysTick_IRQn, 15);

	_context_initialization();
	Sys_SysTick_Initialization();

	OS_CreateTaskStatic(_idle_task, _idle_stack_handle, 0);

	OS_EXIT_CRITICAL(prev_irq);
}

//Attention! Stack uses 64 bytes for switch
OS_TaskHandle_t* OS_CreateTaskStatic(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority) {
	OS_TCB_t* free_task = NULL;
	OS_StackDescriptor_t* desc = (OS_StackDescriptor_t*)handle;


	uint32_t prev_irq = OS_ENTER_CRITICAL();

	free_task = _get_free_TCB();
	if (free_task) {
		if (!desc->is_taken) {
			free_task->state = OS_STATE_RESERVED;
			desc->is_taken = 1;
		}
		else {
			free_task = NULL;
		}
	}

	OS_EXIT_CRITICAL(prev_irq);

	if (free_task) {
		free_task->stack_descriptor = desc;
		free_task->stack_pointer = _stack_init(task_ptr, desc);

		prev_irq = OS_ENTER_CRITICAL();

		_add_to_ready_list(free_task, priority);

		OS_EXIT_CRITICAL(prev_irq);
	}

	return (OS_TaskHandle_t*)free_task;
}

OS_Return_t OS_DeleteTask(OS_TaskHandle_t* handle) {
	OS_TCB_t* task_ptr = (OS_TCB_t*)handle;

	if (!task_ptr) {
		return OS_EXIT_ERROR;
	}

	uint32_t prev_irq = OS_ENTER_CRITICAL();

	_remove_from_ready_list(task_ptr);

	OS_EXIT_CRITICAL(prev_irq);

	task_ptr->stack_descriptor->is_taken = 0;
	task_ptr->stack_descriptor = NULL;

	task_ptr->priority = 0;
	task_ptr->stack_pointer = NULL;
	task_ptr->state = OS_STATE_FREE;


	prev_irq = OS_ENTER_CRITICAL();

	_add_free_TCB(task_ptr);

	OS_EXIT_CRITICAL(prev_irq);

	return OS_EXIT_SUCCESS;
}
