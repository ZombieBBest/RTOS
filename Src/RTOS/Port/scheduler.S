#include "port_config.h"
.extern OS_SwitchLogic
.global OS_Load_Context
.global OS_Load_Context_test
.global PendSV_Handler
.type PendSV_Handler, %function
.syntax unified

// ======================== INTERNAL ========================
@1
.macro SaveContext
	mrs r0, PSP
	stmdb r0!, {r4-r11}
	vstmdb r0!, {s16-s31}
.endm

@2
.macro LoadContext
	vldmia r0!, {s16-s31}
	ldmia r0!, {r4-r11}
	msr PSP, r0
.endm


// ========================== ISR ===========================

PendSV_Handler:
	mov r3, #PORT_CONFIG_BASEPRI_LOCK_VALUE
	msr basepri, r3

	SaveContext

OS_Load_Context:

	push {r4, lr}

	bl _scheduler_switch_logic

	pop {r4, lr}

	clrex

	LoadContext

	mov r3, #0x00
	msr basepri, r3
	bx LR
