#include"list.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void list_init(struct node** phead)
{
	*phead = (struct node*)malloc(sizeof(struct node));
	(*phead)->next = NULL;
}

void list_add(struct node *phead,int val)
{
	struct node *tmp =(struct node*)malloc(sizeof( struct node));
	tmp->data = val;
	tmp->next = NULL;
	while(phead->next !=NULL)
	{
		phead = phead->next;
	}
	phead->next = tmp;
	printf(" data insert ok\n");
}
int  list_get(struct node *phead)
{
	if(phead->next == NULL)
		return -1 ; 
	struct	node * tmp = phead->next;
	phead->next = tmp->next;
	int data = tmp->data;
	free(tmp);
	return data;
}
void list_destroy(struct node*phead)
{



}


