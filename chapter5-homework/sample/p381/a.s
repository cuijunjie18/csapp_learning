	.file	"a.c"
	.text
	.globl	func_a
	.type	func_a, @function
func_a:
.LFB0:
	.cfi_startproc
	endbr64
	cmpl	%edi, %esi
	movl	%edi, %eax
	cmovge	%esi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	func_a, .-func_a
	.globl	func_b
	.type	func_b, @function
func_b:
.LFB1:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	cmpl	%esi, %edi
	jle	.L3
	movl	%edi, %eax
.L3:
	ret
	.cfi_endproc
.LFE1:
	.size	func_b, .-func_b
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	$1, %esi
	movl	$2, %edi
	call	func_a
	movl	%eax, %ebp
	movl	$1, %esi
	movl	$2, %edi
	call	func_b
	movl	%eax, %ebx
	movl	%ebp, %esi
	leaq	.LC0(%rip), %rbp
	movq	%rbp, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	%ebx, %esi
	movq	%rbp, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2:
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
