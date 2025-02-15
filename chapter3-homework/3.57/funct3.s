	.file	"funct3.c"
	.text
	.globl	funct3
	.type	funct3, @function
funct3:
.LFB39:
	.cfi_startproc
	endbr64
	movss	(%rdx), %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	(%rdi), %xmm2
	subsd	%xmm2, %xmm0
	comisd	.LC0(%rip), %xmm0
	jbe	.L6
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	mulss	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtss2sd	%xmm1, %xmm0
	ret
.L6:
	addss	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtss2sd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE39:
	.size	funct3, .-funct3
	.globl	funct3_optim
	.type	funct3_optim, @function
funct3_optim:
.LFB40:
	.cfi_startproc
	endbr64
	movss	(%rdx), %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	(%rdi), %xmm2
	subsd	%xmm2, %xmm0
	comisd	.LC0(%rip), %xmm0
	jbe	.L12
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	mulss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	ret
.L12:
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm1, %xmm1
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	ret
	.cfi_endproc
.LFE40:
	.size	funct3_optim, .-funct3_optim
	.globl	funct3_ans
	.type	funct3_ans, @function



funct3_ans:
	movapd	%xmm0, %xmm2
	movss	(%rdx), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdl	(%rdi), %xmm0
	comisd	%xmm0, %xmm2
	jbe	.L18
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	mulss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	ret
.L18:
	addss	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssq	%rsi, %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	ret




	.cfi_endproc
.LFE41:
	.size	funct3_ans, .-funct3_ans
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	0
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
