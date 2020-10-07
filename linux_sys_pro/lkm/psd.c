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

void dfs(struct task_struct *task);
static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
};

int proc_init(void)
{
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	dfs(&init_task);
	return 0;
}

void proc_exit(void)
{
	remove_proc_entry(PROC_NAME, NULL);
}

void dfs(struct task_struct *task)
{
	struct task_struct *next_task;
	struct list_head *list;

	list_for_each(list, &(task->children)){
		next_task = list_entry(list, struct task_struct, sibling);

		printk("command = [%s] pid = [%d] state = [%d]", next_task->comm, next_task->pid, next_task->state);
		dfs(next_task);		
	}
	return 0;
}

module_init(proc_init);
module_exit(proc_exit);
