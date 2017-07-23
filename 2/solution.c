#include <linux/init.h>
#include <linux/module.h>
#include "checker.h"

MODULE_LICENSE("GPL");

int init_module(void)
{
	call_me("Hello from my module!");
	return 0;
}

void cleanup_module(void)
{
	call_me("Hello from my module!");
}
