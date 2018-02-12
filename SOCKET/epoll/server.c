#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<ctype.h>
#include"wrap.h"
#include<string.h>
#include<sys/epoll.h>
#define SERV_PORT 8888
#define MAXLINE 128
#define OPEN_MAX 1024
void main()
{
	struct sockaddr_in serv_addr,clieaddr;
	struct epoll_event  ep[OPEN_MAX];
	int client[OPEN_MAX];

	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"192.168.42.100",&serv_addr.sin_addr);

	Bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	Listen(listenfd,128);

	int i;
	for(i = 0;i < OPEN_MAX;i++)
		client[i] = -1;//初始化监听文件描述符的集合

	int maxi = -1;

	int efd = epoll_create(OPEN_MAX);//创建红黑树
	assert(efd != -1);

	struct epoll_event tep;
	tep.events = EPOLLIN;
	tep.data.fd = listenfd;

	int res = epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
	assert(res != -1);

	while(1)
	{
		int nready = epoll_wait(efd,ep,OPEN_MAX,-1);
		if(nready < 0)
			perr_exit("epoll errot");
		for( i = 0;i < nready ;i++)
		{
			if(!(ep[i].events & EPOLLIN))
			continue;

			int j;
			if(ep[i].data.fd == listenfd)
			{
				int cliaddr_len = sizeof(clieaddr);
				int connfd = Accept(listenfd,(struct sockaddr*)&clieaddr,&cliaddr_len);
				printf("IP:%s , PORT:%d\n",
						inet_ntoa(clieaddr.sin_addr),
						ntohs(clieaddr.sin_port));
				for( j = 0;j< OPEN_MAX;j++)
					if(client[j] < 0)
					{
						client[j] = connfd;
						break;
					}
				if(j == OPEN_MAX)
				{
					puts("too many client\n");
					exit(1);
				}
				if(j > maxi)
					maxi = j;
				tep.events = EPOLLIN;
				tep.data.fd = connfd;
				res = epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
				assert(res!= -1);
			}
			else
			{
				int sockfd = ep[i].data.fd;
				char buf[128] = {0};
				int n;
					if( (n = Read(sockfd,buf,127)) == 0)
					{
						printf("clien[%d] abort\n",j);
						for(j = 0;j <= maxi;j++)
							if(client[j] == sockfd)
							{
								client[j] = -1;
								break;
							}
						res = epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
						assert(res != -1);
						Close(sockfd);
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
				}
			}
		}
		Close (listenfd);
		Close(efd);
		return ;
	}

