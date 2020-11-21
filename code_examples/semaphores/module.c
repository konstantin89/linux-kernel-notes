/**
 * semaphore_example
 * 
 * Basic Kernel module that demonstrates kernel semaphore usage.
 * In this example, few kthreads are spawn and used to concurrently 
 * fill list of elements.
 */

#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>
#include <linux/delay.h>
#include "fill_list.h"

//Number of threads concurrently filling the list. 
#define THREADS_TO_START 3

#define SECONDS_TO_WAIT_FOR_THREADS 3

static void sleep_seconds(unsigned int seconds)
{
    msleep(1000 * seconds);
}

static int semaphore_example(void)
{
    init_fill_list();

    if(start(THREADS_TO_START) != FL_SUCCESS_CODE)
    {
        printk(KERN_ERR "[X] semaphore_example start failed");
        return FL_ERROR_CODE;
    }

    //Sleep until all threads finish to run.
    sleep_seconds(SECONDS_TO_WAIT_FOR_THREADS);

    //Print list content into /var/log/syslog
    print_list();

    //Clean used resources
    clean_fill_list();

	return FL_SUCCESS_CODE;
}

static int __init init(void)
{
    int exit_code = 0;

    printk(KERN_INFO "[ ] semaphore_example init started");

    exit_code = semaphore_example();

    printk(KERN_INFO "[ ] semaphore_example init done");

    return exit_code;
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
