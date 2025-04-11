#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int leftmost_one(unsigned x){
    /*
    思路：先构造最高位1右边全1的数即[0001...]->[000111...111]
    */
   x |= x >> 1; // 如果有高位1，至少得到了2位1
   x |= x >> 2; // 同理，得到的2位1继续往右复制
   x |= x >> 4;
   x |= x >> 8;
   x |= x >> 16;
   return x ^ (x >> 1); // 仅保留最高位1
}

int main()
{
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
    assert(leftmost_one(0x0001) == 0x0001);
    assert(leftmost_one(0x0) == 0x0);
    assert(leftmost_one(0x80000000) == 0x80000000);
    return 0;
}