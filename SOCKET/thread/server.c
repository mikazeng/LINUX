#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#define MAXLINE 80
#define PORT 6666
struct s_info{
	struct sockaddr_in cliaddr;
	int connfd;
};
void * do_work(void *arg)
{
	char buf[128] = {0};
	char str[128] = {0};
	struct s_info*ts = (struct s_info*)arg;
	printf("thread begin \n");
	printf("Accepting IP:%s PORT:%d\n",	
			inet_ntoa(ts->cliaddr.sin_addr)
			,ts->cliaddr.sin_port);
	while(1)
	{
		int	n = read(ts->connfd,buf,sizeof(buf));
		if(n == 0)
		{
			printf(" IP:%s PORT:%d has been quit\n",	
					inet_ntoa(ts->cliaddr.sin_addr)
					,ts->cliaddr.sin_port);
			break;
		}
		char * s = buf;
		while(*s)
		{
			*s = toupper(*s);
			s++;
		}
		write(ts->connfd,buf,n);
	}
	close(ts->connfd);
}
int main()
{
	struct sockaddr_in servaddr;
	struct sockaddr_in clieaddr;
	socklen_t client_len;
	int listenfd,connfd;
	pthread_t pid;
	int i= 0;
	struct s_info ts[383];
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servaddr.sin_addr.s_addr  = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,128);//指定的链接上限数

	printf("Accepting connecting....\n");
	while(1)
	{
		client_len = sizeof(clieaddr);
		connfd = accept(listenfd,(struct sockaddr*)&clieaddr,&client_len);
		printf(" accept success\n");
		ts[i].cliaddr = clieaddr;
		ts[i].connfd = connfd;
		printf("%d\n",ts->connfd);	
		pthread_create(&pid,NULL,do_work,(void*)&ts[i]);
		pthread_detach(pid);
		i++;
		//nc 127.0.0.1 6666 命令链接一个服务器　
	}
	return 0;
}



