#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/proc_fs.h>
#include <linux/slab.h>

#include <asm/io.h>

#include "gpio.h"

#define LLL_MAX_USER_SIZE 1024

static struct proc_dir_entry *lll_proc;

static char data_buffer[LLL_MAX_USER_SIZE + 1] = {0};

static unsigned int *gpio_registers = NULL;

ssize_t lll_read(struct file *file, char __user *user, size_t size, loff_t *off)
{
    char buf[128];
    if (copy_from_user(buf, user, 64))
        return 0;
    unsigned int port, value;
    sscanf(buf, "%d", &port);
    printk("lll_read %d\n", port);
    value = GET_GPIO(port);
    sprintf(buf, "%d", value);
    copy_to_user(user, buf, sizeof(buf));
    return 0;
    return sizeof(buf);
}

ssize_t lll_write(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    char buf[64];
    if (copy_from_user(buf, user, 64))
        return 0;
    unsigned int port, value;
    sscanf(buf, "%d-%d", &port, &value);
    printk("write %d-%d\n", port, value);
    if (value)
        SET_GPIO(port);
    else
        CLR_GPIO(port);

    return 0;
}

static int lll_open(struct inode *node, struct file *f)
{
    printk("inode name:%s, size:%d, type:%x, mode;%x \n", "node->name", node->i_size, 0xFF, node->i_mode);
    printk("file: name:%s, type:%x, mode:%x \n", "no name", 0xFF, f->f_mode);
    return 0;
}

#define OpenPortForWrite 1
#define OpenPortForRead 2

static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    unsigned int value;
    switch (cmd)
    {
    case OpenPortForWrite: // Write
        if (copy_from_user(&value, (unsigned int *)arg, sizeof(value)))
        {
            pr_err("Data Write : Err!\n");
        }
        printk("Value = %u\n", value);
        OUT_GPIO(value);
        break;
    case OpenPortForRead: // Read
    {
        unsigned int port, mode;
        if (copy_from_user(&port, (unsigned int *)arg, sizeof(port)))
        {
            pr_err("Data Read : Err!\n");
        }
        if (copy_from_user(&mode, (unsigned int *)(arg + 4), sizeof(mode)))
        {
            pr_err("Data Read : Err!\n");
        }
        printk("Open port(%d) for read(%d)\n", port, mode);
        INP_GPIO(port);
        pull_mode(port, mode);
    }
    break;
    case 3: // PortIn
        if (copy_to_user((int32_t *)arg, &value, sizeof(value)))
        {
            pr_err("Data Read : Err!\n");
        }
        break;
    case 4: // PortOut
        if (copy_to_user((int32_t *)arg, &value, sizeof(value)))
        {
            pr_err("Data Read : Err!\n");
        }
        break;
    default:
        pr_info("Default\n");
        break;
    }
    return 0;
}

static const struct proc_ops lll_proc_fops = {
    .proc_read = lll_read,
    .proc_write = lll_write,
    .proc_open = lll_open,
    .proc_ioctl = etx_ioctl,
};

static int __init gpio_driver_init(void)
{

    unsigned int *gpio_registers = (unsigned int *)ioremap(BCM2837_GPIO_ADDRESS, PAGE_SIZE);
    if (gpio_registers == NULL)
    {
        printk("Failed to map GPIO memory to driver\n");
        return -1;
    }
    gpio_init(gpio_registers);

    printk("Successfully mapped in GPIO memory\n");

    // create an entry in the proc-fs
    lll_proc = proc_create("my-gpio", 0666, NULL, &lll_proc_fops);
    if (lll_proc == NULL)
    {
        return -1;
    }

    return 0;
}

static void __exit gpio_driver_exit(void)
{
    printk("Leaving my driver!\n");
    iounmap(gpio_registers);
    proc_remove(lll_proc);
    return;
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Driver Study");
MODULE_DESCRIPTION("Test of writing drivers for RASPI");
MODULE_VERSION("1.0");
