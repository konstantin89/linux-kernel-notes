#ifndef __NL_COMMON__
#define __NL_COMMON__

#include <linux/netlink.h>

/* maximum payload size in Bytes exchanged between kernel and userspace
 * in either directions*/
#define MAX_PAYLOAD 1024

/*User defined NL MSG TYPES, should be > 16 */
#define NLMSG_GREET     20

/* user define netlink protocol.
 * It should match with Netlink Socket protocol opened in kernel space.*/

/* Define a New Netlink protocol ID
 * In file linux/netlink.h, you can see in line no [8-33]
 * lists the reserved IDs used for Netlink protocols already implemented
 * in Linux. We can use upto max 31th protocol number for Netlink. Let
 * us just pick the unused one - 31 below */

#define NETLINK_TEST_PROTOCOL   31

static inline char *
netlink_get_msg_type(__u16 nlmsg_type){

    switch(nlmsg_type){
        case NLMSG_NOOP:
            return "NLMSG_NOOP";
        case NLMSG_ERROR:
            return "NLMSG_ERROR";
        case NLMSG_DONE:
            return "NLMSG_DONE";
        case NLMSG_OVERRUN:
            return "NLMSG_OVERRUN";
        case NLMSG_GREET:
            return "NLMSG_GREET";
        default:
            return "NLMSG_UNKNOWN";
    }
}

static inline void
nlmsg_dump(struct nlmsghdr *nlh){
#ifdef __KERNEL__
    printk(KERN_INFO "Dumping Netlink Msgs Hdr");
#else
    printf("Dumping Netlink Msgs Hdr");
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Type = %s", 
        netlink_get_msg_type(nlh->nlmsg_type));
#else
    printf("  Netlink Msg Type = %s",
        netlink_get_msg_type(nlh->nlmsg_type));
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg len  = %d", nlh->nlmsg_len);
#else
    printf("  Netlink Msg len  = %d", nlh->nlmsg_len);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg flags  = %d", nlh->nlmsg_flags);
#else
    printf("  Netlink Msg flags  = %d", nlh->nlmsg_flags);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
#else
    printf("  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
#endif
#ifdef __KERNEL__
    printk(KERN_INFO "  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#else
    printf("  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#endif
}

#endif /* __NL_COMMON__ */
