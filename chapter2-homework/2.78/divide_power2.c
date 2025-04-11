#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

/*Divide by power of 2. Assume 0 <= k < w-1*/
int divide_power2(int x,int k){
    /*思路：c语言除法总是向零舍入，于是我们希望正数向下舍入，负数向上舍入，模拟c语言的舍入
        而右移动运算对于负数来说是向下舍入，如111101 = -3，右移1位111110 = -2，我们希望是-1;
    */
    int neg = x & INT_MIN; // 判断负数
    (neg && (x = x + (1 << k) - 1)); // 如果是负数先ceil一下
    return x >> k;
}

int main()
{
    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);
    return 0;
}