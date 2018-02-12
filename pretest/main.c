#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
void main(int argc,char **argv)
{
	if(argc < 2){
		printf("input arg num\n");
		return;
	}
	int num = atoi(argv[1]);

	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr =inet_addr("39.107.94.67");

	addr.sin_addr.s_addr =inet_addr("127.0.0.1");
	addr.sin_port = htons(6666);
	int i;
   for( i = 0;i <num;i++)
   {
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		printf("create sock failed\n");
	}
	
/*	
	int opt = 1;
	if(setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt)))
	{
		printf("set sock failed \n");
		return ;
	}


	caddr.sin_port = htons(p++);
	if(bind(sock,(struct sockaddr*)&caddr,sizeof(caddr))==-1)
	{
		printf("bind error\n");

	}
	*/

	if(connect(sock,(struct sockaddr*)&addr,sizeof(addr)) == 0)
		printf("build connection %d\n",i);
	else
		printf("connect failed\n");

   }

   sleep(60);
}
