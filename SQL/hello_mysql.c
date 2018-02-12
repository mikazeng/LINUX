#include<mysql/mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
void main()
{
	MYSQL mysql;//定义一个mysql变量
	MYSQL* connect;
	mysql_init(&mysql);//初始化mysql,相当于SQL内部初始化了一个TCP的SOCKET和开辟了NYSQL必要的内存.

	connect = mysql_real_connect(&mysql,"localhost","run","32875094","db1",0,0,0);
	//localhost表示本地127.0.0.1,连接到本地的mysql
	if(connect==NULL){
		printf("%s",mysql_error(&mysql));
		return ;
	}
	//终端输入的 时候会带有\n字符
	mysql_query(connect,"set names utf8");//执行sql语句


/*	if(mysql_query(connect,"delete from student where name = '小李'")==0)//执行sql语句
	{
		printf("delete ok\n");
	}
	else
	{
		printf("%s",mysql_error(&mysql));
	}
*/
	//mysql_query(connect,"INSERT INTO student (name, sex, age, class) VALUES ('曾润良', '女', 23, 'C++班')");

	mysql_query(connect,"select * from student");//直接执行select语句，该方法错误!!!输入没有任何结果
	//mysql_query(connect,"select * from student where name = '小龙女'");
	MYSQL_RES * res = mysql_store_result(connect);//该函数得到查询结果。将该结果放到MYSQL_RES结构中该方法必须提前知道返回的数据中有多少列

	MYSQL_FIELD * field = mysql_fetch_field(res);
	mysql_set_character_set(mysql,"utf8");//设置字符集
	int count = 0;
	while(field != NULL)
	{
		printf("%s\t",field->name);
		field = mysql_fetch_field(res);//该函数得到所有的列名，并通过field->name成员结构打印出来
		count++;//记录有多少个列，这样就不不知道有多少列
		//直接调用函数获得列的数量int num = mysql_num_fields(res);
	}
	putchar(10);
	MYSQL_ROW   row = mysql_fetch_row(res);//结果返回的是字段（行）
	while(row != NULL)
	{

		int i =0;
		for(i =0;i<count;++i){
			printf("%s\t",(const char*)row[i]);
		}
		putchar(10);
			/*
		printf("name= %s\tsex = %s\tage = %s\t class= %s\n",(const char *)row[0],(const char *)row[1],(const char *)row[2],(const char *)row[3]);

		*/
		row = mysql_fetch_row(res);//遍历每一行，该方法必须提前知道有多少列

	}
	mysql_free_result(res);//释放res的资源

	mysql_close(connect);//断开与SQL server的连接

	puts("hello world");

}
