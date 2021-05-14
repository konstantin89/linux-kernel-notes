obj-m += greetNetlinkLKM.o
all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean

i:
	sudo insmod greetNetlinkLKM.ko

u:
	sudo rmmod greetNetlinkLKM.ko