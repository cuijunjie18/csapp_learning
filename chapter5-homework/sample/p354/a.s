get_nums:
.LFB39:
	.cfi_startproc
	endbr64
	movl	$100, %eax
	ret

test_a:
.LFB40:
	pushq	%rbp
	pushq	%rbx
	movl	$0, %ebx
	movl	$0, %ebp
	jmp	.L3
.L4:
	addl	$1, %ebp
	addl	$1, %ebx
.L3:
	movl	$0, %eax
	call	get_nums
	cmpl	%ebx, %eax
	jg	.L4
	movl	%ebp, %eax
	popq	%rbx
	popq	%rbp
	ret

test_b:
.LFB41:
	movl	$0, %eax
	call	get_nums
	movl	%eax, %ecx
	movl	$0, %edx
	movl	$0, %eax
	jmp	.L7
.L8:
	addl	$1, %eax
	addl	$1, %edx
.L7:
	cmpl	%ecx, %edx
	jl	.L8
	ret

main:
.LFB42:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$0, %eax
	call	test_a
	movl	%eax, %ebx
	movl	$0, %eax
	call	test_b
	movl	%eax, %ecx
	movl	%ebx, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
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
