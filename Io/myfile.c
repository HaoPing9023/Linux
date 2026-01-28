#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

//重定向
int main(int argc, char* argv[])
{
    //将标准输入（键盘）重定向到argv[1]中
    if (argc != 2) exit(1);

    int fp = open(argv[1], O_RDONLY);
    if (fp < 0) exit(2);
    
    dup2(fp, 0);
    close(fp);

    while (1)
    {
        char buffer[128];
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        printf("%s", buffer);
    }



    ////将标准输出（显示器）重定向到log.txt中
    ////用fp获取log.txt的下标
    //int fp = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    //if(fp < 0) exit(1);
    //
    ////将 标准输出 指向 fp 指向的 位置
    ////此时fp 和 标准输出stdout(fd = 1) 指向同一块窗口号
    ////如果 1 号 fd 已经打开（屏幕），先把它关掉
    ////让 1 号 fd 变成 oldfd 的一个“副本”（指向同一个底层对象）
    //dup2(fp, 1);

    //close(fp);

    //printf("Hello 重定向\n");
    //fprintf(stdin, "Hello 重定向\n");
    return 0;
}



//int main()
//{
//    umask(0);
//    
//    //读取
//    int fp = open("log.txt", O_RDONLY);
//    if(fp < 0)
//    {
//        perror("open");
//        return 1;
//    }
//    printf("fp:%d\n", fp);
//    
//    //开始读取
//    while(1)
//    {
//        char buffer[128];
//
//        //从fp读， 在buffer中显现，预计长度为buffer的长度，-1预留'\n'的位置
//        int n = read(fp, buffer, sizeof(buffer) - 1);
//        if(n > 0)   //若读取到字符
//        {
//            //等价于buffer[n] = '\0'
//            buffer[n] = 0;  //在字符串末尾添加'\0'，
//            printf("%s\n", buffer);
//        }
//        else if(n == 0) 
//        {
//            break;
//        }
//    }
//    
//
//
//
//    
// //   //写入
// //   int fp = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
//
// //   //若打开失败
// //   if(fp < 0)
// //   {
// //       perror("open");
// //       return 1;
// //   }
// //   printf("fp:%d\n", fp);
// //   
// //   //开始写入
// //   int cnt = 3;
// //   int a = 123456;
// //   
// //   while(cnt)
// //   {
// //       char buffer[128];
// //
// //       //格式化a为字符串形式，存入buffer中
// //       snprintf(buffer, sizeof(buffer), "%d", a);
// //
// //       //写入到fp中，从buffer中获取数据，长度为buffer的字符长度
// //       write(fp, buffer, strlen(buffer));
// //       cnt--;
// //   }
// //   
// //   close(fp);
//}
////int main()
////{
////    FILE* fp = fopen("log.txt", "w");
////    if(fp == NULL)
////    {
////        perror("fopen");
////        return 1;
////    }
////    
////    const char* msg = "Hello file:";
////    int cnf = 1;
////    while(cnf <= 10)
////    {
////        char buffer[1024];
////        snprintf(buffer, sizeof(buffer), "%s%d\n", msg, cnf++);
////        fwrite(buffer, strlen(buffer), 1, fp);
////    }
////
////    fclose(fp);
////    return 0;
////}
