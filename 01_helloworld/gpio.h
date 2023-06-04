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

#define MMIO_BASE 0x3F000000

#define GPFSEL0 ((volatile unsigned int *)(MMIO_BASE + 0x00200000))
#define GPFSEL1 ((volatile unsigned int *)(MMIO_BASE + 0x00200004))
#define GPFSEL2 ((volatile unsigned int *)(MMIO_BASE + 0x00200008))
#define GPFSEL3 ((volatile unsigned int *)(MMIO_BASE + 0x0020000C))
#define GPFSEL4 ((volatile unsigned int *)(MMIO_BASE + 0x00200010))
#define GPFSEL5 ((volatile unsigned int *)(MMIO_BASE + 0x00200014))
#define GPSET0 ((volatile unsigned int *)(MMIO_BASE + 0x0020001C))
#define GPSET1 ((volatile unsigned int *)(MMIO_BASE + 0x00200020))
#define GPCLR0 ((volatile unsigned int *)(MMIO_BASE + 0x00200028))
#define GPLEV0 ((volatile unsigned int *)(MMIO_BASE + 0x00200034))
#define GPLEV1 ((volatile unsigned int *)(MMIO_BASE + 0x00200038))
#define GPEDS0 ((volatile unsigned int *)(MMIO_BASE + 0x00200040))
#define GPEDS1 ((volatile unsigned int *)(MMIO_BASE + 0x00200044))
#define GPHEN0 ((volatile unsigned int *)(MMIO_BASE + 0x00200064))
#define GPHEN1 ((volatile unsigned int *)(MMIO_BASE + 0x00200068))
#define GPPUD ((volatile unsigned int *)(MMIO_BASE + 0x00200094))
#define GPPUDCLK0 ((volatile unsigned int *)(MMIO_BASE + 0x00200098))
#define GPPUDCLK1 ((volatile unsigned int *)(MMIO_BASE + 0x0020009C))

#define BCM2837_GPIO_ADDRESS 0x3F200000
#define BCM2711_GPIO_ADDRESS 0xfe200000

#define GPIO_GPFSEL0 0
#define GPIO_GPFSEL1 1
#define GPIO_GPFSEL2 2
#define GPIO_GPFSEL3 3
#define GPIO_GPFSEL4 4
#define GPIO_GPFSEL5 5

#define GPIO_GPSET0 7
#define GPIO_GPSET1 8

#define GPIO_GPCLR0 10
#define GPIO_GPCLR1 11

#define GPIO_GPLEV0 13
#define GPIO_GPLEV1 14

#define GPIO_GPEDS0 16
#define GPIO_GPEDS1 17

#define GPIO_GPREN0 19
#define GPIO_GPREN1 20

#define GPIO_GPFEN0 22
#define GPIO_GPFEN1 23

#define GPIO_GPHEN0 25
#define GPIO_GPHEN1 26

#define GPIO_GPLEN0 28
#define GPIO_GPLEN1 29

#define GPIO_GPAREN0 31
#define GPIO_GPAREN1 32

#define GPIO_GPAFEN0 34
#define GPIO_GPAFEN1 35

#define GPIO_GPPUD 37
#define GPIO_GPPUDCLK0 38
#define GPIO_GPPUDCLK1 39

/** GPIO Register set */
// extern unsigned int *gpio;
/*
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3  \
                                                                                     : 2) \
                                                      << (((g) % 10) * 3))

// #define GPIO_SET *(gpio + 7)  // sets   bits which are 1 ignores bits which are 0
// #define GPIO_CLR *(gpio + 10) // clears bits which are 1 ignores bits which are 0

#define SET_GPIO(g) (*(gpio + 7) = (1 << g))
#define CLR_GPIO(g) (*(gpio + 10) = (1 << g))
#define GET_GPIO(g) (*(gpio + 13) & (1 << g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio + 37)     // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio + 38) // Pull up/pull down clock
*/