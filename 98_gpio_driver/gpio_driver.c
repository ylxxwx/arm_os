#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/proc_fs.h>
#include <linux/slab.h>

#include <asm/io.h>

#include "gpio.h"

#define LLL_MAX_USER_SIZE 1024

static struct proc_dir_entry *lll_proc[22];

static char data_buffer[LLL_MAX_USER_SIZE + 1] = {0};

static unsigned int *gpio_registers = NULL;

ssize_t lll_read(struct file *file, char __user *user, size_t size, loff_t *off)
{
    return 0;
}

ssize_t lll_write(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    return 0;
}

int lll_open(struct inode *node, struct file *f)
{
    printk("inode name:%s, size:%d, type:%x, mode;%x \n", "node->name", node->i_size, 0xFF, node->i_mode);
    printk("file: name:%s, type:%x, mode:%x \n", "no name", 0xFF, f->f_mode);
    return 0;
}

static const struct proc_ops lll_proc_fops = {
    .proc_read = lll_read,
    .proc_write = lll_write,
    .proc_open = lll_open,
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
    for (int idx = 0; idx < 22; idx++)
    {
        char name[16];
        sprintf(name, "my-gpio-%d", idx);
        lll_proc[idx] = proc_create(name, 0666, NULL, &lll_proc_fops);
        if (lll_proc == NULL)
        {
            return -1;
        }
    }

    return 0;
}

static void __exit gpio_driver_exit(void)
{
    printk("Leaving my driver!\n");
    iounmap(gpio_registers);
    for (int idx = 0; idx < 22; idx++)
    {
        proc_remove(lll_proc[idx]);
    }
    return;
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Driver Study");
MODULE_DESCRIPTION("Test of writing drivers for RASPI");
MODULE_VERSION("1.0");
