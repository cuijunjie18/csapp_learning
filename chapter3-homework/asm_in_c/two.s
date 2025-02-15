	.file	"two.c"
	.text
	.globl	my_test
	.type	my_test, @function
my_test:
.LFB39:
	.cfi_startproc
	endbr64
#APP
# 6 "two.c" 1
	movl $21,%edi
	
# 0 "" 2
# 11 "two.c" 1
	movl %edi,%esi
	
# 0 "" 2
# 16 "two.c" 1
	movl %esi,%eax
	
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE39:
	.size	my_test, .-my_test
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	endbr64
	movl	$200, %esi
	movl	$100, %edi
	call	my_test
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE40:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
