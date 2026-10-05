% ifdef YAPPING

    'Sup? Today we are making the simplest bootloader ever...
    Initial idea is fucking with the first stage boot loading without scope creeping into second stager 
    or loading the kernel

    and we'll test it using bosch for a few reasons:

    0- it uses GPL so I won't get sued
    1- it is a x86 emulator that supports processor(s) (including protected mode), 
    memory, disks, display, Ethernet, BIOS and common hardware peripherals of PCs. 
    2- I don't own a floppy disk yet

    resources: https://www.joe-bergeron.com/posts/Writing%20a%20Tiny%20x86%20Bootloader/

% endif



mov ax 0x7C0    ; ax, the lower 16 bits of 64 bit register rax and our bootlader starts here (goes for 512 bytes to 0x7E0 if I didn't fuck up the math)
mov ds, ax

mov ax, 0x7E0
mov ss, ax

mov sp, 0x2000






.clearscreen: 

    push bp
    mov bp, sp
    pusha ; before interuption we 'save' the current register values


    mov ah, 0x07; tells BIOS to fucking scroll
    mov al, 0x00; clears the window

    mov bh, 0x05; purple on black check: https://en.wikipedia.org/wiki/VGA_text_mode#BIOS_Color_Attribute

    mov cx, 0x00; marks top left as (0,0)
    mov dh, 0x18
    mov dl, 0x4f
    
