#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>
#include<stdint.h>
uint64_t vir_to_phy(unsigned long vaddr)
{
	int page_size = getpagesize();
	int index = vaddr / page_size;//虚地址中地几个页
	int offset = vaddr % page_size;//页中偏移
	int file_offset = index * 8;//文件中记录映射关系
	int fd = open("/proc/self/pagemap",O_RDONLY);
	assert(fd != -1);
	int res =lseek(fd,file_offset,SEEK_SET);
	assert(res!=-1);
	uint64_t val = 0;
	read(fd,&val,8);
	printf("val=%d\n",val);
	uint64_t phy =0;
	if(val & ((uint64_t)1<<63))//是否在内存中
	{
		val &=(((uint64_t )1<<55) - 1);//＆上前56个1
		printf("val=%d\n",val);
		phy = val * page_size + offset;
		return phy;
	}
	return 0;
}
void main()
{
	int a =10;
	int b = vir_to_phy(&a);
	printf("vir= %x\n",&a);
	printf("phy=%x\n",b);
}
