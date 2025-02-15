	.file	"find_range.c"
	.text
	.globl	find_range_origin
	.type	find_range_origin, @function
find_range_origin:
.LFB39:
	.cfi_startproc
	endbr64
	pxor	%xmm1, %xmm1
	comiss	%xmm0, %xmm1
	ja	.L5
	ucomiss	%xmm1, %xmm0
	jp	.L8
	jne	.L8
	movl	$1, %eax
	ret
.L8:
	comiss	.LC0(%rip), %xmm0
	jbe	.L10
	movl	$2, %eax
	ret
.L5:
	movl	$0, %eax
	ret
.L10:
	movl	$3, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	find_range_origin, .-find_range_origin
	.globl	find_range
	.type	find_range, @function
find_range:
.LFB40:
	.cfi_startproc
	endbr64
#APP
# 16 "find_range.c" 1
	vxorps %%xmm1,%%xmm1,%%xmm1
	vucomiss %%xmm0,%%xmm1
	ja .L5
	jp .L8
	movl $1,%%eax
	je .L3
	.L8:
	setbe %%al
	movzbl %%al,%%eax
	addl $2,%%eax
	ret
	.L5:
	movl $0,%%eax
	.L3:
	rep;ret
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE40:
	.size	find_range, .-find_range
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
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
