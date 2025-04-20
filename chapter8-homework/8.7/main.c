#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// unsigned int rc;
int secs;

void sigint_handler(int sig) /* SIGINT handler */   //line:ecf:sigint:beginhandler
{
    printf("\nCaught SIGINT!\n");    //line:ecf:sigint:printhandler
    // printf("Slept for %d of %d\n",secs - rc,secs);
    return;                      //line:ecf:sigint:exithandler
}                                              //line:ecf:sigint:endhandler

unsigned int snooze(unsigned int secs){
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d\n",secs - rc,secs);
    return rc;
}

int main(int argc,char *argv[])
{
    if (argc <= 1){
        printf("Please use:%s [seconds/s]\n",argv[0]);
        exit(1);
    }

    secs = atoi(argv[1]);
    if (signal(SIGINT,sigint_handler) == SIG_ERR){
        // unix_error("signal error"); 
        printf("signal error!\n");
    }
    (void)snooze(secs);
    return 0;
}