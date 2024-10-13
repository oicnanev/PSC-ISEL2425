.section text
.global rotate_right

rotate_right:
    # Paràmetros:
    # value - array de 2 elementos de 64 bits (128 no total)
    # n - número de posições a deslocar

    # Carregar os parâmetros
    movq %rdi, %r8                # value
    movq %rsi, %rcx               # n 

    # Carregar os valores de 64 bits
    movq (%r8), %rax              # valor baixo
    movq 8(%r8), %rdx             # valor alto

    # Deslocar / rodar os bits
    shrd %cl, %rdx, %rax          # deslocar valor baixo
    shrd %cl, %rax, %rdx          # deslocar valor alto

    # Armazenar o resultado para retorno
    movq %rax, (%r8)              # guarda o valor baixo
    movq %rdx, 8(%r8)             # guarda o valor alto

    ret

