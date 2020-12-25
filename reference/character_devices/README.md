# Character device drivers

## Example

The example device driver for this chapter is located under  
code_examples/pseudo_character_device directory.  

</br>

## Intro

![](img/device_types.PNG)


![](img/character_devices.PNG)

Character devices allow user to read/write a single byte.  
![](img/char_dev_scheme.PNG)

![](img/character_device_driver.PNG)

Block devices allow users only to read/write blocks of data, and not a single byte. 
![](img/block_devices.PNG)


## Device files

![](img/device_files.PNG)

</br>

Device files are locaded under /dev path. Character devices  
start  have 'c' as their type, while block devices have 'b'.    

![](img/device_files_2.PNG)

## Device number

Major device number is the number of the device, while the minor  
device number represents the device instance.
![](img/device_number.PNG)

There can be multiple device instances in the same time. All the  
instances will have the same major number, but different minor number.  

![](img/device_number_3.PNG)

Device numbers can be viewed in /dev directory. In the example  
below, there are two instances of SDA block device.  
Their minor device numbers are different. 

![](img/device_number_2.PNG)

</br>

## Kernel registration APIs

![](img/kernel_registration_api.PNG)

![](img/kernel_registration_api_2.PNG)

![](img/kernel_registration_api_3.PNG)

</br>

## Allocating device numbers

![](img/alloc_dev_numbers.PNG)

![](img/alloc_dev_numbers_example.PNG)

![](img/alloc_dev_numbers_example_2.PNG)

</br>

## Device numbers represantation

![](img/device_number_represantation.PNG)

</br>

## CDEV structure

![](img/cdev.PNG)

cdev_add API is used to add a character device to the system.

![](img/cdev_add.PNG)

</br>

## VFS operations

![](img/vfs_operations.PNG)

</br>

## Creating device files

![](img/device_file.PNG)

![](img/udev.PNG)

![](img/device_file_2.PNG)

![](img/device_file_3.PNG)

![](img/device_create.PNG)

</br>

## Read Operation

![](img/read_operation.PNG)

![](img/read_operation_steps.PNG)

Copy data from and to user space in kernel space should be done by  specific API calls.  
![](img/copy_to_user.PNG)

![](img/copy_to_user_2.PNG)

![](img/copy_from_user_3.PNG)

</br>

## Error codes

![](img/error_codes.PNG)

</br>

## Write operation

![](img/write_operation.PNG)

![](img/write_operation_2.PNG)

## Using/Testing device

Character devices can be used from command line.

To write to the char device `echo` can be used:

``` bash
echo "content to write" > /dev/pcd
```

Another way of writing data to the char device is copying  
file into the device:

``` bash
cp FILE_PATH /dev/pcd
```

To read from the char device `cat` can be used:

``` bash
cat /dev/pcd
```

