#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>

#define PATH "/usr/bin/killall"

static char *argv[] = { PATH, "xscreensaver", 0 };
static char *envp[] = { 0 };


static int __init mymodule_init(void)
{
  int rc;

  printk ("My module worked!\n");

  rc = call_usermodehelper(PATH, argv, envp, 1);
  printk ("rc=%d\n", rc);
  
  return 0;
}

static void __exit mymodule_exit(void)
{
  printk ("Unloading my module.\n");
  return;
}

module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
