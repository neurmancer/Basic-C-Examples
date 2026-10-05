%ifdef YAPPING

    'Sup? Today we are making the simplest bootloader ever...
    Initial idea is fucking with the first stage boot loading without scope creeping into second stager 
    or loading the kernel

    and we'll test it using bosch for a few reasons:

    0- it uses GPL so I won't get sued
    1- it is a x86 emulator that supports processor(s) (including protected mode), 
    memory, disks, display, Ethernet, BIOS and common hardware peripherals of PCs. 
    2- I don't own a floppy disk yet

    resources: https://www.joe-bergeron.com/posts/Writing%20a%20Tiny%20x86%20Bootloader/

    to create the asm object: nasm -f bin miserable_bootloader -o boot.com
    to try the fucker: bochs -f bochsrc.txt
%endif

    bits 16


    mov ax, 0x7C0    ; ax, the lower 16 bits of 64 bit register rax and our bootlader starts here
    mov ds, ax

    mov ax, 0x7E0
    mov ss, ax

    mov sp, 0x2000


    call clearscreen

    push 0000
    call movecursor

    add sp, 2

    push thing
    call print
    add sp, 2

.halt:
    cli
    hlt
    jmp .halt



clearscreen: 

    push bp
    mov bp, sp
    pusha ; before interuption we 'save' the current register values


    mov ah, 0x07; tells BIOS to fucking scroll
    mov al, 0x00; clears the window

    mov bh, 0x05; purple on black check: https://en.wikipedia.org/wiki/VGA_text_mode#BIOS_Color_Attribute

    mov cx, 0x00; marks top left as (0,0)
    mov dh, 0x18
    mov dl, 0x4f
    int 0x10; video interrupt call

    popa
    mov sp, bp
    pop bp

    ret 


movecursor:
    push bp
    mov bp, sp
    pusha

    mov dx, [bp+4] ; [] is just pointer notation
    mov ah, 0x02     
    mov bh, 0       ; select display page 0, matching print
    
    int 0x10

    popa
    mov sp, bp
    pop bp
    ret


print:
	push bp
	mov bp, sp
	pusha
	
    mov si, [bp+4]	 	; grab the pointer to the data
	mov bh, 00h
    mov bl, 00h
	mov ah, 0Eh  		; print character to TTY
 
 .char:

	mov al, [si]   		; get the current char from our pointer position
	add si, 1		; keep incrementing si till we see \0
	
    or al, 0
	
    je .return        	
	
    int 10h         	; print the character if we're not done
	
    jmp .char	  	; keep on fucking going
 
 .return:
	popa
	mov sp, bp
	pop bp
	ret

; BIOS teletype needs CR (13) + LF (10) to start at column 0 on the next row.
; Ordinary NASM strings keep backslashes literal, handy for ASCII art.
thing:
    db "  +-------------------------+",13,10
    db "  |  NeurOS boot sequence   |",13,10
    db "  +-------------------------+",13,10
    db "          /\_/\",13,10
    db "         ( o.o )",13,10
    db "          > ^ <",13,10,13,10
    db "  No kernel yet. Have a prime: 13",13,10,0
    times 510-($-$$) db 0
    dw 0xAA55
