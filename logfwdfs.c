#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

#define LOGFWDFS_OK 0

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cbuschka");
MODULE_DESCRIPTION("A Simple Hello World module");

static int __init logfwdfs_init(void)
{
    printk(KERN_INFO "This is logfwdfs.\n");
    return LOGFWDFS_OK;
}

static void __exit logfwdfs_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(logfwdfs_init);
module_exit(logfwdfs_cleanup);
