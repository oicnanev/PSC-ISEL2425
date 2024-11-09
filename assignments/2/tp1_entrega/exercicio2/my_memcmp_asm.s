    .text
    .global my_memcmp

my_memcmp:
    # Parâmetros:
    # ptr1 -> %rdi
    # ptr2 -> %rsi
    # num  -> %rdx

    # Se num é 0, retorna 0 (nada a comparar)
    test    %rdx, %rdx
    jz      equal

    # Verifica se os ponteiros estão alinhados a 8 bytes, basta verificar um deles
    mov     %rdi, %rax
    and     $0x7, %rax
    jnz     unaligned           # Se ptr1 não está alinhado, processa não alinhado

aligned:
    # Loop para comparar blocos de 64 bits
    mov     %rdx, %r8           # Guarda num em %r8 para contagem de bytes
    shr     $3, %rdx            # Divide num por 8 para contagem de blocos de 64 bits
    jz      compare_remaining   # Se não houver blocos de 64 bits, pula para comparação de bytes restantes

compare_64:
    mov     (%rdi), %rax        # Carrega 8 bytes de ptr1
    mov     (%rsi), %r9         # Carrega 8 bytes de ptr2
    cmp     %r9, %rax           # Compara os blocos de 8 bytes
    jne     compare_bytes       # Se diferentes, vai comparar byte a byte
    add     $8, %rdi            # Avança ptr1
    add     $8, %rsi            # Avança ptr2
    sub     $8, %r8             # Decrementa o contador
    jnz     compare_64          # Continua o loop

compare_remaining:
    # Processa bytes restantes
    and     $0x7, %r8           # Restaura os últimos bytes a serem comparados
    jz      equal               # Se não houver bytes restantes, os blocos são iguais

compare_bytes:
    movb    (%rdi), %al         # Carrega um byte de ptr1
    movb    (%rsi), %r9b        # Carrega um byte de ptr2
    cmp     %al, %r9b           # Compara os bytes
    jne     diff_found          # Se diferentes, calcula o resultado
    inc     %rdi                # Avança ptr1
    inc     %rsi                # Avança ptr2
    dec     %r8                 # Decrementa contador de bytes
    jnz     compare_bytes       # Continua o loop se houver mais bytes

equal:
    # Se todos os bytes comparados são iguais, retorna 0
    xor     %eax, %eax          # Define o retorno como 0
    jmp     end

diff_found:
    # Se houver diferença em bytes, calcula o valor de retorno
    movzbl  %al, %eax           # Converte o byte atual de ptr1 para 32 bits
    movzbl  %r9b, %r9d          # Converte o byte atual de ptr2 para 32 bits
    sub     %r9d, %eax          # Calcula a diferença entre os bytes

end:
    ret

unaligned:
    # Loop para comparar byte a byte quando não alinhados
    mov     %rdx, %r8           # Guarda num em %r8
    jz      equal               # Se num é 0, já são iguais

unaligned_loop:
    movb    (%rdi), %al         # Carrega um byte de ptr1
    movb    (%rsi), %r9b        # Carrega um byte de ptr2
    cmp     %al, %r9b           # Compara os bytes
    jne     diff_found          # Se diferentes, calcula o resultado
    inc     %rdi                # Avança ptr1
    inc     %rsi                # Avança ptr2
    dec     %r8                 # Decrementa contador
    jnz     unaligned_loop      # Continua o loop se houver mais bytes

    jmp     equal               # Se todos os bytes são iguais, vai para o retorno

    .section    .note.GNU-stack
