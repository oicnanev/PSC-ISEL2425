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
    .globl array_remove_cond

array_remove_cond:
    # Prologuo
    push %rbp                      # Salva o Base pointer (stack pointer)
    mov  %rsp, %rbp                # Configura a stack frame
    push %rbx                      # Salva o %rbx

    # Parâmetros:
    # array       -> %rdi
    # size        -> %rsi
    # eval        -> %rdx
    # context     -> %rcx
    # element_size -> %r8

    # Configuração de variáveis locais
    mov  %rdi, %r9                 # Guarda 'array' em %r9 (ponteiro para início do array)
    mov  %rsi, %r10                # Guarda 'size' em %r10
    imul %r8, %rsi                 # Multiplica 'size' por 'element_size'
    lea  (%r9, %rsi, 1), %r11      # Calcula 'last' (array + size * element_size) em %r11

loop_start:
    cmp  %r9, %r11                 # Verifica se current < last
    jge  end_loop                  # Se current >= last, termina o loop

    # Chamada para eval(*current, context)
    mov  (%r9), %rdi               # Coloca *current em %rdi (primeiro argumento para eval)
    mov  %rcx, %rsi                # Coloca context em %rsi (segundo argumento para eval)
    call *%rdx                     # Chama a função eval

    test %eax, %eax                # Verifica o retorno de eval
    jz   no_remove                 # Se eval retornar 0, salta a remoção

    # Remoção do elemento (memmove)
    lea  (%r9, %r8, 1), %rdi       # Ponteiro para current + 1 (novo início de origem para memmove)
    mov  %r9, %rsi                 # Ponteiro para current (destino em memmove)
    sub  %r9, %r11                 # Calcula o número de elementos após current
    sub  %r8, %r11                 # Ajusta para contar sizeof(void *)
    mov  %r11, %rdx                # Tamanho em bytes a ser movido
    call memmove                   # Executa memmove

    # Ajustes após a remoção
    sub  $1, %r10                  # Decrementa o tamanho do array
    sub  %r8, %r11                 # Ajusta o ponteiro 'last' após a remoção (last -= 1)
    jmp  loop_start                # Continua o loop

no_remove:
    add  %r8, %r9                  # current += element_size (avança ponteiro)
    jmp  loop_start                # Continua o loop

end_loop:
    mov  %r10, %rax                # Coloca o tamanho final em %rax (valor de retorno)

    # Epiloguo
    pop  %rbx                      # Restaura o %rbx
    mov  %rbp, %rsp                # Restaura o stack pointer
    pop  %rbp                      # Restaura a stack frame
    ret                            # Retorna


    .section    .note.GNU-stack
