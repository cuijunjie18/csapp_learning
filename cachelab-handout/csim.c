/*
author : cuijunjie18
date : 
*/

// 忽略所有I开头的指令加载

#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define llu unsigned long long

// 命令行参数
int S = 1,E = 1,B = 1;
int verbose = 0; // 是否单步输出结果
int debug = 0; // 启动调试

// cache大小相关变量
int address_size = 36; // 地址值为36位二进制
int b_size = 1,s_size = 1,t_size = 0,valid_bit = 1;
int T = 4; // 标志区域用 unsigned 存
int row_size = 0; // 一行的字节数
int cache_size = 0; // cache总大小
unsigned char* cache; // 指向字节内存
unsigned* row_frame; // 行的时间戳数组

int frame_id = 0; // 时间戳

// // 状态
// enum run_state{HIT,MISS,EVICT,NONE};

int hits,misses,evictions;

void show_bytes(llu x){
    int nums[65];
    int cnt = 0;
    if (x == 0) printf("0");
    while (x){
        nums[++cnt] = x % 2;
        x /= 2;
    }
    for (int i = cnt; i >= 1; i--) printf("%d",nums[i]);
    printf(" ");
}

void Get_input(int argc,char *argv[],int *s_size,int *E,int *b_size, char **tracefile,int *verbose){
    int opt;
    // 定义选项字符串：h和v是标志，s/E/b/t需要参数
    const char *optstring = "hdvs:E:b:t:";
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 's':
                *s_size = atoi(optarg);  // 将字符串参数转为整数
                break;
            case 'E':
                *E = atoi(optarg);
                break;
            case 'b':
                *b_size = atoi(optarg);
                break;
            case 't':
                *tracefile = optarg;  // 直接保存文件路径
                break;
            case 'v':
                *verbose = 1;        // 设置详细模式标志
                break;
            case 'd':
                debug = 1;  //启动调试模式
                break;
            case 'h':
                printf("Usage: %s -s <s> -E <E> -b <b> -t <tracefile>\n", argv[0]);
                exit(0);
            case '?':
                // 处理错误选项或缺少参数
                fprintf(stderr, "Unknown option: -%c\n", optopt);
                exit(1);
            default:
                fprintf(stderr, "Unexpected error\n");
                exit(1);
        }
    }
    // printf("%s\n",*tracefile);
    if (*s_size == 0 || *E == 0 || *b_size == 0 || *tracefile == NULL){
        printf("Usage: %s -s <s> -E <E> -b <b> -t <tracefile>\n", argv[0]);
        exit(1);
    }
}

void cache_init(){
    cache = (unsigned char*) malloc(cache_size * sizeof(unsigned char)); // 单位为1个字节
    row_frame = (unsigned*) malloc(E * S * sizeof(unsigned)); // 单位为4个字节
    memset(cache,0,cache_size * sizeof(unsigned char)); // 全部设置为0
    memset(row_frame,0,E * S * sizeof(unsigned));
}

// 查看cache每一行的tag
void show_cache_tag(){
    unsigned char* p = cache;
    unsigned label = 0;
    for (int i = 0; i < S * E; i++){
        for (int j = 4; j >= 1; j--) label = (label << 8) + p[j];
        printf("%d:%u;",i,label);
        p += row_size;
    }
    printf("\n");
}

// 查看cache每一行的valid
void show_cache_valid(){
    unsigned char* p = cache;
    for (int i = 0; i < S * E; i++){
        printf("%d = %d;",i,p[0]);
        p += row_size;
    }
    printf("\n");
}

// 驱逐机制
void LRU(unsigned t,unsigned s,unsigned b){
    unsigned char* p = cache + s * E * row_size;
    unsigned *r = row_frame + s * E;
    int minn = 99999999; // 害群之马，低级错误，应该初始化为最大值，而不是0
    int index = 0;
    for (int i = 0; i < E; i++){
        if (r[i] < minn){
            minn = r[i];
            index = i;
        }
    }
    r[index] = frame_id;
    p += index * row_size;
    unsigned temp =  t;
    // 高地址存高位
    for (int i = 1; i <= 4; i++){
        p[i] = temp % 256;
        temp /= 256;
    }
}

