# Linux Kernel Reference

## Chapters

[Linux Kernel Modules](lkm/README.md)

## Commands

``` bash

[uname -r] : Check the kernel version of the running host

```

## Cloning kernel sources

Run `uname -` command to get the kernel release running on  
the given host.  

For output of `4.19.118-v7+` on RaspPi machine, we need to clone 
the `rpi-4.19.y` branch from RaspPi   kernel repo.  

``` bash

git clone -b rpi-4.19.y --depth 1 https://github.com/raspberrypi/linux --single-branch

```