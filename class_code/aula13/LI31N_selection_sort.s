	.globl selection_sort
	.text
/*
void selection_sort(int a[], int size) {
	int min_idx;
	for (int i = 0; i < size-1; i++) {
		min_idx = i;
		for (int j = i+1; j < size; j++)
			if (a[j] < a[min_idx])
				min_idx = j;
		if (min_idx != i)
			swap(&a[i], &a[min_idx]);
	}
}
*/

# rdi = a; rsi = size
selection_sort:
	push	%rbx					# rbx = a
	push	%rbp					# rbp = size
	push	%r12					# r12 = i
	push	%r13					# r13 = min_idx
	mov		%rdi, %rbx
	mov		%esi, %ebp
	
	# For initiation
	xor		%r12, %r12				# i = 0
	jmp		selection_sort_for1_cond
selection_sort_for1_body:
	mov		%r12d, %r13d			# min_idx = i
	lea		1(%r12d), %eax			# j = i+1
	jmp		selection_sort_for2_cond
selection_sort_for2_body:
	mov		(%rbx, %r13, 4), %ecx	# ecx = a[min_idx]
	cmp		%ecx, (%rbx, %rax, 4)	# a[j] < a[min_idx]
	jge		selection_sort_if1_end
	mov		%eax, %r13d				# min_idx = j
selection_sort_if1_end:
	inc		%eax					# j++
selection_sort_for2_cond:
	cmp		%ebp, %eax				# j < size
	jl		selection_sort_for2_body
	cmp		%r12d, %r13d			# min_idx != i
	je		selection_sort_if2_end
	lea		(%rbx, %r12, 4), %rdi	# rdi = &a[i]
	lea		(%rbx, %r13, 4), %rsi	# rsi = &a[min_idx]
	call	swap					# swap(&a[i], &a[min_idx])
selection_sort_if2_end:
	inc		%r12d					# i++
selection_sort_for1_cond:
	lea		-1(%ebp), %eax			# eax = size-1
	cmp		%eax, %r12d				# i - (size-1)
	jl		selection_sort_for1_body

	pop		%r13
	pop		%r12
	pop		%rbp
	pop		%rbx
	ret

	# This section eliminates linking warning
	.section .note.GNU-stack,"",@progbits
