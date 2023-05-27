obj-m += my-gpio-driver.o
my-gpio-driver-objs += gpio_driver.o gpio.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean
