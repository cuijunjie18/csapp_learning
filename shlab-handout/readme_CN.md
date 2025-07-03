[文件内容开始]
===== 第1页 =====

CS 213，2002年秋季

实验作业 L5：编写自己的Unix Shell
发布时间：10月24日，截止时间：10月31日（周四）晚上11:59

Harry Bovik (bovik@cs.cmu.edu) 是本作业的主要负责人。
简介

本作业的目的是通过编写一个支持作业控制的简单Unix Shell程序，加深对进程控制和信号处理概念的理解。
实验安排

    最多两人一组完成。

    仅需电子提交。

    作业的澄清和修改将通过课程网站发布。

实验材料获取说明

（此处为站点特定说明，描述如何获取 shlab-handout.tar 文件。以下是CMU的指导：）

    将 shlab-handout.tar 复制到你的工作目录。

    执行以下命令：
    bash

    tar xvf shlab-handout.tar  # 解压文件  
    make                       # 编译测试程序  

    在 tsh.c 文件顶部的注释中填写组员姓名和Andrew ID。

tsh.c（tiny shell）已包含一个简单Shell的基础框架，你需要完成以下空函数：

    eval：解析和执行命令行的主函数（约70行）。

    builtin_cmd：处理内置命令（quit、fg、bg、jobs，约25行）。

    do_bgfg：实现 bg 和 fg 命令（约50行）。

    waitfg：等待前台作业完成（约20行）。

    sigchild_handler：捕获 SIGCHILD 信号（约80行）。

    sigint_handler：捕获 SIGINT（Ctrl+C）信号（约15行）。

    sigtstp_handler：捕获 SIGTSTP（Ctrl+Z）信号（约15行）。

修改代码后，运行 make 重新编译。启动Shell：
bash

./tsh  
tsh> [输入命令]  

===== 第2页 =====
Unix Shell基础

Shell是交互式命令行解释器，代表用户运行程序。其工作流程：

    打印提示符。

    读取标准输入的命令行。

    根据命令内容执行操作。

命令行结构：

    首个单词为内置命令或可执行文件路径，其余为参数。

    以 & 结尾的命令在后台运行（Shell不等待作业完成），否则在前台运行。

作业控制：

    Ctrl+C 向前台作业发送 SIGINT（默认终止进程）。

    Ctrl+Z 向前台作业发送 SIGTSTP（默认暂停进程）。

    内置命令：

        jobs：列出后台作业。

        bg <作业>：将暂停的后台作业转为运行状态。

        fg <作业>：将后台作业转为前台运行。

        kill <作业>：终止作业。

tsh规范

    提示符为 tsh>。

    不支持管道（|）或I/O重定向（<、>）。

    需处理僵尸进程，并在作业因未捕获信号终止时打印PID和信号描述。

===== 第3页 =====
测试工具

    参考解答：tshref 是可执行的参考Shell，你的输出应与其一致（除PID外）。

    测试驱动：sdriver.pl 根据跟踪文件（trace01-16.txt）自动测试Shell。
    bash

    ./sdriver.pl -t trace01.txt -s ./tsh -a "-p"  # 测试你的Shell  
    make test01                                   # 等效命令  

提示

    仔细阅读教材第8章（异常控制流）。

    关键函数：waitpid、kill、fork、execve、setpgid、sigprocmask。

    信号处理需向整个前台进程组发送信号（使用 kill(-pid, sig)）。

    避免在 vi、emacs 等复杂程序中测试，建议使用 /bin/ls、/bin/echo。

评分标准

    正确性（80分）：16个跟踪文件，每个5分。

    代码风格（10分）：注释清晰（5分），检查所有系统调用返回值（5分）。

===== 第4页 =====
提交说明

（此处为站点特定说明，以下是CMU的指导：）

    在 tsh.c 头部注释中填写组员信息。

    团队命名格式：

        单人：Andrew ID

        双人：ID1+ID2

    提交命令：
    bash

make handin TEAM=团队名  

修改后重新提交需递增版本号：
bash

    make handin TEAM=团队名 VERSION=2  

祝你好运！

[文件内容结束]