#include "sys_timer.h"
#include "config.h"
#include <stm32f4xx.h>


void Sys_SysTick_Initialization(void) {
	SysTick->LOAD = CONFIG_F_CPU_HZ / CONFIG_TICK_RATE_HZ - 1UL;
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);
}

void SysTick_Handler(void) {
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}
