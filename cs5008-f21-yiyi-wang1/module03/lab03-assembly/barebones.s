# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
						# (1) What are we setting up here?
						# Ans: getting memory from stack 
	pushq %rbp				#push the pointer in %rbp to stack
	movq  %rsp, %rbp			#move the pointer in %rsp to %rbp

							# (2) What is going on here
							# Ans:
	movq $1, %rax			#move 1 to 8-byte register %rax; 
	movq $1, %rdi			#move 1 to 8-byte register %rdi
	leaq .hello.str,%rsi		#move ".hello.str" to %rsi


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans:syscall is system call. It is a request to the kernel to do somthing.
					#
	syscall			# Which syscall is being run?
					# Ans:write

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: printf.

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
							# Ans:exit.	
	syscall

	popq %rbp			# (Note we do not really need
					    # this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
								# Ans: 13 characters including whitespace and "\0" at the end.	
