    .section .text
    .globl get_val_ptr

get_val_ptr:
    # Prologo
    push    %rbp                # Guarda o valor do base pointer
    mov     %rsp, %rbp          # Configura o stack frame

    # Armazenamento dos argumentos em variaveis locais
    mov     %rdi, -8(%rbp)      # Armazena items
    mov     %rsi, -16(%rbp)     # Armazena item_idx
    mov     %rdx, -24(%rbp)     # Armazena data_idx
    mov     %rcx, -32(%rbp)     # Armazena val_idx
    movl    %r8d, %eax          # Armazena mask
    movw    %ax, -36(%rbp)      # Armazena mask como word

    # Calcular o endereco de items[item_idx] 
    mov     -16(%rbp), %rdx     # Carrega item_idx em %rdx
    mov     %rdx, %rax          # item_idx em %rax
    add     %rax, %rax          # Multiplica por 2
    add     %rdx, %rax          # Multiplica por 3 (3 x item_idx)
    sal     $3, %rax            # Multiplica por 8 (24 bytes por item)
    mov     %rax, %rdx          # Armazena em %rdx 
    mov     -8(%rbp), %rax      # Carrega items em %rax
    add     %rdx, %rax          # Calcula endereco de items[items_idx]
    movl    16(%rax), %eax      # Carrega items[item_idx].valid em %eax
    test   %eax, %eax          # Testa se valid e zero
    je  check_null              # Se zero salta para check_null

    # Calcular endereco de items[item_idx].data[data_idx]
    mov     -16(%rbp), %rdx     # Carrega item_idx em %rdx
    mov     %rdx, %rax          # item_idx em %rax
    add     %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    add     %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    sal     $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    mov     %rax, %rdx          # Armazena o resultado em %rdx
    mov     -8(%rbp), %rax      # Carrega items em %rax
    add     %rdx, %rax          # Calcula o endereço de items[item_idx]
    mov     8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    mov     -24(%rbp), %rdx     # Carrega data_idx em %rdx
    sal     $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    add     %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    mov     (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]
    
    # Carregar o campo flags e length da strtuct data
    movzwl  (%rax), %eax        # Carrega valor em 16 bits
    shrw    $6, %ax             # Desloca os bits para a direita para obter length
    movzwl  %ax, %eax           # Armazena length em %eax 
    
    # Verificar se val_idx e menor que length
    cmp     %rax, -32(%rbp)     # Compara val_idx com length
    jnb check_null              # Se val_idx >= length, salta para check_null
    
    # Calcular novamentye o endereco de items[item_idx].data[data_idx]
    mov     -16(%rbp), %rdx     # Carrega item_idx em %rdx
    mov     %rdx, %rax          # item_idx em %rax
    add     %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    add     %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    sal     $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    mov     %rax, %rdx          # Armazena o resultado em %rdx
    mov     -8(%rbp), %rax      # Carrega items em %rax
    add     %rdx, %rax          # Calcula o endereço de items[item_idx]
    mov     8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    mov     -24(%rbp), %rdx     # Carrega data_idx em %rdx
    sal     $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    add     %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    mov     (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]
    
    # Aplicar mascara ao campo flags
    movzbl  (%rax), %eax        # Carrega flags
    and     $63, %eax           # Aplica mascara para o bter 6 bits de menor peso
    movzbl  %al, %edx           # Armazena resultado em %eax
    movswl  -36(%rbp), %eax     # Carrega mask
    and     %edx, %eax          # Aplicar mascara a mask
    
    test    %eax, %eax          # Testa se o resultado e zero
    je  check_null              # Se for zero, salta para check_null
    
    # Calcular novamente o endereco de items[item_idx].data[data_idx].vals[val_idx]
    mov     -16(%rbp), %rdx     # Carrega item_idx em %rdx
    mov     %rdx, %rax          # item_idx em %rax
    add     %rax, %rax          # Multiplica item_idx por 2 (2 * item_idx)
    add     %rdx, %rax          # Multiplica por 3 (3 * item_idx)
    sal     $3, %rax            # Multiplica por 8 (8 * 3 * item_idx = 24 * item_idx)
    mov     %rax, %rdx          # Armazena o resultado em %rdx
    mov     -8(%rbp), %rax      # Carrega items em %rax
    add     %rdx, %rax          # Calcula o endereço de items[item_idx]
    mov     8(%rax), %rax       # Carrega o valor de items[item_idx].data (ponteiro para ponteiro)
    mov     -24(%rbp), %rdx     # Carrega data_idx em %rdx
    sal     $3, %rdx            # Multiplica data_idx por 8 (8 * data_idx)
    add     %rdx, %rax          # Adiciona ao ponteiro de ponteiro para obter items[item_idx].data[data_idx]
    mov     (%rax), %rax        # Carrega o valor de items[item_idx].data[data_idx]

    # Calcular o endereco de vals[val_idx]
    mov     -32(%rbp), %rdx     # Carrega val_idx em %rdx
    add     %rdx, %rdx          # Multiplica val_idx por 2 (2 * val_idx)
    add     %rdx, %rax          # Adiciona o resultado ao endereco base
    add     $2, %rax            # Ajusta o endereco para vals[cal_idx]
    jmp     end                 # Salta para o final

check_null:
    mov     $0, %eax

end:
    pop     %rbp
    ret

    .section .note.GNU-stack
