void bubble_p(long* data, long count)
data in %rdi, count in %rsi

bubble_p:
.LFB41:
	leaq	-8(%rdi,%rsi,8), %rsi       # get (data + 8 * count - 8) to last
	jmp	.L18
.L19:
	addq	$8, %rax
.L21:
	cmpq	%rsi, %rax                  
	jnb	.L23                            # if i >= last
	movq	8(%rax), %rdx               # i + 1
	movq	(%rax), %rcx                # i
	cmpq	%rcx, %rdx
	jge	.L19
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
	jmp	.L19
.L23:
	subq	$8, %rsi                    # last - 8
.L18:
	cmpq	%rdi, %rsi                  
	jbe	.L24                            # if last <= data
	movq	%rdi, %rax                  # data to i
	jmp	.L21
.L24:
	ret