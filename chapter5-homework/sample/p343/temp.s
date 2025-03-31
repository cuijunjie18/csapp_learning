xp in %rdi,yp in %rsi

twiddle1:
	movq	(%rdi), %rax
	addq	(%rsi), %rax
	movq	%rax, (%rdi)
	addq	(%rsi), %rax
	movq	%rax, (%rdi)
	ret

twiddle2:
	movq	(%rsi), %rax
	addq	%rax, %rax
	addq	%rax, (%rdi)
	ret
