#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <asm/io.h>

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include "gpio.h"

#define DEVICE_NAME "mygpio"
#define BUF_LEN 1024

// Define custom ioctl commands
#define IOCTL_PORT_INP _IOW(0, 1, char *)
#define IOCTL_PORT_OUT _IOW(0, 2, char *)

static int Major;         // Major number assigned to our device driver
static char msg[BUF_LEN]; // Buffer to store data written to the device
static int msg_len;       // Length of the message stored in the buffer

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

    unsigned int *ioctl_msg = (unsigned int *)arg;
    unsigned int port = ioctl_msg[0];
    unsigned int dir = ioctl_msg[1];
    unsigned int pull = ioctl_msg[2];

    switch (cmd)
    {
    case IOCTL_PORT_INP:
        // Set the message in the device's buffer
        INP_GPIO(port);
        pull_mode(port, pull);
        break;
    case IOCTL_PORT_OUT:
        OUT_GPIO(port);
        break;

    default:
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

    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0)
    {
        printk(KERN_ALERT "Failed to register char device: %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "Registered char device with major number %d\n", Major);
    return 0;
}

// Cleanup function for the module
static void __exit my_gpio_cleanup(void)
{
    // Unregister the character device
    unregister_chrdev(Major, DEVICE_NAME);
    iounmap(gpio_registers);
    printk(KERN_INFO "Unregistered char device\n");
}

module_init(my_gpio_init);
module_exit(my_gpio_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Liping LIU");
MODULE_DESCRIPTION("GPIO Driver Example");
