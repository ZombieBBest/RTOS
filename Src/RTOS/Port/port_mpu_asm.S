.syntax unified
.extern MemManage_Handler_C
.global MemManage_Handler
.type MemManage_Handler, %function

MemManage_Handler:
	bkpt
	tst lr, #4

	ite ne
	mrsne r0, psp
	mrseq r0, msp

	push {r4, lr}

	bl MemManage_Handler_C

	pop {r4, lr}

	bx lr
