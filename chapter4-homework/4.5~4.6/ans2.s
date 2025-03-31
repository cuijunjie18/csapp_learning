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
    mrmovq  (%rdi),%r10         # get *start for add
    mrmovq  (%rdi),%rdx         # get *start for save
    irmovq  $0,%rbx             # set zero to %rbx
    subq    %rdx,%rbx           # get -*start
    andq    %r10,%r10           # test *start
    cmovl   %rbx,%r10           # if *start < 0 , set (-*start) to %r10
    addq    %r10,%rax           # sum += abs(*start)
    subq    %r9,%rdi            # start++
    subq    %r8,%rsi            # count--
test :
    jne loop
    ret

