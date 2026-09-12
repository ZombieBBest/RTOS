#include <stdint.h>

// ====================== DEFINITIONS =======================

#define PC_SP_INDEX					(6UL)
#define SVC_NUM_INSTRUCTION_INDEX	(-2UL)

#define ARG0_SP_INDEX				(0UL)
#define ARG1_SP_INDEX				(1UL)
#define ARG2_SP_INDEX				(2UL)
#define ARG3_SP_INDEX				(3UL)

// ====================== ISR_HANDLE ========================

extern uint32_t OS_SVC_Dispatcher(uint32_t svc_arg, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t* caller_sp);

void SVC_Handler_C(uint32_t* sp) {
	uint32_t pc_reg = sp[PC_SP_INDEX];
	uint8_t svc_arg = *((uint8_t*)((uintptr_t)pc_reg + SVC_NUM_INSTRUCTION_INDEX));

	uint32_t arg0 = sp[ARG0_SP_INDEX];
	uint32_t arg1 = sp[ARG1_SP_INDEX];
	uint32_t arg2 = sp[ARG2_SP_INDEX];
	uint32_t arg3 = sp[ARG3_SP_INDEX];

	uint32_t result = OS_SVC_Dispatcher(svc_arg, arg0, arg1, arg2, arg3, sp);

	sp[0] = result;
}
