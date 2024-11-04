/*
struct data { short flags:6; short length:10; short vals[]; };

struct info { double ref; struct data **data; int valid; };

short *get_val_ptr(struct info items[],
                      size_t item_idx, size_t data_idx, size_t val_idx, short mask)
{
	return items[item_idx].valid
		&& val_idx < items[item_idx].data[data_idx]->length
		&& (items[item_idx].data[data_idx]->flags & mask)
			? &items[item_idx].data[data_idx]->vals[val_idx]
			: NULL;
}
*/

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
    shl  $4, %rax                    # Multiplica item_idx por 16 bytes (sizeof(struct info))
    add  %rdi, %rax                  # Calcula o endereço de items[item_idx]
    mov  12(%rax), %eax              # Carrega o campo 'valid' (offset 12 em struct info)

    # Verifica se items[item_idx].valid é 0
    test %eax, %eax                  # Testa se 'valid' é zero
    jz   return_null                 # Se zero, retorna NULL

    # Carrega o endereço de data -> data[data_idx] (dentro de items[item_idx])
    mov  (%rax), %rbx                # Carrega items[item_idx].data (ponteiro de ponteiro)
    mov  %rdx, %rax                  # data_idx em %rax
    shl  $3, %rax                    # Multiplica data_idx por 8 (sizeof(struct data*))
    add  %rbx, %rax                  # Adiciona ao ponteiro de ponteiro para obter data[data_idx]

    # Verifica se data[data_idx] não é NULL
    mov  (%rax), %rbx                # Carrega o ponteiro data[data_idx] em %rbx
    test %rbx, %rbx                  # Verifica se data[data_idx] é NULL
    jz   return_null                 # Se for NULL, retorna NULL

    # Carrega o campo 'length' de data[data_idx]
    movw 2(%rbx), %ax                # Carrega o campo 'length' de data[data_idx]
    cmp  %cx, %ax                    # Compara 'val_idx' com 'length'
    jbe  return_null                 # Se val_idx >= length, retorna NULL

    # Carrega o campo 'flags' de data[data_idx] e aplica o 'mask'
    movw (%rbx), %ax                 # Carrega o campo 'flags'
    test %r8w, %ax                   # Aplica o 'mask' com AND
    jz   return_null                 # Se o resultado for zero, retorna NULL

    # Se todas as condições são verdadeiras, retorna o endereço de data[data_idx].vals[val_idx]
    lea  4(%rbx,%rcx,2), %rax         # Calcula o endereço de vals[val_idx] (cada short ocupa 2 bytes)
    jmp  end                          # Pula para o final

return_null:
    xor  %rax, %rax                   # Retorna NULL (rax = 0)

end:
    # Epilogo
    pop  %rbx                         # Restaura %rbx
    mov  %rbp, %rsp                   # Restaura o ponteiro de pilha
    pop  %rbp                         # Restaura o quadro de pilha
    ret                               # Retorna


	.section	.note.GNU-stack
