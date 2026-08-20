#include "config.h"
.extern OS_SwitchLogic
.global OS_Load_Context
.global PendSV_Handler
.type PendSV_Handler, %function
.syntax unified


PendSV_Handler:
	mov r4, #OS_BASEPRI_LOCK_VALUE
	msr basepri, r4

	mrs r0, PSP
	stmdb r0!, {r4-r11}

	push {lr}

	bl OS_SwitchLogic

	pop {lr}

OS_Load_Context:
	clrex
	ldmia r0!, {r4-r11}
	msr PSP, r0

	mov r4, #0x00
	msr basepri, r4
	bx LR
