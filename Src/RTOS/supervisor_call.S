#include "config.h"
.global SVC_Handler
.type SVC_Handler, %function
.extern SVC_Handler_C
.syntax unified
.thumb


SVC_Handler:
	mov r4, #OS_BASEPRI_LOCK_VALUE
	msr basepri, r4

	tst lr, #4
	ite eq
	mrseq r0, msp
	mrsne r0, psp

	bl SVC_Handler_C

	mov r4, #0x00
	msr basepri, r4
	bx lr
