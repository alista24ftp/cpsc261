	.text 
	.globl fib
fib:
	xorq %rax, %rax		#clears rax for use (rax=0)
	movq $0, %rsi		#first test the 0th case fib(0)
	cmpq %rsi, %rdi		#compare n and 0
	jle .Ldone		#if n=0, return rax=0, exit routine
	addq $1, %rsi		#otherwise test 1st case fib(1)
	movq $1, %rdx		#store fib(1)=1 into rdx
	cmpq %rsi, %rdi		#compare n and 1
	jle .Lfibisone		#if n=1, go to .Lfibisone, returns rax=1, exit
	addq $1, %rsi		#otherwise check for fib(2)
	movq $1, %rcx		#store fib(2)=1 into rcx
	cmpq %rsi, %rdi		#compare n and 2
	jle .Lfibisone		#if n=2, go to .Lfibisone, returns rax=1, exit

.Lactualfib:			#otherwise it checks for fib(3) to fib(n)
	movq %rdi, %rsi		#save whatever n is into rsi
	movq $3, %rdi		#starts with n=3
	movq %rdx, %rax		#move fib(1) to rax
	addq %rcx, %rax		#add fib(1) with fib(2), save result in rax
	cmpq %rsi, %rdi		#check to see if n=3
	jl .Lloop		#if 3<n, jump to .Lloop
	jmp .Ldone		#if n=3, exit by returning rax

.Lloop:
	addq $1, %rdi		#rdi holds value of present n, and now increment
	movq %rax, %rdx		#save rax temporarily at rdx
	addq %rcx, %rax		#add rax (fib(n-1)) with rcx (fib(n-2))
	movq %rdx, %rcx		#replace rcx with rdx (fib(n-1)) for next loop
	cmpq %rsi, %rdi		#compare present n with actual n
	jl .Lloop		#redo the loop if present<actual n
	jmp .Ldone		#if present=actual n, we're finished, return rax
	
.Lfibisone:
	movq $1, %rax		#return with rax=1 (due to either n=1 or 2)
	

.Ldone:	
	ret		
