section .text


x890:			inc rsi
				mov al, [rsi]

				add r13b, al
				cmp al, 0x31

				je xa27

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk

right_pas:		mov rdi, R_password
				call slowprint
				jmp exit_DateAsk

x8c5:			mov al, [rsi]

				add r13, rax
				cmp al, 0x31

				je x91f

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk

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

				jmp farara

away:			mov r12, 0x264
				ret
farara:
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

				inc r15
				mov cl, [rbx]
				cmp cl, 0x00
				jne rep_slowprint

				pop rax
				pop rcx
				pop rbx
				pop rbp


				mov rax, r15
				ret



section .text

x91f:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x36

				je x99e

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk


x93c:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x30

				je x890

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk


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


x96a:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x2e

				je x984

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk



section .text


x984:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x32

				je x93c

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk

x99e:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x2e

				je xa0d

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk

section .text

global DateAsking
;------------------------------------------
;
;------------------------------------------

DateAsking:		push rdi
				push rsi
				push rdx
				push r11
				push rcx
				push rbx

				mov rdi, 0x00
				mov rsi, buf_DateAsk
				mov rdx, 11
				mov rax, 0x00
				syscall

				xor r13, r13
				xor rax, rax
				jmp x8c5

exit_DateAsk:	pop rbx
				pop rcx
				pop r11
				pop rdx
				pop rsi
				pop rdi

				mov rax, r13

				ret


x9ef:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x37

				je x96a

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk



section .data

R_password:		db "You're right!", 0x0a, 0x00
W_password:		db "Nope!", 0x0a, 0x00

section .bss

buf_DateAsk:		resb 11

section .text

xa0d:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x30

				je x9ef

				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk


xa27:			inc rsi
				mov al, [rsi]

				add r13, rax
				cmp al, 0x36

				mov rax, r13
				je right_pas

				dec rax
				mov rdi, W_password
				call slowprint
				jmp exit_DateAsk


section .text

global CatAsking
;----------------------------------------
;
;----------------------------------------

CatAsking:		push rdi
				push rsi
				push rdx
				push r11
				push rcx
				push rbx

				sub rsp, 8

				mov rdi, 0x01
				mov rsi, rsp
				mov rdx, 120
				mov rax, 0x00
				syscall

				xor rax, rax
				xor rcx, rcx
				xor rdx, rdx

				mov rcx, 6

cat_loop:		mov al, [rsi]
				add rdx, rax

				inc rsi
				loop cat_loop

				call away

				cmp r12, rdx
				je molodec

				mov rdi, ne_molorik
				call slowprint

exit_cat:		add rsp, 8

				pop rbx
				pop rcx
				pop r11
				pop rdx
				pop rsi
				pop rdi

				mov rax, rbx

				ret

molodec:		mov rdi, molorik
				call slowprint
				jmp exit_cat

section .data

molorik:		db 0x0a, 'Ty molodec!', 0xa, 0x0
ne_molorik:		db 'Nope!', 0x0a, 0x0
