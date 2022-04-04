#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	char *name="FIFO1.fifo";
	char string[3];
	int fd;
	if((fd=open(name,O_RDONLY))<0) {
		printf("Error: Can't open FIFO for reading.\n");
	}
	
	read(fd,string,3);
	printf("Read from FIFO: %s\n",string);
	close(fd);
	
	unlink(name);
}
