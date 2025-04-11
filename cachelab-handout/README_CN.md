以下是cachelab.pdf文件的中文翻译：
第1页

15-213/18-213，2012年秋季
缓存实验：理解缓存内存
发布时间：2012年10月2日，星期二
截止时间：2012年10月11日，23:59
最晚提交时间：2012年10月14日，23:59

1. 实验安排
   
    本实验为个人项目。
   
    必须在64位x86-64架构机器上完成。
   
    站点特定说明：请在此处插入其他安排细节（如如何寻求帮助）。

第2页
2. 实验概述

本实验旨在帮助理解缓存内存对C程序性能的影响。
实验分为两部分：

    Part A：编写一个约200-300行的C程序，模拟缓存内存的行为。
    
    Part B：优化矩阵转置函数，最小化缓存未命中次数。

3. 实验材料下载
   
    站点特定说明：此处应说明如何分发cachelab-handout.tar文件。
   
    将文件复制到Linux目录后解压：
   
   ```bash
   linux> tar xvf cachelab-handout.tar  
   ```
   
    修改文件：csim.c（缓存模拟器）和trans.c（转置函数）。
   
    编译命令：
   
   ```bash
   linux> make clean  
   linux> make  
   ```

警告：请勿使用Windows工具（如WinZip）解压，避免数据丢失。
第3页

1. 实验描述
   参考跟踪文件（Trace Files）
   
    位于traces/目录，由valgrind生成。
   
    跟踪文件格式示例：
   
   ```txt
   I 0400d7d4,8        # 指令加载  
   M 0421c7f0,4        # 数据修改（加载+存储）  
   L 04f6b868,8        # 数据加载  
   S 7ff0005c8,8       # 数据存储  
   ```
   
    操作类型：I（指令）、L（加载）、S（存储）、M（修改）。

Part A：编写缓存模拟器

在csim.c中实现模拟器，接受与参考程序csim-ref相同的命令行参数，输出命中（hits）、未命中（misses）和驱逐（evictions）次数。

命令行参数：

```bash
./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>  
```

-s <s>：组索引位数（组数 S=2sS=2s）
-E <E>：关联度（每组行数）
-b <b>：块位数（块大小 B=2bB=2b）

第4页
Part A编程规则

    在csim.c文件头注释中注明姓名和登录ID。
    
    代码必须无警告编译。
    
    使用malloc动态分配数据结构，支持任意s,E,bs,E,b。
    
    仅处理数据缓存：忽略所有I开头的指令加载。
    
    调用printSummary(hit_count, miss_count, eviction_count)输出结果。
    
    假设内存访问对齐，忽略请求大小。

Part B：优化矩阵转置

    目标：在trans.c中实现transpose_submit函数，最小化缓存未命中。
    
    给定函数原型：
    ```c
    
    void transpose_submit(int M, int N, int A[N][M], int B[M][N]);  
    
    ```
    
    规则：
    
        最多使用12个int类型局部变量。
    
        禁止使用递归、数组或malloc。
    
        禁止修改数组A，仅能操作B。

第5页

1. 评分标准
   
    总分：60分
   
        Part A：27分（8个测试用例）
       
        Part B：26分（性能评分）
       
        代码风格：7分

Part A评分

    每个测试用例的命中、未命中和驱逐次数需与参考结果完全一致。
    
    示例测试命令：
    ```bash
    ./csim -s 1 -E 1 -b 1 -t traces/yi2.trace  
    ```

Part B评分

    针对三种矩阵规模优化：
    
        32×32：未命中数 m<300 得8分，m>600 得0分。
    
        64×64：m<1300 得8分，m>2000 得0分。
    
        61×67：m<2000 得10分，m>3000 得0分。

第6页
1. 实验步骤
Part A调试建议

    使用小规模跟踪文件（如traces/dave.trace）调试。
    
    参考csim-ref的-v模式输出详细信息。
    
    使用getopt解析命令行参数：
    
    ```c
    
    #include <getopt.h>  
    #include <stdlib.h>  
    #include <unistd.h>  
    
    ```

Part B调试建议

    使用分块（Blocking）技术减少冲突未命中。
    
    通过test-trans生成跟踪文件并分析：
    
    ```bash
    
    ./test-trans -M 32 -N 32  
    
    ```
    使用参考模拟器调试：
    
    ```bash
    
    ./csim-ref -v -s 5 -E 1 -b 5 -t trace.f0  
    
    ```

第7页

1. 提交说明
   
    每次运行make时，会生成userid-handin.tar文件，包含csim.c和trans.c。
   
    站点特定说明：此处应说明如何提交文件（如通过课程平台）。
   
    禁止使用Windows/Mac生成提交文件，仅接受.tar格式。

关键提示

    Part A核心：正确解析跟踪文件，实现LRU替换策略。
    
    Part B核心：分块优化（如32x32矩阵使用8x8分块），避免对角线冲突未命中。
    
    实验资源：
    
        分块技术文档：CS:APP Blocking Notes

如需进一步解释或代码示例，请随时提问！