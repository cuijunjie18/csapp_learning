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

float_bits float_absval(float_bits f){
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned NaN = !(exp ^ 0xFF) & (!!(frac ^ 0)); // 判断NaN情况
    unsigned abs_f = (exp << 23) | frac;
    return conditional(NaN,f,abs_f);
}

int main()
{
    assert(float_absval(0x83123456) == 0x03123456); // 一般负数
    assert(float_absval(0x63123456) == 0x63123456); // 一般正数
    // float_bits test = float_absval(0x7F800000);
    // unsigned x = 0x7F800000;
    // show_bytes_big((byte_pointer) &x,sizeof(x));
    // show_bytes_big((byte_pointer) &test,sizeof(test));
    assert(float_absval(0x7F800000) == 0x7F800000); // 正无穷大
    assert(float_absval(0xFF800000) == 0x7F800000); // 负无穷大
    assert(float_absval(0xFF812345) == 0xFF812345); // NaN
    return 0;
}