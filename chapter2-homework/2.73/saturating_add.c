#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int TMax = 0x7FFFFFFF;
const int TMin = 0x80000000;

int posetive_over(int x,int y){
    // return x >= 0 && y >= 0 && x + y < 0 // 非位级运算表示
    // 判断正负，看符合位
    int w = sizeof(int) >> 3;
    int xp = (x >> (w - 1)) & 0x1;
    int yp = (y >> (w - 1)) & 0x1;
    int zp = ((x + y) >> (w - 1)) & 0x1;
    return (!xp) & (!yp) & zp;
}

int negative_over(int x,int y){
    // return x < 0 && y < 0 && x + y >= 0 // 非位级运算表示
    // 同posetive_over类似思路
    int w = sizeof(int) >> 3;
    int xp = (x >> (w - 1)) & 0x1;
    int yp = (y >> (w - 1)) & 0x1;
    int zp = ((x + y) >> (w - 1)) & 0x1;
    return xp & yp & (!zp);
}

/*饱和相加：负数溢出为TMin，正溢出为TMax*/
int saturating_add(int x,int y){
    int p_over = posetive_over(x,y);
    int n_over = negative_over(x,y);
    /*
    if (p_over) return TMax;
    else if (n_over) return TMin;
    else return x + y;
    非位级表示
    */
   int sum = x + y;
   (p_over && (sum = TMax)) || (n_over && (sum = TMin)); // ?什么用法，应该是位级条件语句(条件表达式)
    return sum;
}

int main()
{
    printf("%d\n%d\n",TMax,TMin);
    assert(TMax == saturating_add(TMax, 0x1234));
    assert(TMin == saturating_add(TMin, -0x1234));
    assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
    return 0;
}