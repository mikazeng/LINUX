#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<ctype.h>
#include"wrap.h"
#include<string.h>
#include<poll.h>
#define SERV_PORT 8888
#define MAXLINE 128
#define OPEN_MAX 1024
void main()
{
	struct sockaddr_in serv_addr,clieaddr;
	struct pollfd client[OPEN_MAX];
	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"192.168.42.100",&serv_addr.sin_addr);

	Bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	Listen(listenfd,128);

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;//监听普通读事件

	int i = 1;
	for(i = 1;i < OPEN_MAX;i++)
		client[i].fd = -1;//初始化监听文件描述符的集合

	int maxi = 0;	

	while(1)
	{
		int nready = poll(client,maxi + 1,-1);
		if(nready < 0)
			perr_exit("poll errot");
		if(client[0].revents & POLLRDNORM)
		{
			int cliaddr_len = sizeof(clieaddr);
			int connfd = Accept(listenfd,(struct sockaddr*)&clieaddr,&cliaddr_len);
			printf("IP:%s , PORT:%d\n",
					inet_ntoa(clieaddr.sin_addr),
					ntohs(clieaddr.sin_port));
			for( i = 0;i< OPEN_MAX;i++)
			if(client[i].fd < 0)
			{
				client[i].fd = connfd;
				client[i].events = POLLRDNORM;
				break;
			}
			if(i == OPEN_MAX)
			{
				puts("too many client\n");
				exit(1);
			}
			if(i > maxi)
				maxi = i;
			if(--nready == 0)
				continue;
		}
		for ( i = 0;i <= maxi;i++)//检测哪个客户端就绪
		{
			int sockfd;
			char buf[128] = {0};
			if( (sockfd = client[i].fd) < 0)
				continue;
			if(client[i].revents & POLLRDNORM)//sockfd就绪
			{
				ssize_t n;
				if( (n = Read(sockfd,buf,127)) == 0)
				{
					printf("clien[%d] abort\n",i);
					Close(sockfd);
					client[i].fd = -1;
				}
				else
				{
					char *s = buf;
					while(*s)
					{
						*s = toupper(*s);
						s++;
					}
					write(sockfd,buf,n);
				}
				if(--nready == 0)
					break;
			}
		}
	}
	Close (listenfd);
	return ;
}

