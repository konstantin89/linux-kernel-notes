# Linux Kernel Modules

## Basic LKM structure

### Module entry point

Prototype: `int func_name(void)`

Entry point function should return 0 if the init has been done  
successfuly. Non zero return value will indicate errors and prevent  
the modules load.  

The init function should be static and should be marked with the  
`__init` macro.  

</br>

### Module exit point

Prototype: `void func_name(void)`

The exit function should be static and should be marked with the  
`__exit` macro. 

</br>

### The __init and __exit macros
 
![](img/init_exit_macros.PNG)

![](img/init_section_of_elf_file.PNG)

![](img/kernel_build.PNG)

</br>

### Hello World module example

main.cpp
``` C

#include<linux/module.h>

static int __init helloworld_init(void)
{
   pr_info("Hello world\n");
   return 0;
}

static void __exit helloworld_cleanup(void)
{
  pr_info("Good bye world\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Incognito");
MODULE_DESCRIPTION("A simple hello world kernel module");

```

Makefile
```
obj-m := main.o

all:
	make -C /usr/lib/modules/4.19.0-12-amd64/build M=$(PWD) modules

clean:
	make -C /usr/lib/modules/4.19.0-12-amd64/build M=$(PWD) clean

```

Run "sudo insmod main.ko" to insntall the generated kernel module.
Then run "sudo dmesg" to view the kernel logs to find "Hello world".

</br>

## Compiling kernel modules

### In-tree Out-tree kernel modules

![](img/dynamicaly_loadable_modules.PNG)

</br>

![](img/out_of_tree_modules.PNG)

</br>

### Makefiles

![](img/module_makefile.PNG)

![](img/module_makefile_2.PNG)

![](img/make_syntax.PNG)

![](img/make_syntax_targets.PNG)


</br>

## Intree building

![](img/intree_building.PNG)
