#include "drivers_periphery_include.h"
#include <string.h>

OS_DriversFunctions_t drivers_handlers_table[CONFIG_NUM_OF_DRIVERS];

uint8_t drivers_handlers_table_free_index = 0;

uint8_t table_of_drivers_indexes[DRIVERS_NUM];

void _drivers_initialization(void) {
	os_drivers_handlers_table_ptr = drivers_handlers_table;

	memset(drivers_handlers_table, (uintptr_t)NULL, sizeof(OS_DriversFunctions_t) * CONFIG_NUM_OF_DRIVERS);
	memset(table_of_drivers_indexes, -1, sizeof(uint8_t) * DRIVERS_NUM);
}
