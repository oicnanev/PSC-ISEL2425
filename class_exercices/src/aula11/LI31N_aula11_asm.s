	.globl my_toupper, my_strlen
	
	.text
	
# rdi = c
my_toupper:
	mov		%edi, %eax
	cmp		$'a', %eax
	jb		my_toupper_end
	cmp		$'z', %eax
	ja		my_toupper_end
	add		$'A'-'a', %eax
my_toupper_end:
	ret
	
# rdi = const char *str
my_strlen:
	mov		$0, %eax
	test	%rdi, %rdi
	jz		my_strlen_end
	jmp		my_strlen_while_cond
my_strlen_while_loop:
	inc		%eax
my_strlen_while_cond:
	cmpb	$0, (%rdi, %rax)
	jne		my_strlen_while_loop
my_strlen_end:
	ret
	
	# This section eliminates linking warning
	.section .note.GNU-stack,"",@progbits
