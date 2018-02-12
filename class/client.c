#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 6000 
int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);
	struct sockaddr_in saddr,caddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr("192.168.31.120");
	//inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);传入传出参数
	int res = connect (sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res!=-1);
	printf("ok\n");
	char buff[128] = {0};
	fgets(buff,128,stdin);
	send(sockfd,buff,strlen(buff),0);
	memset(buff,0,128);
	recv(sockfd,buff,127,0);
	puts(buff);
	close(sockfd);
}










