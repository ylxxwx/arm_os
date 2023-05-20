# 01 helloworld

```shell
The UART data address is 0x101f1000.
UART0 interface 0x101f1000 -- 0x101f1fff 4kb
UART1 interface 0x101f2000 -- 0x101f2fff 4kb

UART two mode, FIFO mode or non-FIFO mode.

/* serial port register offsets */
#define UART_DATA        0x00 
#define UART_FLAGS       0x06
#define UART_INT_ENABLE  0x0e
#define UART_INT_TARGET  0x0f
#define UART_INT_CLEAR   0x11

/* serial port bitmasks */
#define UART_RECEIVE  0x10
#define UART_TRANSMIT 0x20
```

```shell
# Use Serial 1
UART1 interface 0x101f2000
$ 	qemu-system-arm $(QEMU_FLAGS) -kernel $(OS).bin -serial vc:800x600 -serial mon:stdio
	Hello Open World
```

### kp 02 

versatilepb arm926 loads the kernel to physical address 0x10000.
So in myos.ld, the base address is set to 0x10000.


```shell
qemu-system-aarch64 -smp 2 -M virt -m 1024 -cpu cortex-a53  -kernel Image -append 'root=/dev/vda console=ttyAMA0' -drive if=none,file=minrootfs.ext3,id=hd0 -device virtio-blk-device,drive=hd0  -netdev user,id=mynet -device virtio-net-pci,netdev=mynet -nographic
```
