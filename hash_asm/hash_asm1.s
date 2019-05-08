	.file	"hash_asm1.cpp"
	.text
	.p2align 4,,15
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
	.p2align 4,,10
	.p2align 3
.L3:
	movl	%ecx, %edx
	addq	$1, %rdi
	sall	$5, %edx
	addl	%edx, %ecx
	addl	%eax, %ecx
	movzbl	(%rdi), %eax
	cmpl	%esi, %eax
	jne	.L3
	movl	%ecx, %eax
	movl	$274877907, %edx
	imull	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	sarl	$6, %edx
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	$1000, %edx, %edx
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movl	$381, %eax
	ret
	.cfi_endproc
.LFE1939:
	.size	_Z8GNU_hashPKcc, .-_Z8GNU_hashPKcc
	.p2align 4,,15
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
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movzbl	(%rsi), %r8d
	testb	%r8b, %r8b
	je	.L15
	movq	%rsi, %rax
	movl	$5381, %ecx
	.p2align 4,,10
	.p2align 3
.L9:
	movl	%ecx, %edx
	addq	$1, %rax
	sall	$5, %edx
	addl	%edx, %ecx
	addl	%r8d, %ecx
	movzbl	(%rax), %r8d
	testb	%r8b, %r8b
	jne	.L9
	movl	%ecx, %eax
	movl	$274877907, %edx
	mull	%edx
	shrl	$6, %edx
	imull	$1000, %edx, %edx
	subl	%edx, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,2), %r12
	salq	$3, %r12
.L8:
	addq	%rdi, %r12
	movq	%r12, %rdi
	call	_ZNK4list4sizeEv@PLT
	movq	%r12, %rdi
	movq	%rax, %rbx
	call	_ZNK4list4headEv@PLT
	testq	%rbx, %rbx
	movq	%rax, %rdx
	je	.L18
	movzbl	0(%rbp), %ecx
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L12:
	subq	$1, %rbx
	movq	8(%rdx), %rdx
	je	.L18
.L14:
	testb	%cl, %cl
	movq	(%rdx), %rax
	je	.L7
	cmpb	(%rax), %cl
	jne	.L12
	movl	$1, %esi
.L11:
	movzbl	0(%rbp,%rsi), %edi
	testb	%dil, %dil
	je	.L7
	addq	$1, %rsi
	cmpb	-1(%rax,%rsi), %dil
	je	.L11
	subq	$1, %rbx
	movq	8(%rdx), %rdx
	jne	.L14
	.p2align 4,,10
	.p2align 3
.L18:
	xorl	%eax, %eax
.L7:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	.cfi_restore_state
	movl	$9144, %r12d
	jmp	.L8
	.cfi_endproc
.LFE1940:
	.size	_Z9find_wordPK4listPKc, .-_Z9find_wordPK4listPKc
	.p2align 4,,15
	.globl	search_comp
	.type	search_comp, @function
search_comp:
.LFB1941:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L33
	movzbl	(%rdx), %ecx
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L28:
	subq	$1, %rdi
	movq	8(%rsi), %rsi
	je	.L33
.L30:
	testb	%cl, %cl
	movq	(%rsi), %rax
	je	.L25
	cmpb	(%rax), %cl
	jne	.L28
	movl	$1, %r8d
.L27:
	movzbl	(%rdx,%r8), %r9d
	testb	%r9b, %r9b
	je	.L38
	addq	$1, %r8
	cmpb	-1(%rax,%r8), %r9b
	je	.L27
	subq	$1, %rdi
	movq	8(%rsi), %rsi
	jne	.L30
.L33:
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L25:
	rep ret
	.p2align 4,,10
	.p2align 3
.L38:
	rep ret
	.cfi_endproc
.LFE1941:
	.size	search_comp, .-search_comp
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
