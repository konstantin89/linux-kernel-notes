// @brief: Network hook on ARP traffic

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_arp.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

static struct nf_hook_ops *nfho = NULL;

static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
  printk("ARP_IN hook function called \n");
  
  char mac_head = skb_mac_header(skb);
  
  // Work with MAC header by accessing mac_head.
  
   return NF_ACCEPT; // Continue packet processing.
}

static int __init LKM_init(void)
{
  int err = 0;
  
  printk("Netfilter hook module init called \n");
  
  dev = NULL;
  
  nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
 
  if(NULL == nfho)
  {
    printk("Failed to alocate nf_hook_ops structure! \n");
    return -1;
  }
    
    /* Initialize netfilter hook */
    nfho->hook     = (nf_hookfn*)hfunc;  /* hook function */
    nfho->hooknum     = NF_ARP_IN;       /* received packets */
    nfho->pf     = PF_INET;              /* ARP protocol */
    nfho->priority     = 1;              /* priority */
    nfho->dev = dev;
 
    err = nf_register_net_hook(&init_net, nfho);
    
    if(err)
    {
        printk("Failed to register hook! Error: [%d] \n", err);
        return -1;
    }
 
  return 0;
}

static void __exit LKM_exit(void)
{
    printk("Netfilter hook module exit called \n");
  
    nf_unregister_net_hook(&init_net, nfho);
    kfree(nfho);
}

module_init(LKM_init);
module_exit(LKM_exit);