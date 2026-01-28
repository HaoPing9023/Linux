#include"mystdio.h"
#include <string.h>
#include <unistd.h>

int main()
{
    MyFile *filep = MyFopen("./log.txt", "a");
    if(!filep)
    {
        printf("fopen error!\n");
        return 1;
    }

    int cnt = 10;
    while(cnt--)
    {
        char *msg = (char*)"hello myfile!!!";
        MyFwrite(filep, msg, strlen(msg));
        MyFFlush(filep);
        printf("buffer: %s\n", filep->outbuffer);
        sleep(1);
    }
    MyFclose(filep); // FILE *fp

    return 0;
}


//编译为.o文件
//gcc -c *c
//
//打包归档
//ar -rc libmyc.a *.o
//
//链接使用
//gcc usercode.c -I ./头文件路径 ./静态库路径 -l库名称(归档时的名称去掉lib和.a,如libmyc.a 最后静态库名称为myc)
//gcc usercode.c -I ./include ./lib -lmyc       //默认生成a.out, 可以使用 -o 指定名称
//
//安装静态库
//sudo cp lib/include/* /usr/include/
//sudo cp lib/mylib/* /lib64
//安装后链接
//gcc usercode.c -lmyc
//
//查看关联库
//ldd a.out


