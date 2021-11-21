#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/netfilter_arp.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
static unsigned int arp_in_hook (unsigned int hooknum,
#else
static unsigned int arp_in_hook (struct nf_hook_ops *hops,
#endif
                                 struct sk_buff *skb,
                                 const struct net_device *in,
                                 const struct net_device *out,
				 int (*okfn)(struct sk_buff *))
{
  char *mac_head;

  mac_head = skb_mac_header (skb);
  printk ("%02x:%02x:%02x:%02x:%02x:%02x\n",mac_head[6]&0xff,mac_head[7]&0xff,mac_head[8]&0xff,mac_head[9]&0xff,mac_head[10]&0xff,mac_head[11]&0xff);
  return NF_ACCEPT;
}

static struct nf_hook_ops tr_hook_ops = {
  .owner = THIS_MODULE,
  .hook = arp_in_hook,
  .pf = NFPROTO_ARP,
  .hooknum = NF_ARP_IN,
  .priority = INT_MIN,
};
static int __init net_init(void)
{
  int err;

  err = nf_register_hook (&tr_hook_ops);

  return err;
}

static void __exit net_exit (void)
{
  nf_unregister_hook (&tr_hook_ops);
  return;
}

module_init(net_init);
module_exit(net_exit);
MODULE_LICENSE ("GPL");
MODULE_VERSION ("0.1");
