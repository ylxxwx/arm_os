/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "io.h"
#include "gpio.h"

// volatile unsigned int *gpio;

void pull_up(unsigned int pin)
{
    gpio_pull(pin, 2);
    /*
    GPIO_PULL = 2;
    sleep(150);
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    sleep(150);
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
    */
}

void pull_down(unsigned int pin)
{
    gpio_pull(pin, 1);
    /*
    GPIO_PULL = 1;
    sleep(150);
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    sleep(150);
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
    */
}

void pull_disable(unsigned int pin)
{
    gpio_pull(pin, 0);
    /*
    GPIO_PULL = 0;
    sleep(150);
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    sleep(150);
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
    */
}

void led_init()
{
    // gpio = (unsigned int *)0x3f200000;
    //  INP_GPIO(20);
    //  OUT_GPIO(21);
    gpio_useAsInput(20);
    gpio_useAsOutput(21);
    // pull_up(20);
    pull_down(20);
}

static void gpio_pin_on(unsigned int pin)
{
    // SET_GPIO(pin);
    gpio_set(pin, 1);
    return;
}

static void gpio_pin_off(unsigned int pin)
{
    // CLR_GPIO(pin);
    gpio_clear(pin);
    return;
}

static int gpio_pin_read(unsigned int pin)
{
    return gpio_read(pin);
    // return GET_GPIO(pin);
}

void main()
{
    int light = 0;
    // int a = 100;
    // set up serial console
    uart_init();
    uart_writeText("Hello world!\n\r");
    uart_writeText("I am here!\n\r");
    sleep(500000);
    led_init();
    // say hello
    // uart_puts("Hello World!\n");
    // echo everything back
    while (1)
    {
        // uart_send(uart_getc());
        // uart_send('A');
        int ret = gpio_pin_read(20);
        if (ret)
        {
            gpio_pin_on(21);
            light = 0;
            uart_writeText("Light is on!\n\r");
        }
        else
        {
            gpio_pin_off(21);
            light = 1;
            uart_writeText("Light is off!\n\r");
        }
        sleep(500000);
    }

    while (1)
        sleep(500);
    return 0;
}
