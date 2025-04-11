#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long cread(long* xp){
    return xp ? *xp : 0;
}

long cread_alt(long* xp){
    return !xp ? 0 : *xp;
}

int main()
{
    printf("Hello,world!\n");
    long a = 0;
    assert(cread(&a) == cread_alt(&a));
    assert(cread(NULL) == cread_alt(NULL));
    return 0;
}