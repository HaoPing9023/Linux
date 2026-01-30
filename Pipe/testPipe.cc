#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void Child_Write(int wfd)
{
    char buffer[1024];
    int cnf = 0;
    while (true)
    {
        snprintf(buffer, sizeof(buffer), "I am child, pid: %d, cnf: %d", getpid(), cnf++);
        write(wfd, buffer, strlen(buffer));
        sleep(1);
    }
}

void Father_Read(int rfd)
{
    sleep(1);
    char buffer[1024];
    while (true)
    {
        buffer[0] = 0;
        ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = 0;
            cout << "Child say : " << buffer << endl;
        }
        else if (n == 0)
        {
            cout << "n : " << n << endl;
            cout << "child 退出，我也退出";
            break;
        }
        else break;
    }
}


int main()
{
    int fds[2] = {0};
    int n = pipe(fds);
    if (n < 0)
    {
        cerr << "pipe error" << endl;
        return 1;
    }
    cout << "fds[0] : " << fds[0] << endl;
    cout << "fds[1] : " << fds[1] << endl;

    pid_t id = fork();
    if (id == 0)
    {
        // child
        //  f -> r, c -> w
        close(fds[0]);
        Child_Write(fds[1]);
        close(fds[1]);
        exit(1);
    }

    // father
    close(fds[1]);
    Father_Read(fds[0]);
    close(fds[0]);

    sleep(5);

    int status = 0;
    int ret = waitpid(id, &status, 0);

    if(ret > 0)
    {
        printf("exit code: %d, exit signal: %d\n", (status>>8)&0xFF, status&0x7F);
        sleep(5);
    }
    return 0;
}