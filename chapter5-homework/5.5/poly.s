	.file	"poly.c"
	.text
	.globl	_Z4polyPddl
	.type	_Z4polyPddl, @function
_Z4polyPddl:
.LFB0:
	.cfi_startproc
	endbr64
	movapd	%xmm0, %xmm3
	movsd	(%rdi), %xmm0
	testq	%rsi, %rsi
	jle	.L1
	leaq	8(%rdi), %rax
	leaq	8(%rdi,%rsi,8), %rdx
	movapd	%xmm3, %xmm1
.L3:
	movapd	%xmm1, %xmm2
	mulsd	(%rax), %xmm2
	addsd	%xmm2, %xmm0
	mulsd	%xmm3, %xmm1
	addq	$8, %rax
	cmpq	%rdx, %rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	_Z4polyPddl, .-_Z4polyPddl
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
