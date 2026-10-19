#include "core_supervisor_dispatcher.h"

#include "../Port/port_functions.h"
#include "../Drivers/GPIO/gpio_stm32f4.h"
#include "core_manager.h"
#include "core_handlers.h"

// ====================== ISR_HANDLE ========================

uint32_t OS_SVC_Dispatcher(uint32_t svc_arg, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t* caller_sp) {
	uint32_t result = -1;

	switch(svc_arg) {
		case SVC_START_OS:
			_port_start_scheduler_from_svc((void*)arg0);
			break;

		case SVC_CREATE_TASK:
			result = (uint32_t)_core_create_task_handler((void(*)(void))arg0, (OS_StackHandle_t)arg1, arg2);
			break;

		case SVC_DELETE_TASK:
			result = (uint32_t)_core_delete_task_handler((OS_TaskHandle_t)arg0);
			break;

		case SVC_YIELD:
			_port_yield();
			break;

		case SVC_SUICIDE_TASK:
			result = (uint32_t)_core_task_suicide_handler();
			break;

		case SVC_SET_FPSCR:
			result = (uint32_t)_core_fpu_settings_handler(caller_sp, arg0, arg1, arg2, arg3);
			break;

		case SVC_RESTART_TASK:
			_core_task_context_reset_handler();
			break;
	}

	return result;
}
