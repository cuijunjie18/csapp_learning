#include <stdio.h>
#include <stdlib.h>

typedef unsigned char* byte_pointer;

int is_little_endian(){
    int x = 12345;
    byte_pointer t = (byte_pointer) &x;
    // char* t = (char*) &x;
    // for (int i = 0; i < sizeof(x); i++){
    //     printf("%.2x ",t[i]);
    // }
    // printf("\n%x",t); // 输出的是t的值，即x存储的地址
    //printf("\n%x",t[0]); // 对应字节处的16进制值
    // t[0] = 0x81; // 直接修改对应地址的字节值
    //printf("\n%x",t[0]); // 检测是否变化

    // int 为 4个字节，高3位字节补0(因为39(16进制)最高位为0，其实unsigned char肯定是补0，char则看最高位)，最终结果应该是57
    int check = t[0];
    // printf("%d\n",check);
    if (check == 57) return 1; // 小端
    else return 0; // 大端
}

int main()
{
    if (is_little_endian()){
        printf("This machine is little_endian!\n");
    }
    else{
        printf("This machine is big_endian!\n");
    }
    return 0;
}