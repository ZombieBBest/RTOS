.extern OS_SwitchLogic
.global OS_Load_Context
.global PendSV_Handler
.type PendSV_Handler, %function
.syntax unified


PendSV_Handler:
	cpsid i
	mrs r0, PSP
	stmdb r0!, {r4-r11}

	push {lr}

	bl OS_SwitchLogic

	pop {lr}

OS_Load_Context:
	clrex
	ldmia r0!, {r4-r11}
	msr PSP, r0

	cpsie i
	bx LR
