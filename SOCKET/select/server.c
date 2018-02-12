#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<ctype.h>
#include"wrap.h"
#include<string.h>
#define SERV_PORT 8888
#define MAXLINE 128
int client[FD_SETSIZE];
fd_set rset,allset;
void main()
{
	int connfd;
	struct sockaddr_in serv_addr,clieaddr;
	socklen_t clie_addr_len ;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN]; 

	int listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"192.168.42.100",&serv_addr.sin_addr);
	Bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	Listen(listenfd,128);

	int maxfd = listenfd;
	int maxi = -1;//最大下标
	int i;

	for(i = 0;i < FD_SETSIZE;i++)
		client[i] = -1;//初始化监听文件描述符的集合

	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);//listenfd加入到监听集合中
	
	while(1)
	{
		rset = allset;
		int nready = select(maxfd + 1,&rset,NULL,NULL,NULL);//rset   be changed 
		if(nready < 0)
			perr_exit("select errot");

		if(FD_ISSET(listenfd,&rset))
		{
			int cliaddr_len = sizeof(clieaddr);
			connfd = Accept(listenfd,(struct sockaddr*)&clieaddr,&cliaddr_len);
			printf("IP:%s , PORT:%d\n",
					inet_ntoa(clieaddr.sin_addr),
					ntohs(clieaddr.sin_port));

			for( i = 0;i< FD_SETSIZE;i++)
			if(client[i] < 0)
			{
				client[i] = connfd;
				break;
			}
			if(i == FD_SETSIZE)
			{
				puts("too many client\n");
				exit(1);
			}
			FD_SET(connfd,&allset);//
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;
			if(--nready == 0)
				continue;
		}
		for ( i = 0;i <= maxi;i++)//检测哪个客户端就绪
		{
			int sockfd;
			if( (sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd,&rset))//sockfd就绪
			{
				ssize_t n;
				if( (n = Read(sockfd,buf,127)) == 0)
				{
					Close(sockfd);
					FD_CLR(sockfd,&allset);
					client[i] = -1;
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

