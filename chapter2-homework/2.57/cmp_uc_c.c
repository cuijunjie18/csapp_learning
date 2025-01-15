#include <stdio.h>
#include <stdlib.h>

void show_bytes1(char* b,int len){
    // 低地址到高地址
    for (int i = 0; i < len; i++){
        printf("%.2x ",b[i]);
    }
    printf("\n");
}

void show_bytes2(unsigned char* b,int len){
    // 低地址到高地址
    for (int i = 0; i < len; i++){
        printf("%.2x ",b[i]);
    }
    printf("\n");
}

void show_short(short x){
    show_bytes1((char*) &x,sizeof(x));
    show_bytes2((unsigned char*) &x,sizeof(x));
}

int main()
{
    short x = 40292;
    show_short(x);
    return 0;
}