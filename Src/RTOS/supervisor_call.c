#include "supervisor_call.h"
#include "os_manager.h"
#include "Port/port_macroses.h"
#include "supervisor_core_functions.h"

uint32_t OS_SVC_Dispatcher(uint32_t svc_arg, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t* caller_sp) {
	uint32_t result = -1;

	switch(svc_arg) {
		case SVC_START_OS:
			PORT_START_SCHEDULER_FROM_SVC(arg1);
			break;

		case SVC_CREATE_TASK:
			result = (uint32_t)_svc_create_task_static_handle((void(*)(void))arg1, (OS_StackHandle_t)arg2, arg3);
			break;

		case SVC_DELETE_TASK:
			result = (uint32_t)_svc_delete_task_handle((OS_TaskHandle_t)arg1);
			break;

		case SVC_SET_FPSCR:
			_svc_fpu_settings_handle(caller_sp, arg1, arg2, arg3, arg4);
			break;
	}

	return result;
}
