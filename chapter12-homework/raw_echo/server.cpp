#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 8001
#define MAXN 2048

char buf[MAXN];

int main(int agrc,char *argv[])
{
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
    if (listen(listen_fd, 1) < 0){
        std::cerr << "Listen failed!" << std::endl;
        close(listen_fd);
        return -1;
    }
    std::cout << "Listen on port: " << PORT << std::endl; 

    // Accept
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int connect_fd = accept(listen_fd,(sockaddr*) &client_addr,&client_len);
    if (connect_fd < 0){
        std::cerr << "Connect failed!" << std::endl;
        close(listen_fd);
        return -1;
    }
    inet_ntop(client_addr.sin_family, &client_addr.sin_addr, buf, client_len);
    std::cout << "Connect with client: " << buf << std::endl;

    while (true){
        int recv_bytes = recv(connect_fd, buf, MAXN, 0);
        if (recv_bytes > 0){
            int status = send(connect_fd, buf, recv_bytes, 0);
            if (status < 0){
                std::cerr << "Send failed!" << std::endl;
                break;
            }
        }else if (recv_bytes == 0){
            std::cout << "Connection closed by client." << std::endl;
            break;
        }else{
            std::cerr << "Recv failed!" << std::endl;
            break;
        }
    }

    close(listen_fd);
    close(connect_fd);
    return 0;
}