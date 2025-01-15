#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

/*截断乘积高w位*/
int signed_high_prod(int x,int y){
    int64_t mul = (int64_t) x * y;
    return mul >> 32;
}

/*不是很理解!*/
unsigned unsigned_high_prod(unsigned x, unsigned y) {
  /* TODO calculations */
  int sig_x = x >> 31;
  int sig_y = y >> 31;
  int signed_prod = signed_high_prod(x, y);
  return signed_prod + x * sig_y + y * sig_x; // 利用了(2-18)式中的公式
}

/* a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

int main()
{
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;

    assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;
}