#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/interrupt.h>/*for tasklets API*/

static int __init my_init(void){
	printk(KERN_INFO,"my_init\n");
	return 0;
}

void my_exit(void){
	printk(KERN_INFO,"my_exit\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Hyun Beak <koungku93@gmail.com>");
MODULE_LICENSE("GPL");