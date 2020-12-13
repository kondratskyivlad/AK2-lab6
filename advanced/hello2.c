// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>

#include "hello1.h"

extern int print_hello(uint);

static uint repeats = 1;
module_param(repeats, uint, 0660);
MODULE_PARM_DESC(repeats, "The number of times the greeting is repeated. Valid values are 0 - 10, unwanted values are 5 - 10.\n");

static int __init hello2_init(void)
{
	return print_hello(repeats);
}

static void __exit hello2_exit(void)
{
	/* Do nothing here right now */
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_AUTHOR("Vladislav Kondratsky");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training. Module 2.");
MODULE_LICENSE("Dual BSD/GPL");
