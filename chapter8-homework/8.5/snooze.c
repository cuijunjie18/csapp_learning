/*我的错误*/
unsigned int snooze(unsigned int secs){
    int x = secs - sleep(secs);
    printf("Slept for %d of %d\n",x,secs);
    return secs - x;
}

/*答案*/
unsigned int snooze(unsigned int secs){
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d\n",secs - rc,secs);
    return rc;
}