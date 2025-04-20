### 8.23

参考csapp solution

``` shell
   SIGUSR2      SIGUSR2  SIGUSR2  SIGUSR2  SIGUSR2
      |            |        |        |        |
being handled   Pending  Canceld  Canceld  Canceld
 need 1 sec
```

第一个信号在处理，第二个信号在pending,其他的都abandon了

我的解决方案

```c
for (i = 0; i < 5; i++) {
    Kill(getppid(), SIGUSR2);
    sleep(1); // 信号延时发送，确保之前发送的信号已经处理完成
    printf("sent SIGUSR2 to parent\n");
}
```