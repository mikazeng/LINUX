#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<assert.h>
#include<string.h>
#include<sys/types.h>
#include<sys/sem.h>

void main()
{
     int shmid = shmget((key_t)666,256,IPC_CREAT|0666); 
     assert(shmid != -1);
     printf("%d",shmid);
     char *s = shmat(shmid,NULL,0);
     while(1)
     {

     }
     shmdt(s); 
}
