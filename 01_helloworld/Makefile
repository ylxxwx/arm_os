#
# Copyright (C) 2018 bzt (bztsrc@github)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCP = aarch64-linux-gnu-objcopy
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

all: clean kernel8.img

start.o: start.S
	$(CC) $(CFLAGS) -c start.S -o start.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	$(LD) -nostdlib start.o $(OBJS) -T myos.ld -o kernel8.elf
	$(OBJCP) -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true
	rm -rf rmyos.bin myos.elf kernel8.img myos.asm

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial mon:stdio
