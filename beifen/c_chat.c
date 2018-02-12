#include"fun.h"
extern int sockfd;
void main()
{
	set_ser_sock();
	cli_connect();
	int choic = 0;
	while(1){
		printf("input your choic\n");
		printf("1.regist\t2.login\t3.all\t4.online\t5.one\t6.grop\t7.get\n");
		scanf("%d",&choic);
		getchar();char buff[64] = {0};
		switch(choic)
		{
			case 1: cli_regist();
					break;
			case 2:cli_login();
				   break;
			case 3:cli_ShowAll();
				   break;
			case 4:get_online();
				   break;
			case 5:cli_onetalk();
				   break;
			case 6:cli_grptalk();
				   break;
			case 7:read(sockfd,buff,64);puts(buff);
				   break;
			default:printf("error\n");	
					break;
		}
	}

}
