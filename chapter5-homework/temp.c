#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func_a(){
    double x = 0;
    for (int i = 0; i < 100000000; i++){
        x += sin((double)i);
    }
    return x;
}

double func_b(){
    double x = 0;
    for (int i = 0; i < 1000000000; i++){
        x += sin((double)i);
    }
    return x;
}

int main()
{
    double y = func_a();
    double z = func_b();
    printf("%f,%f\n",y,z);
    return 0;
}