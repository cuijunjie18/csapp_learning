	.file	"funct2.c"
	.text
	.globl	funct2
	.type	funct2, @function
funct2:
.LFB39:
	.cfi_startproc
	endbr64
	pxor	%xmm2, %xmm2
	cvtsi2ssl	%edi, %xmm2
	mulss	%xmm1, %xmm2
	cvtss2sd	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rsi, %xmm1
	divsd	%xmm1, %xmm0
	subsd	%xmm0, %xmm2
	movapd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE39:
	.size	funct2, .-funct2
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
