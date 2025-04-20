### 8.22

收获：
- execv()函数通常无返回，且是直接在同一个进程PID下接下文
- execv()函数构造的argv最后一个字符串必须是NULL,即argv[最后] = NULL;