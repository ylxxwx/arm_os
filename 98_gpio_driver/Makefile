obj-m += my-gpio-driver.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules

my-gpio-driver.o: gpio_driver.o gpio.o

clean:
	make -C $(KDIR) M=$(shell pwd) clean
