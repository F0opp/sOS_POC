[BITS 32]

extern sOS

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
	; entry address tag (type=3)
	align 8
	dw 3, 0
	dd 12
	dd start
	
	; end tag
	align 8
	dw 0, 0
	dd 8
multiboot_header_end:

SECTION .data 
string: db 'Welcome to sOS!', 0

;entry point
SECTION .text
start:
    mov esp, _sys_stack
    call sOS
    jmp stublet

stublet:
    jmp $

SECTION .bss
	resb 8192
_sys_stack: 