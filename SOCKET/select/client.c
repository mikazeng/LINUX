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
void main()
{
	struct sockaddr_in serv_addr;
	int sockfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//inet_pton(AF_INET,"192.168.42.100",&serv_addr.sin_addr);
	Connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	char buf[128] = {0};
	while(fgets(buf,127,stdin) != NULL)
	{
		Write(sockfd,buf,127);
		int n = Read( sockfd,buf,127);
		if( n == 0) Close(sockfd);
		puts(buf);
	}
	close(sockfd);
	return ;
}

