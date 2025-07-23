#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    std::string a;
    std::getline(std::cin,a);
    std::cout << a << std::endl;
    return 0;
}