	.text
	.p2align 4,,15
	.globl	sum
sum:
	xorq	%rax, %rax 		#clears rax for use
	testq	%rsi, %rsi		#test to see if rsi is 0
	jle	.Ldone			#if rsi=0 then go to .Ldone
	xorq	%rdx, %rdx		#otherwise, clear rdx for use

.Lloop:
	addq	(%rdi,%rdx,8), %rax	#add the entry of the array 						#(indicated by rdx) stored in rdi to rax
	
	addq	$1, %rdx		#increment rdx by 1
	cmpq	%rsi, %rdx		#compare rsi and rdx
	jl	.Lloop			#if rdx is less than rsi, jump 						#to .Lloop, otherwise go to .Ldone
.Ldone:
	rep		#doesn't really do anything except preventing the 				#routine from accidentally returning after certain 				#jumps when it's not supposed to
	
	ret		#returns with sum stored in rax
