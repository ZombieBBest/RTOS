#include "supervisor_call.h"
#include "os_manager.h"
#include "../Port/port_macroses.h"
#include "isr_core_functions.h"

// ====================== ISR_HANDLE ========================

uint32_t OS_SVC_Dispatcher(uint32_t svc_arg, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t* caller_sp) {
	uint32_t result = -1;

	switch(svc_arg) {
		case SVC_START_OS:
			_port_start_scheduler_from_svc((void*)arg0);
			break;

		case SVC_CREATE_TASK:
			result = (uint32_t)_isr_create_task_static_handle((void(*)(void))arg0, (OS_StackHandle_t)arg1, arg2);
			break;

		case SVC_DELETE_TASK:
			result = (uint32_t)_isr_delete_task_handle((OS_TaskHandle_t)arg0);
			break;

		case SVC_SUICIDE_TASK:
			_isr_task_suicide_handle();
			break;

		case SVC_SET_FPSCR:
			_isr_fpu_settings_handle(caller_sp, arg0, arg1, arg2, arg3);
			break;
	}

	return result;
}
