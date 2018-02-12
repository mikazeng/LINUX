#include<unistd.h>
#include<stdio.h>
#include<assert.h>

void main()
{
	pid_t pid = fork();
	assert(pid !=-1);
	if(pid == 0)
	{

		excvl("./my.sh",NULL);
	}

	wait(NULL);
	printf("main over");
}
