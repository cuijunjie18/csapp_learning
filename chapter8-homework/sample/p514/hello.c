#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int test_params = 1;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr,"error!");
        exit(1);
    }
    else if (rc == 0){
        printf("I am son!hello,world!\n");
        printf("Son : %p\n",&test_params);
        test_params += 100;
        printf("Son : %d\n",test_params);
        printf("Son : %p\n",&test_params);
        exit(0);
    }
    printf("I am father!hello,world!\n");
    printf("Father : %p\n",&test_params);
    test_params -= 100;
    printf("Father : %d\n",test_params);
    printf("Father : %p\n",&test_params);
    return 0;
}