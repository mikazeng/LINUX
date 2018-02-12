/*producer and constmer*/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
pthread_rwlock_t rwlock;
int good = 0;
void *writer(void *argv)
{
    while(1)
    {
	pthread_rwlock_wrlock(&rwlock);
	good = rand() % 1000;
	printf("%u witre:%d\n",(unsigned int)pthread_self() % 100,good);
	pthread_rwlock_unlock(&rwlock);
	sleep(rand()%2);
    }
    return NULL;
}
void *reader(void *argv)
{
    while(1)
    {
	pthread_rwlock_rdlock(&rwlock);
	printf("%u read:%d\n",(unsigned int)pthread_self() % 100,good);
	pthread_rwlock_unlock(&rwlock);
	sleep(rand()%2);

    }
    return NULL;
}
void main()
{
    pthread_t pt[8];
    int i;
    pthread_rwlock_init(&rwlock,NULL);
    for(i=0;i < 3;i++)
    {
	pthread_create(&pt[i],NULL,writer,NULL);
    }
    for(;i<8;i++)
	pthread_create(&pt[i],NULL,reader,NULL);
    for(i=0;i<8;i++)
	pthread_join(pt[i],NULL);
    pthread_rwlock_destroy(&rwlock);
}
