#include"process.h"

#include<string.h>

#define NUM 101
#define STYLE '#'   //进度条图标

void FlushProcess(double total, double current)
{
    char buffer[NUM];   //进度条
    memset(buffer, 0, sizeof(buffer));
    const char* lable = "|/-\\";      //加载图标
    int len = strlen(lable);

    int num = (int)(current * 100 / total);   //进度条的进度（需要填充多少STYLE）
    for(int i = 0; i < num; ++i)
    {
        buffer[i] = STYLE;
    }
    
    static int cnf = 0;     //每次调用FlushProcess函数时cnf不变，目的是保持加载图标正常旋转
    cnf %= len;
    
    double rate = current / total;  //加载进度

    printf("[%-100s][%.1lf%%][%c]\r", buffer, rate * 100, lable[cnf++]);
    fflush(stdout);
}

void process_v1()
{
    int cnf = 0;
    char buffer[NUM];   //进度条
    memset(buffer, 0, sizeof(buffer));
    
    const char* lable = "|/-\\";      //旋转图标
    int len = strlen(lable);
    
    while(cnf <= 100)
    {
        printf("[%-100s][%d%%][%c]\r", buffer, cnf, lable[cnf % len]);
        fflush(stdout);     //刷新输出流（刷新缓存）
        buffer[cnf] = STYLE;
        ++cnf;
        usleep(50000);
    }
    printf("\n");

}
