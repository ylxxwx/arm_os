// GPIO

// PERIPHERAL_BASE = 0xFE000000,
volatile unsigned int PERIPHERAL_BASE = 0x3F000000;
// #define PERIPHERAL_BASE 0x3F000000
#define GPFSEL0 (PERIPHERAL_BASE + 0x200000)
#define GPLEV0 (PERIPHERAL_BASE + 0x200034)
#define GPSET0 (PERIPHERAL_BASE + 0x20001C)
#define GPCLR0 (PERIPHERAL_BASE + 0x200028)
#define GPPUPPDN0 (PERIPHERAL_BASE + 0x2000E4)
#define GPPUD (PERIPHERAL_BASE + 0x200094)     // Pi 3B
#define GPPUDCLK0 (PERIPHERAL_BASE + 0x200098) // Pi 3B

enum
{
    GPIO_MAX_PIN = 53,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_INPUT = 7,
    GPIO_FUNCTION_OUTPUT = 1,
};

enum
{
    Pull_None = 0,
    Pull_Up = 2,
    Pull_Down = 1,
};

void mmio_write(long reg, unsigned int val) { *(volatile unsigned int *)reg = val; }
unsigned int mmio_read(long reg) { return *(volatile unsigned int *)reg; }

unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max)
{
    unsigned int field_mask = (1 << field_size) - 1;

    if (pin_number > field_max)
        return 0;
    if (value > field_mask)
        return 0;

    unsigned int num_fields = 32 / field_size;
    unsigned int reg = base + ((pin_number / num_fields) * 4);
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

unsigned int gpio_set(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN); }
unsigned int gpio_clear(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN); }
unsigned int gpio_function(unsigned int pin_number, unsigned int value)
{
    return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN);
}

void sleep(int r)
{
    while (r--)
    {
        ; // asm volatile("nop");
    }
}

unsigned int gpio_pull(unsigned int pin_number, unsigned int value)
{
    mmio_write(GPPUD, value);
    sleep(150);
    mmio_write(GPPUDCLK0, 1 << pin_number);
    sleep(150);
    mmio_write(GPPUD, 0);
    mmio_write(GPPUDCLK0, 0);
    return 0;
}

void gpio_useAsAlt5(unsigned int pin_number)
{
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

void gpio_useAsInput(unsigned int pin_number)
{
    gpio_function(pin_number, GPIO_FUNCTION_INPUT);
}

void gpio_useAsOutput(unsigned int pin_number)
{
    gpio_function(pin_number, GPIO_FUNCTION_OUTPUT);
}

unsigned int gpio_read(unsigned int pin_number)
{
    return (mmio_read(GPLEV0) & (1 << pin_number));
}

// UART
#define AUX_BASE (PERIPHERAL_BASE + 0x215000)
#define AUX_ENABLES (AUX_BASE + 4)
#define AUX_MU_IO_REG (AUX_BASE + 64)
#define AUX_MU_IER_REG (AUX_BASE + 68)
#define AUX_MU_IIR_REG (AUX_BASE + 72)
#define AUX_MU_LCR_REG (AUX_BASE + 76)
#define AUX_MU_MCR_REG (AUX_BASE + 80)
#define AUX_MU_LSR_REG (AUX_BASE + 84)
#define AUX_MU_CNTL_REG (AUX_BASE + 96)
#define AUX_MU_BAUD_REG (AUX_BASE + 104)

enum
{
    AUX_UART_CLOCK = 500000000,
    UART_MAX_QUEUE = 16 * 1024
};

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK / (baud * 8)) - 1)

void uart_init()
{
    mmio_write(AUX_ENABLES, 1); // enable UART1
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_CNTL_REG, 0);
    mmio_write(AUX_MU_LCR_REG, 3); // 8 bits
    mmio_write(AUX_MU_MCR_REG, 0);
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_IIR_REG, 0xC6); // disable interrupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
    gpio_useAsAlt5(14);
    gpio_useAsAlt5(15);
    mmio_write(AUX_MU_CNTL_REG, 3); // enable RX/TX
}

unsigned int uart_isWriteByteReady() { return mmio_read(AUX_MU_LSR_REG) & 0x20; }

void uart_writeByteBlockingActual(unsigned char ch)
{
    while (!uart_isWriteByteReady())
        ;
    mmio_write(AUX_MU_IO_REG, (unsigned int)ch);
}

void uart_writeText(char *buffer)
{
    while (*buffer)
    {
        if (*buffer == '\n')
            uart_writeByteBlockingActual('\r');
        uart_writeByteBlockingActual(*buffer++);
    }
}
