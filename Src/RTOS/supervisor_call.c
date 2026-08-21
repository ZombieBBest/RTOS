#include "supervisor_call.h"
#include "os_manager.h"

#define SVC_START_CONDITION()				\
	__asm volatile (						\
		"mov r0, %[task_sp] 	\n\t"		\
		"ldr lr, =0xFFFFFFFD 	\n\t"		\
		"b OS_Load_Context 		\n\t"		\
		:									\
		: [task_sp] "r" (arg1)				\
		: "r1", "r2", "r3", "r12", "memory" \
	)

extern OS_TaskHandle_t OS_CreateTaskStatic_SVC(void(*task_ptr)(void), OS_StackHandle_t handle, uint32_t priority);
extern OS_Return_t OS_DeleteTask_SVC(OS_TaskHandle_t handle);

void SVC_Handler_C(uint32_t* sp) {
	uint32_t pc_reg = sp[6];
	uint8_t svc_arg = ((uint8_t*)pc_reg)[-2];

	uint32_t arg1 = sp[0];
	uint32_t arg2 = sp[1];
	uint32_t arg3 = sp[2];

	uint32_t result = 0xFFFFFFFF;

	switch(svc_arg) {
		case SVC_START_OS:
			SVC_START_CONDITION();
			break;

		case SVC_CREATE_TASK:
			result = (uint32_t)OS_CreateTaskStatic_SVC((void(*)(void))arg1, (OS_StackHandle_t)arg2, arg3);
			break;

		case SVC_DELETE_TASK:
			result = (uint32_t)OS_DeleteTask_SVC((OS_TaskHandle_t)arg1);
			break;
	}

	sp[0] = result;
}
