#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

char* const argv[] = {
    (char* const)"other",
    (char* const)"-a",
    (char* const)"-b",
    (char* const)"-c",
    (char* const)"-d",
    NULL
};

char* const addenv[] = {
    (char* const)"MYVAL1=11111111111",
    (char* const)"MYVAL2=22222222222",
    (char* const)"MYVAL3=33333333333",
    NULL
};

int main()
{
    printf("我的程序开始了\n");
    if(fork() == 0)
    {
        //child进程
        printf("I am Child, My Pid Is : %d\n", getpid());
        sleep(1);
        
        for(int i = 0; addenv[i]; ++i)
        {
            putenv(addenv[i]);
        }

        extern **environ;
        execvpe("./other", argv, environ);

        //execv("other", argv);
        //execv("./other", argv);
        //execlp("ls", "ls", "-a", "-l", NULL);
        //execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
        //execl("./other", "other", NULL);
        //execl("/usr/bin/python3", "python", "other.py", NULL);
        exit(1);
    }
    
    waitpid(-1, NULL, 0);
    printf("我的程序结束了\n");
    
    return 0;
}
