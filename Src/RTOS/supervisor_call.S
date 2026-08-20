#include "config.h"
.global SVC_Handler
.type SVC_Handler, %function
.extern SVC_Handler_C
.syntax unified


SVC_Handler:
	mov r3, #OS_BASEPRI_LOCK_VALUE
	msr basepri, r3

	tst lr, #4
	ite eq
	mrseq r0, msp
	mrsne r0, psp

	push {lr}

	bl SVC_Handler_C

	pop {lr}

	mov r3, #0x00
	msr basepri, r3
	bx lr
