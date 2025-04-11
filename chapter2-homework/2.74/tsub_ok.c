#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

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

int tsub_ok(int x,int y){
    // bug：-y可能出错，当且仅当y = TMin时
    int p_over = posetive_over(x,-y);
    int n_over = negative_over(x,-y);
    return (!p_over) & (!n_over);
}

int main()
{
    assert(!tsub_ok(0x00, INT_MIN));
    assert(tsub_ok(0x00, 0x00));
    return 0;
}