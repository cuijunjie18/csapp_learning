/* Starter function for tmult_ok */
/* Multiply arguments and indicate whether it did not overflow */
int tmult_ok_asm(long x, long y, long *dest) {
    long p = x * y;
    *dest = p;
    return p > 0;
}

int tmult_ok1(long x,long y,long *dest){
    int result;
    *dest = x * y;
    asm("setae %al");
    return result;
}

int tmult_ok2(long x,long y,long *dest){
    int result;
    *dest = x * y;
    asm ("setae %%bl\n\t"
         "movzbl %%bl,%[val]"
         : [val] "=r" (result) /*Output*/
         :  /*No inputs*/
         : "%bl" /*break protect*/
        );
    return result;
}

int tmult_ok3(long x,long y,long *dest){
    unsigned char bresult;
    *dest = x * y;
    asm("setae %[b]\n\t"
        : [b] "=r" (bresult)
        :
        : 
    );
    return (int) (bresult);
}

int umult_ok(unsigned long x,unsigned long y,unsigned long *dest){
    unsigned char result;
    asm("movq %[x],%%rax\n\t"
        "mulq %[y]\n\t"
        "movq %%rax,%[p]\n\t"
        "setae %[b]\n\t"
        : [p] "=r" (*dest), [b] "=r" (result)
        : [x] "r" (x), [y] "r" (y)
        : "%rax", "%rdx"
    );
    return result;
}

int my_test(long x,long y){
    asm("movq $21,%rdi");
    asm("movq %rsi,%rsi");
    return x;
}

int intumult_ok_asm(unsigned long x,unsigned long y,unsigned long *dest){
    unsigned long p = x * y;
    *dest = p;
    return p > 0;
}