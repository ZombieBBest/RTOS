#ifndef CONTEXT_SWITCH_LOGIC_H_
#define CONTEXT_SWITCH_LOGIC_H_

#include <stdint.h>

// =================== SCHEDULER_PROTOTYPE ==================

void* _scheduler_switch_logic(void* current_task_stack_pointer);

#endif
