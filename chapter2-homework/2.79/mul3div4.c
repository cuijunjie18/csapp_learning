#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

/*注意负数除法的舍入即可*/
int mul3div4(int x){
    int y = (x << 1) + x;
    int neg = y & INT_MIN;
    (neg && (y = y + 4 - 1));
    return y >> 2;
}

int main()
{   
    int x = 0x87654321;
    assert(mul3div4(x) == x * 3 / 4);
    return 0;
}