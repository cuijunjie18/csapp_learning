origin:
    subq $8,%rsp
    movq REG,(%rsp)

my_revise:
    movq REG,%rax
    subq $8,%rsp
    movq %rax,(%rsp)

ans_revise:
    movq REG,-8(%rsp)
    subq $8,%rsp