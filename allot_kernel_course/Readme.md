# Allot Kernel Course

## mknod
Make Node used to create device nodes for character devices.  
This means we can take character device minor and major numbers to create a device file node.  

For example, let check acme.c char device:  
1. Make sure that no acme is present in /proc/devices  
2. Compile acme.ko using make    
3. sudo insmod acme.ko   
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