#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define MAXN 2048

void usage(char *argv[]){
    printf("usage:%s <server_ip> <server_port>\n",argv[0]);
}

int main(int argc,char *argv[])
{
    if (argc < 3){
        usage(argv);
        return -1;
    }

    // Generate socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        std::cerr << "Generate socket failed!" << std::endl;
        return -1;
    }

    // Set range of outtime
    // struct timeval tv;
    // tv.tv_sec = 5; // 5s
    // tv.tv_usec = 0;
    // if (setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) < 0){
    //     std::cerr << "Set socket opt failed!" << std::endl;
    //     close(sock);
    //     return -1;
    // }

    // Parse ip and port in argv
    uint16_t port = atoi(argv[2]);
    std::string server_ip = argv[1];
    sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) < 0){
        std::cerr << "Invalid ip!" << std::endl;
        close(sock);
        return -1;
    }

    // connect
    if (connect(sock, (sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        std::cerr << "Connect failed!" << std::endl;
        close(sock);
        return -1;
    }
    std::cout << "Connect to server: " << server_ip << std::endl;

    char buf[MAXN];
    std::string input;
    while (true){
        std::cout << ">echo ";
        std::getline(std::cin,input); // support completed sentence
        if (send(sock, input.c_str(), input.size(), 0) < 0){
            std::cerr << "Send failed!" << std::endl;
            break;
        }
        int recv_bytes = recv(sock, buf, MAXN, 0);
        if (recv_bytes > 0){
            buf[recv_bytes] = '\0';
            std::cout << buf << std::endl;
        }else if (recv_bytes == 0){
            std::cout << "Connection closed by server!" << std::endl;
            break;
        }else{
            std::cout << "Receive failed!" << std::endl;
            break;
        }
    }

    close(sock);
    return 0;
}