#include"fun.h"

void main()
{
	Init_head();
	set_ser_sock();
	bind_listen();
	ser_accept();
	Destroy();
}