// 加载到缓存
void load_to_cache(unsigned t,unsigned s,unsigned b){
    int flag = 0; // 是否有空行
    unsigned char* p = cache + s * E * row_size;
    unsigned *r = row_frame + s * E;

    // 在当前组查找空行
    for (int i = 0; i < E; i++){
        if (p[0] == 1){
            p += row_size;
            r++;
            continue; // 已经valid,跳过
        }
        // printf("%d empty!\n",i + s * E);
        flag = 1;
        p[0] = 1; // 标记为valid
        unsigned temp = t;
        for (int i = 1; i <= 4; i++){
            // 高地址存高位
            p[i] = temp % 256;
            temp /= 256;
        }
        *r = frame_id; // 记录时间戳
        break;
    }
    if (!flag){
        // printf("ALL cache full!\n");
        evictions++;
        if (verbose) printf("miss eviction ");
        LRU(t,s,b);
    }
    else{
        if (verbose) printf("miss ");
    }
    return;
}

// cache匹配
void Find(unsigned t,unsigned s,unsigned b){
    frame_id++; // 时间戳++

    unsigned char *p = cache + s * E * row_size;
    unsigned *r = row_frame + s * E;
    int flag = 0; // 是否找到
    unsigned label = 0;

    // 对当前组的每一行进行标志位匹配
    for (int i = 0; i < E; i++){
        // valid = 0,未缓存
        if (p[0] == 0){
            p += row_size;
            r++;
            continue; 
        }
        // 高地址存高位，提取出label
        for (int j = 4; j >= 1; j--){
            label = (label << 8) + p[j];
        }
        if (label == t){
            flag = 1;
            *r = frame_id; // 记录时间戳
            break;
        }
        p += row_size;
        r++;
    }
    if (!flag){
        misses++; // miss
        load_to_cache(t,s,b);
        // printf("Find nothing!");
    }
    else{
        // printf("Hit!\n");
        hits++; // hit
        if (verbose) printf("hit ");
    }
    return;
}

void Run_trace(FILE* fp){
    char opcode;
    unsigned long long address;
    int data_size; // 一般来说是数据对齐的，所以4个字节与8个字节的数据基本不会加载到两个不同的行中
    unsigned t,s,b;
    unsigned mask_b = 1;

    for (int i = 1,j = 1; i <= b_size; i++, j <<= 1) mask_b |= j;   
    while (fscanf(fp," %c %llx,%d",&opcode,&address,&data_size) > 0){
        if (opcode == 'I') continue;
        if (verbose) printf("%c %llx,%d ",opcode,address,data_size);
        t = (unsigned)(address) >> (s_size + b_size); // 截取高位
        b = (unsigned)(address) & mask_b; // 截取低位
        s = ((unsigned)(address) ^ (t << (s_size + b_size)) ^ b) >> b_size; // 计算中位
        // printf("tag:%u,s_index:%u\n",t,s);
        // continue;
        if (debug){
            printf("Debug:");
            printf("address = ");
            show_bytes(address);
            printf("t = ");
            show_bytes(t);
            printf("s = ");
            show_bytes(s);
            printf("b = ");
            show_bytes(b);
        }
        switch (opcode) {
            case 'S':
                Find(t,s,b);
                break;
            case 'L':
                Find(t,s,b);
                break;
            case 'M':
                Find(t,s,b);
                Find(t,s,b);
                break;
            default:
                break;
        }
        // show_cache_valid();
        // show_cache_tag();
        if (verbose) printf("\n");
        // fflush(stdout);
    }
}

int main(int argc,char *argv[])
{
    char **tracefile = (char**)malloc(sizeof(char*));
    *tracefile = NULL;

    Get_input(argc,argv,&s_size,&E,&b_size,tracefile,&verbose); // 解析命令行参数

    // 分配cache空间
    t_size = address_size - b_size - s_size;
    for (int i = 1; i <= s_size; i++) S *= 2;
    for (int i = 1; i <= b_size; i++) B *= 2;
    row_size = B + T + valid_bit; // 一行的字节数
    cache_size = S * E * row_size;
    cache_init();
    printf("(s,E,b) = %d %d %d\n",s_size,E,b_size);

    // 读取文件
    FILE* fp = NULL;
    // char prefix[20] = "traces/";
    // char *file_name = strcat(prefix,*tracefile); // 注意strcat不要重复调用
    printf("file = %s\n\n",*tracefile);
    // char file_name[50] = "traces/yi2.trace";
    fp = fopen(*tracefile,"r");
    if (fp == NULL){
        printf("Fail to open %s\n",*tracefile);
        exit(1);
    }

    // show_cache_valid();
    // show_cache_tag();
    Run_trace(fp); // 执行
    printSummary(hits, misses, evictions); // 结果

    // 释放
    fclose(fp);
    free(cache);
    free(row_frame);
    return 0;
}