#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    scanf("%d",&a);
    int cnt = 0;
    int show[33];
    while (a){
        show[++cnt] = a%2;
        a /= 2;
    }
    for (int i = cnt; i >= 1; i--) printf("%d",show[i]);
    return 0;
}