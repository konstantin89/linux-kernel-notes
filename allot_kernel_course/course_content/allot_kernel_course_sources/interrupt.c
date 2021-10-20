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
} dev_info;

  
static irqreturn_t my_interrupt_handler(int irq, void *dev_id) 
{
    // info is what we passed as &dev_info to request_irq
    // this variable is just a argument carrier from module_init to IRQ handler.
    
    struct info_to_pass *info = dev_id;
 
    // static counter to just print debug message 100 times,
    // saying we received interrupt, after 100, we don't print anything
    // but interrupt might have came.
    if (info->mycount < 100) {
        printk("interrupt.ko: Interrupt #%d \n", info->mycount);
        info->mycount++;
    }
    return IRQ_HANDLED;
}


static int __init mymodule_init(void) 
{
	printk(KERN_ALERT "interrupt.ko: Loaded at: %llu ns\n", ktime_get_ns() );
  
/* request_irq: allocate a given interrupt line */
// int request_irq(unsigned int irq,
//                irq_handler_t handler,
//                unsigned long flags,
//                const char *name,
//                void *dev)
    dev_info.mycount = 0;
  
    if (request_irq(irq, &my_interrupt_handler, IRQF_SHARED, "interrupt.ko", &dev_info)) 
    {
        printk(KERN_ERR "interrupt.ko: cannot register IRQ %d\n", irq);
        return -EIO;
    }
  
//The second parameter, handler, is a function pointer to the actual interrupt handler that services this interrupt. This function is invoked whenever the operating system receives the interrupt.
  
// IRQF_SHARED. This flag specifies that the interrupt line can be shared among multiple interrupt handlers. Each handler registered on a given line must specify this flag; otherwise, only one handler can exist per line.
  
    printk("Request on IRQ %d succeeded\n", irq);
    return 0;
}
  
static void __exit mymodule_exit(void) {
    free_irq(irq, &dev_info);
    printk("Freeing IRQ %d\n", irq);
  
    printk ("Unloading my module.\n");
    return;
}
  
module_init(mymodule_init);
module_exit(mymodule_exit);
  
MODULE_LICENSE("GPL");
