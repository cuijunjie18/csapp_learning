#include <stdio.h>
#include <stdlib.h>

int odd_ones(unsigned x){
    /*
    思路：对应位置临时存储其包含1的奇偶情况，最后汇总在第0位
    */
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 0x00000001;
}

int main()
{
    printf("%d\n",odd_ones(0x10101011));
    printf("%d\n",odd_ones(0x11101011));
    return 0;
}