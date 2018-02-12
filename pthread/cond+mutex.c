/*producer and constmer*/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
pthread_mutex_t mutex;
pthread_cond_t cond;//
int good = 0;
void *customer(void *argv)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(good == 0)
			pthread_cond_wait(&cond,&mutex);
		good--;
		printf("customer:%d\n",good);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	return NULL;
}
void *producer(void *argv)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		good++;
		printf("producer:%d\n",good);
		pthread_mutex_unlock(&mutex);
		if(good == 1)
			pthread_cond_signal(&cond);
		sleep(rand()%3);
	}
	return NULL;
}
void main()
{
	pthread_t pt1,pt2;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&pt1,NULL,customer,NULL);
	pthread_create(&pt2,NULL,producer,NULL);

	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
