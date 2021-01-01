#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PAYLOAD 1024 /* maximum payload size*/

struct sockaddr_nl src_addr;
struct sockaddr_nl dest_addr;

struct nlmsghdr *nlh = NULL;
struct iovec iov;
struct msghdr msg;


int main()
{

    int sock_fd;

    sock_fd = socket(PF_NETLINK, SOCK_RAW, NEW_TEST_NETLINK);

    if(sock_fd < 0)
    {
        printf("Error - Failed to crete socket\n");
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); /* self pid */

    int bindRetVal = bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

    if (bindRetVal < 0)
    {
        printf("Error - Failed to bind socket\n");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; /* For Linux Kernel */
    dest_addr.nl_groups = 0; /* unicast */

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));

    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));

    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), "Hello");

    // iov = input/output vector
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;

    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    printf("Sending message to kernel\n");
    ssize_t sentBytes = sendmsg(sock_fd,&msg,0);

    if(sentBytes < 0)
    {
        printf("sendmsg failed to send data to kernel with errno [%d] \n", errno);
    }

    printf("Sent [%d] bytes to kernel\n", sentBytes);


    printf("Waiting for message from kernel\n");

    /* Read message from kernel */
    recvmsg(sock_fd, &msg, 0);
    printf("Received message payload: %s\n", (char *)NLMSG_DATA(nlh));
    close(sock_fd);

    free(nlh);

    return 0;
}