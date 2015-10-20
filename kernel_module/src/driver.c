#include "driver.h"

	static int __init drv_devchar_init(void)
	{
		drv_data.count_usage=0;
	
		if ((drv_data.major_number = register_chrdev(0, DEVICE_NAME, &fops))<0)
			return drv_data.major_number;
   
		drv_data.amm_class = class_create(THIS_MODULE, CLASS_NAME);
		if (IS_ERR(drv_data.amm_class))
		{               
			unregister_chrdev(drv_data.major_number, DEVICE_NAME);
			printk(KERN_INFO "Driver: Error\n");		
			return PTR_ERR(drv_data.amm_class);				
		}

		drv_data.amm_device = device_create(drv_data.amm_class, NULL, MKDEV(drv_data.major_number, 0), NULL, DEVICE_NAME);
		if (IS_ERR(drv_data.amm_device))
		{               
			class_destroy(drv_data.amm_class);         
			unregister_chrdev(drv_data.major_number, DEVICE_NAME);
			printk(KERN_INFO "Driver: Error\n");
			return PTR_ERR( drv_data.amm_device);
		}
		printk(KERN_INFO "Driver: Hello\n");
		return 0;
	}
	
	static void __exit drv_devchar_exit(void)
	{
		device_destroy(drv_data.amm_class, MKDEV(drv_data.major_number, 0));   
		class_unregister(drv_data.amm_class);                         
		class_destroy(drv_data.amm_class);                            
		unregister_chrdev(drv_data.major_number, DEVICE_NAME);    
		printk(KERN_INFO "Driver: Bye\n");		
	}

	static int dev_open(struct inode *inodep, struct file *filep)
	{
	   drv_data.count_usage++;
	   printk(KERN_INFO "Driver: Opened %d times\n", drv_data.count_usage);
	   return 0;
	}

	static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
	{
		int error_count = 0;
		
		error_count = copy_to_user(buffer, drv_data.message, drv_data.sizeof_message);

		if (error_count==0)            
			return (drv_data.sizeof_message=0);  
		else 
			return -EFAULT;              
	}

	static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
	{
		sprintf(drv_data.message, "%s", buffer);   
		drv_data.sizeof_message = strlen(drv_data.message); 
		printk(KERN_INFO "Driver: Received %zu characters from the user\n", len);
		return len;
	}

	static int dev_release(struct inode *inodep, struct file *filep)
	{
		return 0;
	}


	module_init(drv_devchar_init);
	module_exit(drv_devchar_exit);