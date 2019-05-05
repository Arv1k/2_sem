section .text

global _start

;---------------------------------------------
extern CatAsking
;---------------------------------------------

_start:			call CatAsking

				mov rax, 0x03c
				xor rdi, rdi
				syscall

section .data

str:			db '123456', 0xa, 0x0
