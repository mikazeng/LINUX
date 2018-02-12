#include<stdio.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<fcntl.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE  128
#define PORT 6000
char * ip = "127.0.0.1";
int main(int argc,char* argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE] ={0};
	int n ;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);	
	servaddr.sin_addr.s_addr = inet_addr("192.168.31.120");
//	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
//  inet_pton(AF_INET,ip,&servaddr.sin_addr.s_addr);
	Connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("connect ok\n");
	
	printf("input:");
	fgets(buf,127,stdin);
	puts(buf);
	write(sockfd,buf,strlen(buf)- 1);

	memset(buf,0,128);
	read(sockfd,buf,sizeof(buf));
	puts(buf);
	write(sockfd,"ok",2);
	int fd = open("file",O_WRONLY);
	assert(fd != -1);
	while(1)
	{
		int n = read(fd,buf,128);	
		if( n == 0)
		{
			printf("ok");
			break;
		}
		write(fd,buf,n);
	}
	return 0;
}

