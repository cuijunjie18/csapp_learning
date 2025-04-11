#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[105] = "0000";
    int a[5];
    int ans = sscanf(str,"%d%d%d%d",a,a+1,a+2,a+3);
    printf("%d\n",ans);
    for (int i = 0; i < 4; i++) printf("%d ",a[i]);
    printf("\n");
    return 0;
}