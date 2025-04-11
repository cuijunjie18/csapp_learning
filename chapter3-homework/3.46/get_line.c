#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_line(){
    char buf[4];
    char *result;
    gets(buf);
    result = (char *)malloc(strlen(buf));
    strcpy(result,buf);
    return result;
}

int main()
{
    get_line();
    printf("Hello,world!");
    return 0;
}