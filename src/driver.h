#ifndef _DRIVER_H
	#define _DRIVER_H
	
		#include <linux/init.h>           
		#include <linux/module.h>         
		#include <linux/device.h>         
		#include <linux/kernel.h>         
		#include <linux/fs.h>             
		#include <asm/uaccess.h>
	
			#define  DEVICE_NAME "tdriver"    
			#define  CLASS_NAME  "tdriver"        

			MODULE_LICENSE("GPL");            
			MODULE_AUTHOR("Io.D");    
			MODULE_DESCRIPTION("Template Driver Module");  
			MODULE_VERSION("0.1"); 
		
			struct drv_data_t
			{
				int    major_number;
				char   message[256];
				short  sizeof_message;
				int    count_usage; 
				struct class	* amm_class;	
				struct device	* amm_device;			
			}drv_data;
			
			static int     dev_open(struct inode *, struct file *);
			static int     dev_release(struct inode *, struct file *);
			static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
			static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
			
			static struct file_operations fops =
			{
			   .open = dev_open,
			   .read = dev_read,
			   .write = dev_write,
			   .release = dev_release,
			};
			
			static int __init drv_devchar_init(void);
			static void __exit drv_devchar_exit(void);
			static int dev_open(struct inode *inodep, struct file *filep);
			static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
			static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
			static int dev_release(struct inode *inodep, struct file *filep);
	
#endif
	
