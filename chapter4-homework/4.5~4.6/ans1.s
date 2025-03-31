long sum(long *start,long count){
    long sum = 0;
    while (count){
        sum += abs(*start);
        start++;
        count--;
    }
}
start in %rdi,count in %rsi

# 条件分支(控制、跳转)语句实现
sum : 
    irmovq  $8,%r8
    irmovq  $1,%r9
    xorq    %rax,%rax           # sum = 0
    andq    %rsi,%rsi           # set CC
    jmp test    
loop :  
    mrmovq  (%rdi),%r10         # get *start
    andq    %r10,%r10           # set CC
    jge     pos                 # if *start >= 0, go to pos
    rrmovq  %r10,%rbx           # *start(which is negtive) to %rbx
    subq    %rbx,%r10           # use twice subq make *start = -*start
    subq    %rbx,%r10           
pos :   
    addq    %r10,%rax           # sum += *start
    subq    %r9,%rdi            # start++
    subq    %r8,%rsi            # count--
test :
    jne loop
    ret

