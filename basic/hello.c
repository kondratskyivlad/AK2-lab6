// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/slab.h>

static uint repeats = 1;
module_param(repeats, uint, 0660);
MODULE_PARM_DESC(repeats, "The number of times the greeting is repeated. Valid values are 0 - 10, unwanted values are 5 - 10.\n");

struct data {
	ktime_t time;
	struct list_head list;
};

struct list_head *iter, *iter_safe;
struct data *item;
LIST_HEAD(list);

static int __init hello_init(void)
{
	int i;

	pr_alert("repeats: %d\n", repeats);
	if (repeats >= 0 && repeats <= 10) {
		if (repeats == 0)
			pr_warn("Small value!\n");
		else if (repeats > 5 && repeats <= 10)
			pr_warn("Big value!\n");

		for (i = 0; i < repeats; i++) {
			item = kmalloc(sizeof(*item), GFP_KERNEL);
			item->time = ktime_get_ns();
			list_add_tail(&(item->list), &list);
			pr_alert("Hello, world!\n");
		}
	} else {
		pr_err("The parameter value is greater than 10.\n");
		return -EINVAL;
	}
	return 0;
}

static void __exit hello_exit(void)
{
	list_for_each_safe(iter, iter_safe, &list) {
		item = list_entry(iter, struct data, list);
		pr_info("%lu\n", (unsigned long) item->time);
		list_del(iter);
		kfree(item);
	}
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Vladislav Kondratsky");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
