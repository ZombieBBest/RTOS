#include "gpio_stm32f4.h"
#include <stm32f4xx.h>

#include "../drivers_periphery_include.h"
#include "../../Core/core_manager.h"

OS_Return_t OS_GPIO_Register_Driver(void) {
	uint8_t id = drivers_functions_table_free_index;

	if (id >= DRIVERS_NUM) {
		return OS_DRIVER_EXIT_ERROR_DRIVERS_OVERFLOW;
	}

	drivers_functions_table_free_index++;

	drivers_functions_table[id];





	return OS_EXIT_SUCCESS;
}
