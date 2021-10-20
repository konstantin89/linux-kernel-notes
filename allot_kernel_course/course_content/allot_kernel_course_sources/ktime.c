#include <linux/init.h>
#include <linux/module.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	printk(KERN_ALERT "Loaded at: %llu ns\n", ktime_get_ns() );
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Removed at: %llu ns\n", ktime_get_ns() );
}

module_init(hello_init);
module_exit(hello_exit);

