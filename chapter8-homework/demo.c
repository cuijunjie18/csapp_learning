#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXARGS 100005

int main()
{
    char *argv[MAXARGS];
    char *delim;
    // char *buf = "123 456 789 1 3 "; // 字符常量不可修改
    char args[] = "123 456 789 1 3 ";
    char *buf = args;
    int argc = 0;
    argc = 1;
    argc = 0;
    while ((delim = strchr(buf,' '))){
        argv[++argc] = buf;
        *delim = '\0'; // 切断buf后面的联系，即识别到'\0'字符串结尾
        buf = delim + 1;
        while (*buf && (*buf == ' ')) buf++;
    }
    printf("Argc : %d\n",argc);
    for (int i = 1; i <= argc; i++){
        printf("Argv[%d]: %s\n",i,argv[i]);
    }
    return 0;
}