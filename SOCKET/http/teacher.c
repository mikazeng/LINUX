#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PATH "/home/run/SOCKET/http"
int main()
{
    signal(SIGCHLD,SIG_IGN);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert( sockfd != -1 );

    struct sockaddr_in saddr,caddr;
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(80);
	//root saddr.sin_addr.s_addr = inet_addr("192.168.31.120");

    int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    assert( res != -1 );

    listen(sockfd,20);

    while( 1 )
    {
        int len = sizeof(caddr);
        int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
        if ( c < 0 )
        {
            continue;
        }

        pid_t pid = fork();
        assert( pid != -1 );

        if ( pid == 0 )
        {
            close(sockfd);
            //接受http请求报文
            char recvbuff[512] = {0};
            if ( recv(c,recvbuff,511,0) <= 0 )
            {
                close(c);
                exit(0);
            }

            printf("read:\n%s\n",recvbuff);
            char *s = strtok(recvbuff," ");
            if ( s == NULL )
            {
                close(c);
                exit(0);

            }

            printf("Mode:%s\n",s);

            s = strtok(NULL," ");
            if ( s == NULL )
            {
                close(c);
                exit(0);
            }

			puts(s);
			if ( strcmp(s,"/") == 0 )
			{
				s = "/index.html";
			}

			char path[256] = {PATH};
			strcat(path,s);

			puts(path);
			int fd = open(path,O_RDONLY);
			if ( fd == -1 )
			{
				send(c,"not find",8,0);
				close(c);
				exit(0);
			}

			struct stat st;
			lstat(path,&st);

			char sendbuff[1024] = {0};
			strcpy(sendbuff,"HTTP/1.1 200 OK\r\n");
			strcat(sendbuff,"Server: myhttpd\r\n");
			sprintf(sendbuff+strlen(sendbuff),"Content-Length: %d\r\n",st.st_size);
			strcat(sendbuff,"\r\n");
			send(c,sendbuff,strlen(sendbuff),0);
			printf("send head:\n%s\n",sendbuff);

			char data[512] = {0};
			int num = 0;
			while( (num = read(fd,data,512)) > 0 )
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
