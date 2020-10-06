#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gcd.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

int simple_init(void){
 printk(KERN_INFO "%ld\n", gcd(3300, 24)); 
 return 0;
}

void simple_exit(void){
 printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(simple_init);
module_exit(simple_exit);
