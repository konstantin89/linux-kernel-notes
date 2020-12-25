obj-m := main.o

all:
	make -C /usr/lib/modules/4.19.0-12-amd64/build M=$(PWD) modules

clean:
	make -C /usr/lib/modules/4.19.0-12-amd64/build M=$(PWD) clean
