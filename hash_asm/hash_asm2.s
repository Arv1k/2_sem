	.file	"hash_asm2.cpp"
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
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movb	%al, -28(%rbp)
	movl	$5381, -4(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -5(%rbp)
.L3:
	movzbl	-5(%rbp), %edx
	movsbl	-28(%rbp), %eax
	cmpl	%eax, %edx
	je	.L2
	movl	-4(%rbp), %edx
	movl	%edx, %eax
	sall	$5, %eax
	addl	%eax, %edx
	movzbl	-5(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	addq	$1, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -5(%rbp)
	jmp	.L3
.L2:
	movl	-4(%rbp), %ecx
	movl	$274877907, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$6, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$1000, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltd
	movl	%edx, %eax
	xorl	-4(%rbp), %eax
	subl	%edx, %eax
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
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movl	$0, %r13d
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %r12
	movl	$0, %ebx
.L16:
	cmpq	$0, -40(%rbp)
	je	.L8
	movq	-48(%rbp), %rax
	movq	(%rax), %r13
	movl	$0, %ebx
.L12:
	movl	%ebx, %eax
	cmpq	%rax, %r12
	jbe	.L9
	movl	%ebx, %edx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	%ebx, %eax
	addq	%r13, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L18
	nop
	addl	$1, %ebx
	jmp	.L12
.L18:
	nop
.L9:
	movl	%ebx, %eax
	cmpq	%rax, %r12
	je	.L13
	subq	$1, -40(%rbp)
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	.L16
.L13:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	jmp	.L15
.L8:
	movl	$0, %eax
.L15:
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1843:
	.size	_Z11search_compmP9list_elemPKc, .-_Z11search_compmP9list_elemPKc
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
