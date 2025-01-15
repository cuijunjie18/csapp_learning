#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void copy_int(int val, void* buf, int maxbytes){
    /*
    sizeof(val) returns type size_t, it usually is a kind of unsigned type.
    And it always >= 0.
    So we should convert the unsigned to int.
    */
    if (maxbytes - (int) sizeof(val) >= 0){
        memcpy(buf,(void *)&val,sizeof(val));
    }
}

int main()
{
    int maxbytes = sizeof(int) * 10;
    void* buf = malloc(maxbytes);
    int val;

    val = 0x12345678;
    copy_int(val, buf, maxbytes);
    assert(*(int*)buf == val);

    val = 0xAABBCCDD;
    copy_int(val, buf, 0);
    assert(*(int*)buf != val);

    free(buf);
    return 0;
}