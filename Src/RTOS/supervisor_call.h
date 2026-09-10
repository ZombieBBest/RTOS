#ifndef RTOS_SUPERVISOR_CALL_H_
#define RTOS_SUPERVISOR_CALL_H_

// ==================== TYPE_DEFINITIONS ====================

typedef enum {
	SVC_START_OS,
	SVC_CREATE_TASK,
	SVC_DELETE_TASK,
	SVC_DELETE_CURRENT_TASK,
	SVC_SET_FPSCR
} OS_SVC_Enter_t;

#endif
