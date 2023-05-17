#include <vm.h>

volatile unsigned int * const UART0_VA = ((volatile unsigned int *)MMIO_P2V(0x101f1000));
//volatile unsigned int * const UART1_VA = (unsigned int*)0x101f2000;

void print_uart0_vm(const char *s) {
    while(*s != 0) {
        *UART0_VA = (unsigned int)(*s);
        s++;
    }
}
