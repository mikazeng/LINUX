#include<stdio.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE 80
#define PORT 6000
char * ip = "127.0.0.1";
int main(int argc,char* argv[])
{
	struct sockaddr_in servaddr;

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	assert(sockfd != -1);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);	
	servaddr.sin_addr.s_addr = inet_addr("192.168.31.120");
//	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
//  inet_pton(AF_INET,ip,&servaddr.sin_addr.s_addr);
	char str[128] = {0};
	while(1){
		fgets(str,127,stdin);
		int n = sendto(sockfd,str,127,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		recvfrom(sockfd,str,127,0,NULL,NULL);
		puts(str);
	}

	close(sockfd);
	return 0;
}



