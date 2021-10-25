# Allot Kernel Course

## mknod
Make Node used to create device nodes for character devices.  
This means we can take character device minor and major numbers to create a device file node.  

For example, let check acme.c char device:  
1. Make sure that no acme is present in /proc/devices  
2. Compile acme.ko using make    
3. sudo insmod `acme.ko`   
4. Make sure that acme is present in /proc/devices    
5. Create device node for the acme (mknod acme c 92 0)   
6. Write to the device node (echo "hello world" > acme)  
7. Read from device node (cat acme).   

## /proc/devices
This file allows one to inspect the current loaded devices.
```
cat /proc/devices

Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
...

Block devices:
  8 sd
  9 md
 65 sd
 66 sd
...

```

## modinfo

modinfo allows one to inspect compiled kernel object file for metadata.
```
[root@EMBD-VM-00074 src]# modinfo acme.ko
filename:       /home/student/src/acme.ko
author:         Free Electrons
description:    Example character driver
license:        GPL
srcversion:     63C55A07FA93E83D7CE3302
depends:
retpoline:      Y
name:           acme
vermagic:       5.4.17-2102.204.4.4.el8uek.x86_64 SMP mod_unload modversions
```

## slab allocator
Slab allocator is optimiesed for small memory chunks allocations.  
cat `/proc/slabinfo` file presents all available slab segments.  
`slabtop` application can be used to inspect slab managers on the system.   
 

 Example code for working with slab allocator.  
 Check `/proc/slabinfo` for the new my_cache slab.  
``` C
static struct kmem_cache *my_cachep;

static int __init hello_init(void)
{
  void* obj;

  /* 
    Note that new slab will be created only if object size param for  
    kmem_cache_create is non round number (not a pow of 2).  
  */
  my_cachep = kmem_cache_create(
    "my_cache", // Name
    1679, // Object size
    0, 
    SLAB_HWCACHE_ALIGN, 
    NULL);

  // Allocate object from cache
  obj = kmem_cache_alloc(my_cachep, GFP_KERNEL);
 
  // Release the allocated block
  kmem_cache_free(my_cachep, obj);

  return 0;
}

static void __exit hello_exit(void)
{ 
  printk(KERN_ALERT "Goodbye, cruel world\n");

  //Release the cache
  kmem_cache_destroy(my_cachep);
}

```
