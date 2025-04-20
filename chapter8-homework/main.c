#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv,char **envp)
{
    printf("Command-line arguments:\n");
    for (int i = 1; i < argc; i++){
        printf("    argv[%2d]: %s\n",i - 1,argv[i]);
    } 
    printf("Environment variables:\n");
    for (int i = 0; envp[i] != NULL; i++){
        printf("    envp[%2d]: %s\n",i,envp[i]);
    }
    return 0;
}