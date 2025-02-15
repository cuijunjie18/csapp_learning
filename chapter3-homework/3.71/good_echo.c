#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN_SIZE 5

/*我的错误*/
// void good_echo(){
//     char buf[5];
//     char *p = fgets(buf,5,stdin);
//     puts(p);
// }

/*参考答案：要满足任意长度输入且不会产生缓冲区溢出*/
void good_echo(){
    char buf[MAXN_SIZE];
    while (1){
        char *p = fgets(buf,MAXN_SIZE,stdin);
        if (p == NULL) break;
        printf("%s",p);
    }
    printf("\n");
}

int main()
{
    good_echo();
    return 0;
}