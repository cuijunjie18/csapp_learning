#include "csapp.h"

int main() 
{
    char command1[50] = "echo 666";
    char *argv[4] = {"","-c","echo 666",NULL}; // 最后一个
    int status = execv("/usr/bin/sh",argv);
    // char *argv[3] = {NULL,NULL,NULL};
    // execv(command1,argv);
    if (status == -1){
        printf("Execv Fail!\n");
    }
    return 0;
}
