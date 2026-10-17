#include "port_config.h"
.extern OS_SwitchLogic
.global OS_Switch_Context
.global PendSV_Handler
.type PendSV_Handler, %function
.syntax unified

// ======================== INTERNAL ========================
@1
.macro SaveContext
	mrs r0, PSP
	stmdb r0!, {r4-r11}
	vstmdb r0!, {s16-s31}
	stmdb r0!, {r4, lr}		@r4 used like aligner
.endm

@2
.macro LoadContext
	ldmia r0!, {r4, lr}		@r4 used like aligner
	vldmia r0!, {s16-s31}
	ldmia r0!, {r4-r11}
	msr PSP, r0
.endm


// ========================== ISR ===========================

PendSV_Handler:
	mov r3, #PORT_CONFIG_BASEPRI_LOCK_VALUE
	msr basepri, r3

	SaveContext

OS_Switch_Context:
	bl _scheduler_switch_logic

	clrex

	LoadContext

	mov r3, #0x00
	msr basepri, r3
	bx LR
