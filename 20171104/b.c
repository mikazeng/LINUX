#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<sys/msg.h>
#include<unistd.h>
#include"list.h"
#include<semaphore.h>
struct mess
{
	long type;
	int val;
};
struct node *head;
sem_t sem;//信号量
pthread_mutex_t mutex;//互斥量
void *thread_fun(void *arg)
{
	int index = (int)arg;
	while(1)
	{
		sem_wait(&sem);
		pthread_mutex_lock(&mutex);
		printf("pthead%d : data %d\n",index,list_get(head));
		pthread_mutex_unlock(&mutex);
	}
}

void main()
{
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert(msgid != -1);
	struct mess dt;
	dt.type = 1;
	list_init(&head);
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem,0,0);
	pthread_t id[3];
	int i =0;
	for(;i<3;i++)
	{
		pthread_create(&id[i],NULL,thread_fun,(void *)i);
	}
	while(1)
	{
		msgrcv(msgid,(void *)&dt,sizeof(int),1,0);//接收数据
		//printf("%d\n",dt.val);
		pthread_mutex_lock(&mutex);
		list_add(head,dt.val);
		sem_post(&sem);
		pthread_mutex_unlock(&mutex);
	}
}
