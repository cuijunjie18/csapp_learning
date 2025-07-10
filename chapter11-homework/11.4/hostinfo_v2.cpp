#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>//结构体addrinfo, in_addr
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc,char *argv[])
{
    struct addrinfo *p, *listp, hints;
    struct sockaddr_in* sockp;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
	    fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
	    exit(0);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));                         
    hints.ai_family = AF_INET;       /* IPv4 only */        //line:netp:hostinfo:family
    hints.ai_socktype = SOCK_STREAM; /* Connections only */ //line:netp:hostinfo:socktype
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    for (p = listp; p; p = p->ai_next) {
        sockp = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(p->ai_family,&sockp->sin_addr, buf, p->ai_addrlen);       
        printf("%s\n", buf);
    } 
}