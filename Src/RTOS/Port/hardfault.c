#include "stm32f4xx.h"

// ========================== ISR ===========================

void HardFault_Decoder(unsigned int *stack) {
    volatile uint32_t r0  = stack[0];
    volatile uint32_t r1  = stack[1];
    volatile uint32_t r2  = stack[2];
    volatile uint32_t r3  = stack[3];
    volatile uint32_t r12 = stack[4];
    volatile uint32_t lr  = stack[5];
    volatile uint32_t pc  = stack[6];
    volatile uint32_t psr = stack[7];

    volatile uint32_t cfsr  = SCB->CFSR;
    volatile uint32_t hfsr  = SCB->HFSR;
    volatile uint32_t mmfar = SCB->MMFAR;

    (void)r0; (void)r1; (void)r2; (void)r3; (void)r12; (void)lr; (void)pc; (void)psr;
    (void)cfsr; (void)hfsr; (void)mmfar;

    __asm("bkpt #0");
    while(1);
}

__attribute__((naked)) void HardFault_Handler(void) {
	__asm volatile (
		"tst lr, #4				\n\t"
		"ite eq					\n\t"
		"mrseq r0, msp			\n\t"
		"mrsne r0, psp			\n\t"
		"b HardFault_Decoder	\n\t"
	);
}
