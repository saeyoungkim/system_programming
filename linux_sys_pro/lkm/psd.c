#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#define BUFFER_SIZE 128
#define PROC_NAME "psd"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ps");
MODULE_AUTHOR("KIM");

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
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

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
	static int flag  = 0;

	if(flag){
		flag = 0;
		return 0;
	}

	flag = 1;

	struct task_struct *task;
	struct list_head *list;

	list_for_each(list, init_task.children){
		task = list_entry(list, struct task_struct, sibling);

		printk("command = [%s] pid = [%d] state = [%d]", task->comm, task->pid, task->state);
	}
	return 0;
}

module_init(proc_init);
module_exit(proc_exit);
