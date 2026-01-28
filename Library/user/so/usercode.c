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

//动态库链接方式：
//1、拷贝至系统
//   cp -p ./lib/include/* /usr/include
//   cp -p ./lib/mylib/* /lib64
//
//2、建立软链接
//   ln -s $(pwd)/lib/mylib/libmyc.so /lib64/libmyc.so
//
//3、LD_LIBRARY_PATH
//   cd lib/mylib/
//   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
//
//4、/etc/ld.so.conf.d/
//   cd lib/mylib/
//   pwd > userso.conf
//   sudo mv userso.conf /etc/ld.so.conf.d/
//   sudo ldconfig      //重新加载配置
