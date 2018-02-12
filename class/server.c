#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#define PORT 6000
int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);
	struct sockaddr_in saddr,caddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);传入传出参数
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);
	listen(sockfd,128);//socket转换成监听的套接字,已完成三次握手队列之和
	//int inet_ntop
	while(1)
	{
		int len = sizeof(caddr);
		int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
		assert(c != -1);
		printf("ok \n");
		printf("IP:%s POTR:%d",
				inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
		char buf[128] = {0};
	int res = read(c,buf,127);
	if(res == -1 && errno == EINTR)
	{
		printf("again\n");
	}
	}
	close(sockfd);
}

