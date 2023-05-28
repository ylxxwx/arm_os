#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <asm/io.h>

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include "gpio.h"

volatile unsigned int *gpio;
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

#define GPIO_PULLCLK0_ADDR 38

void gpio_init(unsigned int *);
void pull_mode(unsigned int pin, int mode);
void Pull_up(unsigned int pin);
void Pull_down(unsigned int pin);

void gpio_init(unsigned int *gpio_base_addr)
{
    gpio = (unsigned int *)gpio_base_addr;
    printk("gpio: %p\n", gpio);
}

static void short_sleep(void)
{
    int r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
}

void Pull_up(unsigned int pin)
{
    int r = 150;
    printk("%p, %d\n", gpio, pin);
    GPIO_PULL = 2;
    printk("set GPIO_PULL %p, %d\n", gpio, pin);
    short_sleep();
    printk("after sleep %p, %d\n", gpio, pin);
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    unsigned int val = (1 << pin);
    gpio[GPIO_PULLCLK0_ADDR] = val; // 0x03000000;
    printk("PULL CLK %x \n", val, 1);
    short_sleep();
    GPIO_PULL = 0;
    gpio[GPIO_PULLCLK0_ADDR] = 0;
}

void Pull_down(unsigned int pin)
{
    GPIO_PULL = 1;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void Pull_disable(unsigned int pin)
{
    GPIO_PULL = 0;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void pull_mode(unsigned int pin, int mode)
{
    GPIO_PULL = mode;
    short_sleep();
    // clock on GPIO 24 & 25 (bit 24 & 25 set)
    GPIO_PULLCLK0 = 1 << pin; // 0x03000000;
    short_sleep();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
}

void gpio_pin_on(unsigned int pin)
{
    SET_GPIO(pin);
    return;
}

void gpio_pin_off(unsigned int pin)
{
    CLR_GPIO(pin);
    return;
}

#define DEVICE_NAME "mygpio"
#define BUF_LEN 1024

typedef struct tagPortIn
{
    unsigned int port;
    unsigned int dir;
    unsigned int mode;
} PortInit;

// Define custom ioctl commands
#define IOCTL_PORT_INP _IOW(1, 1, PortInit *)
#define IOCTL_PORT_OUT _IOW(2, 2, PortInit *)

static int major = 50; // Major number assigned to our device driver
static int minor = 0;  // Minor number assigned to our device driver
static dev_t devno;
static struct cdev my_cdev; // Character device structure

static char msg[BUF_LEN]; // Buffer to store data written to the device
static int msg_len;       // Length of the message stored in the buffer
static dev_t dev_num;     // Device number
#define LLL_MAX_USER_SIZE 1024

static unsigned int *gpio_registers = NULL;

#define OpenPortForWrite 1
#define OpenPortForRead 2

// Function called when the device is opened
static int device_open(struct inode *inode, struct file *file)
{
    return 0; // Nothing to do here for now
}

// Function called when the device is closed
static int device_release(struct inode *inode, struct file *file)
{
    return 0; // Nothing to do here for now
}

// Function called when data is read from the device
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    unsigned int port = *offset;
    unsigned char value = 0;
    value = GET_GPIO(port);
    printk("read %d-%d\n", port, value);
    put_user(value, buffer);
    return 1;
}

// Function called when data is written to the device
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    int bytes_written = 0;
    unsigned int port = *offset;
    unsigned char value = *buffer;

    printk("write %d-%d\n", port, value);

    if (value)
        SET_GPIO(port);
    else
        CLR_GPIO(port);

    return 1;
}

// Function called when ioctl command is invoked
static long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    PortInit init;
    ret = copy_from_user(&init, arg, sizeof(init));
    unsigned int port = init.port;
    unsigned int dir = init.dir;
    unsigned int pull = init.mode;

    switch (cmd)
    {
    case IOCTL_PORT_INP:
        // Set the message in the device's buffer
        printk("In Port: %d, mode: %d\n", port, pull);
        // INP_GPIO(port);
        //  Pull_up(port);
        // Pull_down(port);
        //  pull_mode(port, pull);
        break;
    case IOCTL_PORT_OUT:
        printk("Out Port: %d \n", port);
        // OUT_GPIO(port);
        break;

    default:
        printk("Unknown IOCTL %d\n", cmd);
        return -ENOTTY; // Invalid ioctl command
    }

    return 0;
}

// File operations structure for our device driver
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl, // Use unlocked_ioctl for newer kernel versions
    .open = device_open,
    .release = device_release};

struct class *my_class;
int curr_dev;
// Initialization function for the module
static int __init my_gpio_init(void)
{
    // Register the character device
    unsigned int *gpio_registers = (unsigned int *)ioremap(BCM2837_GPIO_ADDRESS, PAGE_SIZE);
    if (gpio_registers == NULL)
    {
        printk("Failed to map GPIO memory to driver\n");
        return -1;
    }
    printk("Base address: %p\n", gpio_registers);
    // gpio_init(gpio_registers);
    gpio = gpio_registers;
    INP_GPIO(20);
    OUT_GPIO(21);
    Pull_down(20);

    devno = MKDEV(major, minor);                          // 根据主设备号和次设备号合成设备号
    int rc = register_chrdev_region(devno, 1, "my-gpio"); // 向系统中注册设备号
    if (rc < 0)
    {
        printk("register_chrdev_region failed!");
        return rc;
    }
    cdev_init(&my_cdev, &fops);        // 初始化字符设备结构体
    rc = cdev_add(&my_cdev, devno, 1); // 将字符设备结构体加入系统中
    if (rc < 0)
    {
        printk("cdev_add failed!");
        return rc;
    }
    printk("dev init success");
    return 0;
}

// Cleanup function for the module
static void __exit my_gpio_cleanup(void)
{
    // Unregister the character device
    iounmap(gpio_registers);
    cdev_del(&my_cdev);
    unregister_chrdev_region(devno, 1); // 向系统中注销设备号    printk(KERN_INFO "Unregistered char device\n");
}

module_init(my_gpio_init);
module_exit(my_gpio_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Liping LIU");
MODULE_DESCRIPTION("GPIO Driver Example");
