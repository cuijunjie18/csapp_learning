#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int agrc,char **argv,char **envp)
{
    char filename[40] = "/usr/bin/ls";
    int status = execv(filename,argv);
    if (status == -1){
        printf("Fail to exce %s\n",filename);
        exit(1);
    }
    return 0;
}