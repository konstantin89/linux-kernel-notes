#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

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

typedef struct my_work_t
{
    struct work_struct my_work;
    struct info_to_pass *info;
} my_work_t;

static struct workqueue_struct *my_queue;

my_work_t *work1;

void my_work_func(struct work_struct *work)
{    
    my_work_t* my_work = (my_work_t*)work;
    struct info_to_pass *info = my_work->info;
    
    long timePassed = 0;
     
    if (info->mycount < 100) 
    {
        long prevTime = info->prevTime;      
        if(prevTime != 0) timePassed = ktime_get_ns() - info->prevTime;
       
        printk("interrupt.ko: Interrupt #%d, time from prev call [%lu]\n", info->mycount, timePassed);
        info->mycount++;
         
    }
    
    kfree(work);
}

static irqreturn_t irq_handler_my(int irq, void *dev_id) 
{  
    dev_info.prevTime = ktime_get_ns();

    // Schedule work.
    work1 = (my_work_t*)kmalloc(sizeof(my_work_t), GFP_KERNEL);
    if(work1)
    {
        INIT_WORK((struct work_struct*)work1, my_work_func);
        work1->info = &dev_info;
        queue_work(my_queue, (struct work_struct*)work1);
    }
    return IRQ_HANDLED;
}

static int __init mymodule_init(void) 
{
    printk(KERN_ALERT "interrupt.ko: Loaded at: %llu ns\n", ktime_get_ns() );
    
    my_queue = create_workqueue("my_queue");
    
    dev_info.mycount = 0;
    dev_info.prevTime = 0;
    if (request_irq(irq, &irq_handler_my, IRQF_SHARED, "interrupt.ko", &dev_info)) 
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
    
    flush_workqueue(my_queue);
    destroy_workqueue(my_queue);
    
    return;
}
  
module_init(mymodule_init);
module_exit(mymodule_exit);
  
MODULE_LICENSE("GPL");