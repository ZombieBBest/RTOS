#ifndef PORT_SYS_TIMER_H_
#define PORT_SYS_TIMER_H_

#include <stdint.h>

void _port_sys_SysTick_Initialization(uint32_t cpu_f_hz, uint32_t tick_hz);

void _port_sys_SysTick_Start(void);

#endif
