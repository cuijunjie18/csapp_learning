get_len:
	movl	$100, %eax
	ret


combine1:
	pushq	%rbx
	movl	$0, %ebx	# i = 0
	jmp	.L3				# to for
.L4:
	addl	$1, %ebx	# i++
.L3:
	movl	$0, %eax	# len = 0
	call	get_len		# len = get_len()
	cmpl	%ebx, %eax	# if judge
	jg	.L4
	popq	%rbx
	ret


combine2:
	movl	$0, %eax	# len = 0 
	call	get_len		# len = get_len()
	movl	$0, %edx	# i = 0
	jmp	.L7
.L8:
	addl	$1, %edx	# i++
.L7:
	cmpl	%eax, %edx
	jl	.L8
	ret


combine3:
	movl	$0, %eax
	call	get_len		# len = get_len()
	movl	$0, %edx	# i = 0
	jmp	.L10
.L11:
	addl	$1, %edx
.L10:
	cmpl	%eax, %edx
	jl	.L11
	ret