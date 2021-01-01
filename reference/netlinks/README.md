# Netlinks

## Links 

[Define new netlink protocol](https://www.linuxjournal.com/article/7356)

## Adding new netlink protocol

All netlink families are defined in "KERN_VER/include/uapi/linux/netlink.h" file.
In order to define a new protocod, you have to add a macro in netlink.h so
both user and kernel spaes will be able to access it.

``` C
#define NETLINK_SCSITRANSPORT	18
#define NETLINK_ECRYPTFS        19
#define NETLINK_RDMA            20
#define NETLINK_CRYPTO          21	
#define NETLINK_SMC             22	

#define NEW_TEST_NETLINK        23 // New netlink protocol

#define MAX_LINKS 32		
```
