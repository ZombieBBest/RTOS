#ifndef RTOS_CORE_CORE_MUTEX_H_
#define RTOS_CORE_CORE_MUTEX_H_

#include "core_context.h"

typedef struct {
	_Bool is_free;
	uint32_t priority_ceiling;
	OS_TCB_t* owner_ptr;

	OS_TCB_t* queue_wait_list[CONFIG_NUM_OF_PRIORITIES];
	uint32_t priority_bitmup;
} OS_Mutex_t;

//GLOBAL ONLY
#define OS_CREATE_MUTEX(name)	\
	__attribute__((section(".core_mutexes"), used)) static OS_Mutex_t sys_##name##_mutex_struct; 	\
	extern const void* name; 																		\
	const void* name = &sys_##name##_mutex_struct

#endif
