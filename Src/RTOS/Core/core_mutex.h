#ifndef RTOS_CORE_CORE_MUTEX_H_
#define RTOS_CORE_CORE_MUTEX_H_

#include "core_context.h"
#include "core_return_type.h"

typedef struct {
	_Bool is_free;
	uint32_t priority_ceiling;
	OS_TCB_t* owner_ptr;

	OS_TCB_t* queue_wait_list[CONFIG_NUM_OF_PRIORITIES];
	uint32_t priority_bitmup;
} OS_Mutex_t;

typedef void* OS_MutexHandle_t;

//GLOBAL ONLY
#define OS_CREATE_MUTEX(name)	\
	__attribute__((section(".core_mutexes"), used)) static OS_Mutex_t sys_##name##_mutex_struct; 	\
	extern const OS_MutexHandle_t name; 															\
	const OS_MutexHandle_t name = &sys_##name##_mutex_struct

OS_Return_t OS_TakeMutex(OS_MutexHandle_t mutex_handle);

#endif
