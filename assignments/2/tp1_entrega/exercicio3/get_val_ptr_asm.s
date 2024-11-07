.section .text
.globl get_val_ptr

get_val_ptr:
    # Prologo
    push %rbp                       # Salva o valor de %rbp
    mov  %rsp, %rbp                 # Configura o quadro de pilha
    push %rbx                       # Salva %rbx (preservado pela convenção de chamada)

    # Argumentos de entrada:
    # items      -> %rdi
    # item_idx   -> %rsi
    # data_idx   -> %rdx
    # val_idx    -> %rcx
    # mask       -> %r8

    # Carrega o campo 'valid' do item `items[item_idx]`
    mov  %rsi, %rax                  # item_idx em %rax
    imul $24, %rax, %rax             # Multiplica item_idx por 24 bytes (sizeof(struct info))
    add  %rdi, %rax                  # Calcula o endereço de items[item_idx]
    mov  16(%rax), %eax              # Carrega o campo 'valid' (offset 16 em struct info)

    # Verifica se items[item_idx].valid é 0
    test %eax, %eax                  # Testa se 'valid' é zero
    jz   return_null                 # Se zero, retorna NULL

    # Carrega o endereço do ponteiro data[data[idx] (dentro de items[item[idx])
    mov  8(%rax), %rbx               # Carrega o ponteiro items[item_idx].data (ponteiro de ponteiro)
    mov  %rdx, %rax                  # data_idx em %rax
    shl  $3, %rax                    # Multiplica data_idx por 8 (sizeof(struct data*))
    add  %rbx, %rax                  # Adiciona ao ponteiro de ponteiro para obter data[data[idx]

    # Verifica se data[data[idx não é NULL
    mov  (%rax), %rbx                # Carrega o ponteiro data[data[idx em %rbx
    test %rbx, %rbx                  # Verifica se data[data[idx é NULL
    jz   return_null                 # Se for NULL, retorna NULL

    # Carrega o campo 'flags e length' e aplica as máscaras
    movw (%rbx), %ax                 # Carrega o campo 'flags e length'
    shr $6, %ax                      # Desloca os bits para a direita para obter o valor correto de length
    and $0x03FF, %ax                 # Aplica a máscara para length (bits 6 a 15)
    cmp  %cx, %ax                    # Compara 'val_idx' com 'length'
    jae  return_null                 # Se val_idx >= length, retorna NULL

    # Carrega o campo 'flags' e aplica o 'mask'
    movw (%rbx), %ax                 # Carrega novamente o campo 'flags e length'
    and $0x003F, %ax                 # Aplica a máscara para flags (bits 0 a 5)
    test %r8w, %ax                   # Aplica o 'mask' com AND
    jz   return_null                 # Se o resultado for zero, retorna NULL

    # Se todas as condições são verdadeiras, retorna o endereço de data[data[idx].vals[val_idx]
    lea  4(%rbx,%rcx,2), %rax        # Calcula o endereço de vals[val[idx] (cada short ocupa 2 bytes)
    jmp  end                         # Pula para o final

return_null:
    xor  %rax, %rax                  # Retorna NULL (rax = 0)

end:
    # Epilogo
    pop  %rbx                        # Restaura %rbx
    mov  %rbp, %rsp                  # Restaura o ponteiro de pilha
    pop  %rbp                        # Restaura o quadro de pilha
    ret                              # Retorna

.section .note.GNU-stack
