	.file	"switchv.c"
	.text
	.globl	switchv
	.type	switchv, @function
switchv:
.LFB23:
	.cfi_startproc
	endbr64
	cmpq	$3, %rdi
	je	.L4
	jg	.L3
	testq	%rdi, %rdi
	je	.L5
	cmpq	$2, %rdi
	jne	.L6
	movl	$3003, %eax
	ret
.L3:
	cmpq	$5, %rdi
	jne	.L7
	movl	$3003, %eax
	ret
.L4:
	movl	$3276, %eax
	ret
.L5:
	movl	$2730, %eax
	ret
.L6:
	movl	$3549, %eax
	ret
.L7:
	movl	$3549, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	switchv, .-switchv
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"idx = %ld, val = 0x%lx\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$88, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movl	$0, %ebx
	jmp	.L9
.L10:
	leal	-1(%rbx), %ebp
	movslq	%ebp, %rdi
	call	switchv
	movq	%rax, %rcx
	movslq	%ebx, %rax
	movq	%rcx, (%rsp,%rax,8)
	movl	%ebp, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebx
.L9:
	cmpl	$7, %ebx
	jle	.L10
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L13
	movl	$0, %eax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
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
