# Linux Kernel Reference

## Chapters

[Linux Kernel Modules](lkm/README.md)  
[Character device drivers](character_devices/README.md)

</br>

## References

[Driver references](https://github.com/niekiran/linux-device-driver-1)

</br>

## Commands

``` bash

[uname -r] : Check the kernel version of the running host

[sudo dmesg] : View kernel log messages

[sudo insmod main.ko] : Install kernel module


```

</br>

## Cloning kernel sources

Run `uname -` command to get the kernel release running on  
the given host.  

For output of `4.19.118-v7+` on RaspPi machine, we need to clone 
the `rpi-4.19.y` branch from RaspPi   kernel repo.  

``` bash

git clone -b rpi-4.19.y --depth 1 https://github.com/raspberrypi/linux --single-branch

```
