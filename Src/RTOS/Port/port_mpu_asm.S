.syntax unified
.extern MemManage_Handler_C
.global MemManage_Handler
.type MemManage_Handler, %function

MemManage_Handler:
	bkpt
	tst lr, #4

	ittee eq
	mrseq r0, msp
	moveq r1, #1
	mrsne r0, psp
	movne r1, #0

	push {r4, lr}

	bl MemManage_Handler_C

	pop {r4, lr}

	bx lr
