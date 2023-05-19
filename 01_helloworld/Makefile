OS = myos

# tools
AR = aarch64-linux-gnu-ar
AS = aarch64-linux-gnu-as
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy
OBJDUMP = aarch64-linux-gnu-objdump

CPU = cortex-a53
ARCH_QEMU_FLAGS = -M virt -cpu cortex-a53 -m 256M

# don't get pulseaudio related errors when qemu starts
export QEMU_AUDIO_DRV = none

# flags
CFLAGS = -mcpu=$(CPU)   \
         -std=c99 -pedantic -Wall -Wextra  -fPIC  \
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
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel $(OS).elf

qemu2: $(OS).bin 
	qemu-system-arm $(QEMU_FLAGS) -kernel $(OS).bin -serial vc:800x600 -serial mon:stdio

qemu-gdb: $(OS).bin
	qemu-system-arm $(QEMU_FLAGS) -gdb tcp::26000 -S -kernel $(OS).bin

clean:
	rm -f $(OBJS) $(EXTRA_CLEAN)
	rm -f $(OS).elf $(OS).bin $(OS).asm
