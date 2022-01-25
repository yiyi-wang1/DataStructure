	.file	"guessing-game.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Make a guess:"
.LC1:
	.string	"%d"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Error: please pick a number from 1 to 50."
	.section	.rodata.str1.1
.LC3:
	.string	"No, guess higher!"
.LC4:
	.string	"No, guess lower!"
.LC5:
	.string	"You got it!"
	.text
	.p2align 4,,15
	.globl	guess
	.type	guess, @function
guess:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%edx, %edx
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%edi, %ebx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movl	$0, (%rsp)
	.p2align 4,,10
	.p2align 3
.L2:
	cmpl	%edx, %ebx
	je	.L13
.L8:
	movl	$.LC0, %edi
	xorl	%eax, %eax
	addl	$1, %ebp
	call	printf
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC1, %edi
	call	__isoc99_scanf
	movl	(%rsp), %edx
	testl	%edx, %edx
	je	.L10
	cmpl	$50, %edx
	jg	.L10
	cmpl	%edx, %ebx
	jg	.L14
	.p2align 4,,6
	jl	.L15
	cmpl	%edx, %ebx
	.p2align 4,,7
	jne	.L2
	movl	$.LC5, %edi
	call	puts
	movl	(%rsp), %edx
	cmpl	%edx, %ebx
	jne	.L8
	.p2align 4,,10
	.p2align 3
.L13:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	%ebp, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
	movl	$.LC2, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L14:
	movl	$.LC3, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L15:
	movl	$.LC4, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L2
	.cfi_endproc
.LFE20:
	.size	guess, .-guess
	.section	.rodata.str1.8
	.align 8
.LC6:
	.string	"======================================"
	.align 8
.LC7:
	.string	"CPU Says: picked a number from 1 to 50"
	.align 8
.LC8:
	.string	"================================================"
	.align 8
.LC9:
	.string	"Here are the results of your guessing abilities!"
	.align 8
.LC10:
	.string	"Game %d you took you %d guesses\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB21:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	leaq	16(%rsp), %r12
	movl	$0, 16(%rsp)
	movl	$0, 20(%rsp)
	movl	$0, 24(%rsp)
	movl	$0, 28(%rsp)
	leaq	20(%r12), %r13
	movl	$0, 32(%rsp)
.L25:
	movl	$.LC6, %edi
	xorl	%ebp, %ebp
	call	puts
	movl	$.LC7, %edi
	call	puts
	movl	$.LC6, %edi
	call	puts
	xorl	%edi, %edi
	call	time
	movl	%eax, %edi
	call	srand
	call	rand
	movl	$1374389535, %edx
	movl	%eax, %ebx
	movl	$0, (%rsp)
	imull	%edx
	movl	%ebx, %eax
	sarl	$31, %eax
	sarl	$4, %edx
	subl	%eax, %edx
	movl	$50, %eax
	imull	%eax, %edx
	subl	%edx, %ebx
	xorl	%edx, %edx
	addl	$1, %ebx
	.p2align 4,,10
	.p2align 3
.L17:
	cmpl	%ebx, %edx
	je	.L32
.L23:
	movl	$.LC0, %edi
	xorl	%eax, %eax
	addl	$1, %ebp
	call	printf
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC1, %edi
	call	__isoc99_scanf
	movl	(%rsp), %edx
	testl	%edx, %edx
	je	.L29
	cmpl	$50, %edx
	jg	.L29
	cmpl	%edx, %ebx
	jg	.L33
	.p2align 4,,6
	jl	.L34
	cmpl	%edx, %ebx
	.p2align 4,,7
	jne	.L17
	movl	$.LC5, %edi
	call	puts
	movl	(%rsp), %edx
	cmpl	%ebx, %edx
	jne	.L23
	.p2align 4,,10
	.p2align 3
.L32:
	movl	%ebp, (%r12)
	addq	$4, %r12
	cmpq	%r13, %r12
	jne	.L25
	movl	$.LC8, %edi
	xorl	%ebx, %ebx
	call	puts
	movl	$.LC9, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
.L27:
	movl	16(%rsp,%rbx,4), %edx
	movl	%ebx, %esi
	xorl	%eax, %eax
	movl	$.LC10, %edi
	addq	$1, %rbx
	call	printf
	cmpq	$5, %rbx
	jne	.L27
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L29:
	.cfi_restore_state
	movl	$.LC2, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L33:
	movl	$.LC3, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L34:
	movl	$.LC4, %edi
	call	puts
	movl	(%rsp), %edx
	jmp	.L17
	.cfi_endproc
.LFE21:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
