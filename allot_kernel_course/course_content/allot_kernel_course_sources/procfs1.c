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
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");

#define procfs_name "helloworld"

struct timespec curr_tm;

/**
 * This structure hold information about the /proc file
 *
 */
struct proc_dir_entry *Our_Proc_File;

/* The data to return */

char data[] = "Hello world!\n";

/* Put data into the proc fs file */

ssize_t procfile_read (struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	int rc, ret = 0, cnt;

	if (*ppos > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else if (data[0]) {
		/* fill the buffer, return the buffer size */
		cnt = sizeof(data);
		if (count < cnt)
			cnt = count;
		rc = copy_to_user(buffer, data, cnt);
		*ppos += cnt;
		ret= cnt;
	}

	return ret;
}

/* File operations structure */

static const struct file_operations proc_file_fops = {
 .owner = THIS_MODULE,
 .read  = procfile_read,
};

/* Init function */

int init_module()
{
	Our_Proc_File = proc_create(procfs_name, 0644, NULL, &proc_file_fops);  // New in Kernel 3.10
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(procfs_name, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       procfs_name);
		return -ENOMEM;
	}

	getnstimeofday(&curr_tm);
	//	printk(KERN_INFO "/proc/%s created at %2d\n", procfs_name, (int)(curr_time.tv_sec) );

	printk(KERN_INFO "/proc/%s created at: %.2lu:%.2lu:%.2lu:%.6lu \n", procfs_name,
                   (curr_tm.tv_sec / 3600) % (24), (curr_tm.tv_sec / 60) % (60), 
                   (curr_tm.tv_sec % 60), (curr_tm.tv_nsec / 1000) );
	
	return 0;	/* everything is ok */
}

void cleanup_module()
{
	remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}
