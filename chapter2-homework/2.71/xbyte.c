#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned packet_t;

/*默认机器采用补码，且算术右移*/
int xbyte(packet_t word, int bytenum){
    /*利用算术右移的性质可以将要提取的字节左边补足符合位*/
    int maxnum = 3;
    return (int) word << ((maxnum - bytenum) << 3) >> (maxnum << 3);
}

int main()
{
    assert(xbyte(0x00112233, 0) == 0x33);
    assert(xbyte(0x00112233, 1) == 0x22);
    assert(xbyte(0x00112233, 2) == 0x11);
    assert(xbyte(0x00112233, 3) == 0x00);
    
    assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
    assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
    assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);
    return 0;
}