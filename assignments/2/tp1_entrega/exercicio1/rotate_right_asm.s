    .text
    .global rotate_right

    # Função rotate_right
    # Parâmetros:
    # - rdi: Ponteiro para o array de 2x64 bits (value)
    # - esi: Número de posições para deslocar (n)
    
    rotate_right:
        # Carregar os dois valores de 64 bits
        mov     (%rdi), %rax        # Carregar a primeira parte (64 bits) em %rax
        mov     8(%rdi), %r8        # Carregar a segunda parte (64 bits) em %rbx

        # Truncar a rotação
        mov     %esi, %ecx          # Copiar o número de posições para %ecx
        and     $127, %ecx          # Limitar o número de posições a 127

        # Se a rotação for maior ou igual a 64, trocar os registos
        cmp     $64, %ecx           # Compara 64 com o número de posiçoes
        jb      rotate              # Se a rotação for < 64, pular a troca de registros

        # Troca os registos e ajusta a rotação
        xchg    %rax, %r8           # Trocar as partes alta e baixa
        sub     $64, %ecx           # Ajustar o número de rotações

    rotate:
        # Realizar a rotação
        mov     %rax, %rdx          # Guardar a parte baixa de %rax em %rdx
        shrd    %cl, %r8, %rax      # Realizar a rotação (parte alta para a parte baixa)
        shrd    %cl, %rdx, %r8      # Realizar a rotação (parte baixa para a parte alta)

        # Colocar o valor deslocado de volta para o array
        mov     %rax, (%rdi)        # Armazenar a parte alta no array
        mov     %r8, 8(%rdi)        # Armazenar a parte baixa no array

        ret                         # Retornar


    .section    .note.GNU-stack
