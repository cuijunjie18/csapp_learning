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

float_bits float_negate(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned NaN = !(exp ^ 0xFF) & (!!(frac ^ 0)); // 判断NaN情况
    unsigned neg_f = ((~sign) << 31) | (exp << 23) | frac;
    return conditional(NaN,f,neg_f);
}

int main()
{
    assert(float_negate(0x83123456) == 0x03123456); // 一般负数->正数
    assert(float_negate(0x63123456) == 0xE3123456); // 一般正数->负数
    // float_bits test = float_negate(0x7F800000);
    // unsigned x = 0x7F800000;
    // show_bytes_big((byte_pointer) &x,sizeof(x));
    // show_bytes_big((byte_pointer) &test,sizeof(test));
    assert(float_negate(0x7F800000) == 0xFF800000); // 正无穷大->负无穷大
    assert(float_negate(0xFF800000) == 0x7F800000); // 负无穷大->正无穷大
    assert(float_negate(0xFF812345) == 0xFF812345); // NaN不变
    return 0;
}