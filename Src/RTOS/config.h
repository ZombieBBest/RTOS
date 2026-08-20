#ifndef CONFIG_H_
#define CONFIG_H_

#ifndef __ASSEMBLER__
#include <assert.h>
#endif

#define CONFIG_F_CPU_HZ					16000000UL
#define CONFIG_TICK_RATE_HZ				1000UL

#define CONFIG_NUM_OF_TASKS				3
#define CONFIG_NUM_OF_PRIORITIES		32

#define CONFIG_KERNEL_PRIORITY       	5
#define CONFIG_NVIC_PRIO_BITS			4
#define OS_BASEPRI_LOCK_VALUE     		(CONFIG_KERNEL_PRIORITY << (8 - CONFIG_NVIC_PRIO_BITS))

#endif
