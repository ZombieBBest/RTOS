#include "core_mutex.h"
#include "core_supervisor_dispatcher.h"
#include "../Port/port_macroses.h"

OS_Return_t OS_TakeMutex(OS_MutexHandle_t mutex_handle) {
	return (OS_Return_t)_PORT_PRIVATE_SYSCALL_1_RET(SVC_TAKE_MUTEX, (uint32_t)mutex_handle);
}
