如果将short、long、double的地址中的数据以char* 指针读取，即以char型数据解读对应地址的字节，那么
unsigned char 与 char有区别，char在负数赋值时%.2x输出会高位补1，输出4个字节