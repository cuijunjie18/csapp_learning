#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void mmapcopy(int fd,int size){
    char *bufp;
    bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0); //只读映射，私有映射(修改不写回)
    write(1,bufp,size);
    return;
}

int main(int argc,char **argv)
{
    struct stat stat;
    int fd;

    if (argc != 2){
        printf("usage: %s <filename>\n",argv[0]);
        exit(0);
    }

    fd = open(argv[1], O_RDONLY, 0);
    fstat(fd, &stat);
    // printf("%ld\n",stat.st_size);
    printf("%d\n",fd);
    mmapcopy(fd, stat.st_size);
    exit(0);
}