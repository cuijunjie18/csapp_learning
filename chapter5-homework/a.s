


_Z1av:
	endbr64
	movl	$0, %eax
	jmp	.L2
.L3:
	addl	$1, %eax
.L2:
	cmpl	$99, %eax
	jle	.L3
	ret



_Z1bv:
	movl	$0, %eax
	jmp	.L5
.L6:
	addl	$1, %eax
.L5:
	cmpl	$99, %eax
	jle	.L6
	ret
