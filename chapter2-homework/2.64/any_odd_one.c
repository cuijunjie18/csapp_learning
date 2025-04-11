#include <stdio.h>
#include <stdlib.h>

int any_odd_one(unsigned x){
    // 假设w(unsigned) = 32
    unsigned fill_even = 0x55555555;
    return !(~(fill_even | x));
}

int main()
{
    unsigned d = 0xAAAAAAAA;
    printf("%d\n",any_odd_one(d));
    return 0;
}