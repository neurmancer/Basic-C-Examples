	.file	"important.c"
	.intel_syntax noprefix
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
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	edi, 0
	call	time@PLT
	mov	edi, eax
	call	srand@PLT
	lea	rax, sigsegvHandler[rip]
	mov	rsi, rax
	mov	edi, 11
	call	signal@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	ecx, 0
	mov	edx, 2
	mov	esi, 0
	mov	rdi, rax
	call	setvbuf@PLT
	lea	rax, .LC0[rip]
	mov	QWORD PTR -8[rbp], rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	DWORD PTR -16[rbp], 0
	jmp	.L2
.L7:
	mov	edx, DWORD PTR -16[rbp]
	movsx	rax, edx
	imul	rax, rax, 1296593901
	shr	rax, 32
	sar	eax, 4
	mov	ecx, edx
	sar	ecx, 31
	sub	eax, ecx
	imul	ecx, eax, 53
	mov	eax, edx
	sub	eax, ecx
	test	eax, eax
	jne	.L3
	lea	rax, .LC3[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 300000
	call	usleep@PLT
	mov	DWORD PTR -12[rbp], 0
	jmp	.L4
.L5:
	lea	rax, .LC4[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC5[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC6[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC7[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC4[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC5[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC6[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	lea	rax, .LC7[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 175250
	call	usleep@PLT
	add	DWORD PTR -12[rbp], 1
.L4:
	cmp	DWORD PTR -12[rbp], 4
	jle	.L5
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	jmp	.L6
.L3:
	lea	rax, .LC8[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	call	rand@PLT
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	eax, edx
	add	eax, 1
	imul	eax, eax, 150000
	mov	edi, eax
	call	usleep@PLT
	mov	edi, 46
	call	putchar@PLT
	call	rand@PLT
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	eax, edx
	add	eax, 1
	imul	eax, eax, 150000
	mov	edi, eax
	call	usleep@PLT
	mov	edi, 46
	call	putchar@PLT
	call	rand@PLT
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	eax, edx
	add	eax, 1
	imul	eax, eax, 150000
	mov	edi, eax
	call	usleep@PLT
	mov	edi, 46
	call	putchar@PLT
	mov	edi, 300000
	call	usleep@PLT
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
.L6:
	add	DWORD PTR -16[rbp], 1
.L2:
	cmp	DWORD PTR -16[rbp], 484
	jle	.L7
	mov	rax, QWORD PTR -8[rbp]
	mov	BYTE PTR [rax], 97
	mov	rax, QWORD PTR stderr[rip]
	mov	rcx, rax
	mov	edx, 5
	mov	esi, 1
	lea	rax, .LC9[rip]
	mov	rdi, rax
	call	fwrite@PLT
	mov	eax, 0
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
.LC13:
	.string	"\033[?25h"
	.text
	.globl	sigsegvHandler
	.type	sigsegvHandler, @function
sigsegvHandler:
.LFB7:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	DWORD PTR -4[rbp], edi
	lea	rax, .LC10[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 6
	call	sleep@PLT
	lea	rax, .LC11[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush@PLT
	mov	edi, 6
	call	sleep@PLT
	lea	rax, .LC12[rip]
	mov	rdi, rax
	call	puts@PLT
	lea	rax, .LC13[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 1
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
