get_len:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$100, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	get_len, .-get_len
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$0, %ebx
	jmp	.L3
.L4:
	addl	$1, %ebx
.L3:
	movl	$0, %eax
	call	get_len
	cmpl	%ebx, %eax
	jg	.L4
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	combine1, .-combine1
	.globl	combine2
	.type	combine2, @function
combine2:
.LFB2:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	call	get_len
	movl	$0, %edx
	jmp	.L7
.L8:
	addl	$1, %edx
.L7:
	cmpl	%eax, %edx
	jl	.L8
	ret
	.cfi_endproc
.LFE2:
	.size	combine2, .-combine2
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB3:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	call	get_len
	movl	$0, %edx
	jmp	.L10
.L11:
	addl	$1, %edx
.L10:
	cmpl	%eax, %edx
	jl	.L11
	ret
	.cfi_endproc
.LFE3:
	.size	combine3, .-combine3
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
