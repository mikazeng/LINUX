#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node*next;
};
void list_init(struct node** phead);
void list_add(struct node *phead,int val);
int  list_get(struct node *phead);
void list_destroy(struct node*phead);
