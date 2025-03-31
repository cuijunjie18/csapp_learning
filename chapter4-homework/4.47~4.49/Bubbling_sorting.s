	.file	"Bubbling_sorting.c"
	.text
	.globl	bubble_a
	.type	bubble_a, @function
bubble_a:
.LFB39:
	.cfi_startproc
	endbr64
	leaq	-1(%rsi), %r9
	jmp	.L2
.L3:
	addq	$1, %rax
.L5:
	cmpq	%r9, %rax
	jge	.L7
	leaq	8(%rdi,%rax,8), %rsi
	movq	(%rsi), %rcx
	leaq	(%rdi,%rax,8), %rdx
	movq	(%rdx), %r8
	cmpq	%r8, %rcx
	jge	.L3
	movq	%r8, (%rsi)
	movq	%rcx, (%rdx)
	jmp	.L3
.L7:
	subq	$1, %r9
.L2:
	testq	%r9, %r9
	jle	.L8
	movl	$0, %eax
	jmp	.L5
.L8:
	ret
	.cfi_endproc
.LFE39:
	.size	bubble_a, .-bubble_a
	.globl	bubble_b
	.type	bubble_b, @function
bubble_b:
.LFB40:
	.cfi_startproc
	endbr64
	leaq	-1(%rsi), %r9
	jmp	.L10
.L11:
	addl	$1, %eax
.L13:
	movslq	%eax, %rdx
	cmpq	%r9, %rdx
	jge	.L15
	movslq	%eax, %rdx
	leaq	8(%rdi,%rdx,8), %rsi
	movq	(%rsi), %rcx
	leaq	(%rdi,%rdx,8), %rdx
	movq	(%rdx), %r8
	cmpq	%r8, %rcx
	jge	.L11
	movq	%r8, (%rsi)
	movq	%rcx, (%rdx)
	jmp	.L11
.L15:
	subq	$1, %r9
.L10:
	testq	%r9, %r9
	jle	.L16
	movl	$0, %eax
	jmp	.L13
.L16:
	ret
	.cfi_endproc
.LFE40:
	.size	bubble_b, .-bubble_b
	.globl	bubble_p
	.type	bubble_p, @function
bubble_p:
.LFB41:
	.cfi_startproc
	endbr64
	leaq	-8(%rdi,%rsi,8), %rsi
	jmp	.L18
.L19:
	addq	$8, %rax
.L21:
	cmpq	%rsi, %rax
	jnb	.L23
	movq	8(%rax), %rdx
	movq	(%rax), %rcx
	cmpq	%rcx, %rdx
	jge	.L19
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
	jmp	.L19
.L23:
	subq	$8, %rsi
.L18:
	cmpq	%rdi, %rsi
	jbe	.L24
	movq	%rdi, %rax
	jmp	.L21
.L24:
	ret
	.cfi_endproc
.LFE41:
	.size	bubble_p, .-bubble_p
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$96, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	jmp	.L26
.L27:
	movl	$10, %edx
	subq	%rcx, %rdx
	movslq	%eax, %rcx
	movq	%rdx, (%rsp,%rcx,8)
	addl	$1, %eax
.L26:
	movslq	%eax, %rcx
	cmpl	$9, %eax
	jle	.L27
	movq	%rsp, %rdi
	movl	$10, %esi
	call	bubble_a
	movl	$0, %ebx
	jmp	.L28
.L29:
	movslq	%ebx, %rax
	movq	(%rsp,%rax,8), %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebx
.L28:
	cmpl	$9, %ebx
	jle	.L29
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
	jmp	.L30
.L31:
	movl	$10, %edx
	subq	%rcx, %rdx
	movslq	%eax, %rcx
	movq	%rdx, (%rsp,%rcx,8)
	addl	$1, %eax
.L30:
	movslq	%eax, %rcx
	cmpl	$9, %eax
	jle	.L31
	movq	%rsp, %rdi
	movl	$10, %esi
	call	bubble_b
	movl	$0, %ebx
	jmp	.L32
.L33:
	movslq	%ebx, %rax
	movq	(%rsp,%rax,8), %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebx
.L32:
	cmpl	$9, %ebx
	jle	.L33
	movl	$10, %edi
	call	putchar@PLT
	movq	88(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L36
	movl	$0, %eax
	addq	$96, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L36:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE42:
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
