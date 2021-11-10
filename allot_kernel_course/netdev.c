// 
//
// After the module is loaded, check `ifconfig -a` and make sure that the Ethernet device is persent there.
// You can identify the device by its MAC address.
//
// sudo insmod netdev.ko
// sudo rmmod netdev
//

#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/init.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>

static struct net_device *dev;

static int my_open(struct net_device *dev)
{
	pr_info("Hit: my_open(%s)\n", dev->name);
	return 0;
}

static int my_close(struct net_device *dev)
{
	pr_info("Hit: my_close(%s)\n", dev->name);
	return 0;
}

static int my_do_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
  printk("Got IOCTL with command [%d]\n", cmd);
  
  return 0;
} 

static int stub_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	consume_skb(skb);
	return 0;
}

static struct net_device_ops ndo = {
	.ndo_open = my_open,
	.ndo_stop = my_close,
	.ndo_start_xmit = stub_start_xmit,
  .ndo_do_ioctl = my_do_ioctl,
};

static int __init my_init(void)
{
  int j;
  
	pr_info("Loading stub network module:....");
  
  dev = alloc_etherdev(0);
  dev->netdev_ops = &ndo;
  
 	for (j = 0; j < ETH_ALEN; ++j) 
  {
    // Set mock MAC address to the device.
		dev->dev_addr[j] = (char)j;
	}
 
	if (register_netdev(dev)) 
  {
		pr_info(" Failed to register\n");
		free_netdev(dev);
		return -1;
	}
	pr_info("Succeeded in loading %s!\n\n", dev_name(&dev->dev));
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Unloading stub network module\n\n");
 
	unregister_netdev(dev);
	free_netdev(dev);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");