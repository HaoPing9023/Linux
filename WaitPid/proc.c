#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<errno.h>

typedef void (*func_t)();
#define NUM 5
func_t handlers[NUM + 1];

//任务
void DownLoad()
{
	printf("我是一个下载的任务\n");
}

void Flush()
{
	printf("我是一个刷新的任务\n");
}

void Log()
{
	printf("我是一个查看日志的任务\n");
}

void registerHandler(func_t h[], func_t f)
{
	int i = 0;
	for (; i < NUM; ++i)
	{
		if (h[i] == NULL) break;
	}
	if (i == NUM) return;
	h[i] = f;
	h[i + 1] = NULL;
}

int main()
{
    registerHandler(handlers, DownLoad);
    registerHandler(handlers, Flush);
    registerHandler(handlers, Log);

    pid_t id = fork();
    if(id == 0)
    {
        //子进程
        int cnt = 3;
        while(cnt)
        {
            printf("这是一个子进程, pid : %d, ppid : %d\n", getpid(), getppid());
            sleep(1);
            --cnt;
            //int *p = 0;
            //*p = 100;
        }
        exit(1);
    }
    //父进程
    while(1)
    {
        int status = 0;
        //pid_t rid = wait(NULL);
        //pid_t rid = waitpid(id, &status, 0);
        pid_t rid = waitpid(id, &status, WNOHANG);
        if(rid > 0)
        {
            printf("wait success, rid: %d, exit code : %d, exit signal : %d\n", rid, (status >> 8) & 0xFF, status & 0x7F);
            break;
        }
        else if(rid == 0)
        {
            //进行回调处理
            for(int i = 0; handlers[i]; ++i)
            {
                handlers[i]();
            }
            printf("本轮调用结束，子进程没有退出\n");
            sleep(1);
        }   
        else
        {
            printf("等待失败\n");
            break;
        }
    }
    return 0;
}
