	.file	"one.c"
	.text
	.globl	tmult_ok_asm
	.type	tmult_ok_asm, @function
tmult_ok_asm:
.LFB0:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	testq	%rdi, %rdi
	setg	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	tmult_ok_asm, .-tmult_ok_asm
	.globl	tmult_ok1
	.type	tmult_ok1, @function
tmult_ok1:
.LFB1:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
#APP
# 12 "one.c" 1
	setae %al
# 0 "" 2
#NO_APP
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	tmult_ok1, .-tmult_ok1
	.globl	tmult_ok2
	.type	tmult_ok2, @function
tmult_ok2:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
#APP
# 19 "one.c" 1
	setae %bl
	movzbl %bl,%eax
# 0 "" 2
#NO_APP
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2:
	.size	tmult_ok2, .-tmult_ok2
	.globl	tmult_ok3
	.type	tmult_ok3, @function
tmult_ok3:
.LFB3:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
#APP
# 31 "one.c" 1
	setae %al
	
# 0 "" 2
#NO_APP
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	tmult_ok3, .-tmult_ok3
	.globl	umult_ok
	.type	umult_ok, @function
umult_ok:
.LFB4:
	.cfi_startproc
	endbr64
	movq	%rdx, %rcx
#APP
# 41 "one.c" 1
	movq %rdi,%rax
	mulq %rsi
	movq %rax,%rdi
	setae %sil
	
# 0 "" 2
#NO_APP
	movq	%rdi, (%rcx)
	movzbl	%sil, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	umult_ok, .-umult_ok
	.globl	my_test
	.type	my_test, @function
my_test:
.LFB5:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
#APP
# 53 "one.c" 1
	movq $21,%rdi
# 0 "" 2
# 54 "one.c" 1
	movq %rsi,%rsi
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE5:
	.size	my_test, .-my_test
	.globl	intumult_ok_asm
	.type	intumult_ok_asm, @function
intumult_ok_asm:
.LFB6:
	.cfi_startproc
	endbr64
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	testq	%rdi, %rdi
	setne	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE6:
	.size	intumult_ok_asm, .-intumult_ok_asm
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
