	.file	"hash_asm.cpp"
	.text
	.globl	_Z8GNU_hashPKcc
	.type	_Z8GNU_hashPKcc, @function
_Z8GNU_hashPKcc:
.LFB1939:
	.cfi_startproc
	movzbl	(%rdi), %eax
	movsbl	%sil, %esi
	cmpl	%esi, %eax
	je	.L4
	movl	$5381, %ecx
.L3:
	movl	%ecx, %edx
	sall	$5, %edx
	addl	%edx, %ecx
	addl	%eax, %ecx
	addq	$1, %rdi
	movzbl	(%rdi), %eax
	cmpl	%esi, %eax
	jne	.L3
.L2:
	movl	$274877907, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$6, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	imull	$1000, %edx, %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	ret
.L4:
	movl	$5381, %ecx
	jmp	.L2
	.cfi_endproc
.LFE1939:
	.size	_Z8GNU_hashPKcc, .-_Z8GNU_hashPKcc
	.globl	_Z11search_compmP9list_elemPKc
	.type	_Z11search_compmP9list_elemPKc, @function
_Z11search_compmP9list_elemPKc:
.LFB1941:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L13
	movzbl	(%rdx), %eax
	jmp	.L12
.L13:
	movl	$0, %eax
	ret
.L17:
	movl	$0, %eax
	ret
.L10:
	movq	8(%rsi), %rsi
	subq	$1, %rdi
	je	.L17
.L12:
	testb	%al, %al
	je	.L8
	movq	(%rsi), %rcx
	cmpb	(%rcx), %al
	jne	.L10
	movl	$0, %r8d
.L9:
	addl	$1, %r8d
	movslq	%r8d, %r10
	movzbl	(%rdx,%r10), %r9d
	testb	%r9b, %r9b
	je	.L8
	cmpb	(%rcx,%r10), %r9b
	jne	.L10
	jmp	.L9
.L8:
	movq	(%rsi), %rax
	ret
	.cfi_endproc
.LFE1941:
	.size	_Z11search_compmP9list_elemPKc, .-_Z11search_compmP9list_elemPKc
	.globl	_Z9find_wordPK4listPKc
	.type	_Z9find_wordPK4listPKc, @function
_Z9find_wordPK4listPKc:
.LFB1940:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbp
	movq	%rsi, %rbx
	movl	$0, %esi
	movq	%rbx, %rdi
	call	_Z8GNU_hashPKcc
	cltq
	leaq	(%rax,%rax,2), %rax
	leaq	0(%rbp,%rax,8), %rbp
	movq	%rbp, %rdi
	call	_ZNK4list4sizeEv@PLT
	movq	%rax, %r12
	movq	%rbp, %rdi
	call	_ZNK4list4headEv@PLT
	movq	%rbx, %rdx
	movq	%rax, %rsi
	movq	%r12, %rdi
	call	_Z11search_compmP9list_elemPKc
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1940:
	.size	_Z9find_wordPK4listPKc, .-_Z9find_wordPK4listPKc
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
