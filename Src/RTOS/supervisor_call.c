#include "supervisor_call.h"
#include "os_manager.h"
#include "Port/port_macroses.h"
#include "supervisor_core_functions.h"

void SVC_Handler_C(uint32_t* sp) {
	uint32_t pc_reg = sp[6];
	uint8_t svc_arg = ((uint8_t*)pc_reg)[-2];

	uint32_t arg1 = sp[0];
	uint32_t arg2 = sp[1];
	uint32_t arg3 = sp[2];
	uint32_t arg4 = sp[3];

	uint32_t result = -1;

	switch(svc_arg) {
		case SVC_START_OS:
			PORT_START_SCHEDULER_FROM_SVC();
			break;

		case SVC_CREATE_TASK:
			result = (uint32_t)OS_CreateTaskStatic_SVC_Handle((void(*)(void))arg1, (OS_StackHandle_t)arg2, arg3);
			break;

		case SVC_DELETE_TASK:
			result = (uint32_t)OS_DeleteTask_SVC_Handle((OS_TaskHandle_t)arg1);
			break;

		case SVC_SET_FPSCR:
			OS_FPU_Settings_SVC_Handle(sp, arg1, arg2, arg3, arg4);
			break;
	}

	sp[0] = result;
}
