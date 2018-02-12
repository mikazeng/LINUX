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
int main()
{
	struct sockaddr_in servaddr;
	struct sockaddr_in clieaddr;

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servaddr.sin_addr.s_addr  = inet_addr("192.168.31.120");
	servaddr.sin_port = htons(PORT);

	int res = Bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	assert(res != -1);

	printf("Accepting connecting UDP....\n");
	while(1)
	{
		socklen_t client_len = sizeof(clieaddr);
		char buf[128] = {0};
		int n = recvfrom(sockfd,buf,127,0,(struct sockaddr*)&clieaddr,&client_len);
		//如果一次性没有读取完成的话，剩余打就丢弃．因为DUP是面向分组的
		//ＵＤＰ的收发次数必须对应，recvfrom对应一个sendto
		//一次只允许读一个报文，没有读完的话将造成丢包
		if (n < 0) perror("recvfrom error\n");

		printf("Accepting IP:%s PORT:%d\n",		
				inet_ntoa(clieaddr.sin_addr)
				,clieaddr.sin_port);

	char * s = buf;
		while(*s)
		{
			*s = toupper(*s);
			s++ ;
		}

		n = sendto(sockfd,buf,n,0,(struct sockaddr*)&clieaddr,sizeof(clieaddr));
		if(n < 0) perror("sendto perror\n");

	}
	//nc 127.0.0.1 6666 命令链接一个服务器　
	//hello world 
	Close(sockfd);
	return 0;
}

