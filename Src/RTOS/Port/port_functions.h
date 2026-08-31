#ifndef RTOS_PORT_PORT_FUNCTIONS_H_
#define RTOS_PORT_PORT_FUNCTIONS_H_

#include <stdint.h>
#include <stddef.h>
#include <stm32f4xx.h>
#include "core_config.h"

static inline void _port_fpu_apply_settings(void) {
	SCB->CPACR |= (3 << 22) | (3 << 20);

	FPU->FPCCR &= ~(FPU_FPCCR_LSPEN_Msk | FPU_FPCCR_ASPEN_Msk);
	__DSB();
	__ISB();
}

static inline void _port_PendSV_enter(void) {
	__asm volatile("" : : : "memory");
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}

static inline void* _port_stack_init(void(*task_ptr)(void), void(*return_ptr)(void), void* stack_base, size_t stack_size) {

	uintptr_t* stack_ptr = (uintptr_t*)((uintptr_t)stack_base + stack_size);

	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//FPSCR, S15...
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//...S1
	*(--stack_ptr) = 0;																		//S0

	*(--stack_ptr) = (1 << 24);						*(--stack_ptr) = (uint32_t)task_ptr;	//PSR, PC
	*(--stack_ptr) = (uintptr_t)return_ptr;			*(--stack_ptr) = 0;						//LR, R12
	*(--stack_ptr) = 0;								*(--stack_ptr) = 0;						//R3, R2
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//R1, R0

	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//R11...
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//...R4

	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//S31...
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;
	*(--stack_ptr) = 0; 							*(--stack_ptr) = 0;						//...S16

	return (void*)stack_ptr;
}

#endif
