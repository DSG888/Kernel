#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
//#include <linux/string.h>

MODULE_LICENSE("GPL");

static dev_t first;							// ID
static unsigned int count = 1;				// Счетчик устройства
static int my_major = 240, my_minor = 0;	// Старший и младший номера устройств
static struct cdev *my_cdev;				//
//static char str[256] = {'\0'};

static int N = 0;	// общее количество данных, записанных в устройство.
static int M = 0;	// общее количество открытий устройства на чтение или запись

#define MYDEV_NAME "myCharDev"		//	Отображаемое имя
#define KBUF_SIZE (size_t) ((10) * PAGE_SIZE)

static int mychrdev_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	
	//M++;
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;
	
	//printk(KERN_INFO "Opening device %s", MYDEV_NAME);
	counter++;
	//printk(KERN_INFO "Counter: %d:", counter);
	//printk(KERN_INFO "Module refcounter: %d", module_refcount(THIS_MODULE));

	return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file)
{
	//printk(KERN_INFO "Releaseing device %s", MYDEV_NAME);
	
	char *kbuf = file->private_data;
	//printk(KERN_INFO "Free buffer");
	
	if (kbuf)
		kfree(kbuf);
	kbuf = NULL;
	file->private_data = NULL;
	return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
//	char *kbuf = file->private_data;
	
//	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
//	*ppos += nbytes;

	M++;
	
	
	printk(KERN_INFO "%d %d\n", M,N);
	
	return 0;// nbytes;
}

static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	M++;
	char *kbuf = file->private_data;
	
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;
	

	N += nbytes;
	//printk(KERN_INFO "Write device %s nbytes = %d, ppos = %d", MYDEV_NAME, nbytes, (int)*ppos);
	return nbytes;
}

static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release
};


static int __init init_chardev(void)
{
	//printk(KERN_INFO "Hello user!");
	
	first = MKDEV(my_major, my_minor);	// Инициализация устройства (Создание ноды)
	register_chrdev_region(first, count, MYDEV_NAME);	// Регистрация региона (идентификаторов)
	
	my_cdev = cdev_alloc();				// Выделение памяти для структуры с атрибутами устройства
	
	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);
	
	return 0;
}

static void __exit cleanup_chardev(void)
{
	//printk(KERN_INFO "Leaving user!");

	if (my_cdev)
		cdev_del(my_cdev);
	unregister_chrdev_region(first, count);
}

module_init(init_chardev);
module_exit(cleanup_chardev);

