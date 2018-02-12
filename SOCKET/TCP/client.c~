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
#define PORT 6666
char * ip = "127.0.0.1";
int main(int argc,char* argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE] ={0};
	int n ;
	int fd = socket(AF_INET,SOCK_STREAM,0);
	assert(fd != -1);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);	
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
//  inet_pton(AF_INET,ip,&servaddr.sin_addr.s_addr);
	connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("connect ok\n");
	fgets(buf,128,stdin);
	write(fd,buf,strlen(buf));
	n = read(fd,buf,sizeof(buf));
	printf("Recev From :");
	fflush(stdout);
	assert(n != -1);
	write(STDOUT_FILENO,buf,n);
	putchar(10);
	close(fd);
	return 0;
}



