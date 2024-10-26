    .global rotate_right

    .text

rotate_right:
    # Paràmetros:
    # value - array de 2 elementos de 64 bits (128 no total) %rdi
    # n - número de posições a deslocar %rsi

    # Se n for 0, retornar
    test %rsi, %rsi
    bz   end

    # Assegurar que n não é maior que 128
    movq %rsi, %rax               # n em %rax
    movq $128, %rbx               # divisor em %rbx
    div  %rbx                     # Dividir rax por rbx (o quociente vai para rax, o resto para rdx)
    movq %rdx, $rsi               # Armazenar o resto de volta em n

    # Se n for 64, basta trocar a ordem, value[0] = value[1] e value[1] = value[0]
    # Se n for maior que 64, subtrair 64
    movq $64, %rdx                # %rdx = 64
    cmp  %rsi, %rdx
    be   swap_values
    bns  main_algorithm
    sub  %rdx, %rsi

main_algorithm:
    movq %rdi, %r8                # endereço de value - preservado em r8

    # Carregar os valores de 64 bits
    movq (%r8), %rax              # parte baixa apontada por r8 para rax
    movq 8(%r8), %rdx             # parte alta apontada por r8 + 8 para rdx

    # Deslocar / rodar os bits
    movq %rax, %r9                # preservar cópia da parte baixa em r9
    shrd %rsi, %rdx, %rax         # deslocar para a dir n bits do rdx para rax
    shrd %rsi, %rax, %rdx         # deslocar para a dir n bits do rax para rdx
    # TODO: adicionar a parte em falta a %rdx delocado 64 - n para a esquerda
    movq %10, %rsi                # copiar n (%rsi) para %r10
    sub  $64, %r10                # n - 64
    ror  %r10, %r9                # rodar os bits da parte baixa 64 - n

    # criar mascara
    movq $-1, %r11                # todos os bits de %r11 a 1
    shl  $1, %r10                 # deslocar n bits para a esquerda
    sub  $1, %r10                 # ajustar para criar mascara correta
    not  %r10                     # inverter para ter máscara correta
    and  %r11, %r10               # meter bits que não interessam a 0
    and  %r10, %r9                # meter bits que não interessam a 0
    or   %r9, %r8                 # copiar a parte em falta para %r8

    # Armazenar o resultado
    movq %rax, (%r8)              # guarda a parte baixa no endereço apontado por r8
    movq %rdx, 8(%r8)             # guarda a parte alta no endereço apontado por r8 + 8
    b    end

swap_values:
    movq 8(%rsi), %rax            # parte alta apontada por %rsi para %rax
    movq (&rsi), %rdx             # parte baixa apontada por %rsi para %rdx

end:
    ret

    # this section eliminates liking warnings
    .section .note.GNU-stack,"",@progbits

