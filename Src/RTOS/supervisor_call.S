.global SVC_Handler
.type SVC_Handler, %function
.syntax unified


SVC_Handler:
	cpsid i
	ldr lr, =0xFFFFFFFD

	b OS_Load_Context
