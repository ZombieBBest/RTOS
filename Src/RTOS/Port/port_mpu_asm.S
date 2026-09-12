.syntax unified
.extern MemManage_Handler_C
.global MemManage_Handler
.type MemManage_Handler, %function

MemManage_Handler:
	bkpt
	tst lr, #4

	itee ne
	mrsne r0, psp
	moveq r0, #0				@If MSP - Enter HardFault
	bxeq r0

	push {r4, lr}

	bl MemManage_Handler_C

	pop {r4, lr}

	bx lr
