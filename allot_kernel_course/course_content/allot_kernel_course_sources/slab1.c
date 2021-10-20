#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/../mm/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("My name");
MODULE_DESCRIPTION("This module does nothing");

static char *whom = "world";
module_param(whom, charp, 0);

static int objsize = 1000;
module_param(objsize, int, 0755);



static struct kmem_cache* my_cachep;

static void init_my_cache( void )
{

   my_cachep = kmem_cache_create( 
                  "my_cache",            /* Name */
                  objsize,               /* Object Size */
                  0,                     /* Alignment */
                  SLAB_HWCACHE_ALIGN,    /* Flags */
                  NULL);          	/* Constructor */

  if (my_cachep==NULL)
	printk (KERN_ALERT "kmem_cache_create failed!");   
  else
  {
  	printk(KERN_ALERT  "Cache name is %s\n", my_cachep->object_size ); // kmem_cache_name( my_cachep ) );
	printk(KERN_ALERT  "Cache object size is %d\n", kmem_cache_size( my_cachep ) );
  }

  return;
}


int slab_test( void )
{
  void *object;

  object = kmem_cache_alloc( my_cachep, GFP_KERNEL );

  if (object) {

    kmem_cache_free( my_cachep, object );

  }
  else
	printk(KERN_ALERT "Object allocated");

  return 0;
}

static int __init hello_init(void)
{
    init_my_cache();

    slab_test();

    return 0;
}

static void __exit hello_exit(void)
{
	kmem_cache_destroy( my_cachep );

	printk(KERN_ALERT "Goodbye, %s!\n", whom);
}

module_init(hello_init);
module_exit(hello_exit);

