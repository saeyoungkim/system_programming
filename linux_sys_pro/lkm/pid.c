#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

long pid = 0;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("write and read");
MODULE_AUTHOR("KIM");

ssize_t proc_write(struct file *file, const char __user *usr_buf, size_t count, loff_t *pos);

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.write = proc_write,
	.read = proc_read,
};

int proc_init(void)
{
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	return 0;
}

void proc_exit(void)
{
	remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_write(struct file *file, const char __user *usr_buf, size_t count, loff_t *pos)
{
	char *k_mem;

	k_mem = kmalloc(count, GFP_KERNEL);

	copy_from_user(k_mem, usr_buf, count);

	if(kstrtol(k_mem, 10, &pid) != 0) return -1;

	printk(KERN_INFO "%s\n", k_mem);

	kfree(k_mem);

	return count;
}

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
	char buf[BUFFER_SIZE];

	static int flag = 0;

	if(flag){
		flag = 0;
		return 0;
	}

	flag = 1;

	struct pid *vpid = find_vpid((int)pid);
	if(vpid == NULL) return -1;

	struct task_struct *p_task = pid_task(vpid, PIDTYPE_PID);

	int rv = sprintf(buf, "command = [%s] pid = [%ld] state = [%ld]\n", p_task->comm, pid, p_task->state);
	
	copy_to_user(usr_buf, buf, rv);

	return rv;
}

module_init(proc_init);
module_exit(proc_exit);
