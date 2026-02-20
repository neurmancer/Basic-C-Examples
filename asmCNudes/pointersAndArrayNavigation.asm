	.file	"pointersAndArrayNavigation.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%p\t%2d\n"
.LC1:
	.string	"Am I gay tho"
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
	sub	rsp, 64
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	edi, 0
	call	time@PLT
	mov	edi, eax
	call	srand@PLT
	pxor	xmm0, xmm0
	movaps	XMMWORD PTR -32[rbp], xmm0
	movd	DWORD PTR -16[rbp], xmm0
	lea	rax, -32[rbp]
	mov	QWORD PTR -56[rbp], rax
	jmp	.L2
.L3:
	call	rand@PLT
	movsx	rdx, eax
	imul	rdx, rdx, 680390859
	shr	rdx, 32
	sar	edx, 4
	mov	ecx, eax
	sar	ecx, 31
	sub	edx, ecx
	imul	ecx, edx, 101
	sub	eax, ecx
	mov	edx, eax
	mov	rax, QWORD PTR -56[rbp]
	mov	DWORD PTR [rax], edx
	add	QWORD PTR -56[rbp], 4
.L2:
	lea	rax, -32[rbp]
	add	rax, 20
	cmp	QWORD PTR -56[rbp], rax
	jb	.L3
	lea	rax, -32[rbp]
	mov	QWORD PTR -48[rbp], rax
	jmp	.L4
.L5:
	mov	rax, QWORD PTR -48[rbp]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR -48[rbp]
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	add	QWORD PTR -48[rbp], 4
.L4:
	lea	rax, -32[rbp]
	add	rax, 20
	cmp	QWORD PTR -48[rbp], rax
	jb	.L5
	lea	rax, .LC1[rip]
	mov	QWORD PTR -40[rbp], rax
	jmp	.L6
.L7:
	mov	rax, QWORD PTR -40[rbp]
	movzx	eax, BYTE PTR [rax]
	movsx	eax, al
	mov	edi, eax
	call	putchar@PLT
	add	QWORD PTR -40[rbp], 1
.L6:
	mov	rax, QWORD PTR -40[rbp]
	movzx	eax, BYTE PTR [rax]
	test	al, al
	jne	.L7
	mov	edi, 10
	call	putchar@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
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
