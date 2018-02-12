#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<assert.h>
#include<string.h>
#include<sys/types.h>
union semun
{
	int val;
};
void main()
{
	int shmid=shmget((key_t)666,256,IPC_CREAT|0666); 
	assert(shmid != -1);
	printf("%d",shmid);
	char *s = shmat(shmid,NULL,0);
	assert(s != (char*) -1);
	assert(semid != -1);
	while(1)
	{
		strcpy(s,"hello world\n");
	}
	shmdt(s); 
}
