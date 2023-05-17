# 01 vm

Setup virtual memory mapping using MCU.

## kp 01 enable MCU

```
	mov r0, #1
	bl set_domain_access_control       ; 	mcr p15, 0, r0, cr3, cr0, 0

	ldr r0, =startup_sectiontable     
	sub r0, #KERNEL_BASE
	bl set_translation_table_base      ;    mcr p15, 0, r0, cr2, cr0, 0

	bl read_control_register           ;    mrc p15, 0, r0, cr1, cr0, 0
	orr r0, #1
	bl set_control_register            ;    mcr p15, 0, r0, cr1, cr0, 0
```

## kp 02 section table structure

section table has 4 mode
10 1M mapping
01 to page table.

VM <--> physical Address 

