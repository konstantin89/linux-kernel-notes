#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <asm/page.h> // For PAGE_SIZE

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tutorial");
MODULE_DESCRIPTION("Kernel memory notes");

/*
Additional reading

    https://linux-kernel-labs.github.io/refs/pull/183/merge/labs/memory_mapping.html

kmalloc - low memory segment

    kmalloc allocates memory in low memory. 
    This is the memory segment where kernel stores all important data structures.
    Its both virtually and physically continuous. 
    You can allocate relatively small memory segments (few KBs) with it. 
    Kernel stacks are allocated in low memory.
    Kernel code and text are allocated in low memory

vmalloc - high memory segment

    vmalloc allocates memory on high memory segment.

    "high memory" refers to the region of physical memory beyond the low memory region. 
    On 32-bit systems, high memory is typically used to map additional physical memory 
    beyond what can be directly addressed by the kernel. On 64-bit systems, the concept 
    of high memory is less relevant due to the larger address space.

*/

/*
kmalloc flags

GFP_KERNEL
This is the most common flag and is used when allocating memory in a normal kernel context. 
Memory allocated with this flag is subject to standard kernel memory management and can be 
accessed efficiently.
Note that this flag can be used only in contexts that are allowed to sleep.

GFP_ATOMIC
This flag is used when memory allocation is required in atomic or interrupt contexts, 
where sleeping is not allowed. Memory allocated with this flag should be used with caution, 
as it may lead to memory fragmentation. It's suitable for very quick, non-blocking allocations.

GFP_DMA
This flag is used when you need memory that is suitable for direct memory access (DMA) operations. 
It ensures that the allocated memory is in a region of physical memory that is accessible to 
DMA-capable devices.

GFP_USER
This flag is used when allocating memory on behalf of user-space processes. 
It ensures that the memory is accessible from user-space and follows user-space memory 
allocation rules.

GFP_NOFS
This flag is used when allocating memory in a context where the kernel's file system may be locked. 
It is used to avoid potential deadlocks when memory allocation occurs within file system operations.

GFP_NOIO
This flag is used when allocating memory in a context where the kernel's I/O subsystem may be locked. 
It helps avoid potential deadlocks related to I/O operations.

GFP_NOWAIT
This flag is used when you want to attempt memory allocation without blocking. 
If memory is not immediately available, kmalloc will return NULL instead of waiting for memory 
to become available.

GFP_DMA32
This flag is used to request memory in the lower 4GB of physical address space on 64-bit systems. 
It's used to ensure that memory is accessible to devices that have a limitation on addressing 
memory above 4GB.

GFP_TRANSHUGE
This flag is used to request memory for transparent huge pages. 
Transparent huge pages are a memory management feature that combines multiple small pages
into a single large page for improved efficiency.

*/

static char *kmalloc_buffer = NULL; 
static char *vmalloc_buffer = NULL; 

static void AllocMemory(void)
{
    printk(KERN_INFO "System page size: %lu", PAGE_SIZE);

    kmalloc_buffer = kmalloc(1024, GFP_KERNEL);
    if (kmalloc_buffer == NULL)
    {
        printk(KERN_INFO "X kmalloc failed");
        return;
    }

    vmalloc_buffer = vmalloc(PAGE_SIZE);
    if (vmalloc_buffer == NULL)
    {
        printk(KERN_INFO "X vmalloc failed");
        return;
    }
}

static void FreeMemory(void)
{
    if (NULL != kmalloc_buffer)
    {
        kfree(kmalloc_buffer);
        kmalloc_buffer = NULL;
    }

    if (NULL != vmalloc_buffer)
    {
        vfree(vmalloc_buffer);
        vmalloc_buffer = NULL;
    }
}


static int __init hello_init(void) 
{
    printk(KERN_INFO "Kernel init started\n");
    AllocMemory();
    printk(KERN_INFO "Kernel init done\n");

    return 0;
}

static void __exit hello_exit(void) 
{
    printk(KERN_INFO "Goodbye, Kernel!\n");
    FreeMemory();
}

module_init(hello_init);
module_exit(hello_exit);