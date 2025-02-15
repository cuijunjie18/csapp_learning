	.file	"cread_alt.c"
	.text
	.globl	cread
	.type	cread, @function
cread:
.LFB39:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	je	.L3
	movq	(%rdi), %rax
	ret
.L3:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	cread, .-cread
	.globl	cread_alt
	.type	cread_alt, @function
cread_alt:
.LFB40:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	je	.L6
	movq	(%rdi), %rax
	ret
.L6:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE40:
	.size	cread_alt, .-cread_alt
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"cread_alt.c"
.LC1:
	.string	"cread(&a) == cread_alt(&a)"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"cread(NULL) == cread_alt(NULL)"
	.text
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	$0, (%rsp)
	movq	%rsp, %rbp
	movq	%rbp, %rdi
	call	cread
	movq	%rax, %rbx
	movq	%rbp, %rdi
	call	cread_alt
	cmpq	%rax, %rbx
	jne	.L12
	movl	$0, %edi
	call	cread
	movq	%rax, %rbx
	movl	$0, %edi
	call	cread_alt
	cmpq	%rax, %rbx
	jne	.L13
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L14
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	leaq	__PRETTY_FUNCTION__.0(%rip), %rcx
	movl	$16, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
.L13:
	leaq	__PRETTY_FUNCTION__.0(%rip), %rcx
	movl	$17, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
.L14:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
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
