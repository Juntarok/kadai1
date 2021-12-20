//SPDX-License-Identifier:GPL-3.0
/* *Copyright(c)2021 Ryuichi Ueda.Juntaro Kshima. Allrights reserved. */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda & Juntaro Kashima");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file*filp, const char* buf, size_t count, loff_t* pos)
{
	char c, n, number;
	if(copy_from_user(&c, buf, sizeof(char)))
		return -EFAULT;

	if(c =='1'){
		for(n = 0;n <= 30;++n){
			if(number == 0){
				gpio_base[7] = 1 << 25;
				msleep(100);
				number = number + 1;
			}else if(number == 1){
				gpio_base[10] = 1 << 25;
				msleep(100);
				number = 0;
			}
		}
	}else if(c == '2'){
		for(n = 0;n <= 20;++n){
			if(number == 0){
				gpio_base[7] = 1 << 25;
				msleep(200);
				number = number + 1;
			}else if(number ==1){
				gpio_base[10] = 1 << 25;
				msleep(200);
				number = 0;
			}
		}
	}else if(c == '3'){
		for(n = 0;n <= 20;++n){
			if(number == 0){
				gpio_base[7] = 1 << 25;
				msleep(300);
				number = number + 1;
			}else if(number == 1){
				gpio_base[10] = 1 << 25;
				msleep(300);
				number = 0;
			}
		}
	}else if(c == '0'){
		gpio_base[10] = 1 << 25;
	}
	return 1;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
};

static int __init init_mod(void)
{
	int retval;
	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed \n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk("KERN_ERR cdev_add failed major:%d, minor:%d", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed. ");
		return PTR_ERR(cls);
	}

	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	const u32 led = 25;
	const u32 index = led/10;
	const u32 shift = (led%10)*3;
	const u32 mask = ~(0x7<<shift);
	gpio_base[index] = (gpio_base[index] & mask ) | (0x1 << shift);

	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));	
}

module_init(init_mod);
module_exit(cleanup_mod);

