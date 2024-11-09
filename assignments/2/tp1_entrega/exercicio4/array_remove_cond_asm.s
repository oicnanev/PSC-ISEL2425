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
    push    %rbp                    # Salva o Base pointer (stack pointer)
    mov     %rsp, %rbp              # Configura a stack frame
    subq    $48, %rsp               # Aloca espaco para as variaveis locais

    # Parâmetros:
    # array       -> %rdi
    # size        -> %rsi
    # eval        -> %rdx
    # context     -> %rcx
    # element_size -> %r8

    # Armazenar os parametros em variaveis locais (stack frame)    
    movq    %rdi, -24(%rbp)         # Armazena array em -24(%rbp)
    movq    %rsi, -32(%rbp)         # Armazena size em -32(%rbp)
    movq    %rdx, -40(%rbp)         # Armazena eval em -40(%rbp)
    movq    %rcx, -48(%rbp)         # Armazena context em -48(%rbp)

    # Configuracao de current e last
    movq    -24(%rbp), %rax         # Carrega array em %rax
    movq    %rax, -16(%rbp)         # Armazena current em -16(%rbp)
    movq    -32(%rbp), %rax         # Carrega size em %rax
    leaq    (,%rax,8), %rdx         # Calcula size * sizeof(void*) em %rdx        
    movq    -24(%rbp), %rax         # Carrega array em %rax
    addq    %rdx, %rax              # Adiciona size ao array para obter o last
    movq    %rax, -8(%rbp)          # Armazena o last em -8(%rbp)

loop_start:
    # Loop principal
    movq    -16(%rbp), %rax         # Carrega current em %rax
    cmpq    -8(%rbp), %rax          # Compara current com last
    jge     loop_end                # Se current >= last, termina o loop

    # Chamada a eval(*current, context)
    movq    -16(%rbp), %rax         # Carrega current em %rax
    movq    (%rax), %rax            # Carrega *current em %rax
    movq    -48(%rbp), %rdx         # Carrega context em %rdx
    movq    -40(%rbp), %rcx         # Carrega eval em %rcx
    movq    %rdx, %rsi              # Coloca context em %rsi 
    movq    %rax, %rdi              # Coloca *current em %rdi
    call    *%rcx                   # Chama eval(*current, context)

    testl   %eax, %eax              # Testa o retorno de eval
    je      no_remove               # Se eval retornou 0, nada ha a remover

    # Remocao do elemento
    movq    -8(%rbp), %rax          # Carrega last em %rax
    subq    -16(%rbp), %rax         # Calcula last - current
    leaq    -8(%rax), %rdx          # Ajuste de (last - current - 1) elementos
    movq    -16(%rbp), %rax         # Carrega current em %rax
    leaq    8(%rax), %rcx           # Calcula current + 1
    movq    -16(%rbp), %rax         # carrega current em %rax
    movq    %rcx, %rsi              # Coloca current + 1 em %rsi
    movq    %rax, %rdi              # Coloca current em %rdi 
    call    memmove                 # Chama memmove

    subq    $1, -32(%rbp)           # Decremeta size
    subq    $8, -8(%rbp)            # Atualiza o last
    jmp loop_start

no_remove:
    addq    $8, -16(%rbp)           # Avanca current para o proximo elemento
    jmp     loop_start

loop_end:
    movq    -32(%rbp), %rax         # Coloca o tamanho final em %rax

    # Epilogo
    leave                           # Restaura o Base pointer
    ret    

    .section    .note.GNU-stack
