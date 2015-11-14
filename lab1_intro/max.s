	.text
	.globl max
max:
	xorq %rax, %rax		#clear rax for use
	movq %rdi, %rax		#move first argument into rax
	cmpq %rsi, %rax		#compare first argument with second argument
	jl .itsless		#if first<second, jump to .itsless

.itsgreater:			#otherwise it's greater, return rax
	jmp .Ldone

.itsless:
	movq %rsi, %rax		#return value of second argument
.Ldone:	
	ret
