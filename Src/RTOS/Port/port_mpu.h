#ifndef RTOS_PORT_PORT_MPU_H_
#define RTOS_PORT_PORT_MPU_H_

#include <stm32f4xx.h>
#include <stdint.h>
#include <stddef.h>

// ==================== TYPES_DEFINITION ====================

typedef struct {
	uint32_t rbar;
	uint32_t rasr;
} Port_MPU_StackRegion_t;

// =================== FUNCTIONS_PROTOTYPES==================

void _port_mpu_register_stacking_error_callback(void(*callback)(void));

void _port_mpu_initialization(void);

Port_MPU_StackRegion_t _port_mpu_prepare_task_stack_region(uint32_t* stack_start_ptr, size_t stack_size);

// ================= PUBLIC_STATIC_FUNCTIONS ================

static inline void _port_mpu_set_task_stack_region(uint32_t rbar, uint32_t rasr) {
	uint32_t region_num = (rbar & MPU_RBAR_REGION_Msk) >> MPU_RBAR_REGION_Pos;
	MPU->RNR = region_num;

	MPU->RASR &= ~(MPU_RASR_ENABLE_Msk);
	MPU->RBAR = rbar;
	MPU->RASR = rasr;
	__DSB();
	__ISB();
}

#endif
