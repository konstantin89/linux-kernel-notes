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

static void VirtToPhys(void)
{
    phys_addr_t physAddr = 0;
    phys_addr_t diff = 0;

    if ((NULL == kmalloc_buffer) || (NULL == vmalloc_buffer))
    {
        return;
    }

    physAddr = virt_to_phys(kmalloc_buffer);
    printk(KERN_INFO "kmalloc Kernel logical address -> Physical: [%p]->[0x%x]", 
           kmalloc_buffer, physAddr);
    
    diff = kmalloc_buffer - physAddr;
    printk(KERN_INFO "kmalloc Kernel logical address - Physical mapping = [0x%x]", diff);

    physAddr = virt_to_phys(vmalloc_buffer);
    printk(KERN_INFO "vmalloc Kernel logical address -> Physical: [%p]->[0x%x]", 
           vmalloc_buffer, physAddr);
    
    diff = vmalloc_buffer - physAddr;
    printk(KERN_INFO "vmalloc Kernel logical address - Physical mapping = [0x%x]", diff);

    // Example output:
    // [98324.519404] kmalloc Kernel logical address -> Physical: [a4534e74]->[0x3997c00]
    // [98324.519422] kmalloc Kernel logical address - Physical mapping = [0x80000000]
    // [98324.519432] vmalloc Kernel logical address -> Physical: [d4c6f648]->[0x3b84e000]
    // [98324.519444] vmalloc Kernel logical address - Physical mapping = [0x80000000]

    // From "Linux device drivers - Chapter 15"
    // Kernel logical address is the address in kernel space
    // Note that kernel logical address and physical address are diff only by const value!

    // sudo cat /proc/iomem content:
    //
    // 00000000-3b3fffff : System RAM
    //   00008000-00efffff : Kernel code
    //   01000000-01204b47 : Kernel data
    // 3f004000-3f00401f : 3f004000.txp txp@7e004000
    // 3f006000-3f006fff : dwc_otg
    // 3f007000-3f007eff : 3f007000.dma dma@7e007000
    // 3f00a000-3f00a023 : 3f100000.watchdog asb
    // 3f00b840-3f00b87b : 3f00b840.mailbox mailbox@7e00b840
    // 3f00b880-3f00b8bf : 3f00b880.mailbox mailbox@7e00b880
    // 3f100000-3f100113 : 3f100000.watchdog pm
    // 3f101000-3f102fff : 3f101000.cprman cprman@7e101000
    // 3f104000-3f10400f : 3f104000.rng rng@7e104000
    // 3f200000-3f2000b3 : 3f200000.gpio gpio@7e200000
    // 3f201000-3f2011ff : serial@7e201000
    //   3f201000-3f2011ff : 3f201000.serial serial@7e201000
    // 3f202000-3f2020ff : 3f202000.mmc mmc@7e202000
    // 3f206000-3f2060ff : 3f206000.pixelvalve pixelvalve@7e206000
    // 3f207000-3f2070ff : 3f207000.pixelvalve pixelvalve@7e207000
    // 3f212000-3f212007 : 3f212000.thermal thermal@7e212000
    // 3f215000-3f215007 : 3f215000.aux aux@7e215000
    // 3f300000-3f3000ff : 3f300000.mmcnr mmcnr@7e300000
    // 3f400000-3f405fff : 3f400000.hvs hvs@7e400000
    // 3f805000-3f805fff : 3f805000.i2c i2c@7e805000
    // 3f807000-3f8070ff : 3f807000.pixelvalve pixelvalve@7e807000
    // 3f808000-3f8080ff : 3f902000.hdmi hd
    // 3f902000-3f9025ff : 3f902000.hdmi hdmi
    // 3f980000-3f98ffff : dwc_otg
    // 3fc00000-3fc00fff : 3fc00000.v3d v3d@7ec00000
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
    VirtToPhys();
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