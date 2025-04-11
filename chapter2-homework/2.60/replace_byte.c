#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

// 默认在小端机上运行
unsigned replace_byte(unsigned x,int i,unsigned char b){
    byte_pointer p = (byte_pointer) &x;
    p[i] = b;
    return x; 
}

// 从高位开始输出展示
void show_bytes_big(byte_pointer p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

int main()
{
    int x = 0x12345678;
    int ans = replace_byte(x,2,0xAB);
    show_bytes_big((byte_pointer) &x,sizeof(x)); // 先展示原来的x
    show_bytes_big((byte_pointer) &ans,sizeof(ans));
    ans = replace_byte(x,0,0xAB);
    show_bytes_big((byte_pointer) &ans,sizeof(ans));
    return 0;
}