#include "core_config.h"
.extern OS_SwitchLogic
.global OS_Load_Context
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
	mov r3, #CORE_CONFIG_BASEPRI_LOCK_VALUE
	msr basepri, r3

	SaveContext

	push {lr}

	bl OS_SwitchLogic

	pop {lr}

OS_Load_Context:
	clrex

	LoadContext

	mov r3, #0x00
	msr basepri, r3
	bx LR
