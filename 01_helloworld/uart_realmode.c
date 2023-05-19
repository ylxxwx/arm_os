//volatile unsigned int * const UART0_PA = (unsigned int*)0x101f1000;
volatile unsigned int * const UART0_PA = (unsigned int*)0x09000000;

//volatile unsigned int * const UART1_PA = (unsigned int*)0x101f2000;

void print_uart0(const char *s) {
    while(*s != 0) {
        *UART0_PA = (unsigned int)(*s);
        s++;
    }
}
