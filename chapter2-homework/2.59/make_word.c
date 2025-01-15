#include <stdio.h>
#include <stdlib.h>

typedef unsigned char* byte_pointer;

int is_little_endian(){
    int x = 12345;
    byte_pointer t = (byte_pointer) &x;
    int check = t[0];
    if (check == 57) return 1; // 小端
    else return 0; // 大端
}

byte_pointer make_word(int x,int y){
    int len = sizeof(int); // 获取待生成的字节数
    byte_pointer xp = (byte_pointer) &x;
    byte_pointer yp = (byte_pointer) &y;
    byte_pointer ans = (byte_pointer)malloc(len);
    if (is_little_endian()){
        ans[0] = xp[0];
        for (int i = 1; i <= len; i++) ans[i] = yp[i];
    }
    else{
        ans[len - 1] = xp[len - 1];
        for (int i = 0; i < len - 1; i++) ans[i] = yp[i];
    }
    return ans;
}

int main()
{
    int x = 0x89ABCDEF;
    int y = 0x76543210;
    byte_pointer ans = make_word(x,y);
    if (is_little_endian()){
        for (int i = sizeof(int) - 1; i >= 0; i--) printf("%.2x ",ans[i]);
    }
    else{
        for (int i = 0; i < sizeof(int); i++) printf("%.2x ",ans[i]);
    }
    return 0;
}