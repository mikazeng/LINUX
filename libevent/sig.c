#include<signal.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void fun(int sig)
{
	
	printf("%u  is callled\n",(int)pthread_self());

}
void* thfun(void *arg)
{
	while(1)
	{
		printf("thread %uis workign\n",(int)pthread_self());
		sleep(1);
	}
}
void main()
{
	signal(SIGUSR1,fun);
	pthread_t th1;
	pthread_create(&th1,0,thfun,NULL);
	pthread_t th2;
	pthread_create(&th2,0,thfun,NULL);

	sleep(5);
	
	pthread_kill(th1,SIGUSR1);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
}
