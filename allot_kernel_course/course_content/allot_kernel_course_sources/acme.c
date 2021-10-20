/* Dummy character device driver from Free Electrons
 * Referenced in http://free-electrons.com/training/drivers
 *
 * Copyright 2006, Free Electrons <http://free-electrons.com>
 * Modified by Ziv Erez, July 2010
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>

static void *acme_buf;
static int acme_bufsize=8192;
static int acme_buffer_filled = 0;

static int acme_count=1;
static dev_t acme_dev = MKDEV(92,0);

static struct cdev acme_cdev;

static ssize_t
acme_read(struct file *file, char __user *buf, size_t count, loff_t * ppos)
{
   int remaining_size, transfer_size;

   remaining_size = acme_buffer_filled - (int) (*ppos); // bytes left to transfer
   if (remaining_size == 0) { /* All read, returning 0 (End Of File) */
	  return 0;
   }

   /* Size of this transfer */
   transfer_size = min(remaining_size, (int) count);
   
   if (copy_to_user(buf /* to */, acme_buf + *ppos /* from */, transfer_size)) {
      return -EFAULT;
   } else { /* Increase the position in the open file */
      *ppos += transfer_size;
      return transfer_size;
   }
}

static ssize_t
acme_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
   int remaining_bytes;

   /* Number of bytes not written yet in the device buffer */
   remaining_bytes = acme_bufsize - (*ppos);
   
   if (count > remaining_bytes) {
	  /* Can't write beyond the end of the device buffer */
	  return -EIO;
   }

   if (copy_from_user(acme_buf + *ppos /* to */, buf /* from */, count)) {
      return -EFAULT;
   } else {
	  /* Increase the position in the open file */
      *ppos += count;
	  /* Increase the position in the device buffer */
	 acme_buffer_filled = count;
      return count;
   }
}


int acme_open(struct inode *inode, struct file *filp)
{
    /* now trim to 0 the length of the device if open was write-only */

  printk (KERN_ALERT "file flags: %x", filp->f_flags);

    if ( (filp->f_flags & O_APPEND)) 
	  printk (KERN_ALERT "file O_APPEND");
    if ( (filp->f_flags & O_CREAT)) 
	  printk (KERN_ALERT "file O_CREAT");
    if ( (filp->f_flags == O_RDONLY)) 
	  printk (KERN_ALERT "file O_RDONLY");
    if ( (filp->f_flags & O_WRONLY)) 
	  printk (KERN_ALERT "file O_WRONLY");

    return 0;          /* success */
}


static struct file_operations acme_fops =
{
	.owner = THIS_MODULE,
	.read = acme_read,
	.write = acme_write,
	.open = acme_open,
};

static int __init acme_init(void)
{
    int err;
    acme_buf = vmalloc (acme_bufsize); // ioremap (ACME_PHYS, acme_bufsize);

	if (!acme_buf) {
		err = -ENOMEM;
		goto err_exit;
	}

	if (register_chrdev_region(acme_dev, acme_count, "acme")) {
		err=-ENODEV;
		goto err_free_buf;
	}

    cdev_init(&acme_cdev, &acme_fops);

    if (cdev_add(&acme_cdev, acme_dev,
                 acme_count)) {
       err=-ENODEV;
       goto err_dev_unregister;
    }

    return 0;

    err_dev_unregister:
        unregister_chrdev_region(
           acme_dev, acme_count);
    err_free_buf:
        vfree (acme_buf); // iounmap(acme_buf);
    err_exit:
        return err;
}

static void __exit acme_exit(void)
{
 	cdev_del(&acme_cdev);
	unregister_chrdev_region(acme_dev,
                       acme_count);
	vfree (acme_buf); // iounmap(acme_buf);
}

module_init(acme_init);
module_exit(acme_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example character driver");
MODULE_AUTHOR("Free Electrons");


