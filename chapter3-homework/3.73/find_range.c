#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum{NEG,ZERO,POS,OTHER} range_t;

// range_t find_range_origin(float x){
//     int result;
//     if (x < 0) result = NEG;
//     else if (x == 0) result = ZERO;
//     else if (x > 0) result = POS;
//     else result = OTHER;
//     return result;
// }

range_t find_range(float x){
    /*如果不用复合形式，即后面加输入输出列表的，寄存器一个%就OK了*/
    asm("vxorps %xmm1,%xmm1,%xmm1\n\t"
        "vucomiss %xmm0,%xmm1\n\t"
        "ja .A\n\t"
        "jp .B\n\t"
        "movl $1,%eax\n\t"
        "je .C\n\t"
        ".B:\n\t"
        "setbe %al\n\t"
        "movzbl %al,%eax\n\t"
        "addl $2,%eax\n\t"
        "ret\n\t"
        ".A:\n\t"
        "movl $0,%eax\n\t"
        ".C:\n\t"
        "rep;ret"
    );
}

int main()
{
    range_t n = NEG, z = ZERO, p = POS, o = OTHER;
    // assert(o == find_range(0.0/0.0));
    assert(n == find_range(-2.3));
    assert(z == find_range(0.0));
    assert(p == find_range(3.33));
    return 0;
}