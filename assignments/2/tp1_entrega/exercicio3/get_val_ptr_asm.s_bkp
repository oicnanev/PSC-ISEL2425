    .section .text
    .globl get_val_ptr

get_val_ptr:
    # Prologo
    pushq   %rbp                # Guarda o valor do base pointer
    movq    %rsp, %rbp          # Configura o stack frame

    # Armazenamento dos argumentos em variaveis locais
    movq    %rdi, -8(%rbp)      # Armazena items
    movq    %rsi, -16(%rbp)     # Armazena item_idx
    movq    %rdx, -24(%rbp)     # Armazena data_idx
    movq    %rcx, -32(%rbp)     # Armazena val_idx
    movl    %r8d, %eax          # Armazena mask
    movw    %ax, -36(%rbp)      # Armazena mask como word

    # Calcular o endereco de items[item_idx] 
    movq    -16(%rbp), %rdx     # Carrega item_idx em %rdx
    movq    %rdx, %rax          # item_idx em %rax
    addq    %rax, %rax          # Multiplica por 2
    addq    %rdx, %rax          # Multiplica por 3 (3 x item_idx)
    salq    $3, %rax            # Multiplica por 8 (24 bytes por item)
    movq    %rax, %rdx          # Armazena em %rdx 
    movq    -8(%rbp), %rax      # Carrega items em %rax
    addq    %rdx, %rax          # Calcula endereco de items[items_idx]
    movl    16(%rax), %eax      # Carrega items[item_idx].valid em %eax
    testl   %eax, %eax          # Testa se valid e zero
    je  check_null              # Se zero salta para check_null

    # Calcular endereco de items[item_idx].data[data_idx]
    movq    -16(%rbp), %rdx     # Carrega item_idx em %rdx
    movq    %rdx, %rax          # item_idx em %rax
    addq    %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    addq    %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    salq    $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    movq    %rax, %rdx          # Armazena o resultado em %rdx
    movq    -8(%rbp), %rax      # Carrega items em %rax
    addq    %rdx, %rax          # Calcula o endereço de items[item_idx]
    movq    8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    movq    -24(%rbp), %rdx     # Carrega data_idx em %rdx
    salq    $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    addq    %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    movq    (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]
    
    # Carregar o campo flags e length da strtuct data
    movzwl  (%rax), %eax        # Carrega valor em 16 bits
    shrw    $6, %ax             # Desloca os bits para a direita para obter length
    movzwl  %ax, %eax           # Armazena length em %eax 
    
    # Verificar se val_idx e menor que length
    cmpq    %rax, -32(%rbp)     # Compara val_idx com length
    jnb check_null              # Se val_idx >= length, salta para check_null
    
    # Calcular novamentye o endereco de items[item_idx].data[data_idx]
    movq    -16(%rbp), %rdx     # Carrega item_idx em %rdx
    movq    %rdx, %rax          # item_idx em %rax
    addq    %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    addq    %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    salq    $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    movq    %rax, %rdx          # Armazena o resultado em %rdx
    movq    -8(%rbp), %rax      # Carrega items em %rax
    addq    %rdx, %rax          # Calcula o endereço de items[item_idx]
    movq    8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    movq    -24(%rbp), %rdx     # Carrega data_idx em %rdx
    salq    $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    addq    %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    movq    (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]
    
    # Aplicar mascara ao campo flags
    movzbl  (%rax), %eax        # Carrega flags
    andl    $63, %eax           # Aplica mascara para o bter 6 bits de menor peso
    movzbl  %al, %edx           # Armazena resultado em %eax
    movswl  -36(%rbp), %eax     # Carrega mask
    andl    %edx, %eax          # Aplicar mascara a mask
    
    testl   %eax, %eax          # Testa se o resultado e zero
    je  check_null              # Se for zero, salta para check_null
    
    # Calcular novamente o endereco de items[item_idx].data[data_idx].vals[val_idx]
    movq    -16(%rbp), %rdx     # Carrega item_idx em %rdx
    movq    %rdx, %rax          # item_idx em %rax
    addq    %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    addq    %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    salq    $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    movq    %rax, %rdx          # Armazena o resultado em %rdx
    movq    -8(%rbp), %rax      # Carrega items em %rax
    addq    %rdx, %rax          # Calcula o endereço de items[item_idx]
    movq    8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    movq    -24(%rbp), %rdx     # Carrega data_idx em %rdx
    salq    $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    addq    %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    movq    (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]

    # Calcular o endereco de vals[val_idx]
    movq    -32(%rbp), %rdx     # Carrega val_idx em %rdx
    addq    %rdx, %rdx          # Multiplica val_idx por 2 (2 * val_idx)
    addq    %rdx, %rax          # Adiciona o resultado ao endereco base
    addq    $2, %rax            # Ajusta o endereco para vals[cal_idx]
    jmp     end                 # Salta para o final

check_null:
    movl    $0, %eax

end:
    popq    %rbp
    ret

    .section .note.GNU-stack
