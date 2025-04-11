#include <stdio.h>
#include <stdlib.h>

void show_bytes(unsigned char* b,int len){
    // 低地址到高地址
    for (int i = 0; i < len; i++){
        printf("%.2x ",b[i]);
    }
    printf("\n");
}

void show_short(short x){
    show_bytes((unsigned char*) &x,sizeof(x));
}

void show_long(long x){
    show_bytes((unsigned char*) &x,sizeof(x));
}

void show_double(double x){
    show_bytes((unsigned char*) &x,sizeof(x));
}

int main()
{
    short x = 12345;
    long y = 12345;
    double z= 12345;
    show_short(x);
    show_long(y);
    show_double(z);
    return 0;
}
