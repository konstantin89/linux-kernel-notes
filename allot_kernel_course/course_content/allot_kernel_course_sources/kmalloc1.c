#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("My name");
MODULE_DESCRIPTION("This module does nothing");

int __init hello_init(void)
{
	void *ptr;
	long size= 1048576; // 1024*1024

	do
	{
		//ptr = kmalloc(size, GFP_KERNEL);
		ptr = vmalloc(size);
		if (!ptr)
		{
			printk (KERN_ALERT "Failed on size %ld", size);
			size += 1048576;	
			return -ENOMEM;
		}
		// kfree(ptr);
		vfree (ptr);
	}
	while (size += 1048576);

    return 0;
}

static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);

