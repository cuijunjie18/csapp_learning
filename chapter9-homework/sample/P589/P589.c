#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p1 = malloc(sizeof(int) * 4);
    int *p2 = malloc(sizeof(int) * 4);
    int *p3 = malloc(sizeof(int) * 4);
    printf("%p %p %p\n",p1,p2,p3);
    // int *temp = p2;
    free(p2);
    int *p4 = malloc(sizeof(int) * 4);
    printf("%p\n",p2);
    p2[0] = 100;
    printf("%d\n",p2[0]);
    // printf("%p %p\n",p4,temp);
    return 0;
}