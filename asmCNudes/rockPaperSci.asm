	.file	"rockPaperSci.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Rock"
.LC1:
	.string	"Paper"
.LC2:
	.string	"Scissors"
.LC3:
	.string	"Rock, paper, scissors?"
.LC4:
	.string	" %s"
.LC5:
	.string	"Bro try not to be dumb."
	.align 8
.LC6:
	.string	"Try entering something useful next time?"
	.align 8
.LC7:
	.string	"You:%s\nAI(definitly not RNGsus):%s\n"
.LC8:
	.string	"Tie bitch"
.LC9:
	.string	"You won...yeah"
.LC10:
	.string	"You lost sucker"
.LC11:
	.string	"\nWanna try again (y/n): "
.LC12:
	.string	"\033[H\033J"
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
	sub	rsp, 80
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	edi, 0
	call	time@PLT
	mov	edi, eax
	call	srand@PLT
	lea	rax, .LC0[rip]
	mov	QWORD PTR -48[rbp], rax
	lea	rax, .LC1[rip]
	mov	QWORD PTR -40[rbp], rax
	lea	rax, .LC2[rip]
	mov	QWORD PTR -32[rbp], rax
.L20:
	call	rand@PLT
	mov	edx, eax
	movsx	rax, edx
	imul	rax, rax, 1431655766
	shr	rax, 32
	mov	ecx, edx
	sar	ecx, 31
	sub	eax, ecx
	mov	DWORD PTR -68[rbp], eax
	mov	ecx, DWORD PTR -68[rbp]
	mov	eax, ecx
	add	eax, eax
	add	eax, ecx
	sub	edx, eax
	mov	DWORD PTR -68[rbp], edx
	mov	eax, DWORD PTR -68[rbp]
	mov	DWORD PTR -56[rbp], eax
	cmp	DWORD PTR -68[rbp], 2
	jne	.L2
	mov	DWORD PTR -68[rbp], -1
.L2:
	mov	DWORD PTR -64[rbp], 0
	lea	rax, .LC3[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush@PLT
	lea	rax, -18[rbp]
	mov	rsi, rax
	lea	rax, .LC4[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	test	eax, eax
	jns	.L3
	lea	rax, .LC5[rip]
	mov	rdi, rax
	call	puts@PLT
	nop
.L5:
	call	getchar@PLT
	mov	DWORD PTR -52[rbp], eax
	cmp	DWORD PTR -52[rbp], 10
	je	.L4
	cmp	DWORD PTR -52[rbp], -1
	jne	.L5
.L4:
	mov	eax, -1
	jmp	.L21
.L3:
	lea	rax, -18[rbp]
	mov	rdi, rax
	call	puts@PLT
	movzx	eax, BYTE PTR -18[rbp]
	movsx	eax, al
	mov	edi, eax
	call	tolower@PLT
	mov	BYTE PTR -18[rbp], al
	movzx	eax, BYTE PTR -18[rbp]
	cmp	al, 114
	jne	.L7
	mov	DWORD PTR -64[rbp], 0
	jmp	.L8
.L7:
	movzx	eax, BYTE PTR -18[rbp]
	cmp	al, 112
	jne	.L9
	mov	DWORD PTR -64[rbp], 1
	jmp	.L8
.L9:
	movzx	eax, BYTE PTR -18[rbp]
	cmp	al, 115
	jne	.L10
	mov	DWORD PTR -64[rbp], -1
	jmp	.L8
.L10:
	lea	rax, .LC6[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	eax, -2
	jmp	.L21
.L8:
	mov	eax, DWORD PTR -56[rbp]
	cdqe
	mov	rdx, QWORD PTR -48[rbp+rax*8]
	lea	rax, -18[rbp]
	mov	rsi, rax
	lea	rax, .LC7[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 2
	call	sleep@PLT
	mov	eax, DWORD PTR -64[rbp]
	cmp	eax, DWORD PTR -68[rbp]
	jne	.L11
	lea	rax, .LC8[rip]
	mov	rdi, rax
	call	puts@PLT
	jmp	.L12
.L11:
	mov	eax, DWORD PTR -68[rbp]
	add	eax, 1
	cdqe
	mov	rdx, QWORD PTR -48[rbp+rax*8]
	mov	eax, DWORD PTR -64[rbp]
	cdqe
	mov	rax, QWORD PTR -48[rbp+rax*8]
	cmp	rdx, rax
	je	.L13
	cmp	DWORD PTR -64[rbp], -1
	jne	.L14
	cmp	DWORD PTR -68[rbp], 1
	jne	.L14
.L13:
	lea	rax, .LC9[rip]
	mov	rdi, rax
	call	puts@PLT
	jmp	.L12
.L14:
	lea	rax, .LC10[rip]
	mov	rdi, rax
	call	puts@PLT
.L12:
	lea	rax, .LC11[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush@PLT
	lea	rax, -18[rbp]
	mov	rsi, rax
	lea	rax, .LC4[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	test	eax, eax
	jns	.L15
	nop
.L18:
	call	getchar@PLT
	cmp	eax, 10
	je	.L16
	cmp	DWORD PTR -60[rbp], -1
	je	.L16
	mov	eax, 1
	jmp	.L17
.L16:
	mov	eax, 0
.L17:
	mov	DWORD PTR -60[rbp], eax
	cmp	DWORD PTR -60[rbp], 0
	jne	.L18
.L15:
	movzx	eax, BYTE PTR -18[rbp]
	movsx	eax, al
	cmp	eax, 110
	jne	.L19
	mov	eax, 0
	jmp	.L21
.L19:
	lea	rax, .LC12[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	jmp	.L20
.L21:
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L22
	call	__stack_chk_fail@PLT
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
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
