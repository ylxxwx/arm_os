#ifndef MEMORY_H
#define MEMORY_H

#include <hardware.h>

#define KERNEL_BASE 0x80000000


#define P2V(x) (((uint32_t) x) + KERNEL_BASE)
#define V2P(x) (((uint32_t) x) - KERNEL_BASE)

/* memory layout */
#define KERNEL_STACK_BOTTOM (KERNEL_BASE - 2 * PAGE_SIZE)
#define USER_STACK_BOTTOM (KERNEL_BASE - 3 * PAGE_SIZE)
#define KERNEL_SECTION_TABLE ((uint32_t) kernel_end)
#define MMIO_BASE (KERNEL_BASE + 0x40000000)
#define ALLOCATABLE_MEMORY_START (KERNEL_SECTION_TABLE +  0x200000)
#define INTERRUPT_VECTOR_BASE 0xffff0000

#define MMIO_P2V(x) ((volatile unsigned int*) (MMIO_BASE + (x - MMIO_BASE_PHYSICAL)))

#define SECTION_TABLE_ALIGNMENT 16384

#endif
