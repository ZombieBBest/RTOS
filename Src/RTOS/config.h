#ifndef CONFIG_H_
#define CONFIG_H_

#include <assert.h>

#define CONFIG_F_CPU_HZ					16000000UL
#define CONFIG_TICK_RATE_HZ				1000UL

#define CONFIG_GENERAL_HEAP_SIZE	(16UL * 1024UL)
#define CONFIG_HEAP_BLOCK_SIZE		128UL

#define CONFIG_NUM_OF_TASKS			3
#define CONFIG_NUM_OF_PRIORITIES	32

static_assert(CONFIG_GENERAL_HEAP_SIZE > 0, "Invalid size of GENERAL_HEAP_SIZE");
static_assert((CONFIG_GENERAL_HEAP_SIZE % CONFIG_HEAP_BLOCK_SIZE) == 0, "GENERAL_HEAP_SIZE must be a multiple of HEAP_BLOCK_SIZE");
static_assert(CONFIG_HEAP_BLOCK_SIZE >= 128, "HEAP_BLOCK_SIZE must be greater than or equal to 128");

#endif
