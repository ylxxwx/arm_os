obj-m += my-gpio-driver.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules

my-gpio-driver.o: gpio_driver.c gpio.c

clean:
	make -C $(KDIR) M=$(shell pwd) clean
