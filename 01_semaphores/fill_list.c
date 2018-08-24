#include <linux/delay.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h>


#include "fill_list.h"

#define FILLER_ITERATIONS 5
#define USECS_BETWEEN_INSERTIONS 10

static ListEntry g_list;
static struct semaphore g_sem;
static ThreadArr g_thread_arr;

static int clean_thread_arr(void);
static int clean_entry_list(void);
static int filler_func(void* arg);


int init_fill_list(void)
{
    sema_init(&g_sem, 1);
    INIT_LIST_HEAD(&g_list.list);

    return 0;
}

int clean_fill_list(void)
{
    clean_entry_list();
    clean_thread_arr();

    return 0;
}

int start(int thread_count)
{
    int index = 0;

    g_thread_arr.arr = kmalloc(sizeof(struct task_struct*) * thread_count, GFP_KERNEL);

    if(g_thread_arr.arr == NULL)
    {
        printk(KERN_ERR "[X] semaphore_example kmalloc failed");
        return 1;
    }

    for(index=0; index<thread_count; index++)
    {
        printk(KERN_INFO "[ ] semaphore_example starting [%d] thread", index);
        g_thread_arr.arr[index] = kthread_run(filler_func, NULL, "filler_thread");
    }

    return 0;
}

int print_list(void)
{
    struct list_head* node;
    struct list_head* temp_node;
    ListEntry* curr;

    down_interruptible(&g_sem);

    list_for_each_safe(node, temp_node, &g_list.list)
    {
        curr = list_entry(node, struct ListEntry, list);
        printk(KERN_INFO "[ ] semaphore_example producer_tid=[%d]", curr->producer_tid);
    }

    up(&g_sem);

    return 0;
}

static int filler_func(void* arg)
{
    ListEntry* newEntry= NULL;
    int index = 0;

    for(index=0; index<FILLER_ITERATIONS; index++)
    {
        udelay(USECS_BETWEEN_INSERTIONS);

        down_interruptible(&g_sem);

        newEntry = kmalloc(sizeof (struct ListEntry), GFP_KERNEL);
        if (IS_ERR(newEntry)) 
        {
            printk(KERN_ERR "[X] semaphore_example kmalloc failed");
            
            /* HANDLE ERROR */
        }

        INIT_LIST_HEAD(&newEntry->list);
        newEntry->producer_tid = current->pid;
        list_add_tail(&newEntry->list, &g_list.list);

        up(&g_sem);
    }

    return 0;
}

static int clean_thread_arr(void)
{
    int index = 0;

    for(index=0; index < g_thread_arr.size; index++)
    {
        if(g_thread_arr.arr[index] != NULL)
            kthread_stop(g_thread_arr.arr[index]);
    }

    kfree(g_thread_arr.arr);
    g_thread_arr.arr = NULL;
    return 0;
}

static int clean_entry_list(void)
{
    struct list_head* node;
    struct list_head* temp_node;
    ListEntry* curr;

    down_interruptible(&g_sem);

    list_for_each_safe(node, temp_node, &g_list.list)
    {
        curr = list_entry(node, struct ListEntry, list);
        list_del(&curr->list);
    }

    up(&g_sem);

    return 0;
}
