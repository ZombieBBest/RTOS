.extern OS_SwitchLogic
.global OS_Load_Context
.global PendSV_Handler
.type PendSV_Handler, %function
.syntax unified


PendSV_Handler:
	cpsid i
	mrs r0, PSP
	stmdb r0!, {r4-r11}

	bl OS_SwitchLogic

OS_Load_Context:
	clrex
	ldmia r0!, {r4-r11}
	msr PSP, r0

	ldr lr, =0xFFFFFFFD
	cpsie i
	bx LR
