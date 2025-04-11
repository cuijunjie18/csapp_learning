#include <stdio.h>
#include <stdlib.h>

struct {
    char *a;
    short b;
    double c;
    char d;
    float e;
    char f;
    long g;
    int h;
}rec;

struct {
    float e;
    int h;
    char *a;
    double c;
    long g;
    short b;
    char d;
    char f;
}rec_optimzed;


int main()
{
    printf("%lu,%lu\n",sizeof(rec),sizeof(rec_optimzed)); // 56 40
    return 0;
}