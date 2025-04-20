#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *env_name = "PATH";
    char *value = NULL;
    value = getenv(env_name);
    if (value == NULL){
        printf("NULL!\n");
    }
    else{
        printf("%s:\n%s\n",env_name,value);
    }
    return 0;
}