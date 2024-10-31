.text
.global rotate_right

# Função rotate_right
# Parâmetros:
# - rdi: Ponteiro para o array de 2x64 bits (value)
# - esi: Número de posições para deslocar (n)
rotate_right:
    # Guardar os registos de propósito geral
    push    %rbx
    push    %rcx
    push    %rdx

    # Carregar os dois valores de 64 bits
    mov     (%rdi), %rax
    mov     8(%rdi), %rbx

    # Truncar a rotação
    mov     %esi, %ecx
    and     $127, %ecx          # Limita o número de posições a 127

    # Se a rotação for maior ou igual a 64, trocar os registos
    cmp     $64, %ecx
    jb      rotate

    # Troca os registos e ajusta a rotação
    xchg    %rax, %rbx
    sub     $64, %ecx

rotate:
    # Realizar a rotação
    mov     %rax, %rdx          # preservar parte baixa
    shrd    %cl, %rbx, %rax     # rotação da parte alta para a baixa
    shrd    %cl, %rdx, %rbx     # rotação da parte baixa para a alta

    # Colocar o valor deslocado de volta para a array
    mov     %rax, (%rdi)
    mov     %rbx, 8(%rdi)

    # Restaurar os registos de propósito geral
    pop     %rdx
    pop     %rcx
    pop     %rbx

    ret
