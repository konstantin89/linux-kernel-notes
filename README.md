# Linux Kernel Notes


## Links

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

[sudo dmesg] : View kernel log messages

[sudo insmod main.ko] : Install kernel module

[sudo rmmod main.ko] : Uninstall kernel module

[nm main.ko] : List symbols of object file


```

---
</br>

