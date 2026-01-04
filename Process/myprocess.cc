#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int count = 5;
        while(count)
        {
            printf("我是子进程，我正在运行: %d\n", count);
            sleep(1);
            count--;
        }
    }
    else 
    {
        while(1)
        {
            printf("我是父进程，我正在运行...\n");
            sleep(1);
        }
    }
   // printf("我是一个进程, pid: %d\n", getpid());

   //// int x;
   //// scanf("%d", &x);
   // while(1)
   // {
   //     printf("hello bite\n");
   // }
    return 0;
}

