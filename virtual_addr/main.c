#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int g;
int gg;
int add(int x,int y);
void main()
{
	int a =10;
	printf("main:%08x\n",main);
	printf("add:%08x\n",add);
	printf("g:%08x\n",&g);
	printf("a:%08x\n",&a);
}

int add(int x,int y)
{
	return x+y;
}
