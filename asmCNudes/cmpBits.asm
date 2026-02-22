	.file	"cmpBits.c"
	.text
	.globl	cmp_popCounts
	.type	cmp_popCounts, @function
cmp_popCounts:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	andl	%eax, -20(%rbp)
	addl	$1, -8(%rbp)
.L2:
	cmpl	$0, -20(%rbp)
	jne	.L3
	jmp	.L4
.L5:
	movl	-24(%rbp), %eax
	subl	$1, %eax
	andl	%eax, -24(%rbp)
	addl	$1, -4(%rbp)
.L4:
	cmpl	$0, -24(%rbp)
	jne	.L5
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	cmp_popCounts, .-cmp_popCounts
	.section	.rodata
.LC0:
	.string	"A:%d\tB:%d\tRes:%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movq	$0, -8(%rbp)
	jmp	.L8
.L9:
	call	rand@PLT
	movslq	%eax, %rdx
	imulq	$680390859, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$4, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	movl	%edx, -16(%rbp)
	movl	-16(%rbp), %edx
	imull	$101, %edx, %edx
	subl	%edx, %eax
	movl	%eax, -16(%rbp)
	call	rand@PLT
	movslq	%eax, %rdx
	imulq	$680390859, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$4, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	movl	%edx, -12(%rbp)
	movl	-12(%rbp), %edx
	imull	$101, %edx, %edx
	subl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	cmp_popCounts
	movl	%eax, %ecx
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$1, -8(%rbp)
.L8:
	cmpq	$9, -8(%rbp)
	jbe	.L9
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
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
