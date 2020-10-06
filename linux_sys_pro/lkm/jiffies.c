#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(PROC_NAME);
MODULE_AUTHOR("KIM");

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count, loff_t *pos);

struct file_operations proc_ops = {
 .owner = THIS_MODULE,
 .read = proc_read
};

int proc_init(void) {
 proc_create(PROC_NAME, 0666, NULL, &proc_ops);
 return 0;
}

void proc_exit(void) {
 remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count, loff_t *pos)
{
 static int flag = 0;
 int result = 0;

 if(flag) {
  flag = 0;
  return 0;
 }

 flag = 1;

 result = sprintf(user_buf, "%ld\n", jiffies);

 return result;
}

module_init(proc_init);
module_exit(proc_exit);
