#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<sys/msg.h>
#include<unistd.h>
struct mess{
long type;
int val;
};
void main()
{
	int msgid = msgget((key_t)1234,IPC_CREAT|0600);
	assert(msgid != -1);
	struct mess dt;
	dt.type = 1;
	while(1){
		printf("input:\n");
		scanf("%d",&dt.val);
		msgsnd(msgid,(void *)&dt,sizeof(int),0);//发送数据
	}
}
