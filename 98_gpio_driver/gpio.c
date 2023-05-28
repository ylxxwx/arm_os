#include <linux/kernel.h>

#include "gpio.h"
extern volatile unsigned int *gpio;

void gpio_init(unsigned int *gpio_base_addr)
{
    gpio = (unsigned int *)gpio_base_addr;
    printk("gpio: %p\n", gpio);
}

static void short_sleep(void)
{
    int r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
}

void Pull_up(unsigned int pin)
{
    GPIO_PULL = 2;
    short_sleep();
    gpio[GPIO_PULLCLK0_ADDR] = (1 << pin);
    short_sleep();
    GPIO_PULL = 0;
    gpio[GPIO_PULLCLK0_ADDR] = 0;
}

void Pull_down(unsigned int pin)
{
    GPIO_PULL = 1;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void Pull_disable(unsigned int pin)
{
    GPIO_PULL = 0;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void pull_mode(unsigned int pin, int mode)
{
    GPIO_PULL = mode;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void gpio_pin_on(unsigned int pin)
{
    SET_GPIO(pin);
    return;
}

void gpio_pin_off(unsigned int pin)
{
    CLR_GPIO(pin);
    return;
}
