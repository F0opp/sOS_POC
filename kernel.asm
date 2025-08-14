[BITS 32]
[ORG 0x100000]   

;Multiboot2 header consts
MULTIBOOT_HEADER_MAGIC equ 0xE85250D6
MULTIBOOT_HEADER_FLAGS equ 0x00000000
MULTIBOOT_HEADER_LENGTH equ multiboot_header_end - multiboot_header_start
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS + MULTIBOOT_HEADER_LENGTH)
MULTIBOOT_TYPE_3 equ 3
MULTIBOOT_TYPE_0 equ 0

multiboot_header_start:
	align 8
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_LENGTH 
	dd MULTIBOOT_CHECKSUM 
	
	;tags
    align 8
    dw 2 ;type = 2 (address tag)
    dw 0 ;flags = 0
    dd 24 ;size = 24 bytes
    dd multiboot_header_start ;header_addr (runtime phys addr)
    dd 0x100000 ;load_addr  (where to load file)
    dd 0 ;load_end_addr (0 = file size)
    dd 0 ;size of this tag (must be 8)
	
	align 8
    dw 3 ;type = 3
    dw 0 ;flags = 0
    dd 12 ;size = 12 bytes
    dd start
	
	;end tag
    align 8
    dw 0 ;type = 0 (end)
    dw 0
    dd 8 ;size = 8
multiboot_header_end:

SECTION .data 
string: db 'Welcome to sOS!', 0

;entry point
SECTION .text
start:
    mov esp, _sys_stack
    mov edi, 0xB8000

    mov esi, string
    mov ah, 0x0F
	print:
		mov al, [esi]
		cmp al, 0
		je stublet
		inc esi
		stosw
		jmp print
    jmp stublet

stublet:
    jmp $

SECTION .bss
	resb 8192
_sys_stack: 