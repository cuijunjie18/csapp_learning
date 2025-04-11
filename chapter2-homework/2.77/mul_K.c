#include <stdio.h>
#include <assert.h>

int mul_K(int x,int k){
    switch (k)
    {
        case 17:
            return (x << 4) + x;
        case -7:
            return -((x << 3) - x);
        case 60:
            return (x << 6) - (x << 2);
        case -112:
            return -((x << 7) - (x << 4)); 
        default:
            return 0;
    }
}

int main()
{
    int x = (10 << 4) + 10;
    int y = 10 << 4 + 10;
    assert(x != y); // 注意x != y，+-运算级高于<< >>
    assert(mul_K(10,17) == 170);
    assert(mul_K(10,-7) == -70);
    assert(mul_K(10,60) == 600);
    assert(mul_K(10,-112) == -1120);
    return 0;
}