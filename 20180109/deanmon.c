
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>

void main()
{
	pid_t pid = fork();
	if(pid !=0)
	{

		printf("%d",getdtablesize());
		exit(0);
	}
	setsid();
	//chdir("/");
	umask(0);
	close(0);
	close(1);
	close(2);
	int fd = open("time.txt",O_RDWR|O_CREAT|O_APPEND,0666); 
	printf("%d\n",fd);
	assert(fd != -1);
	while(1)
	{
		time_t t ;
		time(&t);	
		write(fd,asctime(localtime(&t)),strlen(asctime(localtime(&t))));
		puts(asctime(localtime(&t)));
		sleep(1);
	}
	exit(1);
}
