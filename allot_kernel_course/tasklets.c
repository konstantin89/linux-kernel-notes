#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
  
// execute it as
// sudo insmod ./interrupt.ko irq=1
// for testing use irq numbers from cat /proc/interrupts
  
// remove module as
// sudo rmmod interrupt
  
static int irq;

module_param(irq, int, 0);
MODULE_PARM_DESC(irq, "The IRQ to hook into");
  
struct info_to_pass {
    int *some_int;
    int mycount;
    long prevTime;
} dev_info;

// Bottom half
void my_tasklet_func(unsigned long data)
{    
    struct info_to_pass *info = (struct info_to_pass*)data;
    long timePassed = 0;
     
    if (info->mycount < 100) 
    {
        /*
        * Calculate the time passed from IRQ call to the time this tasklet  
        * is called. On Oracle Linux, the values I got here are about secs.
        *  2000 nano
        */
        long prevTime = info->prevTime;      
        if(prevTime != 0) timePassed = ktime_get_ns() - info->prevTime;
       
        printk("interrupt.ko: Interrupt #%d, time from prev call [%lu]\n",  
               info->mycount, 
               timePassed);
        info->mycount++;
         
    }
}

// Declare the tasklet as global variable called my_tasklet.
DECLARE_TASKLET(my_tasklet, my_tasklet_func, &dev_info);

static irqreturn_t irq_handler_my(int irq, void *dev_id) 
{
    // Save current time. We will calculate the time from IRQ to tasklet run.  
    dev_info.prevTime = ktime_get_ns();

    // Schedule tasklet to run.
    tasklet_schedule(&my_tasklet);
    return IRQ_HANDLED;
}

static int __init mymodule_init(void) 
{
    printk(KERN_ALERT "interrupt.ko: Loaded at: %llu ns\n", ktime_get_ns());
  
    dev_info.mycount = 0;
    dev_info.prevTime = 0;
    if (request_irq(irq, &irq_handler_my, IRQF_SHARED, "interrupt.ko", &
        dev_info)) 
    {
        printk(KERN_ERR "interrupt.ko: cannot register IRQ %d\n", irq);
        return -EIO;
    }
  
    printk("Request on IRQ %d succeeded\n", irq);
    return 0;
}
  
static void __exit mymodule_exit(void) {
    free_irq(irq, &dev_info);
    printk("Freeing IRQ %d\n", irq);
    printk ("Unloading my module.\n");
    tasklet_kill(&my_tasklet);
    return;
}
  
module_init(mymodule_init);
module_exit(mymodule_exit);
  
MODULE_LICENSE("GPL");
