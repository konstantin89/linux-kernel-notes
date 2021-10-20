# Makefile for the hello module
obj-m += hello.o  

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

EXTRA_CFLAGS = -g

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) M=$(PWD) modules
