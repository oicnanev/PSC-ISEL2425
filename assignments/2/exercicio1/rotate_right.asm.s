.section text
.global rotate_right

rotate_right:
    # Paràmetros:
    # value - array de 2 elementos de 64 bits (128 no total)
    # n - número de posições a deslocar

    # Carregar os parâmetros
    movq %rdi, %r8                # endereço de value - preservado em r8
    movq %rsi, %rcx               # endereço n - preservado em rcx

    # Carregar os valores de 64 bits
    movq (%r8), %rax              # parte baixa apontada por r8 para rax
    movq 8(%r8), %rdx             # parte alta apontada por r8 + 8 para rdx

    # Deslocar / rodar os bits
    shrd %cl, %rdx, %rax          # deslocar para a dir n bits do rdx para rax
    shrd %cl, %rax, %rdx          # deslocar para a dir n bits do rax para rdx

    # Armazenar o resultado
    movq %rax, (%r8)              # guarda a parte baixa no endereço apontado por r8
    movq %rdx, 8(%r8)             # guarda a parte alta no endereço apontado por r8 + 8

    ret

