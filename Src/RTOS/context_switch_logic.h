#ifndef CONTEXT_SWITCH_LOGIC_H_
#define CONTEXT_SWITCH_LOGIC_H_

#include <stdint.h>

void* OS_SwitchLogic(void* current_task_stack_pointer);

#endif
