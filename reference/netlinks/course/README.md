# Linux kenel netlinks

## Links

[Course source code](https://github.com/konstantin89/UdemyCourseOnNetlink)

---
</br>

## Message Structure

The nlmsghdr is defined in [netlink.h](https://elixir.bootlin.com/linux/latest/source/include/linux/netlink.h).  

```
struct nlmsghdr {
    __u32        nlmsg_len;    /* Length of message including header */
    __u16        nlmsg_type;   /* Message content */
    __u16        nlmsg_flags;  /* Additional flags */
    __u32        nlmsg_seq;    /* Sequence number */
    __u32        nlmsg_pid;    /* Sending process port ID */
};
```


### nlmsg_type

Can have the following values: 
```
#define NLMSG_NOOP        0x1    /* Nothing */
#define NLMSG_ERROR       0x2    /* Error */
#define NLMSG_DONE        0x3    /* End of a dump */
#define NLMSG_OVERRUN     0x4    /* Data lost */
```

![](img/message_types.PNG)

### nlmsg_flags

All flags can be found in `netlink.h`.  
Here are some commonly used:  

![](img/message_flags.PNG)


### nlmsg_seq

![](img/message_seq_num.PNG)

### nlmsg_pid

![](img/message_pid.PNG)


---
</br>


## Netlink Protocol ID

Unique protocol number is assigned to each Linux kernel  
subsustem that is capable of using the Netlinks.  

The list of all assigned IDs are defined in [netlink.h](https://elixir.bootlin.com/linux/latest/source/include/uapi/linux/netlink.h#L44) header.  


---
</br>


## Socket Buffers (skbuff)

Netlinks configuration struct as defined in [netlink.h](https://elixir.bootlin.com/linux/latest/source/include/uapi/linux/netlink.h#L44) has the following structure:  
```
struct netlink_kernel_cfg {
    unsigned int groups;
    unsigned int flags;
    void (*input)(struct sk_buff *skb);
    struct mutex *cb_mutex;
    int (*bind)(struct net *net, int group);
    void (*unbind)(struct net *net, int group);
    bool (*compare)(struct net *net, struct sock *sk);
```

Note that input data callback has the following signature:  
```
void (*input)(struct sk_buff *skb)
```

`sk_buff` is structure that represents a socket buffer.  
It is defined in [skbuff.h](https://elixir.bootlin.com/linux/latest/source/include/linux/skbuff.h) header file.  

Two important fields are `data` and `len`.  
Usage example:   
```
struct sk_buff *skb_in;
unsigned char* data_pointer = skb_in->data;
int message_length = skb_in->len;
```

For full code example please use [this](./../../../code_examples/netlink/netlink_course_examples/Greetings_example/kernel/greetNetlinkLKM.c) file.


---
</br>