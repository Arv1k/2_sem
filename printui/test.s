section .text

global main

;-------------------------------------------
extern printf
;-------------------------------------------

main:	;push '!'
		;push 100
		;push 3802
		;push Txt
		;push 0b0
		;push 3565
		;push '<'
		;push buf2
		;call printui

		xor rax, rax
		mov rdx, 12
		mov rsi, 3565
		mov rdi, buf2
		call printf

		mov rax, 0x03c
		xor rdi, rdi
		syscall


section .data

buf2:		db 'Max pid#r %d %c', 0x0a, 0x00
Txt:		db 'love', 0x00
