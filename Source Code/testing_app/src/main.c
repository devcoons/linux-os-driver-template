#include <stdio.h>
#include <fcntl.h>


	int main()
	{
		char buf[200];
		int fd = -1;
	
		printf("Opening device /dev/tdevice\n");
		if ((fd = open("/dev/tdriver", O_RDWR)) < 0) {
			perror("open");
			return -1;
		}
		printf("Writing HELLO to device\n");
			write(fd,"HELLO",6,NULL);
		
		printf("Reading From Device\n");
			read(fd,buf,6,NULL);
			printf("%s\n",buf);
			
		printf("Writing 0123456789 to device\n");
			write(fd,"0123456789",10,NULL);
			
		printf("Reading From Device\n");
			read(fd,buf,10,NULL);
			printf("%s\n",buf);	
	
		printf("Closing device /dev/tdevice\n");
		close(fd);

	return 0;

}
