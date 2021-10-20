#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
 
MODULE_LICENSE("GPL");
 
static struct timer_list my_timer;
 
#if (LINUX_VERSION_CODE  >= KERNEL_VERSION(4,15,0))
 void my_timer_callback( struct timer_list *t )
#else
 void my_timer_callback( unsigned long data )
#endif
{
  printk( "my_timer_callback called (%ld).\n", jiffies );
}
 
int init_module( void )
{
  int ret;
 
  printk("Timer module installing\n");
 
  // my_timer.function, my_timer.data
#if (LINUX_VERSION_CODE  >= KERNEL_VERSION(4,15,0))
  timer_setup( &my_timer, my_timer_callback, 0 ); // From kernel 4.15
#else
  setup_timer( &my_timer, my_timer_callback, 0 ); 
#endif
 
  printk( "Starting timer to fire in 200ms (%ld)\n", jiffies );
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(200) );
  if (ret) printk("Error in mod_timer\n");
 
  return 0;
}
 
void cleanup_module( void )
{
  int ret;
 
  ret = del_timer( &my_timer );
  if (ret) printk("The timer is still in use...\n");
 
  printk("Timer module uninstalling\n");
 
  return;
}
