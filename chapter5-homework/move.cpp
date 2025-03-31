#include <bits/stdc++.h>

using namespace std;

void show(unsigned char* p,int len){
    for (int i = len - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

int main()
{
    int n = INT32_MIN;
    show((unsigned char*) &n,sizeof(n));
    n <<= 1;
    show((unsigned char*) &n,sizeof(n));
    printf("%d\n",n);
    return 0;
}