#ifndef CONTEXT_SWITCH_LOGIC_H_
#define CONTEXT_SWITCH_LOGIC_H_

#include <stdint.h>

uint8_t* OS_SwitchLogic(uint8_t* current_task_stack_pointer);

#endif
