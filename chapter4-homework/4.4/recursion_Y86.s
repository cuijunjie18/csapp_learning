long rsum(long *start,long count)
start in %rdi,count in %rsi

rsum:
    irmovq  $1, %r8
    irmovq  $8, %r9
    andq    %rsi, %rsi
    jle .L3
    pushq   %rbx
    mrmovq  (%rsi), %rbx
    subq    %r8, %rsi
    addq    %r9, %rdi
    call    rsum
    addq    %rbx, %rax
    popq    %rbx
    ret
.L3:
    irmovq  $0, %rax
    ret