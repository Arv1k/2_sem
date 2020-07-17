section .text

global slowprint
;------------------------------------------
; slowprint - slow char by char printing.
;			  String must exist '\0'!
;
; Entry: 	  rdi - pointer to string
;
; Exit:
;
; Destroy:	  flags, rdi, rdx, r11
;------------------------------------------

slowprint:		push rbp
				mov rbp, rsp

				push rbx
				push rcx
				push rax

				xor rbx, rbx
				xor rax, rax

				mov rbx, rdi
				dec rbx

rep_slowprint:	inc rbx

				mov rax, 0x01
				mov rsi, rbx
				mov rdi, 1
				mov rdx, 1
				syscall

				xor rcx, rcx

				mov rcx, 60000000

time_lim:		loop time_lim

				mov cl, [rbx]
				cmp cl, 0x00
				jne rep_slowprint

				pop rax
				pop rcx
				pop rbx
				pop rbp

				ret




section .text

global delay
;------------------------------------------
; delay - loop to wait
;
; Entry:
;
; Exit:
;
; Destroy:
;------------------------------------------

delay:			push rcx

				xor rcx,rcx
				mov rcx, 120000000

time_delay:		loop time_delay

				pop rcx

				ret




section .text

global _printui
;------------------------------------------------
;
;------------------------------------------------

_printui:	pop r14

			push r9
			push r8
			push rcx
			push rdx
			push rsi
			push rdi

			call printui

			add rsp, rax

			push r14

			ret




section .text

global printui
;------------------------------------------------
; printui - printf("string", op1, op2, ...)
;
; Entry:	pointer to string,
;		operators in stack
;
; Exit:
;
; Destroy:
;------------------------------------------------

printui:	push rbp	; saving bp
		mov rbp, rsp

		push r8 ; saving registers
		push rdx
		push rsi
		push r9
		push rdi
		push r12
		push r13
		push r14

		xor r13, r13

		mov r12, 16

		xor r8, r8	; saving pointer to string
		mov r8,  [rbp + r12]
		mov rdi, r8

rep1:	xor rax, rax
		mov rax, '%'

		call strChr

		cmp rdi, 0
		je onlyStr

		mov al, [rdi + 1]
		mov r9, rax

		jmp whoRu


onlyStr:	xor rax, rax
		mov rax, 0x00
		mov rdi, r8

		call strChr

		cmp rdi, 0
		je exitt

		mov rsi, r8	; printing

		sub rdi, r8
		mov rdx, rdi

		mov rdi, 1
		mov rax, 0x01

		syscall

exitt:	mov rax, r13

		pop r14
		pop r13
		pop r12
		pop rdi
		pop r9
		pop rsi
		pop rdx
	 	pop r8
		pop rbp

		ret

whoRu:		push rsi
		push rax
		push rdx
		push rbx
		push r11

		mov rsi, r8

		sub rdi, r8
		mov rdx, rdi

		mov rdi, 1
		mov rax, 0x01

		syscall

		add r8, rdx
		add r8, 2

		cmp r9, '%'
		je Perc

		add r12, 8
		inc r13

		cmp r9, 'c'
		je Chr

		cmp r9, 's'
		je Str

		cmp r9, 'd'
		je Dec

		cmp r9, 'x'
		je Hex

		cmp r9, 'b'
		je Bin

		mov rax, 0x03c
		xor rdi, rdi
		syscall

Bin:		mov rax, [rbp + r12]
		xor r11, r11
		mov r11, bufSize - 1

		xor rcx, rcx

toBin:		mov rdx, rax
		shr rdx, cl

		cmp rdx, 0
		je print

		and dl, 0b00000001
		add dl, '0'

		mov [buf + r11], dl

		dec r11

		inc cl
		cmp cl, 0x40
		jne toBin

