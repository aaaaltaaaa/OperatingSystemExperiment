#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int signal; //全局共享数
void* thread()
{	//被线程调用的函数
	printf("——————————————————————线程——————————————————————\n");
	printf("线程ID为：%lu\n", (unsigned long int)pthread_self());
	signal = 1; //线程修改数据
	printf("已将共享数据更改\n");
	printf("——————————————————————线程——————————————————————\n");
}
int main()
{
	pthread_t id;
	signal = 0;
	printf("已将共享数据初始化为：%d\n", signal );
	if (pthread_create(&id, NULL, thread, NULL)) //创造线程
	{
		printf("线程创建失败\n");
		return -1;
	}
	else
	{
		sleep(1);//挂起
		printf("线程创建成功\n");
		printf("共享数据更改为：%d\n", signal );
		printf("线程ID为：%lu\n", id);
	}
}

