	.globl	my_abs, my_abs_v2

my_abs:
	test	%rdi, %rdi
	jns		my_abs_L0
	neg		%rdi
my_abs_L0:
	mov		%rdi, %rax
	ret
	
my_abs_v2:
	mov		%rdi, %rax
	neg		%rdi
	cmovns	%rdi, %rax
	ret

	# This section eliminates linking warning
	.section .note.GNU-stack,"",@progbits
