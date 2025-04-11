#include <stdio.h>
#include <stdlib.h>

int my_test(int x,int y){
    int result;
    asm ("movl $21,%%edi\n\t"
         : 
         :
         : "%edi"
        );
    asm ("movl %%edi,%%esi\n\t"
         :
         :
         : "%esi"
        );
    asm("movl %%esi,%[val]\n\t"
        : [val] "=r" (result)
        :
        :
    );
    return result;
}

int main()
{
    int x = my_test(100,200);
    printf("%d\n",x);
    return 0;
}