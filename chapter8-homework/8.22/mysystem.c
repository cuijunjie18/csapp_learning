#include "csapp.h"

int mysystem(char *command){
    int status;

    pid_t pid = fork();
    if (pid == 0){
        char *argv[4] = {"","-c",command,NULL};
        execv("/usr/bin/sh",argv);
    }

    // 输出子进程的PID
    printf("Execv pid : %d\n",pid);
    while (Waitpid(-1, &status, 0) > 0){
        // exit退出或者return返回
        if (WIFEXITED(status)){
            return WEXITSTATUS(status);
        }

        // 信号中断
        if (WIFSIGNALED(status)){
            return WTERMSIG(status);
        }
    }
}

int main(int argc,char *argv[])
{
    int status;
    char command1[50] = "./hello";
    status = mysystem(command1);
    printf("The status of command %s is %d\n",command1,status);

    char command2[50] = "./loop";
    status = mysystem(command2);
    printf("The status of command %s is %d\n",command2,status);
    return 0;
}