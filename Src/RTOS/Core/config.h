#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#include <assert.h>

#define CONFIG_F_CPU_HZ					(16000000UL)
#define CONFIG_TICK_RATE_HZ				(1000UL)

#define CONFIG_NUM_OF_TASKS				(4UL)
#define CONFIG_NUM_OF_PRIORITIES		(32UL)

static_assert((CONFIG_NUM_OF_TASKS >= 1), "Error: CONFIG_NUM_OF_TASKS must be greater than or equal to 1");

#endif
