#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str_save[105];
char input[105];

void phase_5(long rbx){
    /*rbx = 0x6038c0*/
    char stack[105]; // save reflect_str
    long a = 0;
    while (a < 6){
        int ecx = input[a]; // get input[a]
        stack[0] = ecx & 0x000000FF; // get ascii from ecx(only 8 bits),so stack[0] = input[a]
        long rdx = stack[0];
        rdx &= 0xF; // mask 0th~3th bits，make rdx [0,15]
        rdx = str_save[rdx];
        stack[0x10 + a] = rdx; // get reflect_str
        a++;
    }
}

int main()
{
    char input[105];
    phase_5(input);
    return 0;
}