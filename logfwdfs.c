#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#define LOGFWDFS_OK 0

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cornelius Buschka <cbuschka@gmail.com>");
MODULE_DESCRIPTION("Log forwarding filesystem.");

// https://www.kernel.org/doc/html/latest/filesystems/vfs.html
static struct file_system_type logfwdfs_fs_type = {
    "logfwdfs",
    0,
    NULL
    };

static int __init logfwdfs_init(void)
{
    int rc;

    printk(KERN_INFO "logfwdfs: This is logfwdfs.\n");

    if ((rc = register_filesystem(&logfwdfs_fs_type)) != 0) {
        printk(KERN_ERR "logfwdfs: Registering logfwdfs failed.\n");
        return rc;
    } else {
        printk(KERN_INFO "logfwdfs: logfwdfs registered.\n");
    }

    return LOGFWDFS_OK;
}

static void __exit logfwdfs_cleanup(void)
{
    unregister_filesystem(&logfwdfs_fs_type);

    printk(KERN_INFO "logfwdfs: Cleaning up module.\n");
}

module_init(logfwdfs_init);
module_exit(logfwdfs_cleanup);
