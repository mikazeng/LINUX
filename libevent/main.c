#include<stdio.h>
#include<stdlib.h>
#include<event.h>
#include<signal.h>
#include<assert.h>
#include<string.h>
#include<time.h>
void signal_cb(int fd,short ev ,void *arg )
{
	printf("RECV fd %d  :SIGINT\n",fd);
}
void time_cb(int fd,short ev,void *arg)
{
	printf(" time out \n");
}
void main()
{
	struct event_base * base = event_init();
	assert( base != NULL);
	//struct event *sig_ev = evsignal_new(base,SIGINT,signal_cb,NULL);
	struct event *sig_ev = event_new(base,SIGINT,EV_SIGNAL,signal_cb,NULL);
	assert(sig_ev!= NULL);
	event_add(sig_ev,NULL);
	//struct event_base *time_ev = evtimer_new(base,time_cb,NULL);
	struct event_base *time_ev = event_new(base,-1,EV_TIMEOUT|EV_PERSIST,time_cb,NULL);
	assert( time_ev != NULL);
	struct timeval tv = {5,0};//超时时间
	event_add(time_ev,&tv);
	event_base_dispatch(base);
	event_free(sig_ev);
	event_free(time_ev);
	event_base_free(base);
}
