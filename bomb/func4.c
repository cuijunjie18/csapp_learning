#include <stdio.h>
#include <stdlib.h>

int func4(int edi,int esi,int edx){
    int result = edx;
    result -= esi;
    unsigned int ecx = result;
    ecx >>= 31;
    result += ecx;
    result >>= 1;
    ecx = result + esi;
    if (ecx > edi){
        edx = ecx - 1;
        result = 2 * func4(edi,esi,edx);
        return result;
    }
    else{
        result = 0;
        if (ecx < edi){
            esi = ecx + 1;
            result = 2 * func4(edi,esi,edx) + 1;
            return result;
        }
        else{ // ecx == edi
            return result;
        }
    }
}

int func4_optim(int edi,int esi,int edx){
    /*esi first is 0;edx first is 14*/
    int result = edx - esi; // first 14
    unsigned ecx = result;
    ecx >>= 31; // first to 0
    result = (result + ecx) >> 1; // first to 7
    ecx = result + esi; // first to 7
    if (ecx > edi){
        return 2 * func4_optim(edi,esi,ecx - 1);
    }
    else if (ecx < edi) return 2 * func4(edi,ecx + 1,edx) + 1;
    else return 0;
}

int main()
{
    int x = func4(0,1,14);
    printf("%d\n",x);
    return 0;
}