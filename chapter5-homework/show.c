#include <stdio.h>
#include <stdlib.h>

void show(unsigned char* p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

char hex[4];

int main()
{   
    // float n = -925;
    // show((unsigned char*) &n,sizeof(n));
    unsigned char hex[4];
    hex[0] = 0x00;
    hex[1] = 0x00;
    hex[2] = 0x01;
    hex[3] = 0xc4;
    float *n = (float *) hex;
    printf("%f\n",*n);
    return 0;
}