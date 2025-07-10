#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(){
    printf("execute the program in the following format:\n./hex2dd 0x<8-hex>\n");
    exit(0);
}

char toupper(char a){
    if (a > 'z' || a < 'a') return a;
    return a + 'Z' - 'z';
}

void check(char *hex){
    int len = strlen(hex);
    if (len != 10) usage();
    if (hex[0] != '0' || hex[1] != 'x') usage();
    for (int i = 2; i < len; i++){
        if ((hex[i] >= '0' && hex[i] <= '9') || 
            ((toupper(hex[i]) >= 'A') && (toupper(hex[i]) <= 'F'))) continue;
        usage();
    }
}

int GetNum(char a,char b){
    int x = 0,y = 0;
    if (a >= '0' && a <= '9') x = a - '0';
    else x = toupper(a) - 'A' + 10;
    if (b >= '0' && b <= '9') y = b - '0';
    else x = toupper(b) - 'A' + 10;
    return x * 16 + y;
}

int main(int argc,char *argv[])
{
    if (argc != 2) usage();

    // 获取参数
    char *hex = argv[1];
    check(hex);

    // 解析ip
    int ip[4];
    for (int i = 0; i < 4; i++){
        char a = hex[2 * (i + 1)];
        char b = hex[2 * (i + 1) + 1];
        ip[i] = GetNum(a,b);
    }
    printf("%d",ip[0]);
    for (int i = 1; i < 4; i++) printf(".%d",ip[i]);
    printf("\n");
    return 0;
}

