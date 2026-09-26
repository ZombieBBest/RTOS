#ifndef RTOS_DRIVERS_GPIO_GPIO_STM32F4_H_
#define RTOS_DRIVERS_GPIO_GPIO_STM32F4_H_

#include "stdint.h"

typedef struct {
	uint32_t moder;
	uint32_t ospeedr;
	uint32_t pupdr;
	uint32_t afr[2];
	uint16_t otyper;
} RTOS_GPIO_PinSettings;

#endif
