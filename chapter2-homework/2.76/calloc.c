#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void* calloc(size_t nmemb,size_t size){
    if (size == 0 || nmemb == 0) return NULL;
    void* p = (void*)malloc(nmemb * size);
    memset(p,0,nmemb * size);
    return p;
}

int main()
{
    int* a = (int*)calloc(sizeof(int),10);
    for (int i = 0; i < 10; i++) printf("%d ",a[i]);
    assert(calloc(0,100) == NULL);
    assert(calloc(1,0) == NULL);
    return 0;
}