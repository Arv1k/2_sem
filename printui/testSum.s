section .text

global _Sum

_Sum:		push rbp
			mov rbp, rsp

			push rbx

			mov rax, [rbp + 16]
			mov rbx, [rbp + 24]

			add rax, rbx

			pop rbx
			pop rbp

			ret 16