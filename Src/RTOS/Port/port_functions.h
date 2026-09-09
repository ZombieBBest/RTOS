#ifndef RTOS_PORT_PORT_FUNCTIONS_H_
#define RTOS_PORT_PORT_FUNCTIONS_H_

#include <stdint.h>
#include <stddef.h>
#include <stm32f4xx.h>

#include "port_config.h"

#define FPSCR_AHP_Pos				(26U)
#define FPSCR_DN_Pos				(25U)
#define FPSCR_FZ_Pos				(24U)
#define FPSCR_RMODE_Pos				(22U)

#define _get_FPSCR_from_SP(sp)		(&sp[24])
#define INITIAL_EXC_RETURN  	 	(0xFFFFFFED)

static inline void _port_fpu_start_settings(void) {
	SCB->CPACR |= (3 << 22) | (3 << 20);

	FPU->FPCCR &= ~(FPU_FPCCR_LSPEN_Msk | FPU_FPCCR_ASPEN_Msk);
	__DSB();
	__ISB();
}

static inline void _port_fpu_mode_settings(uint32_t* sp, uint32_t AHP, uint32_t DN, uint32_t FZ, uint32_t RMODE) {
	uint32_t* FPSCR_ptr = _get_FPSCR_from_SP(sp);
	*FPSCR_ptr &= ~((1 << FPSCR_AHP_Pos) | (1 << FPSCR_DN_Pos) | (1 << FPSCR_FZ_Pos) | (3 << FPSCR_RMODE_Pos));
	*FPSCR_ptr |= ((uint32_t)AHP << FPSCR_AHP_Pos) | ((uint32_t)DN << FPSCR_DN_Pos) |
				((uint32_t)FZ << FPSCR_FZ_Pos) | ((uint32_t)RMODE << FPSCR_RMODE_Pos);
}

static inline void _port_PendSV_enter(void) {
	__asm volatile("" : : : "memory");
	SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
	__asm volatile("dsb" : : : "memory");
	__asm volatile("isb" : : : "memory");
}

static inline void _port_start_scheduler_from_svc(void* first_task_sp) {
	__set_CONTROL(__get_CONTROL() | CONTROL_nPRIV_Msk);
	__asm volatile (
		"mov r0, %[task_sp] 	\n\t"
		"ldr lr, =%[lr_exc] 	\n\t"
		"b OS_Load_Context_test 		\n\t"
		:
		: [task_sp] "r" (first_task_sp),
		  [lr_exc]  "i" (INITIAL_EXC_RETURN)
		: "r0", "lr", "memory"
	);
}

static inline void* _port_stack_init(void(*task_ptr)(void), void(*return_ptr)(void), void* stack_base, size_t stack_size) {

	uintptr_t* stack_ptr = (uintptr_t*)((uintptr_t)stack_base + stack_size);
	*(--stack_ptr) = 0;

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
