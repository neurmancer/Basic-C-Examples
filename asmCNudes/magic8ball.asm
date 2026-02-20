	.file	"magic8ball.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Yup"
.LC1:
	.string	"Nope"
.LC2:
	.string	"Maybe if you git gut"
.LC3:
	.string	"Eventually"
.LC4:
	.string	"if you never gonna give up"
.LC5:
	.string	"When pigs start to fly"
.LC6:
	.string	"When the hell freezes"
.LC7:
	.string	"Fuck you mean by that?"
	.align 8
.LC8:
	.string	"I know the answer but ain't gonna tell you for free.Feed me LLM tokens to get your answers."
	.align 8
.LC9:
	.string	"Ask your desired question(and please make it Y/N question):"
.LC10:
	.string	" %s"
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
	sub	rsp, 176
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	edi, 0
	call	time@PLT
	mov	edi, eax
	call	srand@PLT
	lea	rax, .LC0[rip]
	mov	QWORD PTR -160[rbp], rax
	lea	rax, .LC1[rip]
	mov	QWORD PTR -152[rbp], rax
	lea	rax, .LC2[rip]
	mov	QWORD PTR -144[rbp], rax
	lea	rax, .LC3[rip]
	mov	QWORD PTR -136[rbp], rax
	lea	rax, .LC4[rip]
	mov	QWORD PTR -128[rbp], rax
	lea	rax, .LC5[rip]
	mov	QWORD PTR -120[rbp], rax
	lea	rax, .LC6[rip]
	mov	QWORD PTR -112[rbp], rax
	lea	rax, .LC7[rip]
	mov	QWORD PTR -104[rbp], rax
	lea	rax, .LC8[rip]
	mov	QWORD PTR -96[rbp], rax
	mov	DWORD PTR -168[rbp], 9
	call	rand@PLT
	cdq
	idiv	DWORD PTR -168[rbp]
	mov	DWORD PTR -164[rbp], edx
	mov	QWORD PTR -80[rbp], 0
	mov	QWORD PTR -72[rbp], 0
	mov	QWORD PTR -64[rbp], 0
	mov	QWORD PTR -56[rbp], 0
	mov	QWORD PTR -48[rbp], 0
	mov	QWORD PTR -40[rbp], 0
	mov	QWORD PTR -32[rbp], 0
	mov	QWORD PTR -24[rbp], 0
	lea	rax, .LC9[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush@PLT
	lea	rax, -80[rbp]
	mov	rsi, rax
	lea	rax, .LC10[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	mov	eax, DWORD PTR -164[rbp]
	cdqe
	mov	rax, QWORD PTR -160[rbp+rax*8]
	mov	rdi, rax
	call	puts@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
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
