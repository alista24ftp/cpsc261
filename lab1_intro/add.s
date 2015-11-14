	.text
	.globl	add
add:
	pushq	%rbp 		#save the current frame pointer
	movq	%rsp, %rbp 	#move the address of stack pointer to frame 					#pointer
	
	movq	%rdi, %rax 	#move the first argument of the addition to rax
	addq	%rsi, %rax	#add the second argument with the first
	popq	%rbp	#now that the routine is over, pop the frame pointer
	ret		#return from the routine with the sum saved inside rax
