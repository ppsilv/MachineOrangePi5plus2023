#include <linux/module.h>
#include <linux/init.h>


/*Meta information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paulo da Silva");
MODULE_DESCRIPTION("My first driver in orange pi");
MODULE_INFO(intree, "Y");


static int __init ModuleInit(void)
{
	printk("hello: Input - This is my first Kernel driver PAULOSILVA");
	return(0);
}
	
static void __exit ModuleExit(void)
{
	printk("hello: Output - Module PAULOSILVA exiting...");
}

module_init(ModuleInit);
module_exit(ModuleExit);

