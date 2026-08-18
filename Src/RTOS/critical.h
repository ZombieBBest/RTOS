#ifndef CRITICAL_H_
#define CRITICAL_H_

#include <stm32f4xx.h>

static inline uint32_t OS_ENTER_CRITICAL(void) {
    uint32_t primask = __get_PRIMASK();

    __disable_irq();
    __asm volatile("" : : : "memory");
    return primask;
}

static inline void OS_EXIT_CRITICAL(uint32_t prev_irq) {
	__asm volatile("dsb" : : : "memory");
    __set_PRIMASK(prev_irq);
}

#endif
