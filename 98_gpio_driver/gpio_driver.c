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

// Define custom ioctl commands
#define IOCTL_PORT_INP _IOW(0, 1, char *)
#define IOCTL_PORT_OUT _IOW(0, 2, char *)

static int Major;           // Major number assigned to our device driver
static char msg[BUF_LEN];   // Buffer to store data written to the device
static int msg_len;         // Length of the message stored in the buffer
static dev_t dev_num;       // Device number
static struct cdev my_cdev; // Character device structure
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

    // Allocate a device number
    if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0)
    {
        printk(KERN_ALERT "Failed to allocate device number\n");
        return -1;
    }

    // Initialize the character device structure
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    printk("cdev init, dev_num:%d\n", dev_num);
    // Add the character device to the system
    if (cdev_add(&my_cdev, dev_num, 1) != 0)
    {
        printk(KERN_ALERT "Failed to add character device\n");
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }
    printk("cdev add OK, dev_num:%d\n", dev_num);
    return 0;
}

// Cleanup function for the module
static void __exit my_gpio_cleanup(void)
{
    // Unregister the character device
    iounmap(gpio_registers);
    cdev_del(&my_cdev);

    // Release the device number
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Unregistered char device\n");
}

module_init(my_gpio_init);
module_exit(my_gpio_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Liping LIU");
MODULE_DESCRIPTION("GPIO Driver Example");
