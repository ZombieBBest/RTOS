#ifndef RTOS_MEMORY_H_
#define RTOS_MEMORY_H_

#include <string.h>
#include <stdint.h>

typedef void* OS_StackHandle_t;

typedef struct{
	void* stack_ptr;
	size_t stack_size;
	_Bool is_taken;
} OS_StackDescriptor_t;


//size_in_bytes must be a multiply of 2
#define OS_CREATE_STACK(name, size_in_bytes)												\
	static uint8_t name##_sys_stack[size_in_bytes] __attribute__((aligned(size_in_bytes)));	\
																							\
	static OS_StackDescriptor_t name##_sys_descriptor = {									\
			.stack_ptr = (void*)&name##_sys_stack,											\
			.stack_size = size_in_bytes,													\
			.is_taken = 0,																	\
	};																						\
	OS_StackHandle_t name = (OS_StackHandle_t)&name##_sys_descriptor;





#endif
