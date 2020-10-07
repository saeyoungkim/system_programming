#include <linux/list.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/gcd.h>
#include <asm/uaccess.h>

#define PROC_NAME "clist"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("clist");
MODULE_AUTHOR("KIM");

struct color {
	int red;
	int blue;
	int green;
	struct list_head list;
};

void add_color(int r, int b, int g, struct list_head* color_list){
	struct color* c;

	c = kmalloc(sizeof(struct color), GFP_KERNEL);

	c->red = r;
	c->blue = b;
	c->green = g;

	list_add_tail(&c->list, color_list);
}

int proc_init(void) {
        struct color color_list;
	INIT_LIST_HEAD(&color_list.list);

	int r = 0, b = 16, g = 129;

	for(r = 0; r < 4; ++r){
		for(b = 16; b < 18; ++b){
			for(g = 129; g < 131; ++g){
				add_color(r,b,g,&color_list.list);
			}	
		}
	}
	struct color *ptr, *next;

	list_for_each_entry_safe(ptr, next, &color_list.list, list) {
		printk("red = [%d] blue = [%d] green = [%d]", ptr->red, ptr->blue, ptr->green);
		list_del(&ptr->list);
		kfree(ptr);	
	}	
	return 0;
} 
 
void proc_exit(void) {
	return ;
}

module_init(proc_init);
module_exit(proc_exit);
