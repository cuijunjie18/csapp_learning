/*未考虑向偶数舍入问题*/
#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

typedef unsigned char* byte_pointer;

// 从高位开始输出展示
void show_bytes_big(byte_pointer p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

/*x?y:z*/
float_bits conditional(unsigned x,unsigned y,unsigned z){
    int flag = !!(x);
    int masky = flag << 31 >> 31;
    int maskz = ~masky;
    return (masky & y) | (maskz & z);
}

float_bits float_half(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned NaN = !(exp ^ 0xFF) & (!!(frac ^ 0)); // 判断NaN情况
    unsigned Maxn = !(exp ^ 0xFF) & (!(frac ^ 0)); // 无穷大(小)
    unsigned denormalized = !(exp ^ 0); // 非规则化
    unsigned minnormalized = !(exp ^ 1); // 最小规则化的exp
    exp = conditional(Maxn | denormalized,exp,exp - 1);
    frac = conditional(denormalized,frac >> 1,frac);
    frac = conditional(minnormalized,(frac >> 1) + (1 << 22),frac);
    unsigned half_f = (sign << 31) | (exp << 23) | frac;
    return conditional(NaN,f,half_f);
}

int main()
{
    assert(float_half(0x007FFFFF) == 0x003FFFFF); // 非规格数
    assert(float_half(0x83123456) == 0x82923456); // 一般负数
    assert(float_half(0x63123456) == 0x62923456); // 一般正数
    // float_bits test = float_half(0x7F800000);
    // unsigned x = 0x7F800000;
    // show_bytes_big((byte_pointer) &x,sizeof(x));
    // show_bytes_big((byte_pointer) &test,sizeof(test));
    assert(float_half(0x7F800000) == 0x7F800000); // 正无穷大
    assert(float_half(0xFF800000) == 0xFF800000); // 负无穷大
    assert(float_half(0xFF812345) == 0xFF812345); // NaN
    return 0;
}