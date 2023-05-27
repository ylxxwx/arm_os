#pragma once

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

extern unsigned int *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3  \
                                                                                     : 2) \
                                                      << (((g) % 10) * 3))

#define GPIO_SET *(gpio + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio + 10) // clears bits which are 1 ignores bits which are 0

#define SET_GPIO(g) (*(gpio + 7) = (1 << g))
#define CLR_GPIO(g) (*(gpio + 10) = (1 << g))
#define GET_GPIO(g) (*(gpio + 13) & (1 << g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio + 37)     // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio + 38) // Pull up/pull down clock

void gpio_init(unsigned int *);
