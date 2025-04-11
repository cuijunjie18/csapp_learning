#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* The following function does not run properly on some machine */
/*
int bad_int_size_is_32() {
  int set_msb = 1 << 31;
  int beyond_msb = 1 << 32;

  return set_msb && !beyond_msb;
}
*/

int int_size_is_32(){
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = 1 << 15 << 15 << 2;
    return set_msb && !beyond_msb;
}

int main()
{
    assert(int_size_is_32() == 1);
    return 0;
}