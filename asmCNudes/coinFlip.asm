	.file	"coinFlip.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"HEADS"
.LC1:
	.string	"TAILS"
.LC2:
	.string	"\n\n"
.LC3:
	.string	"%d"
.LC4:
	.string	"Heads or tails?(H/T) :"
.LC5:
	.string	"%c"
.LC6:
	.string	"Congrats you little gambler"
.LC7:
	.string	"Better luck next time"
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
	sub	rsp, 32
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	edi, 0
	call	time@PLT
	mov	edi, eax
	call	srand@PLT
	call	rand@PLT
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 31
	add	edx, eax
	and	edx, 1
	sub	edx, eax
	mov	DWORD PTR -12[rbp], edx
	cmp	DWORD PTR -12[rbp], 0
	je	.L2
	lea	rax, .LC0[rip]
	mov	rdi, rax
	call	puts@PLT
	jmp	.L3
.L2:
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	puts@PLT
.L3:
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
	call	rand@PLT
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 31
	add	edx, eax
	and	edx, 1
	sub	edx, eax
	mov	DWORD PTR -12[rbp], edx
	mov	eax, DWORD PTR -12[rbp]
	mov	esi, eax
	lea	rax, .LC3[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, .LC4[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush@PLT
	lea	rax, -17[rbp]
	mov	rsi, rax
	lea	rax, .LC5[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	movzx	eax, BYTE PTR -17[rbp]
	movsx	eax, al
	cmp	eax, 72
	jne	.L4
	mov	DWORD PTR -16[rbp], 1
	jmp	.L5
.L4:
	mov	DWORD PTR -16[rbp], 0
	nop
.L5:
	mov	eax, DWORD PTR -12[rbp]
	cmp	eax, DWORD PTR -16[rbp]
	jne	.L6
	lea	rax, .LC6[rip]
	mov	rdi, rax
	call	puts@PLT
	jmp	.L7
.L6:
	lea	rax, .LC7[rip]
	mov	rdi, rax
	call	puts@PLT
.L7:
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
