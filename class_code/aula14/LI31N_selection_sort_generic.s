	.globl selection_sort_generic
	.text
/*
void selection_sort_generic(void * a, int size, int elem_size, int (*cmp)(void *, void*))
{
	for (int i = 0; i < size-1; i++) {
		int min_idx = i;
		for (int j = i+1; j < size; j++)
			if (cmp(((char*)a + j*elem_size), ((char*)a + min_idx*elem_size)) < 0)
				min_idx = j;
		if (min_idx != i)
			memswap((char*)a + i*elem_size, (char*)a + min_idx*elem_size, elem_size);
	}
}
*/

selection_sort_generic:
	push	%rbx						# a
	push	%rbp						# size
	push	%r12						# elem_size
	push	%r13						# i
	push	%r14						# min_idx
	push	%r15						# j
	sub		$8, %rsp					# cmp
	
	mov		%rdi, %rbx
	mov		%rsi, %rbp
	mov		%rdx, %r12
	mov		%rcx, (%rsp)
	xor		%r13d, %r13d				# i = 0
	jmp		selection_sort_for1_cond
selection_sort_for1_body:
	mov		%r13d, %r14d				# min_idx = i
	lea		1(%r13d), %r15d				# j = i+1
	jmp		selection_sort_for2_cond
selection_sort_for2_body:
	mov		%r15, %rax					# rax = j
	mul		%r12						# j * elem_size
	lea		(%rbx, %rax), %rdi			# rdi = a + j*elem_size
	mov		%r14, %rax					# rax = min_idx
	mul		%r12						# min_idx * elem_size
	lea		(%rbx, %rax), %rsi			# rsi = a + j*elem_size
	call	*(%rsp)						# cmp(...)
	test	%eax, %eax					# cmp(...) < 0
	jns		selection_sort_if1_end
	mov		%r15d, %r14d				# min_idx = j
selection_sort_if1_end:
	inc		%r15d						# j++
selection_sort_for2_cond:
	cmp		%ebp, %r15d					# j < size
	jl		selection_sort_for2_body
	cmp		%r13d, %r14d				# min_idx != i
	je		selection_sort_if2_end
	mov		%r13, %rax					# rax = i
	mul		%r12						# i * elem_size
	lea		(%rbx, %rax), %rdi			# rdi = a + i*elem_size
	mov		%r14, %rax					# rax = min_idx
	mul		%r12						# min_idx * elem_size
	lea		(%rbx, %rax), %rsi			# rsi = a + j*elem_size
	mov		%r12d, %edx					# rdx = elem_size
	call	memswap			
selection_sort_if2_end:		
	inc		%r13d						# i++
selection_sort_for1_cond:
	lea		-1(%ebp), %eax				# eax = size-1
	cmp		%eax, %r13d					# i < size-1
	jl		selection_sort_for1_body
	
	add		$8, %rsp
	pop		%r15
	pop		%r14
	pop		%r13
	pop		%r12
	pop		%rbp
	pop		%rbx
	ret

	# This section eliminates linking warning
	.section .note.GNU-stack,"",@progbits
