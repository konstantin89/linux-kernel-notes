# Character device drivers

##

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

![](img/device_number_represantationn.PNG)
