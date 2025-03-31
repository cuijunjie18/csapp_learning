#include <stdio.h>
#include <stdlib.h>

int get_nums(){
    return 100;
}

int test_a(){
    int x = 0;
    for (int i = 0; i < get_nums(); i++) x++;
    return x;
}

int test_b(){
    int x = 0;
    int nums = get_nums();
    for (int i = 0; i < nums; i++) x++;
    return x;
}

int main()
{
    int a = test_a();
    int b = test_b();
    printf("%d,%d\n",a,b);
    return 0;
}