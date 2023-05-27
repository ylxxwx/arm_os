ifneq ($(KERNELRELEASE),)
    ccflags-y := -std=gnu99 -DENABLE_DEBUG
    mygpio-objs := gpio.o gpio_driver.o
    obj-m := mygpio.o
else
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

.PHONY: modules
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY: clean
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean


#obj-m = my-gpio-driver.o
#my-gpio-driver-objs := gpio_driver.o gpio.o

#KDIR = /lib/modules/$(shell uname -r)/build

#all:
#	make -C $(KDIR) M=$(shell pwd) modules

#gpio_driver.o: gpio_driver.c
#	gcc -c -o gpio_driver.o gpio_driver.c

#clean:
#	make -C $(KDIR) M=$(shell pwd) clean
