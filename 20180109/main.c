#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//deamon

//每次运行的时候都新建一个组，这个程序都是这个组的组长进程
//包括其fork出来的子进程

void main()
{
	fork();
	long t = time(NULL);

	printf("pid = %d , sid = %d ",getpid(),getsid(0));
	printf("pgid = %d\n",getpgrp());
	return;
}


