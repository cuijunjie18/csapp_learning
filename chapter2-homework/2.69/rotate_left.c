#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Do rotate left shift. Assume 0 <= n < w
 * Example when x = 0x12345678 and w = 32:
 *   n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */
unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(unsigned) >> 3;
    unsigned y = x << n;
    // unsigned cut = x >> (w - n); // 这里有问题，如果n = 0，就会 >> overflow!
    unsigned cut = x >> (w - n - 1) >> 1; 
    return y | cut;
}

int main()
{
    assert(rotate_left(0x12345678,4) == 0x23456781);
    assert(rotate_left(0x12345678,20) == 0x67812345);
    return 0;
}