// Defining __KERNEL__ and MODULE allows us to access kernel-level code not usually available to userspace programs.
#undef __KERNEL__
#define __KERNEL__
 
#undef MODULE
#define MODULE

// Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h is needed for KERN_INFO.
#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>        // included for __init and __exit macros
#include <linux/gpio.h>
#include <linux/fs.h>
#include "led.h"

MODULE_DESCRIPTION("led");
MODULE_AUTHOR("Lahoudere Fabien");
MODULE_LICENSE("GPL");

#define LED_GPIO_NUMBER -1
#define DEVICE_NAME "led"

static int major;

static int led_open (struct inode * inode_p, struct file * file_p )
{
	printk(KERN_INFO "Led device opening!\n");

	return 0;
}

static long led_ioctl( struct file * file_p, unsigned int ioctl_num, unsigned long ioctl_param)
{
	printk(KERN_INFO "Controm led device !\n");

	switch (ioctl_num) {
	case IOCTL_GET_VALUE:
		break;

	case IOCTL_SET_VALUE:
		break;
	}

	return 0;
}

static int led_release (struct inode * inode_p, struct file * file_p )
{
	printk(KERN_INFO "Led device released!\n");
	
	return 0;
}


static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = led_ioctl,
	.open = led_open,
	.release = led_release,
};

static int __init led_init(void)
{
	major = register_chrdev(MAJOR_NUM, DEVICE_NAME, &led_fops);
	if (major < 0)
	{
		printk(KERN_ALERT "Registering char device failed with %d\n", major);
		return major;
	}
	else
		printk(KERN_INFO "Led driver assigned to major number %d\n", major);
	
	return 0;
}
 
static void __exit led_cleanup(void)
{
	unregister_chrdev(major, DEVICE_NAME);
}
 
module_init(led_init);
module_exit(led_cleanup);