print:		mov r14, r11

		mov rsi, buf
		mov rdx, bufSize
		mov rdi, 1
		mov rax, 0x01

		syscall

		xor rcx, rcx
		mov rcx, bufSize
		sub rcx, r14

		mov al, 0x00
		mov rdi, buf
		add rdi, r14

		cld
		repne stosb

		jmp ifindU


Hex:		mov rax, [rbp + r12]
		xor r11, r11
		mov r11, bufSize - 1

toHex:		xor rdx, rdx
		mov rbx, 16

		div rbx

		mov rbx, mat16
		add rbx, rdx

		mov dl, [rbx]
		mov [buf + r11], dl

		dec r11
		cmp rax, 0
		jne toHex

		mov r14, r11

		mov rsi, buf
		mov rdx, bufSize
		mov rdi, 1
		mov rax, 0x01

		syscall

		xor rcx, rcx
		mov rcx, bufSize
		sub rcx, r14

		mov al, 0x00
		mov rdi, buf
		add rdi, r14

		cld
		repne stosb

		jmp ifindU

Dec:	mov rax, [rbp + r12]
		xor r11, r11
		mov r11, bufSize - 1

toDec:	xor rdx, rdx
		mov rbx, 10

		div rbx

		mov rbx, mat10
		add rbx, rdx

		mov dl, [rbx]
		mov [buf + r11], dl

		dec r11
		cmp rax, 0
		jne toDec

		mov r14, r11

		mov rsi, buf
		mov rdx, bufSize
		mov rdi, 1
		mov rax, 0x01

		syscall

		xor rcx, rcx
		mov rcx, bufSize
		sub rcx, r14

		mov al, 0x00
		mov rdi, buf
		add rdi, r14

		cld
		rep stosb

		jmp ifindU


Str:	mov rsi, [rbp + r12]
		mov rdi, rsi

		mov rax, 0x00

		call strChr

		cmp rdi, 0
		je exitt

		sub rdi, rsi
		mov rdx, rdi
		mov rdi, 1
		mov rax, 0x01

		syscall
		jmp ifindU

Chr:		mov rax, [rbp + r12]
		mov [buf], al
		mov rsi, buf
		mov rdi, 1
		mov rax, 0x01
		mov rdx, 1

		syscall

		mov al, 0x00
		mov [buf], al

		jmp ifindU

Perc:		mov rax, '%'
		mov [buf], al
		mov rsi, buf
		mov rdi, 1
		mov rax, 0x01
		mov rdx, 1

		syscall

		mov al, 0x00
		mov [buf], al

ifindU:		pop r11
		pop rbx
		pop rdx
		pop rax
		pop rsi

		mov rdi, r8

		jmp rep1


section .bss

buf:		resb 64
bufSize:	equ $ - buf


section .data

mat10:		db '0123456789'
mat16:		db '0123456789abcdef'




section .text

global strChr
;-------------------------------------------------
; strchr - finding the char in string
;
; Entry:	rdi - pointer to string
;		rax - missed char
;
; Exit:		rdi - pointer to the first
;		      occurance of the char in the
;		      string
;
; Destroy:	flags C, P, A, Z, S
;-------------------------------------------------

strChr:		push rbx

repeat:		mov bl, [rdi]

		cmp bl, al
		je found

		cmp bl, 0
		je notFound

		inc rdi
		jmp repeat

notFound:	pop rbx
		xor rdi, rdi
		ret

found:		pop rbx
		ret




global memCpy
;-------------------------------------------------
; memcpy - copying n bytes from source to dest
;
; Entry:	rsi - source string
;		rdi - dest string
;		rcx - n bytes
;
; Exit: 	rsi - pointer to source string
;		rdi - pointer to dest string
;
; Destroy:	rcx
;		flags P, Z
;-------------------------------------------------

memCpy:		push rax

		xor rax, rax
		mov rax, rcx

		cld

		repne movsb

		sub rdi, rax
		sub rsi, rax

		pop rax
		ret
