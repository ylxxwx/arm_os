#include <vm.h>

.global c_entry
.global startup_sectiontable

entry:
  LDR sp, =stack_top
  bl enable_paging
  bl jump_to_high_mem
  BL c_entry
  B .

enable_paging:
	mov r2, lr

	mov r0, #1
	bl set_domain_access_control

	ldr r0, =startup_sectiontable
	sub r0, #KERNEL_BASE
	bl set_translation_table_base

	bl read_control_register
	orr r0, #1
	bl set_control_register

	mov pc, r2
