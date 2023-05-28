#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <asm/io.h>

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include "gpio.h"

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
        INP_GPIO(port);
        // pull_mode(port, pull);
        break;
    case IOCTL_PORT_OUT:
        printk("Out Port: %d \n", port);
        OUT_GPIO(port);
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
    gpio_init(gpio_registers);

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
