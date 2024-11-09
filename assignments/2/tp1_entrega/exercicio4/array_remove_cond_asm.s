	.text
    .globl array_remove_cond

array_remove_cond:
    # Parâmetros:
    # array       -> %rdi
    # size        -> %rsi
    # eval        -> %rdx
    # context     -> %rcx
    # element_size -> %r8

    # Prologuo
    push    %rbp                    # Salva o Base pointer (stack pointer)
    mov     %rsp, %rbp              # Configura a stack frame
    sub     $48, %rsp               # Aloca espaco para as variáveis locais


    # Armazenar os parâmetros em variáveis locais (stack frame)    
    mov     %rdi, -24(%rbp)         # array
    mov     %rsi, -32(%rbp)         # size
    mov     %rdx, -40(%rbp)         # eval
    mov     %rcx, -48(%rbp)         # context

    # Configuracao de current e last
    mov     -24(%rbp), %rax         # Carrega array em %rax
    mov     %rax, -16(%rbp)         # Armazena current em -16(%rbp)
    mov     -32(%rbp), %rax         # Carrega size em %rax
    lea     (,%rax,8), %rdx         # Calcula size * sizeof(void*) em %rdx        
    mov     -24(%rbp), %rax         # Carrega array em %rax
    add     %rdx, %rax              # Adiciona size ao array para obter o last
    mov     %rax, -8(%rbp)          # Armazena o last em -8(%rbp)

loop_start:
    mov     -16(%rbp), %rax         # Carrega current em %rax
    cmp     -8(%rbp), %rax          # Compara current com last
    jge     loop_end                # Se current >= last, termina o loop

    # Chamada a eval(*current, context)
    mov     -16(%rbp), %rax         # Carrega current em %rax
    mov     (%rax), %rax            # Carrega *current em %rax
    mov     -48(%rbp), %rdx         # Carrega context em %rdx
    mov     -40(%rbp), %rcx         # Carrega eval em %rcx
    mov     %rdx, %rsi              # Coloca context em %rsi 
    mov     %rax, %rdi              # Coloca *current em %rdi
    call    *%rcx                   # Chama eval(*current, context)

    test    %eax, %eax              # Testa o retorno de eval
    je      no_remove               # Se eval retornou 0, nada há a remover

    # Remocao do elemento
    mov     -8(%rbp), %rax          # Carrega last em %rax
    sub     -16(%rbp), %rax         # Calcula last - current
    lea     -8(%rax), %rdx          # Ajuste de (last - current - 1) elementos
    mov     -16(%rbp), %rax         # Carrega current em %rax
    lea     8(%rax), %rcx           # Calcula current + 1
    mov     -16(%rbp), %rax         # Carrega current em %rax
    mov     %rcx, %rsi              # Coloca current + 1 em %rsi
    mov     %rax, %rdi              # Coloca current em %rdi 
    call    memmove                 # Chama memmove

    subq    $1, -32(%rbp)           # Decrementa size
    subq    $8, -8(%rbp)            # Atualiza o last
    jmp loop_start

no_remove:
    addq    $8, -16(%rbp)           # Avança current para o próximo elemento
    jmp     loop_start

loop_end:
    mov     -32(%rbp), %rax         # Coloca o tamanho final em %rax

    # Epilogo
    add     $48, %rsp               # Liberta o espaco das variáveis locais
    leave                           # Restaura o Base pointer
    ret    

    .section    .note.GNU-stack
