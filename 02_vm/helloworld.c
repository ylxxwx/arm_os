
void print_uart0_vm(const char *s);

void c_entry(void) {
    print_uart0_vm("Hello world!\n");
}
