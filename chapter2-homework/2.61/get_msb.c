#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

// 从高位开始输出展示
void show_bytes_big(byte_pointer p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

int get_msb(int x){
    int shift_val = (sizeof(int) - 1) << 3;
    int x_right = x >> shift_val;
    return x_right & 0xFF;
}

int main()
{
    int x = 0x12345678;
    int y = get_msb(x);
    show_bytes_big((byte_pointer) &x,sizeof(x));
    show_bytes_big((byte_pointer) &y,sizeof(y));
    return 0;
}