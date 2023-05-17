ENTRY(entry)

start_address = 0x10000;

SECTIONS
{
    . = 0x80000000 + start_address;
    .startup . : AT(start_address){ start.o(.text) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }
    . = ALIGN(8);
    . = . + 0x1000; /*4kB of stack memory*/
    stack_top = .;
}