#ifndef RTOS_CORE_CORE_DRIVERS_TABLE_H_
#define RTOS_CORE_CORE_DRIVERS_TABLE_H_

typedef struct {
	void (*take)(void);
	void (*give)(void);
	void (*mode)(void);
	void (*send)(void);
	void (*read)(void);
} OS_DriversFunctions_t;

extern OS_DriversFunctions_t* os_drivers_functions_table_ptr;

#endif
