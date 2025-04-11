origin_readme：This is an x86-64 bomb for self-study students. 

### 我的bomb实验解题思路

#### (0) 前置知识
**汇编语言、gdb调试、逆向工程**

#### (1) bomb_1

通过汇编代码判断出答案字符串的长度及起始地址即可，**核心理解函数：string_length()和string_not_equal()**.

#### (2) bomb_2

理解**sscanf()函数和read_six_numbers()**的工作原理，然后判断字符串至少包含的整型个数，然后分析phase_2的工作逻辑即可，是一个判断后面整数是前面两倍的逻辑.

#### (3) bomb_3

依旧是考察**sscanf()函数**的工作原理，分析phase_3的工作逻辑即可，是先确定第一个整型的范围，发现是个小范围，对于每个可能取值，汇编代码中均有跳转，每个跳转会得到第二个整型.

#### (4) bomb_4

考察**逆向工程**和**sscanf()函数**和**函数参数理解**，其中第二个整型直接判断出是0，第一个整型需要在一个复杂的数学函数逻辑中给出判断，即**func4()**，逆向出func4()即可判断第一个整型的范围了.

#### (5) bomb_5

整体流程思路回归到(1)，即在其基础上不是单纯比较input_str 和 ans_str，而是将input_str 的值先映射到另一个字符串，
得到一个新的字符串，input_reflect，再比较input_reflect和ans_str，**核心理解函数：string_length()和string_not_equal()**.

#### (6) bomb_6

unfinished!

#### (7) secret_bomb

unfinished!
