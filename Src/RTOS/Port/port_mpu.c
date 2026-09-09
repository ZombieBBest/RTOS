#include "port_mpu.h"
#include "port_config.h"
#include <stm32f4xx.h>
#include <stddef.h>

#define FLASH_REGION_NUMBER		(0UL)
#define SRAM_REGION_NUMBER		(1UL)
#define PERIPH_REGION_NUMBER	(2UL)
#define STACK_REGION_NUMBER		(3UL)

void _port_mpu_initialization(void) {
	MPU->CTRL &= ~(MPU_CTRL_ENABLE_Msk);

	MPU->RBAR = (FLASH_BASE)
			  | (MPU_RBAR_VALID_Msk)
			  | ((FLASH_REGION_NUMBER << MPU_RBAR_REGION_Pos) & MPU_RBAR_REGION_Msk);
	MPU->RASR = (0x02UL << MPU_RASR_AP_Pos)
			  | (0x01UL << MPU_RASR_C_Pos)
			  | (0x01UL << MPU_RASR_B_Pos)
			  | ((PORT_CONFIG_FLASH_SIZE_MPU << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
			  | (0x01UL << MPU_RASR_ENABLE_Pos);


	MPU->RBAR = (SRAM_BASE)
			  | (MPU_RBAR_VALID_Msk)
			  | ((SRAM_REGION_NUMBER << MPU_RBAR_REGION_Pos) & MPU_RBAR_REGION_Msk);
	MPU->RASR = (0x01UL << MPU_RASR_XN_Pos)
			  | (0x01UL << MPU_RASR_AP_Pos)
			  | (0x01UL << MPU_RASR_C_Pos)
			  | (0x01UL << MPU_RASR_B_Pos)
			  | ((PORT_CONFIG_SRAM_SIZE_MPU << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
			  | (0x01UL << MPU_RASR_ENABLE_Pos);


	MPU->RBAR = (PERIPH_BASE)
			  | (MPU_RBAR_VALID_Msk)
			  | ((PERIPH_REGION_NUMBER << MPU_RBAR_REGION_Pos) & MPU_RBAR_REGION_Msk);
	MPU->RASR = (0x01UL << MPU_RASR_XN_Pos)
			  | (0x01UL << MPU_RASR_AP_Pos)
			  | (0x01UL << MPU_RASR_B_Pos)
			  | ((PORT_CONFIG_PERIPH_SIZE_MPU << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
			  | (0x01UL << MPU_RASR_ENABLE_Pos);


	MPU->CTRL |= (MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk);
	__DSB();
    __ISB();
}

//Size must be a multiple of 2
port_MPU_StackRegion_t _port_mpu_prepare_task_stack_region(uint32_t* stack_start_ptr, size_t stack_size) {
	uint32_t highest_bit = 31 - __builtin_clz(stack_size);
	uint32_t size_mpu_format = highest_bit - 1;

	port_MPU_StackRegion_t sr;

	sr.rbar = ((uintptr_t)stack_start_ptr)
			  | (MPU_RBAR_VALID_Msk)
			  | ((STACK_REGION_NUMBER << MPU_RBAR_REGION_Pos) & MPU_RBAR_REGION_Msk);

	sr.rasr = (0x01UL << MPU_RASR_XN_Pos)
			| (0x03UL << MPU_RASR_AP_Pos)
			| (0x01UL << MPU_RASR_C_Pos)
			| (0x01UL << MPU_RASR_B_Pos)
			| ((size_mpu_format << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
			| (0x01UL << MPU_RASR_ENABLE_Pos);

	return sr;
}
