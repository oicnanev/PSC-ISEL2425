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

.section .text
.globl array_remove_cond

array_remove_cond:
    # Prologo
    push %rbp                       # Salva o base pointer
    mov  %rsp, %rbp                 # Configura o quadro de pilha
    push %rbx                       # Salva %rbx (callee-saved)
    push %r12                       # Salva %r12 (callee-saved)
    sub  $32, %rsp                  # Aloca espaço para variáveis locais

    # Parâmetros:
    # array       -> %rdi (ponteiro para array)
    # size        -> %rsi (tamanho em elementos)
    # eval        -> %rdx (função de avaliação)
    # context     -> %rcx (contexto para função eval)

    # Configurando variáveis locais
    mov  %rdi, %r8                  # %r8 = array (ponteiro atual)
    mov  %rsi, %r9                  # %r9 = size (número de elementos)
    lea  (%rdi, %rsi, 8), %r10      # %r10 = last (array + size * sizeof(void *))

loop_start:
    cmp  %r8, %r10                  # Verifica se current < last
    jge  end_loop                   # Sai do loop se current >= last

    # Chama eval(*current, context)
    mov  (%r8), %rdi                # *current (primeiro argumento para eval)
    mov  %rcx, %rsi                 # context (segundo argumento para eval)
    call *%rdx                      # Chama a função eval

    test %eax, %eax                 # Verifica o valor retornado por eval
    jz   no_remove                  # Pula remoção se eval retornar 0

    # Lógica de remoção (memmove para deslocar elementos para a esquerda)
    lea 8(%r8), %rdi                # current + 1 (source para memmove)
    mov  %r8, %rsi                  # current (destination para memmove)
    mov  %r10, %rdx                 # last
    sub  %r8, %rdx                  # (last - current)
    sub  $8, %rdx                   # (last - current - 1) elementos
    call memmove                    # Executa memmove

    # Ajusta last e size após remoção
    sub  $8, %r10                   # last -= sizeof(void *)
    dec  %r9                        # size -= 1
    jmp  loop_start                 # Continua o loop

no_remove:
    add  $8, %r8                    # Avança current por um elemento (sizeof(void *))
    jmp  loop_start                 # Continua o loop

end_loop:
    mov  %r9, %rax                  # Retorna o tamanho final

    # Epilogo
    add  $32, %rsp                  # Restaura o ponteiro de pilha
    pop  %r12                       # Restaura %r12
    pop  %rbx                       # Restaura %rbx
    mov  %rbp, %rsp                 # Restaura o base pointer
    pop  %rbp                       # Restaura o quadro de pilha
    ret                             # Retorna

.section .note.GNU-stack
