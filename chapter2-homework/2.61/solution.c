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

// 获取int型数据的最高位
int get_msb(int x){
    int shift_val = (sizeof(int) - 1) << 3;
    int x_right = x >> shift_val;
    return x_right & 0xFF;
}

// 获取int型数据的最低位
int get_lsb(int x){
    int mask = 0x000000FF;
    return x & mask;
}

int check(int x){
    /*错误，不能用循环
    int check_A = 1,check_B = 1,check_C = 1,check_D = 1;
    for (int i = 0; i < (sizeof(int) << 3); i++){
        check_A &= (x >> i);
        check_B &= (~(x >> i));
    }
    int lsb = get_lsb(x);
    int msb = get_msb(x);
    for (int i = 0; i < (1 << 3); i++){
        check_C &= (lsb >> i);
        check_D &= (~(msb >> i));
    }
    return check_A | check_B | check_C | check_D;
    */
   int check_A = !~x;
   int check_B = !x;
   int check_C = !~(x | 0xFFFFFF00);
   int check_D = !(x & 0xFF000000);
   return check_A | check_B | check_C | check_D;
}
int main()
{
    int x = 0x12345678;
    int y = 0xFFFFFFFF;
    int z = 0x00000000;
    int a = 0x00124123;
    int b = 0x123456FF;
    printf("%d\n",check(x));
    printf("%d\n",check(y));
    printf("%d\n",check(z));
    printf("%d\n",check(a));
    printf("%d\n",check(b));
    return 0;
}