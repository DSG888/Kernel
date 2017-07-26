#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define array_size 5

static int my_sys = 0;

static int a = 0;
static int b = 0;
static int c[array_size] = {0};

module_param(a, int, 0);
module_param(b, int, 0);
module_param_array(c, int, NULL, 0);
//module_param(int_param, int, 0);

static ssize_t b_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	int var, i;
	my_sys = a+b;

	for (i = 0; i<5; ++i)
	{
		my_sys += c[i];  
	}
  
	var = my_sys;
	return sprintf(buf, "%d\n", var);
}
  
static ssize_t b_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	  int var, ret;
  
	  ret = kstrtoint(buf, 10, &var);
	  if (ret < 0)
		  return ret;
  

	  my_sys = var;
	  return count;
}
  
static struct kobj_attribute my_sys_attribute = __ATTR(my_sys, 0664, b_show, b_store);

static struct attribute *attrs[] = {
	  &my_sys_attribute.attr,
	  NULL,
};

static struct attribute_group attr_group = {
	 .attrs = attrs,
};
 
static struct kobject *example_kobj;
 
static int __init example_init(void)
{
	 int retval;

	 example_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
	 if (!example_kobj)
		 return -ENOMEM;

	 retval = sysfs_create_group(example_kobj, &attr_group);
	 if (retval)
		 kobject_put(example_kobj);

	 return retval;
}
 
static void __exit example_exit(void)
{
	kobject_put(example_kobj);
}
 
module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL");
