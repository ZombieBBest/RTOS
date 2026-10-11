#ifndef RTOS_MEMORY_H_
#define RTOS_MEMORY_H_

#include <string.h>
#include <stdint.h>
#include <assert.h>

// ==================== TYPES_DEFINITION ====================

typedef void* OS_StackHandle_t;

typedef struct{
	void* stack_ptr;
	size_t stack_size;
	_Bool is_taken;
} OS_StackDescriptor_t;

// ======================= PUBLIC_API =======================

/* protected with mpu */
/* LOCAL ONLY. Size_in_bytes must be a multiply of 2 and greater than or equal to 256 */
#define OS_CREATE_STACK(size_in_bytes)																								\
({																																	\
	static_assert((size_in_bytes >= 256), "Error: stack must be greater than or equal to 256");										\
	static_assert((size_in_bytes & (size_in_bytes - 1)) == 0, "Error: stack size must be a power of 2 (e.g. 256, 512, 1024...)");	\
																																	\
	static uint8_t sys_stack[size_in_bytes] __attribute__((aligned(size_in_bytes)));												\
																																	\
	static OS_StackDescriptor_t sys_descriptor = {																					\
			.stack_ptr = (void*)&sys_stack,																							\
			.stack_size = size_in_bytes,																							\
			.is_taken = 0,																											\
	};																																\
	(OS_StackHandle_t)&sys_descriptor;																								\
})

#endif
