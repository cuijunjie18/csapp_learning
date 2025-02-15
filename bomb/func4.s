	.file	"func4.c"
	.text
	.globl	func4
	.type	func4, @function


func4:
	movl	%edx, %eax
	subl	%esi, %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%ecx, %eax
	sarl	%eax
	addl	%esi, %eax
	cmpl	%eax, %edi
	jb	.L6
	ja	.L7
	movl	$0, %eax
.L1:
	addq	$8, %rsp
	ret
.L6:
	leal	-1(%rax), %edx
	call	func4
	addl	%eax, %eax
	jmp	.L1
.L7:
	leal	1(%rax), %esi
	call	func4
	leal	1(%rax,%rax), %eax
	jmp	.L1


func4_optim:
.LFB40:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	%edx, %eax
	subl	%esi, %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%ecx, %eax
	shrl	%eax
	addl	%esi, %eax
	cmpl	%eax, %edi
	jb	.L13
	ja	.L14
	movl	$0, %eax
.L8:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	leal	-1(%rax), %edx
	call	func4_optim
	addl	%eax, %eax
	jmp	.L8
.L14:
	leal	1(%rax), %esi
	call	func4
	leal	1(%rax,%rax), %eax
	jmp	.L8
	.cfi_endproc
.LFE40:
	.size	func4_optim, .-func4_optim
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$14, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	func4
	movl	%eax, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE41:
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
