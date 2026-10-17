#ifndef RTOS_DRIVERS_PERIPHERY_INCLUDE_H_
#define RTOS_DRIVERS_PERIPHERY_INCLUDE_H_

#include "../Core/core_config.h"
#include "GPIO/gpio_stm32f4.h"
#include "../Core/core_drivers_table.h"

//---------------------------------------------

extern OS_DRIVERS_DriversFunctions_t drivers_functions_table[CONFIG_NUM_OF_DRIVERS];

//---------------------------------------------

typedef enum {
	DRIVERS_GPIO_PORT_A,
	DRIVERS_GPIO_PORT_B,
	DRIVERS_GPIO_PORT_C,
	DRIVERS_GPIO_PORTS_NUM
} OS_DRIVERS_DriversEnum_t;

//---------------------------------------------

typedef union {
	OS_DRIVERS_GPIO_PinSettings_t pin;
} OS_DRIVERS_DriverSettings_t;

//---------------------------------------------

typedef enum {
	DRIVERS_GPIO_PIN_0	= (1UL << 0UL),
	DRIVERS_GPIO_PIN_1	= (1UL << 1UL),
	DRIVERS_GPIO_PIN_2	= (1UL << 2UL),
	DRIVERS_GPIO_PIN_3	= (1UL << 3UL),
	DRIVERS_GPIO_PIN_4	= (1UL << 4UL),
	DRIVERS_GPIO_PIN_5	= (1UL << 5UL),
	DRIVERS_GPIO_PIN_6	= (1UL << 6UL),
	DRIVERS_GPIO_PIN_7	= (1UL << 7UL),
	DRIVERS_GPIO_PIN_8	= (1UL << 8UL),
	DRIVERS_GPIO_PIN_9	= (1UL << 9UL),
	DRIVERS_GPIO_PIN_10 = (1UL << 10UL),
	DRIVERS_GPIO_PIN_11 = (1UL << 11UL),
	DRIVERS_GPIO_PIN_12 = (1UL << 12UL),
	DRIVERS_GPIO_PIN_13 = (1UL << 13UL),
	DRIVERS_GPIO_PIN_14 = (1UL << 14UL),
	DRIVERS_GPIO_PIN_15 = (1UL << 15UL),
	DRIVERS_GPIO_PIN_NUM
} Drivers_GPIO_PinsEnum_t;

#endif
