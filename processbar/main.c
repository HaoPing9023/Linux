#include"process.h"

double total = 1024.0;
double speed = 1.0;

typedef void (*callback_t)(double total, double currnt);

void DownLoad(callback_t cb)
{
    double current = 0;
    while(current <= total)
    {
        cb(total, current);
        //下载代码
        usleep(3000);   //充当下载数据
        current += speed;
    }
    printf("\ndownload %.2lfMB Done\n", total);

}

void UpLoad(callback_t cb)
{
    double current = 0;
    while(current <= total)
    {
        cb(total, current);
        //下载代码
        usleep(3000);   //充当下载数据
        current += speed;
    }
    printf("\nupload %.2lfMB Done\n", total);
}

int main()
{
    //process_v1();
    DownLoad(FlushProcess);
    UpLoad(FlushProcess);
    return 0;
}
