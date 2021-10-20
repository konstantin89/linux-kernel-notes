#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("My name");
MODULE_DESCRIPTION("Empty character device");

static int major = 90;
module_param(major, int, 0755);

int __init hello_init(void)
{
	
	dev_t first = MKDEV(major,0);
	int ret = register_chrdev_region(first, 3, "DUALTECH");

	if (ret != 0)
	{
		printk (KERN_ALERT "Failed to register major %d", MAJOR(first));		
		return ret;
	}

    return 0;
}

static void __exit hello_exit(void)
{
	unregister_chrdev_region(MKDEV(major,0), 3);
}

module_init(hello_init);
module_exit(hello_exit);

