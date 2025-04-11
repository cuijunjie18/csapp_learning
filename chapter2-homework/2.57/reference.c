#include <stdio.h>
#include <stdlib.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_short(short x) {
	show_bytes((byte_pointer)&x, sizeof(short));
}

void show_int(int x) {
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_long(long x) {
	show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x) {
	show_bytes((byte_pointer)&x, sizeof(double));
}

int main()
{
      short x = 12345;
    long y = 12345;
    double z= 12345;
    show_short(x);
    show_long(y);
    show_double(z);
    return 0;
}