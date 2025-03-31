#include <stdio.h>
#include <stdlib.h>

void bubble_a(long *data,long count){
    long i,last;
    for (last = count - 1;last > 0; last--){
        for (i = 0; i < last; i++){
            if (data[i + 1] < data[i]){
                long t = data[i + 1];
                data[i + 1] = data[i];
                data[i] = t;
            }
        }
    }
}

void bubble_b(long *data,long count){
    long i,last;
    for (last = count - 1; last > 0; last--){
        for (int i = 0; i < last; i++){
            if (*(data + i + 1) < *(data + i)){
                long t = *(data + i + 1);
                *(data + i + 1) = *(data + i);
                *(data + i) = t;
            }
        }
    }
}

void bubble_p(long* data, long count) {
    long *i, *last;
    for (last = data+count-1; last > data; last--) {
        for (i = data; i < last; i++) {
            if (*(i+1) < *i) {
                /* swap adjacent elements */
                long t = *(i + 1);
                *(i + 1) = *i;
                *i = t;
            }
        }
    }
  }

int main()
{
    long n = 10;
    long a[n];
    for (int i = 0; i < n; i++) a[i] = n - i;
    bubble_a(a,n);
    for (int i = 0; i < n; i++) printf("%d ",a[i]);
    printf("\n");
    for (int i = 0; i < n; i++) a[i] = n - i;
    bubble_b(a,n);
    for (int i = 0; i < n; i++) printf("%d ",a[i]);
    printf("\n");
    return 0;
}