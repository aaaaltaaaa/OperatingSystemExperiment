#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
sem_t bus, door; //两个同步信号量
int signal=1;//控制程序是否结束

void* control()//控制进程
{
	sleep(10);
	signal=0;
}

void* driver()//司机进程
{
	while (signal)
	{
		printf("车辆行驶中\n");
		sleep(1);
		printf("车辆到达站点\n");
		sem_post(&bus);//释放信号量bus
		sem_wait(&door);//请求信号量door
		printf("车辆离开站点\n");
	}
}
void* conductor() { //售票员进程
	while (signal)
	{
		sem_wait(&bus); //请求信号量bus
		printf("打开车门\n");
		printf("上下乘客并售票\n");
		sleep(1);
		printf("关闭车门\n");
		sem_post(&door); //释放信号量door
	}
}
int main()
{
	sem_init(&bus, 0, 0); //初始化信号量
	sem_init(&door, 0, 0);
	pthread_t tidDirver, tidConducter,tidControl;
	
	pthread_create(&tidControl, 0, control, 0);//创造控制线程
	pthread_create(&tidDirver, 0, driver, 0); //创造司机线程
	pthread_create(&tidConducter, 0, conductor, 0);//售票员线程

	pthread_join(tidDirver, (void**)0); //回收资源
	pthread_join(tidConducter, (void**)0);
	pthread_join(tidControl, (void**)0);
	
	return 0;
}
