#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#define LOGFWDFS_OK 0

#define LOGFWDFS_MAGIC 0x21324352

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cornelius Buschka <cbuschka@gmail.com>");
MODULE_DESCRIPTION("Log forwarding filesystem.");

// https://www.kernel.org/doc/html/latest/filesystems/vfs.html
static struct file_system_type logfwdfs_fs_type = {
    .owner = THIS_MODULE,
    .name = "logfwdfs",
    .mount = logfwdfs_mount,
    .kill_sb = kill_block_super,
    .fs_flags = 0
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

static struct dentry *logfwdfs_mount(struct file_system_type *type, int flags,
                                      char const *dev, void *data)
  {
      struct dentry *const entry = mount_bdev(type, flags, dev, data, aufs_fill_sb);
      if (IS_ERR(entry))
          pr_err("logfwdfs: mounting failed\n");
      else
          pr_debug("logfwdfs: mounted\n");
      return entry;
  }

static int logfwdfs_fill_sb(struct super_block *sb, void *data, int silent)
  {
      struct inode *root = NULL;

      sb->s_magic = LOGFWDFS_MAGIC_NUMBER;
      sb->s_op = &aufs_super_ops;

      root = new_inode(sb);
      if (!root)
      {
           pr_err("inode allocation failed\n");
           return -ENOMEM;
      }

      root->i_ino = 0;
      root->i_sb = sb;
      root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
      inode_init_owner(root, NULL, S_IFDIR);

      sb->s_root = d_make_root(root);
      if (!sb->s_root)
      {
          pr_err("root creation failed\n");
          return -ENOMEM;
      }

     return 0;
 }

static void logfwdfs_put_super(struct super_block *sb)
  {
      pr_debug("logfwdfs super block destroyed\n");
  }

  static struct super_operations const logfwdfs_super_ops = {
      .put_super = logfwdfs_put_super,
  };

module_init(logfwdfs_init);
module_exit(logfwdfs_cleanup);
