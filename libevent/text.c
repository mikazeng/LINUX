#include<stdio.h>
#include<stdlib.h>
#include<event.h>
#include<signal.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
void signal_cb(int fd,short ev ,void *arg )
{
	printf("RECV fd %d  :SIGINT\n",fd);
}
void time_cb(int fd,short ev,void *arg)
{
	printf(" time out \n");
}
void io_cb(int fd,short ev,void *arg)
{
	if(ev &EV_READ)
	{
		char buff[128]= {0};
		if(recv(fd,buff,127,0) <= 0)
		{
			close(fd);
			printf("%d client close\n",fd);
		}
		else
		{
			puts(buff);
		}

	}
}
int create_socket()
{
	int sockfd  = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in saddr;
	memset(&saddr,0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert( res != -1);

	listen(sockfd,5);

	return sockfd;
}
void accept_cb(int fd, short ev,void *arg)
{
	struct event_base* base= (struct event_base*)arg;
	if(EV_READ & ev)
	{
		struct sockaddr_in caddr;
		int len = sizeof(caddr);	
		int c = accept(fd,(struct sockaddr*)&caddr,&len);
		printf("accept c = %d",c);
		struct event * io_ev = event_new(base,c,EV_READ|EV_PERSIST,io_cb,NULL);
		event_add(io_ev,NULL);
	}

}

void main()
{
	int sockfd  = create_socket();
	struct event_base * base = event_init();
	struct event *sock_ev = event_new(base , sockfd,EV_READ|EV_PERSIST,accept_cb,base);
	event_add(sock_ev,NULL);
	event_base_dispatch(base);
	event_free(sock_ev);
	event_base_free(base);
}
