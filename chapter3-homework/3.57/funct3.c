#include <stdio.h>
#include <stdlib.h>

double funct3(int *ap,double b,long c,float *dp){
    double res;
    float v1 = *dp;
    double v2 = (double) (*ap);
    if (b - v2 > 0){
        float v4 = (float) c;
        float v5 = v4 * v1;
        res = (double) v5;
    }
    else{
        v1 *= 2;
        float v3 = (float) c;
        v3 += v1;
        res = (double) v3;
    }
    return res;
}

double funct3_optim(int *ap,double b,long c,float *dp){
    double res;
    float v1 = *dp;
    if (b - (double) (*ap) > 0){
        float v2 = (float) c * v1;
        res = (double) v2;
    }
    else{
        float v3 = (float) c + v1 * 2;
        res = (double) v3;
    }
    return res;
}

double funct3_ans(int *ap,double b,long c,float *dp){
    int a = *ap;
    float d = *dp;
    if (a < b) return c * d;
    else return c + 2 * d;
}