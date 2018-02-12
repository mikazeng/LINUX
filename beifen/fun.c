#include"fun.h"
struct sockaddr_in seraddr;//服务器ＩＰ和端口号
int sockfd;//服務器文件描述符
pthread_mutex_t  mutex;

//////////////公用函数

void Init_head()
{
	offhead = (OFFnode*)malloc(sizeof(OFFnode));
	memset(offhead,0,sizeof(OFFnode));

	ahead = (USNode*)malloc(sizeof(USNode));
	memset(ahead,0,sizeof(USNode));

	ohead = (OLnode*)malloc(sizeof(OLnode));
	memset(ohead,0,sizeof(OLnode));

	pthread_mutex_init(&mutex,NULL);
}
void Destroy()
{
	free(offhead);
	free(ahead);
	free(ohead);
	pthread_mutex_destroy(&mutex);
}
void set_ser_sock()
{
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	seraddr.sin_port = htons(6666);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
}

////////////服务器端//////////////

void ser_accept()
{
	struct sockaddr_in* cliaddr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	memset(cliaddr,0,sizeof(struct sockaddr_in));
	int len = sizeof(struct sockaddr_in);
	while(1)
	{
	int cfd = accept(sockfd,(struct sockaddr*)cliaddr,&len);
	assert(cfd != -1);

	OLnode*cinfo = (OLnode*)malloc(sizeof(OLnode));
	memset(cinfo,0,sizeof(OLnode));
	cinfo->fd = cfd;
	cinfo->addr = cliaddr;
	pthread_t id;
	pthread_create(&id,NULL,work,(void*)cinfo);//每接受一个客户端一个线程处理,并且传入客户端的文件描述符和ip端口
	}
}
int ser_regist(MSG*data,int fd)
{
	if(data == NULL) return 0;
	if(nameIsUsed(data->mname))
	{
		write(fd,"name error\n",11);
		return 0;
	}
	USNode  *cli =(USNode*)malloc(sizeof(USNode));
	cli->name = data->mname;
	cli->pw = data->pw;
	cli->next = NULL;
	Adduser(cli);	
	write(fd,"regist ok\n",10);
	return 1;
}
int Adduser(USNode*user)//注册时添加加锁
{
	if(user == NULL)return 0;
	assert(ahead != NULL);
	pthread_mutex_lock(&mutex);
	user->next = ahead->next;
	ahead->next = user;
	pthread_mutex_unlock(&mutex);
	return 1;
}

void ShowAlluser(int fd)
{
	assert(ahead != NULL);
	USNode * p = ahead->next;
	assert(p != NULL);
//	write(fd,"------------------------\n",26);
	char buff[1024] = {0};
	while(p)
	{
		sprintf(buff+strlen(buff),"name:%spw:%s\n",p->name,p->pw);
//		printf("name:%sPW:%s\n",p->name,p->pw);
		p = p->next;
	}
	write(fd,buff,sizeof(buff));
//	printf("that all\n");
}
int  nameIsUsed(char *name)
{
	assert( ahead!= NULL);
	if(name == NULL )return 0;
	USNode *p = ahead->next;
	while(p)
	{
		if(!strcmp(name,p->name))return 1;
		p = p->next;
	}
	return 0; 
}

int ser_login(MSG*data,OLnode*node)
{
	if(data == NULL||node == NULL)return 0;
	if(nameIsUsed(data->mname))
	{
		if(Ispw(data->pw,data->mname))
		{
			node->name = data->mname;
			node->next = NULL;
			AddOnline(node);
			return 1;
		}
		else
		{
			write(node->fd,"pw error\n",9);
			return 0;
		}
	}
	else
	{
		write(node->fd,"name error\n",11);
		return 0;
	}
}
int Ispw(char *pw,char *name)
{
	if(name == NULL )return 0;
	USNode *p = ahead->next;
	assert(p != NULL);
	while(p)
	{
		if(!strcmp(pw,p->pw) && !strcmp(name,p->name))return 1;
		p = p->next;
	}
	return 0; 
}
int AddOnline(OLnode*node)
{
	if(node == NULL)return 0;
	assert(ohead != NULL);
	pthread_mutex_lock(&mutex);
	node->next = ohead->next;
	ohead->next = node;
	pthread_mutex_unlock(&mutex);
	write(node->fd,"login success!!!\n",17);
	return 1;
}
void ShowOnline(int fd)
{
	assert(ohead != NULL);
	OLnode * p = ohead->next;
	assert(p != NULL);
//	write(fd,"------------------------\n",26);
	char buff[1024] = {0};
	while(p)
	{
		sprintf(buff+strlen(buff),"name:%spw:%d\n",p->name,p->fd);
//		printf("name:%sPW:%s\n",p->name,p->pw);
		p = p->next;
	}
	write(fd,buff,sizeof(buff));
//	printf("that all\n");

}
int	ser_onetalk(MSG*buff,int fd)
{
	if(buff == NULL)return  0;
	OLnode * p = ohead->next;
	assert( p != NULL);
	printf("%s%s",buff->fname,buff->one_msg);
	while(p)
	{
		if(strcmp(buff->fname,p->name) == 0) break;
		p = p->next;
	}
	if( p == NULL)
	{
		write(fd,"no online\n",9);
		return 0;
	}
	else
	{
		char buff1 [64] = {0};
		sprintf(buff1,"%s:%s",p->name,buff->one_msg);

		write(p->fd,buff1,strlen(buff1) + 1);

		write(fd,"send ok\n",9);
		return 1;
	}

}

