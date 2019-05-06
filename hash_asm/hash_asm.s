	.file	"hash_asm.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.align 4
	.type	_ZL9yad_count, @object
	.size	_ZL9yad_count, 4
_ZL9yad_count:
	.long	119
	.text
	.globl	_Z8GNU_hashPKcc
	.type	_Z8GNU_hashPKcc, @function
_Z8GNU_hashPKcc:
.LFB1841:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -32(%rbp)
	movl	%esi, %eax
	movb	%al, -36(%rbp)
	movl	$5381, %ebx
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -9(%rbp)
.L3:
	movzbl	-9(%rbp), %edx
	movsbl	-36(%rbp), %eax
	cmpl	%eax, %edx
	je	.L2
	movl	%ebx, %eax
	sall	$5, %eax
	leal	(%rax,%rbx), %edx
	movzbl	-9(%rbp), %eax
	leal	(%rdx,%rax), %ebx
	addq	$1, -32(%rbp)
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -9(%rbp)
	jmp	.L3
.L2:
	movl	$274877907, %edx
	movl	%ebx, %eax
	imull	%edx
	sarl	$6, %edx
	movl	%ebx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$1000, %eax, %eax
	subl	%eax, %ebx
	movl	%ebx, %eax
	movl	%eax, %ebx
	movl	%ebx, %edx
	sarl	$31, %edx
	movl	%ebx, %eax
	xorl	%edx, %eax
	subl	%edx, %eax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1841:
	.size	_Z8GNU_hashPKcc, .-_Z8GNU_hashPKcc
	.globl	_Z9find_wordPK4listPKc
	.type	_Z9find_wordPK4listPKc, @function
_Z9find_wordPK4listPKc:
.LFB1842:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_Z8GNU_hashPKcc
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	_ZNK4list4sizeEv@PLT
	movq	%rax, -16(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	_ZNK4list4headEv@PLT
	movq	%rax, -8(%rbp)
	movq	-48(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_Z11search_compmP9list_elemPKc
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1842:
	.size	_Z9find_wordPK4listPKc, .-_Z9find_wordPK4listPKc
	.globl	_Z11search_compmP9list_elemPKc
	.type	_Z11search_compmP9list_elemPKc, @function
_Z11search_compmP9list_elemPKc:
.LFB1843:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
#APP
# 119 "hash_asm.cpp" 1
		pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
.L16:
	cmpq	$0, -16(%rbp)
	je	.L8
	movl	$0, %ebx
.L12:
	movslq	%ebx, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L9
	movslq	%ebx, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movslq	%ebx, %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L18
	addl	$1, %ebx
	nop
	jmp	.L12
.L18:
	nop
.L9:
	movslq	%ebx, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L13
	subq	$1, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L16
.L13:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	jmp	.L15
.L8:
	movl	$0, %eax
.L15:
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret

# 0 "" 2
#NO_APP
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1843:
	.size	_Z11search_compmP9list_elemPKc, .-_Z11search_compmP9list_elemPKc
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
