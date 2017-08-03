#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x21fac097, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xf080f8e0, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x5c5a0946, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xe2b4edad, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x6238cb4f, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x790f2290, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xb7174bf0, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xecd8a25e, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x71ecf5d6, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0xd8e484f0, __VMLINUX_SYMBOL_STR(register_chrdev_region) },
	{ 0xb5419b40, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xc671e369, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x88db9f48, __VMLINUX_SYMBOL_STR(__check_object_size) },
	{ 0x44a4a4c4, __VMLINUX_SYMBOL_STR(module_refcount) },
	{ 0x9e617f71, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xbab4d16f, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

