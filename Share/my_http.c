#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<assert.h>
#include<sys/socket.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/stat.h>
#define PATH "/home/run/SOCKET/http"
int main()
{
    	signal(SIGCHLD,SIG_IGN);
	int sockfd =socket(AF_INET,SOCK_STREAM,0);
	assert( sockfd != -1);
	struct sockaddr_in saddr,caddr;
	bzero(&saddr,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(80);
	//saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res!=-1);
	listen(sockfd,5);

	while(1)
	{
		int len = sizeof(caddr);
		int c  = accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c < 0)
			continue;
		pid_t pid = fork();
		if(pid == 0 )
		{
			close(sockfd);
			char buff[512] = {0};
			recv(c,buff,511,0); 
			printf("recv:\n%s\n",buff);

			char *s = strtok(buff," ");

			printf("MODE:%s\n",s);

			s = strtok(NULL," ");

			puts(s);
			if(strcmp(s,"/") == 0)
				s = "/index.html";

			char path[256] = {PATH};
			strcat(path,s);

			puts(path);
			int fd = open(path,O_RDONLY);
			assert(fd != -1);		
		
			struct stat st;
			lstat(path,&st);//file shux

			char anser[512] = {0};
			strcpy(anser,"HTTP/1.1 200 OK\r\n");
			strcat(anser,"Server: myhttpd\r\n");
			//strcat(anser,"content-Length:512\r\n");
			sprintf(anser+strlen(anser),"Content-Length: %d\r\n",st.st_size);

			strcat(anser,"\r\n");
			send(c,anser,strlen(anser),0);

			char data[512] = {0};
			int num = 0;
			printf("send head :\n%s",anser);	
			while((num = read(fd,data,512) >0))
			{
				send(c,data,num,0);
			}
			close(c);
			close(fd);
			exit(0);
		}
			close(c);
	}
}
