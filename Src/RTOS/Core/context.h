#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>
#include <stm32f4xx.h>

#include "../Drivers/periphery_enums.h"
#include "../Port/port_mpu.h"
#include "memory.h"
#include "config.h"

// ==================== TYPES_DEFINITION ====================

typedef enum {
	OS_STATE_FREE,
	OS_STATE_READY,
	OS_STATE_RESERVED,
	OS_NUM_OF_STATES
} OS_TaskStates_t;

typedef struct OS_TCB_t {
	uint32_t state;
	uint32_t priority;
	void* 	 stack_pointer;
	struct OS_TCB_t* prev_node_ptr;
	struct OS_TCB_t* next_node_ptr;
	OS_StackDescriptor_t* stack_descriptor;

	Port_MPU_StackRegion_t mpu_sr;
	uint16_t permitted_gpio_pins[DRIVERS_GPIO_PORTS_NUM];
} OS_TCB_t;

typedef struct {
	OS_TCB_t* current_run_task;
	uint32_t  global_counter;
	uint32_t  priority_bitmap;
	OS_TCB_t  task_context[CONFIG_NUM_OF_TASKS];
	OS_TCB_t* free_TCB_ptr;
	OS_TCB_t* task_ready_list[CONFIG_NUM_OF_PRIORITIES];

	uint16_t busy_gpio_pins[DRIVERS_GPIO_PORTS_NUM];
} OS_Context_t;

// ========================== EXTERN =========================

extern volatile OS_Context_t os_context;

#endif
