#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define PROC_NAME "seconds"

MODULE_LICENSE("GPL");

ssize_t seconds_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

struct file_operations seconds_ops = {
 .owner = THIS_MODULE,
 .read = seconds_read,
};

int seconds_init(void){
 proc_create(PROC_NAME, 0666, NULL, &seconds_ops);
 return 0;
}

void seconds_exit(void) {
 remove_proc_entry(PROC_NAME, NULL);
}

ssize_t seconds_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
 static int flag = 0;
 unsigned long seconds; 
 if(flag) {
  flag = 0;
  return 0;
 }
 
 flag = 1;
 seconds = jiffies / HZ;
 return sprintf(usr_buf, "%ld\n", seconds);

}

module_init(seconds_init);
module_exit(seconds_exit);

