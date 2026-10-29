#ifndef RTOS_CORE_CORE_DRIVERS_TABLE_H_
#define RTOS_CORE_CORE_DRIVERS_TABLE_H_

#include "core_return_type.h"

typedef struct {
	OS_Return_t (*take)(void);
	OS_Return_t (*give)(void);
	OS_Return_t (*mode)(void);
	OS_Return_t (*send)(void);
	OS_Return_t (*read)(void);
} OS_DriversFunctions_t;

extern OS_DriversFunctions_t* os_drivers_handlers_table_ptr;

#endif
