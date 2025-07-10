#include <stdio.h>
#include <stdlib.h>

void usage(){
    printf("execute the program in the following format:\n./dd2hex xxx.xxx.xxx.xxx\n");
    exit(0);
}

int main(int argc,char *argv[])
{
    if (argc != 2) usage();

    // 获取参数
    char *dd = argv[1];
    int ip = 0;
    printf("0x");
    for (int i = 0; dd[i] != '\0'; i++){
        if (dd[i] == '.'){
            printf("%x",ip);
            ip = 0;
            continue;
        }
        ip = ip * 10 + dd[i] - '0';
    }
    printf("%x\n",ip);
    return 0;
}