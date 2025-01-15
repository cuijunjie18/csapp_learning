#include <stdio.h>
#include <assert.h>

void create(int k,int j){
    int x = -1 << k; // A表达式
    int y = ~(-1 << k) << j; // B表达式
}

int main()
{
    return 0;
}