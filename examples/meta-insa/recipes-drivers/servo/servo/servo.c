#include <linux/module.h> // included for all kernel modules
#include <linux/kernel.h> // included for KERN_INFO
#include <linux/init.h> // included for __init and __exit macros
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>


MODULE_DESCRIPTION("servo");
MODULE_AUTHOR("Lahoudere Fabien");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "servo"
#define MAJOR_NUM 0

static int major = 0, minor = 1;
static struct class * servoclass = NULL;
static struct cdev servodev;
static struct device *device = NULL;

static int servo_open (struct inode * inode_p, struct file * file_p )
{
        printk(KERN_INFO "servo device opening!\n");

        return 0;
}

static int servo_read (struct file *fp, char __user *buf, size_t size, loff_t * pos )
{
        printk(KERN_INFO "servo device read!\n");

        return size;
}

static int servo_write ( struct file *fp, const char __user *buf, size_t size, loff_t * pos )
{
        printk(KERN_INFO "servo device write!\n");
        
        return size;
}

static int servo_release (struct inode * inode_p, struct file * file_p )
{
        printk(KERN_INFO "servo device released!\n");
        
        return 0;
}


static struct file_operations servo_fops = {
        .owner = THIS_MODULE,
        .read = servo_read,
        .write = servo_write,
        .open = servo_open,
        .release = servo_release,
};

static int __init servo_init(void)
{
	int ret = 0;
	dev_t dev = 0;
	
	ret = alloc_chrdev_region ( &dev, MAJOR_NUM, minor, DEVICE_NAME );
	if ( ret < 0 )
	{
		printk( KERN_INFO "alloc_chrdev_region fail\n");
		return ret;
	}

	major = MAJOR(dev);
	printk( KERN_INFO "New device with major: %d\n", major );
	
	servoclass = class_create( THIS_MODULE, DEVICE_NAME );
	if ( IS_ERR(servoclass) )
	{
		ret = PTR_ERR(servoclass);
		printk( KERN_INFO "alloc_chrdev_region fail\n");
		unregister_chrdev_region(MKDEV(major, minor), 1);
		return ret;
	}
	
	cdev_init(&servodev, &servo_fops);
	servodev.owner = THIS_MODULE;
	
	ret = cdev_add( &servodev, MKDEV(major, minor), 1 );
	if ( ret < 0 )
	{
		printk( KERN_INFO "cdev_add fail\n");
		class_destroy(servoclass);
		unregister_chrdev_region(MKDEV(major, minor), 1);
		return ret;
	}

	device = device_create( servoclass, NULL, MKDEV(major, minor), NULL, DEVICE_NAME "%d", minor);
	if (IS_ERR(device)) 
	{
		ret = PTR_ERR(device);
		printk(KERN_WARNING "[target] Error %d while trying to create %s%d", ret, DEVICE_NAME, minor);
		cdev_del(&servodev);
		class_destroy(servoclass);
		unregister_chrdev_region(MKDEV(major, minor), 1); 
	 	return ret;
	 }

        return 0;
}
 
static void __exit servo_cleanup(void)
{
	device_destroy(servoclass, MKDEV(major, minor));
	cdev_del(&servodev);
	class_destroy(servoclass);
	unregister_chrdev_region(MKDEV(major, minor), 1);
	printk("servo: Module cleanup called\n");
}

module_init(servo_init);
module_exit(servo_cleanup);
