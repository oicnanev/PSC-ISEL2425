    .text
    .global my_memcmp

my_memcmp:
    # Prologue
    push %rbp
    mov %rsp, %rbp
    push %rbx
    push %r12

    # Parâmetros:
    # ptr1 -> %rdi
    # ptr2 -> %rsi
    # num  -> %rdx

    # Inicialização
    mov %rdi, %r8           # Guarda ptr1 em %r8
    mov %rsi, %r9           # Guarda ptr2 em %r9
    mov %rdx, %r10          # Guarda num em %r10

    # Se num é 0, retorna 0 (são iguais)
    test %r10, %r10
    jz .equal

    # Verifica se ambos os ponteiros são alinhados a 8 bytes
    mov %r8, %rax
    and $0x7, %rax
    jnz .unaligned          # Se ptr1 não está alinhado, processa não alinhado

    mov %r9, %rbx
    and $0x7, %rbx
    jnz .unaligned          # Se ptr2 não está alinhado, processa não alinhado

.aligned:
    # Loop para comparar blocos de 64 bits
    mov %r10, %r12          # Guarda num em %r12 para contagem de bytes
    shr $3, %r10            # Divide num por 8 para contagem de blocos de 64 bits
    jz .compare_remaining    # Se não houver blocos de 64 bits, pula para comparação de bytes restantes

.compare_64:
    mov (%r8), %rax         # Carrega 8 bytes de ptr1
    mov (%r9), %rbx         # Carrega 8 bytes de ptr2
    cmp %rbx, %rax          # Compara os blocos de 8 bytes
    jne .diff_found_64      # Se diferentes, vai para cálculo do resultado
    add $8, %r8             # Avança ptr1
    add $8, %r9             # Avança ptr2
    sub $8, %r12            # Decrementa o contador
    jnz .compare_64         # Continua o loop

.compare_remaining:
    # Processa bytes restantes
    and $0x7, %r12          # Restaura os últimos bytes a serem comparados
    jz .equal               # Se não houver bytes restantes, os blocos são iguais

.compare_bytes:
    movb (%r8), %al         # Carrega um byte de ptr1
    movb (%r9), %bl         # Carrega um byte de ptr2
    cmp %al, %bl            # Compara os bytes
    jne .diff_found         # Se diferentes, calcula o resultado
    inc %r8                 # Avança ptr1
    inc %r9                 # Avança ptr2
    dec %r12                # Decrementa contador de bytes
    jnz .compare_bytes      # Continua o loop se houver mais bytes

.equal:
    # Se todos os bytes comparados são iguais, retorna 0
    xor %eax, %eax          # Define o retorno como 0
    jmp .end

.diff_found_64:
    # Se houver diferença em blocos de 64 bits
    sub %rbx, %rax          # Calcula a diferença entre os blocos
    jmp .end

.diff_found:
    # Se houver diferença em bytes, calcula o valor de retorno
    movsbl %al, %eax        # Converte o byte atual de ptr1 para 32 bits
    movsbl %bl, %ebx        # Converte o byte atual de ptr2 para 32 bits
    sub %ebx, %eax          # Calcula a diferença entre os bytes

.end:
    # Epilogue
    pop %r12
    pop %rbx
    mov %rbp, %rsp
    pop %rbp
    ret

.unaligned:
    # Loop para comparar byte a byte quando não alinhados
    mov %r10, %r12          # Guarda num em %r12
    jz .equal               # Se num é 0, já são iguais

.unaligned_loop:
    movb (%r8), %al         # Carrega um byte de ptr1
    movb (%r9), %bl         # Carrega um byte de ptr2
    cmp %al, %bl            # Compara os bytes
    jne .diff_found         # Se diferentes, calcula o resultado
    inc %r8                 # Avança ptr1
    inc %r9                 # Avança ptr2
    dec %r12                # Decrementa contador
    jnz .unaligned_loop     # Continua o loop se houver mais bytes

    jmp .equal              # Se todos os bytes são iguais, vai para o retorno

    .section    .note.GNU-stack
