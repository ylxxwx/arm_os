OS = myos

# tools
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CPU = arm926ej-s
ARCH_QEMU_FLAGS = -M versatilepb -cpu arm926 -m 256M

# don't get pulseaudio related errors when qemu starts
export QEMU_AUDIO_DRV = none

# flags
CFLAGS = -mcpu=$(CPU) -gstabs -marm \
         -std=c99 -pedantic -Wall -Wextra -msoft-float -fPIC -mapcs-frame \
         -fno-builtin-printf -fno-builtin-strcpy -Wno-overlength-strings \
         -fno-builtin-exit
ASFLAGS = -mcpu=$(CPU) -g 
QEMU_FLAGS = $(ARCH_QEMU_FLAGS) -nographic

all: $(OS).bin

OBJS = start.o
OBJS += helloworld.o uart_realmode.o


$(OS).bin: $(OBJS) $(OS).ld 
	$(LD) -T $(OS).ld $(OBJS) -o $(OS).elf
	$(OBJCOPY) -O binary $(OS).elf $(OS).bin
	$(OBJDUMP) -D $(OS).elf > $(OS).asm

qemu: $(OS).bin 
	qemu-system-arm $(QEMU_FLAGS) -kernel $(OS).bin

qemu2: $(OS).bin 
	qemu-system-arm $(QEMU_FLAGS) -kernel $(OS).bin -serial vc:800x600 -serial mon:stdio

qemu-gdb: $(OS).bin
	qemu-system-arm $(QEMU_FLAGS) -gdb tcp::26000 -S -kernel $(OS).bin

clean:
	rm -f $(OBJS) $(EXTRA_CLEAN)
	rm -f $(OS).elf $(OS).bin $(OS).asm
