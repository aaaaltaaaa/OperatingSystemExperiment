#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
	int fd[2];//读写标记数组
	int ret = pipe(fd); //创建管道
	if (ret == -1)
	{
		perror("创建管道失败\n");
		return 1;
	}
	pid_t id = fork(); //创建父进程和子进程
	if (id == 0)
	{	//子进程显示进程号
		close(fd[0]);//子进程关闭读通道
		printf("子进程的进程标识码为：%d\n ", getpid());
		int i = 0;
		for (int i = 0; i < 3; ++i)
		{
			{	//往写通道里写入三次指定字符串
				char* imformation = "子进程信息";
				write(fd[1], imformation, strlen(imformation) + 1);
				sleep(2);//挂起
				i++;
			}

		}
	}
	else if (id > 0)
	{
		close(fd[1]);//父进程关闭写通道
		char msg[100];
		printf("父进程的进程标识码为：%d\n", getpid()); //说明信息
		int j = 0;
		while (j < 5)
		{
			memset(msg, '\0', sizeof(msg));
			ssize_t s = read(fd[0], msg, sizeof(msg)); //从管道读取子进程写入的内容
			if (s > 0)
			{
				msg[s - 1] = '\0';
				printf("已获得子进程信息：");
			}
			printf("%s\n", msg); //显示读到的信息
			j++;
		}
	}
	else
	{
		perror("创建进程失败\n");
		return 2;
	}
	return 0;
}
