#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>

static int start = 0;

module_param(start, int, 0);

struct CollatzNode {
	int val;
	struct list_head next;
};

struct list_head* collatzSequence(int start){
	struct list_head* collatz_list;	
	collatz_list = kmalloc(sizeof(struct list_head), GFP_KERNEL);	
	INIT_LIST_HEAD(collatz_list);

	while(start >= 1){
		struct CollatzNode* node;
		node = kmalloc(sizeof(struct CollatzNode), GFP_KERNEL);
		node->val = start;
		list_add_tail(&node->next, collatz_list);
	
		if(start == 1) break;
	
		if((start & 1) == 0){
			start = start >> 1;
		} else {
			start = 3 * start + 1;
		}
	}	

	return collatz_list;
}

int proc_init(void) {
	struct list_head* collatz_list;
	collatz_list = collatzSequence(start);

	struct CollatzNode *ptr, *next;

	list_for_each_entry_safe(ptr, next, collatz_list, next) {
		printk("%d", ptr->val);
		list_del(&ptr->next);
		kfree(ptr);	
	}	

	return 0;
}

void proc_exit(void) {
	return ;
}

module_init(proc_init);
module_exit(proc_exit);

