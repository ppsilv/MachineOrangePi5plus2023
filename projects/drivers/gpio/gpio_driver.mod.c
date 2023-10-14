#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x667bfb48, "module_layout" },
	{ 0x94b7db5d, "cdev_del" },
	{ 0xe7399883, "gpiod_direction_input" },
	{ 0xfe990052, "gpio_free" },
	{ 0x3b398f63, "gpiod_direction_output_raw" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x17e6ec06, "device_destroy" },
	{ 0xeeeebfa8, "cdev_add" },
	{ 0xdfe0a290, "cdev_init" },
	{ 0x383419fd, "class_destroy" },
	{ 0x6ddd9da3, "device_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3ecfccd6, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x4bc431e9, "gpiod_get_raw_value" },
	{ 0x9f49dcc4, "__stack_chk_fail" },
	{ 0xac90c8f6, "gpiod_set_raw_value" },
	{ 0x543dc745, "gpio_to_desc" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9CFB0B07BBCFF7BB9D065A3");
