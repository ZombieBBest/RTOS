#include "port_functions.h"

_Bool _port_copy_from_user(const uint8_t* from, uint8_t* to, size_t size_of_to) {
	if (size_of_to == 0) return 1;

	const uint8_t* src = from;
	uint8_t* dest = to;
	uint32_t remain = size_of_to;

	_Bool user_copy_is_ok = 0;

	asm volatile (
		".global copy_from_user_start_critical		\n\t"
		".global copy_from_user_end_critical		\n\t"
		".global copy_from_user_abort				\n\t"

		"1:											\n\t"
		"cbz %[rem], 2f								\n\t"

		"copy_from_user_start_critical:   			\n\t"
		"ldrbt r3, [%[load]]						\n\t"
		"add r3, #1									\n\t"
		"copy_from_user_end_critical:   			\n\t"

		"strb r3, [%[save]], #1						\n\t"
		"sub %[rem], #1								\n\t"

		"b 1b										\n\t"

		"2:											\n\t"
		"mov %[state], #1							\n\t"

		"copy_from_user_abort:						\n\t"

		: [load] 	"+r" (src),
		  [save] 	"+r" (dest),
		  [rem] 	"+r" (remain),
		  [state] 	"+r" (user_copy_is_ok)
		:
		: "r3", "memory"
	);


	return user_copy_is_ok;
}
