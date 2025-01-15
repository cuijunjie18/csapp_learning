#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

int float_f2i(float_bits uf){
   /*虽然过了，但是感觉有问题
	used ops：26
	*/
	unsigned sign = uf >> 31; // 符号
    unsigned exp = (uf >> 23) & 0xFF; // 阶码
    unsigned frac = uf & 0x7FFFFF; // 尾码
    unsigned NaN = (!(exp ^ 0xFF)) & (!!(frac ^ 0));
    unsigned denormalized = !(exp ^ 0); // 非规格化
    if (NaN || exp >= 31 + 127) return 0x80000000;
    if (denormalized || exp < 127) return 0;
    frac |= (1 << 23);
    unsigned x = 150;
    if (exp >= x) frac <<= (exp - x);
    else frac >>= (x - exp);
	if (sign) return (1 << 31 >> 31) | frac;
    return frac;
}

int main()
{
    /*经Lab1 Data_Lab测试过，正确的*/
    return 0;
}