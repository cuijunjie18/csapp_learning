long rsum(long *start,long count)
start in %rdi,count in %rsi

rsum:
	testq	%rsi, %rsi			# test count
	jle	.L3						# if <= 0
	pushq	%rbx				# save %rbx
	movq	(%rdi), %rbx		# get *start to %rbx
	subq	$1, %rsi			# count - 1 as second argument
	addq	$8, %rdi			# start + 1 as first argument
	call	rsum				# recursion
	addq	%rbx, %rax			# current &start + rsum
	popq	%rbx				# back to earlier *start
	ret							# return
.L3:
	movl	$0, %eax			# return 0
	ret