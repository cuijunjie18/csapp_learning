origin:
    movq (%rsp),REG
    addq $8,%rsp

my_revise:
    movq (%rsp),%rax
    addq $8,%rsp
    movq %rax,REG

ans_revise:
    addq $8,%rsp
    movq -8(%rsp),REG