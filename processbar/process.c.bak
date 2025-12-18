#include"process.h"

#include<unistd.h>
#include<string.h>

#define NUM 101
#define STYLE '#'

void process_v1()
{
    int cnf = 0;
    char buffer[NUM];
    memset(buffer, 0, sizeof(buffer));
    
    while(cnf <= 100)
    {
        printf("[%-100s][%d%%]\r", buffer, cnf);
        fflush(stdout);
        buffer[cnf] = STYLE;
        ++cnf;
        usleep(50000);
    }
    printf("\n");

}
