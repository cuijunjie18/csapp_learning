#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <wait.h>
#include <signal.h>

#define PORT 8001
#define MAXN 2048

// echo 服务
void echo_server(int fd){
    int pid = getpid();
    char buf[MAXN];
    while (true){
        int recv_bytes = recv(fd, buf, MAXN, 0);
        if (recv_bytes > 0){
            int status = send(fd, buf, recv_bytes, 0);
            if (status < 0){
                printf("(%d)Send failed!\n",pid);
                break;
            }
        }else if (recv_bytes == 0){
            printf("(%d) Connection closed by client.\n",pid);
            break;
        }else{
            printf("(%d)Receive failed!\n",pid);
            break;
        }
    }
}

// 一次SIGCHLD回收全部结束的子进程
void sigchld_handler(int sig) //line:conc:echoserverp:handlerstart
{
    while (waitpid(-1, 0, WNOHANG) > 0)
	    ;
    return;
} //line:conc:echoserverp:handlerend

// 信号处理绑定
void My_Signal(int signum,__sighandler_t handler){
	struct sigaction action,old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;

    if (sigaction(signum, &action, &old_action) < 0){
        std::cerr << "Signal error" << std::endl;
        exit(-1);
    }
    std::cout << "Set signal handle successfully." << std::endl;
}

int main(int agrc,char *argv[])
{
    // Set signal
    My_Signal(SIGCHLD, sigchld_handler); // 为SIGCHLD信号设置处理函数

    // generate listen fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0){
        std::cerr << "Generate socket failed!" << std::endl;
        return -1;
    }

    // Set server
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    if (bind(listen_fd, (sockaddr*) &server_addr,sizeof(server_addr)) < 0){
        std::cerr << "Bind failed!" << std::endl;
        close(listen_fd);
        return -1;
    }

    // Listen
    if (listen(listen_fd, 5) < 0){
        std::cerr << "Listen failed!" << std::endl;
        close(listen_fd);
        return -1;
    }
    std::cout << "Listen on port: " << PORT << std::endl; 

    // Accept
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char ip[60];
    int pid;
    while (true){
        int connect_fd = accept(listen_fd,(sockaddr*) &client_addr,&client_len);
        if (connect_fd < 0){
            std::cerr << "Connect failed!" << std::endl;
            close(listen_fd);
            return -1;
        }
        if ((pid = fork()) == 0){
            close(listen_fd);
            echo_server(connect_fd);
            close(connect_fd);
            exit(0);
        }
        inet_ntop(client_addr.sin_family, &client_addr.sin_addr, ip, client_len);
        printf("(%d) Connect with client %s\n",pid,ip);
        close(connect_fd);
    }

    close(listen_fd);
    return 0;
}