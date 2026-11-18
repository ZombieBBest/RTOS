#ifndef RTOS_CORE_CORE_CONFIG_H_
#define RTOS_CORE_CORE_CONFIG_H_

#include <stdint.h>
#include <assert.h>

#define CONFIG_F_CPU_HZ					(16000000UL)
#define CONFIG_TICK_RATE_PER_SEC_HZ		(1000U)

#define CONFIG_NUM_OF_TASKS				(8U)
#define CONFIG_NUM_OF_PRIORITIES		(32U)
#define CONFIG_NUM_OF_DRIVERS			(2U)

#define CONFIG_MAX_MUXEXES_FOR_TASK		(4U)

static_assert((CONFIG_NUM_OF_TASKS >= 1), "Error: CONFIG_NUM_OF_TASKS must be greater than or equal to 1");
static_assert((CONFIG_NUM_OF_TASKS <= 256), "Error: CONFIG_NUM_OF_TASKS must be less than or equal to 256");
static_assert((CONFIG_MAX_MUXEXES_FOR_TASK > 0), "Error: A task must have at least one mutex.");

#endif
