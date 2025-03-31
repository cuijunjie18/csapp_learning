long sum(long *start,long count)
start in %rdi,count in %rsi
sum : 
    xorq    %rax, %rax        # sum = 0
    andq    %rsi, %rsi        # set CC
    jmp test
loop : 
    mrmovq  (%rdi), %r10    # get *start
    addq    %r10, %rax        # sum += *start
    iaddq   $1, %rdi         # start++
    iaddq   $-1, %rsi        # count--
test :
    jne loop
    ret

# 上面错了一处
iaddq $1,%rdi         # start++
# 应该改为
iaddq $8,%rdi         # start++
