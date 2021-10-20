/*
 *  procfs1.c -  create a "file" in /proc
 *
 *  Source: http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html#AEN708
 *  Updated for Kernel 3.10.1 by Ziv Erez (zive@dualtech.co.il) 
 */

#include <linux/module.h>	/* Specifically, a module */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */
#include <linux/uaccess.h>	/* For copy_to_user */
#include <linux/ktime.h>    	/* For ktime */

MODULE_LICENSE("GPL");

#define procfs_name "timeofday"

static struct timeval curr_time;

/**
 * This structure hold information about the /proc file
 *
 */
struct proc_dir_entry *Our_Proc_File;

/* Put data into the proc fs file. */ 

ssize_t procfile_read (struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	int ret, rc;
	char data[64];
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);

	BUG_ON(1);

	if (*ppos > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
    		curr_time = ktime_to_timeval(ktime_get());
		ret = snprintf(data, 64, "%2d.%4d\n", (int)curr_time.tv_sec, (int)curr_time.tv_usec);

		if (count < ret)
			ret = count;
		rc = copy_to_user(buffer, data, ret);
		*ppos += ret;
	}

	return ret;
}

/* File operations structure */

static const struct file_operations proc_file_fops = {
 .owner = THIS_MODULE,
 .read  = procfile_read,
};

int init_module()
{
	Our_Proc_File = proc_create(procfs_name, 0644, NULL, &proc_file_fops);  // New in Kernel 3.10
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(procfs_name, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       procfs_name);
		return -ENOMEM;
	}

	printk(KERN_INFO "/proc/%s created\n", procfs_name);	
	return 0;	/* everything is ok */
}

void cleanup_module()
{
	remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}
