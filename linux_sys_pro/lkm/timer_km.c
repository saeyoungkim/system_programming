#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <asm/param.h>

MODULE_LICENSE("GPL");

int timer_init(void) {
 printk(KERN_INFO "jiffies: %lu\n, HZ: %d\n", jiffies, HZ);
 return 0;
}

void timer_exit(void) {
 printk(KERN_INFO "jiffies: %lu\n", jiffies);
}

module_init(timer_init)
module_exit(timer_exit)
