#include <stdio.h>
#include <stdlib.h>

int is_shift_are_arithmetic()
{
    /*思路：定义一个负数，右移后截断最高位，若为1则算术，否则逻辑*/
    int x = -1; // 定义一个负数
    x = (x >> 1);
    int len = sizeof(x);
    int cut = 1 & (x >> ((len >> 3) - 1));
    return cut;
}

int main()
{
    printf("%d\n",is_shift_are_arithmetic());
    return 0;
}