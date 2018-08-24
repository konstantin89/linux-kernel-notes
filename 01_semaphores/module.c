#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>
#include <linux/delay.h>
#include "fill_list.h"

#define THREADS_TO_START 3

static int __init init(void)
{
    int retVal = 0;

	printk(KERN_INFO "[ ] semaphore_example init started");

	printk(KERN_INFO "[ ] semaphore_example init_fill_list started");
    init_fill_list();

    retVal = start(THREADS_TO_START);
    if(retVal != 0)
    {
        printk(KERN_ERR "[X] semaphore_example start failed");
    }

    msleep(1000 * 3);

    printk(KERN_INFO "[ ] semaphore_example clean_fill_list started");

    clean_fill_list();

    printk(KERN_INFO "[ ] semaphore_example init done");
	return 0;
}

static void __exit cleanup(void)
{
    printk(KERN_INFO "[ ] semaphore_example cleanup started");

    printk(KERN_INFO "[ ] semaphore_example cleanup done");
}

module_init(init);
module_exit(cleanup);

MODULE_AUTHOR("konstantin89");
MODULE_DESCRIPTION("Module that demonstrates kernel semaphore usage");
MODULE_LICENSE("GPL");
