# Linux Kernel Notes

## Links
[Allot Kernel Course ](allot_kernel_course/README.md)  
[Linux kernel reference](reference/README.md)  

---
</br>

## Preparing a Development Environment

### Installing linux kernel headers
All installed Linux kenel headers are located under `/usr/src`.  

On Raspberry Pi use:
```
sudo apt install raspberrypi-kernel-headers
```

On other machines use:
```
 sudo apt-get install linux-headers-$(uname -r)
```

---
</br>


## Commands

``` bash

[uname -r] : Check the kernel version of the running host

[sudo dmesg -w] : View kernel log messages (-w for follow)  

[sudo insmod main.ko] : Install kernel module

[sudo rmmod main.ko] : Uninstall kernel module

[nm main.ko] : List symbols of object file


```

---
</br>

## Important /proc files

### /proc/iomem
Contains ranges of physical memory addresses.
``` bash
pi@raspberrypi:~ $ sudo cat /proc/iomem
00000000-3b3fffff : System RAM
  00008000-00efffff : Kernel code
  01000000-01204b47 : Kernel data
3f004000-3f00401f : 3f004000.txp txp@7e004000
3f006000-3f006fff : dwc_otg
3f007000-3f007eff : 3f007000.dma dma@7e007000
3f00a000-3f00a023 : 3f100000.watchdog asb
3f00b840-3f00b87b : 3f00b840.mailbox mailbox@7e00b840
3f00b880-3f00b8bf : 3f00b880.mailbox mailbox@7e00b880
3f100000-3f100113 : 3f100000.watchdog pm
3f101000-3f102fff : 3f101000.cprman cprman@7e101000
3f104000-3f10400f : 3f104000.rng rng@7e104000
3f200000-3f2000b3 : 3f200000.gpio gpio@7e200000
3f201000-3f2011ff : serial@7e201000
  3f201000-3f2011ff : 3f201000.serial serial@7e201000
3f202000-3f2020ff : 3f202000.mmc mmc@7e202000
3f206000-3f2060ff : 3f206000.pixelvalve pixelvalve@7e206000
3f207000-3f2070ff : 3f207000.pixelvalve pixelvalve@7e207000
3f212000-3f212007 : 3f212000.thermal thermal@7e212000
3f215000-3f215007 : 3f215000.aux aux@7e215000
3f300000-3f3000ff : 3f300000.mmcnr mmcnr@7e300000
3f400000-3f405fff : 3f400000.hvs hvs@7e400000
3f805000-3f805fff : 3f805000.i2c i2c@7e805000
3f807000-3f8070ff : 3f807000.pixelvalve pixelvalve@7e807000
3f808000-3f8080ff : 3f902000.hdmi hd
3f902000-3f9025ff : 3f902000.hdmi hdmi
3f980000-3f98ffff : dwc_otg
3fc00000-3fc00fff : 3fc00000.v3d v3d@7ec00000

```

---
</br>