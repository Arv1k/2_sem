	.file	"hash_asm1.cpp"
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
	.globl	search_comp
	.type	search_comp, @function
search_comp:
.LFB1941:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L12
	movzbl	(%rdx), %ecx
	jmp	.L11
.L16:
	rep ret
.L12:
	movl	$0, %eax
	ret
.L15:
	movl	$0, %eax
	ret
.L9:
	movq	8(%rsi), %rsi
	subq	$1, %rdi
	je	.L15
.L11:
	movq	(%rsi), %rax
	testb	%cl, %cl
	je	.L6
	cmpb	(%rax), %cl
	jne	.L9
	movl	$1, %r8d
.L8:
	movzbl	(%rdx,%r8), %r9d
	testb	%r9b, %r9b
	je	.L16
	addq	$1, %r8
	cmpb	-1(%rax,%r8), %r9b
	jne	.L9
	jmp	.L8
.L6:
	rep ret
	.cfi_endproc
.LFE1941:
	.size	search_comp, .-search_comp
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
	call	search_comp
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
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
