obj-m += hello_kernel_module.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

i:
	sudo insmod hello_kernel_module.ko

u:
	sudo rmmod hello_kernel_module.ko

log:
	sudo dmesg -w

ls:
	sudo lsmod