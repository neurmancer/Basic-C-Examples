	.file	"primePrinter.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"How many primes do you want starting from 2? "
.LC1:
	.string	"%d"
	.align 8
.LC2:
	.string	"Bro enter a positive number, come on..."
.LC3:
	.string	"2"
.LC4:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L2
	movl	-32(%rbp), %eax
	testl	%eax, %eax
	jg	.L3
.L2:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L12
.L3:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, -28(%rbp)
	movl	$3, -24(%rbp)
	jmp	.L5
.L11:
	movl	$1, -20(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-24(%rbp), %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	ceil@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -12(%rbp)
	movl	$2, -16(%rbp)
	jmp	.L6
.L9:
	movl	-24(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L7
	movl	$0, -20(%rbp)
	jmp	.L8
.L7:
	addl	$1, -16(%rbp)
.L6:
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L9
.L8:
	cmpl	$0, -20(%rbp)
	je	.L10
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -28(%rbp)
.L10:
	addl	$2, -24(%rbp)
.L5:
	movl	-32(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L11
	movl	$0, %eax
.L12:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
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
