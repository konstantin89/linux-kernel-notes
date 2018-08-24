obj-m := semaphore_example.o
   
KVERSION = $(shell uname -r)
   
semaphore_example-objs += module.o
semaphore_example-objs += fill_list.o
 
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
