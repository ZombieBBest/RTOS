#include <stdint.h>

extern uint32_t OS_SVC_Dispatcher(uint32_t svc_arg, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t* caller_sp);

void SVC_Handler_C(uint32_t* sp) {
	uint32_t pc_reg = sp[6];
	uint8_t svc_arg = ((uint8_t*)pc_reg)[-2];

	uint32_t arg1 = sp[0];
	uint32_t arg2 = sp[1];
	uint32_t arg3 = sp[2];
	uint32_t arg4 = sp[3];

	uint32_t result = OS_SVC_Dispatcher(svc_arg, arg1, arg2, arg3, arg4, sp);

	sp[0] = result;
}