int ser_grptalk(MSG*buff,int fd)
{
	if(buff == NULL)return  0;
	OLnode * p = ohead->next;
	assert( p != NULL);
	printf("%s%s",buff->fname,buff->one_msg);
	char buff1 [64] = {0};
	while(p)
	{
		sprintf(buff1,"%s:%s",p->name,buff->one_msg);

		write(p->fd,buff1,strlen(buff1) + 1);

		write(fd,"send ok\n",9);
		p = p->next;
	}
		return 1;
}

void *work(void *arg)
{	
	OLnode* cnode = (OLnode*)arg;
	int msglen = sizeof(MSG);
	printf("pthread:%u deal client:%d,ip:%s.....\n",pthread_self()%1000,cnode->fd,inet_ntoa(cnode->addr->sin_addr));
	while(1)
	{
		MSG * buff = (MSG *)malloc(msglen);
		memset(buff,0,msglen);
		int n = recv(cnode->fd,buff,msglen,0);
		if (n <= 0 )
		{
			printf("client[%d] closed\n",cnode->fd);
			free(buff);
			close(cnode->fd);
			break;
		}
		switch(buff->type)
		{
			case REGIST:
				ser_regist(buff,cnode->fd);
				break;
			case LOGIN:
				ser_login(buff,cnode);
				break;
			case ONLINE:
				ShowOnline(cnode->fd);
				break;
			case ALL:
				ShowAlluser(cnode->fd);
				break;
			case ONE:
				ser_onetalk(buff,cnode->fd);
				break;
			case GROUP:
				ser_grptalk(buff,cnode->fd);
				break;
			case EXIT: 
				free(buff);
				buff = NULL;
				close(cnode->fd);
				pthread_exit(NULL);
			default:	
				printf("input error\n");
				break;
		}
		//	printf("type: %d\nname:%s\npw:%s\n",buff->type,buff->mname,buff->pw);
		//send(cnode->fd,"ok",3,0);
	}

	pthread_exit(NULL);
	return NULL;

}

/////////客户端////////////////

int  cli_connect()
{
	int res = connect(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	char str[128] = {0};
	assert(res != -1);
	printf("connect server is ok\n");
	/*
	   while(1)
	   {
	   printf("input:");
	   memset(str,0,128);
	   fgets(str,127,stdin);
	   send(sockfd,str,strlen(str),0);
	   recv(sockfd,str,127,0);
	   printf("recv:%s\n",str);
	   }
	 */
}

void bind_listen()
{
	int res	= bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	assert(res != -1);	
	listen(sockfd,128);
}

int cli_regist()
{
	MSG regist_info = {0};
	regist_info.type = REGIST;
	printf("please input your name\n");
	fgets(regist_info.mname,31,stdin);
	printf("please input your password\n");
	fgets(regist_info.pw,31,stdin);
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("send regi info .....\n");
	char buff[32] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);
}

int cli_login()
{
	MSG regist_info = {0};
	regist_info.type = LOGIN;
	printf("please input your name\n");
	fgets(regist_info.mname,31,stdin);
	printf("please input your password\n");
	fgets(regist_info.pw,31,stdin);
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("login .....\n");
	char buff[32] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);
}

int get_online()
{
	MSG regist_info = {0};
	regist_info.type = ONLINE;
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("get online list.....\n");
	char buff[1024] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);
}
void cli_ShowAll()
{
	MSG regist_info = {0};
	regist_info.type = ALL;
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("get all user  list.....\n");
	char buff[1024] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);
}

int cli_onetalk()
{
	MSG regist_info = {0};
	regist_info.type = ONE;
	printf("who your want to talk\n");
	fgets(regist_info.fname,31,stdin);
	printf("your messagr\n");
	fgets(regist_info.one_msg,31,stdin);
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("send your message .....\n");
	char buff[32] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);

}

int cli_grptalk()
{
	MSG regist_info = {0};
	regist_info.type = GROUP;
	printf("input your message\n");
	fgets(regist_info.grp_msg,31,stdin);
	write(sockfd,&regist_info,sizeof(MSG));	
	printf("send group message .....\n");
	char buff[32] = {0};
	read(sockfd,buff,sizeof(buff));
	puts(buff);
}

void cli_exit()
{
	close(sockfd);
	printf("eixt success!\n");
	exit(0);
}
