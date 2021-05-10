# Linux Kernel Reference

## Chapters

[Linux Kernel Modules](lkm/README.md)   
[Character device drivers](character_devices/README.md)  
[Driver with multiple devices](driver_with_multiple_devices/README.md)  


</br>

## References

[Driver references](https://github.com/niekiran/linux-device-driver-1)


## Cloning kernel sources

Run `uname -` command to get the kernel release running on  
the given host.  

For output of `4.19.118-v7+` on RaspPi machine, we need to clone 
the `rpi-4.19.y` branch from RaspPi   kernel repo.  

``` bash

git clone -b rpi-4.19.y --depth 1 https://github.com/raspberrypi/linux --single-branch

```

</br>

## Linux Utilities

### nm utilitiy

nm utility can be used to list symbols of an object file.

``` bash
debian@debian:~/kernel/hello_world$ nm main.ko
0000000000000000 T cleanup_module
                 U __fentry__
0000000000000000 t helloworld_cleanup
0000000000000000 t helloworld_init
0000000000000000 T init_module
0000000000000000 r __module_depends
0000000000000000 r _note_6
                 U printk
0000000000000000 D __this_module
0000000000000015 r __UNIQUE_ID_name45
0000000000000009 r __UNIQUE_ID_retpoline46
000000000000001f r __UNIQUE_ID_vermagic44
0000000000000000 r ____versions

```

</br>
