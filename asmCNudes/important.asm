	.file	"important.c"
	.text
	.section	.rodata
.LC0:
	.string	"A"
.LC1:
	.string	"\033[?25l"
.LC2:
	.string	"\033[H\033[J"
	.align 8
.LC3:
	.string	"Loading super duper important shit that won't dox your search history to your crush's DMs\t"
.LC4:
	.string	"|\b"
.LC5:
	.string	"/\b"
.LC6:
	.string	"\342\200\224\b"
.LC7:
	.string	"\\\b"
.LC8:
	.string	"Loading very important shit"
.LC9:
	.string	"FUCK\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
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
	leaq	sigsegvHandler(%rip), %rax
	movq	%rax, %rsi
	movl	$11, %edi
	call	signal@PLT
	movq	stdout(%rip), %rax
	movl	$0, %ecx
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	setvbuf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -16(%rbp)
	jmp	.L2
.L7:
	movl	-16(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1296593901, %rax, %rax
	shrq	$32, %rax
	sarl	$4, %eax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	imull	$53, %eax, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	testl	%eax, %eax
	jne	.L3
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$300000, %edi
	call	usleep@PLT
	movl	$0, -12(%rbp)
	jmp	.L4
.L5:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$175250, %edi
	call	usleep@PLT
	addl	$1, -12(%rbp)
.L4:
	cmpl	$4, -12(%rbp)
	jle	.L5
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L6
.L3:
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	addl	$1, %eax
	imull	$150000, %eax, %eax
	movl	%eax, %edi
	call	usleep@PLT
	movl	$46, %edi
	call	putchar@PLT
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	addl	$1, %eax
	imull	$150000, %eax, %eax
	movl	%eax, %edi
	call	usleep@PLT
	movl	$46, %edi
	call	putchar@PLT
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	addl	$1, %eax
	imull	$150000, %eax, %eax
	movl	%eax, %edi
	call	usleep@PLT
	movl	$46, %edi
	call	putchar@PLT
	movl	$300000, %edi
	call	usleep@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L6:
	addl	$1, -16(%rbp)
.L2:
	cmpl	$484, -16(%rbp)
	jle	.L7
	movq	-8(%rbp), %rax
	movb	$97, (%rax)
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC10:
	.string	"Oh fuck something ain't right\r"
	.align 8
.LC11:
	.string	"I can feel it...end is coming for me"
	.align 8
.LC12:
	.string	"\033[H\033[JSegmentation fault (core dumped)"
	.text
	.globl	sigsegvHandler
	.type	sigsegvHandler, @function
sigsegvHandler:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$6, %edi
	call	sleep@PLT
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	stdout(%rip), %rax
	movq	%rax, %rdi
	call	fflush@PLT
	movl	$6, %edi
	call	sleep@PLT
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE7:
	.size	sigsegvHandler, .-sigsegvHandler
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
