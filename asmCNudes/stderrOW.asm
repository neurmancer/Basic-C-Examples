	.file	"stderrOW.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"output.txt"
.LC2:
	.string	"freopen failed"
	.align 8
.LC3:
	.string	"Yet were I a flame I'd be still lighting your cigs on an abyss"
	.align 8
.LC4:
	.string	"Git Gut bro Segfault isn't C's fault\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	rax, QWORD PTR stdout[rip]
	mov	rdx, rax
	lea	rax, .LC0[rip]
	mov	rsi, rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	freopen@PLT
	test	rax, rax
	jne	.L2
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	perror@PLT
	mov	eax, 1
	jmp	.L3
.L2:
	lea	rax, .LC3[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rax, QWORD PTR stderr[rip]
	mov	rcx, rax
	mov	edx, 37
	mov	esi, 1
	lea	rax, .LC4[rip]
	mov	rdi, rax
	call	fwrite@PLT
	mov	eax, 0
.L3:
	pop	rbp
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
