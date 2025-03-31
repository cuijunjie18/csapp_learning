Og:
# a in %rdi,x in %xmm0,degree in %rsi
.LFB0:
	movapd	%xmm0, %xmm3	# save %xmm0
	movsd	(%rdi), %xmm0	# get a[0]
	movapd	%xmm3, %xmm1
	movl	$1, %eax		# i = 1
	jmp	.L2
.L3:
	movslq	%eax, %rdx
	movapd	%xmm1, %xmm2
	mulsd	(%rdi,%rdx,8), %xmm2
	addsd	%xmm2, %xmm0
	mulsd	%xmm3, %xmm1
	addl	$1, %eax
.L2:
	movslq	%eax, %rdx
	cmpq	%rsi, %rdx		# 
	jle	.L3
	ret



O1:
# a in %rdi,x in %rsi,degree in %rdx
.LFB0:
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