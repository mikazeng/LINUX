#ifndef FUN_H
#define FUN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<assert.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
typedef enum{
	REGIST,
	LOGIN,
	ONLINE,
	ONE,
	GROUP,
	EXIT,
	ALL,
}MSG_TYPE;

typedef struct {
	MSG_TYPE type;
		char mname[32];
		char fname[32];
		char one_msg[32];
	union {
		char pw[20];
		char grp_msg[64];
	};
}MSG;

///所有用户链表,登录时使用
typedef struct user{
	char *name;
	char *pw;
	struct 	user*next;
}USNode;

USNode *ahead;//所有用户链表头节点

int Adduser(USNode*user);//注册时添加
int  nameIsUsed(char *name);
void ShowAlluser(int fd);




///在线链表,发送消息时使用
typedef struct online
{
	char *name;
	int fd;
	struct sockaddr_in *addr;
	struct  online *next;
}OLnode;

OLnode * ohead;//在线链表头节点

int  nameIsOline(char *name);

void ShowOnline(int fd);

int Ispw(char *pw,char *name);

int AddOnline(OLnode*node);




//离线链表
typedef struct offline{
	char *name;
	char *msg;
	struct  offline *next;
}OFFnode;

OFFnode* offhead;//离线链表头节点，包含离线消息

int  SendMSG(char *name,char *msg);
int  AddOFline(OFFnode *user);

void Init_head();



///共用函数
void set_ser_sock();

///服务器端函数
void bind_listen();
void ser_accept();
int ser_regist(MSG*data,int fd);
int ser_login();
int	ser_onetalk(MSG*buff,int fd);
int ser_grptalk(MSG*buff,int fd);

void *work(void *arg);

///客户端函数
int  cli_connect();
int cli_regist();
int cli_login();
int get_online();
void cli_ShowAll();
int cli_onetalk();
int cli_grptalk();
void cli_exit();






#endif

