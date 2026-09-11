#include "port_sys_timer.h"

#include <stm32f4xx.h>

// ======================= PUBLIC_API =======================

void _port_sys_SysTick_initialization(uint32_t cpu_f_hz, uint32_t tick_hz) {
	SysTick->LOAD = cpu_f_hz / tick_hz - 1UL;
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

void _port_sys_SysTick_start(void) {
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}
