section .text

global _start

_start:     times 5000 db 0x90

	    mov rax, 0x3c
            xor rdi, rdi
            syscall
