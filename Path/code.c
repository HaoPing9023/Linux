#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **envrion;

int main(int argc, char *argv[], char *env[])
{
    (void)env;
    (void)argc;
    (void)argv;
    
    const char* who = getenv("USER");
    if(who == NULL) return 1;
    
    if(strcmp(who, "haoping") == 0)
        printf("这是我的程序\n");
    else 
        printf("Only haoping\n");


    //char* value = getenv("PATH");
    //if(value == NULL) return 1;
    //printf("PATH -> %s\n", value);

    //for(int i = 0; env[i]; ++i)
    //{
    //    printf("env[%d] -> %s\n", i, env[i]);
    //}

   // if(argc != 2)
   // {
   //     printf("Usage:%s[-a|-b|-c]\n", argv[0]);
   //     return 1;
   // }

   // const char *arg = argv[1];
   // 
   // if(strcmp(arg, "-a") == 0)
   //     printf("这是功能1\n");
   // else if(strcmp(arg, "-b") == 0)
   //     printf("这是功能2\n");
   // else if(strcmp(arg, "-c") == 0)
   //     printf("这是功能3\n");
   // else
   //     printf("Usage:%s[-a|-b|-c]\n", argv[0]);
    
    //for(int i = 0; i < argc; ++i)
    //{
    //    printf("argv[%d]:%s\n", i, argv[i]);
    //}
    
    return 0;
}

