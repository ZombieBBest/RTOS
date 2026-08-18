.global SVC_Handler
.type SVC_Handler, %function
.syntax unified


SVC_Handler:
	cpsid i

	b OS_Load_Context
