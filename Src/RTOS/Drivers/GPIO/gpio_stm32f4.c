#include "gpio_stm32f4.h"
#include <stm32f4xx.h>

#include "../drivers_periphery_include.h"
#include "gpio_stm32f4_handlers.h"

//In main only
OS_Return_t OS_GPIO_Register_Driver(void) {
	uint8_t id = drivers_handlers_table_free_index;

	if (id >= DRIVERS_NUM) {
		return OS_DRIVER_EXIT_ERROR_DRIVERS_OVERFLOW;
	}

	drivers_handlers_table_free_index++;

	drivers_handlers_table[id].take = _drivers_gpio_take_handler;

	return OS_EXIT_SUCCESS;
}
