#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int gval = 100;

int main()
{
    printf("父进程开始运行,pid: %d\n", getpid());
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        return 1;
    }
    else if(id == 0)
    {
        printf("我是一个子进程 !, 我的pid: %d, 我的父进程id: %d, gval: %d\n", getpid(), getppid(), gval);
        sleep(5);
        // child
        while(1)
        {
            sleep(1);
            printf("子进程修改变量: %d->%d", gval, gval+10);
            gval+=10; // 修改
            printf("我是一个子进程 !, 我的pid: %d, 我的父进程id: %d\n", getpid(), getppid());
        }
    }
    else
    {
        //father
        while(1)
        {
            sleep(1);
            printf("我是一个父进程 !, 我的pid: %d, 我的父进程id: %d, gval: %d\n", getpid(), getppid(), gval);
        }
    }
    printf("进程开始运行,pid: %d\n", getpid());

  //  chdir("/home/whb");
  //  fopen("hello.txt", "a");
  //  while(1)
  //  {
  //      sleep(1);
  //      printf("我是一个进程 !, 我的pid: %d, 我的父进程id: %d\n", getpid(), getppid());
  //  }
}

