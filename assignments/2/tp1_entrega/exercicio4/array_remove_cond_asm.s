/*
size_t array_remove_cond(void **array, size_t size,
                    int (*eval)(const void *, const void *), void *context) {
	for (void **current = array, **last = array + size; current < last; ) {
		if (eval(*current, context)) {
			memmove(current, current + 1, (last - current - 1) * sizeof(void *));
			size -= 1;
			last -= 1;
		}
		else {
			current += 1;
		}
	}
	return size;
}
*/
	.text
	.global	array_remove_cond
array_remove_cond:
	# Parâmetros:
    # rdi - array (void **)
    # rsi - size (size_t)
    # rdx - eval (int (*)(const void *, const void *))
    # rcx - context (void *)

    push rbp
    mov rbp, rsp
    sub rsp, 32                # Espaço para variáveis locais

    mov r8, rdi                # r8 = current = array
    lea r9, [rdi + rsi * 8]    # r9 = last = array + size

loop:
    cmp r8, r9                 # current < last?
    jge done

    mov rdi, [r8]              # rdi = *current
    mov rsi, rcx               # rsi = context
    call rdx                   # eval(*current, context)
    test eax, eax              # Verifica o retorno de eval
    jz next                    # Se eval retornar 0, pula para .next

    # memmove(current, current + 1, (last - current - 1) * sizeof(void *))
    lea rdi, [r8 + 8]          # rdi = current + 1
    mov rsi, r8                # rsi = current
    mov rdx, r9
    sub rdx, r8
    sub rdx, 8
    call memmove

    sub rsi, 1                 # size -= 1
    sub r9, 8                  # last -= 1
    jmp loop

next:
    add r8, 8                  # current += 1
    jmp loop

done:
    mov rax, rsi               # Retorna size
    leave

	ret

	.section	.note.GNU-stack

