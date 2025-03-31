#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_bytes(unsigned char *p,int length){
    for (int i = length - 1; i >= 0; i--){
        printf("%.2x ",p[i]);
    }
    printf("\n");
}

/*Basic implementation of memset*/
void *basic_memset(void *s,int c,size_t n){
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n){
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

void *optim_memset(void *s,int c,size_t n){
    long long address = s; // 获取起始地址值

    // 对齐到8字节(long long大小)
    unsigned char *schar = s;
    while (address % 8){
        *schar++ = (unsigned char) c;
        n--;
        address++;
    }

    // 一次拷贝8字节
    unsigned long long *sll = schar;
    while (n >= 8){
        *sll++ = (unsigned long long) c;
        n -= 8;
    }

    // 处理剩下的字节
    schar = sll;
    while (n){
        *schar++ = (unsigned char) c;
        n--;
    }
    return s;
}

void Test()
{
    int a[105];
    int n = sizeof(a) / sizeof(int);
    for (int i = 0; i < n; i++) a[i] = i;
	optim_memset(a,0,sizeof(a));
	for (int i = 0; i < n; i++) printf("%d ",a[i]);
	printf("\n");
	return;
}

int main()
{
    // int a[10];
    // long long b[10];
    // long long x = b; // 可以直接赋地址值
    // // printf("%d,%d,%d\n",sizeof(int),sizeof(a),sizeof(b));
    // // printf("%p\n",a);
    // // printf("%p\n",b);
    // // printf("%ld\n",x);
    // // show_bytes((unsigned char *) &x,sizeof(x));
    // char *p = a;
    // printf("%p\n",p);
    // p++;
    // printf("%p\n",p);
    Test();
    return 0;
}
