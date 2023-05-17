
void print_uart0(const char *s);

void c_entry(void) {
    print_uart0("Hello world!\n");
}
