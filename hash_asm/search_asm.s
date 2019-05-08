section .text

global search_comp
;-----------------------------------------------
;
;-----------------------------------------------

search_comp:     test rdi, rdi
                 je .exit

.begin           movzx ecx, byte [rdx]
                 mov rax, qword [rsi]
                 cmp cl, byte [rax]
                 jne .next_word

                 mov rbx, 0x1

.loop1           movzx ecx, byte [rdx + rbx]
                 test cl, cl
                 je .found

                 cmp cl, byte [rax + rbx]
                 jne .next_word

                 inc rbx
                 jmp .loop1

.next_word:      sub rdi, 0x1
                 je .exit
                 mov rsi, qword [rsi + 0x8]
                 jmp .begin

.exit            xor rax, rax
.found:          ret
