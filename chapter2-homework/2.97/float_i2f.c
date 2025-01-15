/*Unfinished*/

#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_i2f(int x){
    int sign_all = (x >> 31);
    unsigned sign = (x >> 31) & 0x1;
    int y = (sign_all & (~x + 1)) | (~sign_all & x); // 全转化为正数
    unsigned exp = 0;
    unsigned frac = 0;
    unsigned bias = 127;
    int z = y;
    int b16, b8, b4, b2, b1, b0;
	b16 = !!(y >> 16) << 4;
	y = y >> b16;
	b8 = !!(y >> 8) << 3;
	y = y >> b8;
	b4 = !!(y >> 4) << 2;
	y = y >> b4;
	b2 = !!(y >> 2) << 1;
	y = y >> b2;
	b1 = !!(y >> 1);
	y = y >> b1;
	b0 = y;
  	int p = b16 + b8 + b4 + b2 + b1 + b0; // 第一个1的位置(下标认为从1开始)，对应float中的隐式1
    p--;
    if (p > 23){
        exp = p - 23 + bias;
        frac = (z >> (p - 23)) & 0x7FFFFF;
    }
    else{
        exp = bias;
    }
    return (sign << 31) | (exp << 23) | frac;
}

int main()
{

    return 0;
}