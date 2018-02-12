#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE 80
#define PORT 6666
int main()
{
	struct sockaddr_in servaddr;
	struct sockaddr_in clieaddr;
	socklen_t client_len;
	int listenfd,connfd;
	char buf[MAXLINE] ={0};
	char str[INET_ADDRSTRLEN] = {0};
	int fd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servaddr.sin_addr.s_addr  = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	bind(fd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(fd,128);//指定的链接上限数

	printf("Accepting connecting....\n");
		client_len = sizeof(clieaddr);
connfd = accept(fd,(struct sockaddr*)&clieaddr,&client_len);

		printf("Accepting IP:%s PORT:%d\n",		
				inet_ntop(AF_INET,&clieaddr.sin_addr,str,sizeof(str))
				,clieaddr.sin_port);
		while(1)
		{
		    read(connfd,buf,sizeof(buf));
			int fd = open(buf,O_RDONLY);
			if(fd == -1)
				printf("file open failed\n");
			read(connfd,buf,3);
			if(strcmp(buf,"ok")== 0)
				printf("begin recv file\n");

			int n ;
			char str[128] = { 0 };
			while( (n =read(fd,str,128)) != 0)
			{
				write(connfd,str,n);
			}
			printf("file is ok\n");
			close(fd);
		}
		//nc 127.0.0.1 6666 命令链接一个服务器　
		//hello world 
		Close(connfd);
		return 0;
}



