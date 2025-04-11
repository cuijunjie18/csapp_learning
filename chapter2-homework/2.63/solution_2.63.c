#include <stdio.h>
#include <stdlib.h>

typedef unsigned char* byte_pointer;

// 从高位开始输出展示
void show_bytes_big(byte_pointer p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

// 用算术右移实现逻辑右移
unsigned srl(unsigned x,int k){
    unsigned xsra = (int) x >> k;
    unsigned one = (~0) >> k; // 生成高k位为0，其余全1的无符号类型
    unsigned ans = one & xsra;
    return ans;
}

// 用逻辑右移实现算术右移
int sra(int x,int k){
    int xsrl = (unsigned) x >> k;
    int neg = (((unsigned) x) >> ((sizeof(x) << 3) - 1)); // 获取符号位，1为负数
    int mask = neg << ((sizeof(x) << 3) - 1) >> (k - 1); // 构造高k位为neg，其余为0的mask
    return xsrl | mask;
}

int main()
{
    /*测试srl*/
    unsigned x1 = 0xFF123456;
    unsigned x2 = 0x00123456;
    unsigned a = srl(x1,4);
    unsigned b = srl(x2,4);
    show_bytes_big((byte_pointer) &a,sizeof(a));
    show_bytes_big((byte_pointer) &b,sizeof(b));

    /*测试sra*/
    int x3 = 0x00123456;
    int x4 = 0xFF123456;
    int c = sra(x3,4);
    int d = sra(x4,4);
    show_bytes_big((byte_pointer) &c,sizeof(c));
    show_bytes_big((byte_pointer) &d,sizeof(d));
    return 0;
}
