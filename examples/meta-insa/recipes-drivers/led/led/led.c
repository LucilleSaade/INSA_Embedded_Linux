#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/gpio.h>
#include <linux/fs.h>

MODULE_DESCRIPTION("led");
MODULE_AUTHOR("Lahoudere Fabien");
MODULE_LICENSE("GPL");

#define LED_GPIO_NUMBER -1


static int __init led_init(void)
{
	/*** Switch on the led on module insertion ***/
	
	return 0;
}
 
static void __exit led_cleanup(void)
{
	/*** Switch off the led on module deletion ***/
}
 
module_init(led_init);
module_exit(led_cleanup);
