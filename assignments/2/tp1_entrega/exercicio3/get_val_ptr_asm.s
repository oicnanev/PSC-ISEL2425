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
	.text
	.global	get_val_ptr
get_val_ptr:
	push %rbp
    mov %rsp, %rbp
    
    # Carregar os parâmetros
    mov %rdi, -8(%rbp)      # items
    mov %rsi, -16(%rbp)     # item_idx
    mov %rdx, -24(%rbp)     # data_idx
    mov %rcx, -32(%rbp)     # val_idx
    mov %r8, -40(%rbp)      # mask
    
    # Carregar items[item_idx]
    mov -8(%rbp), %rax      # items
    mov -16(%rbp), %rbx     # item_idx
    shl $5, %rbx            # sizeof(struct info) == 32
    add %rbx, %rax          # items + item_idx * sizeof(struct info)
    mov %rax, %rsi
    
    # Verificar se items[item_idx].valid
    mov 16(%rsi), %eax      # items[item_idx].valid
    test %eax, %eax
    jz invalid              # Se valid == 0, salta para invalid
    
    # Carregar items[item_idx].data[data_idx]
    mov -24(%rbp), %rcx     # data_idx
    mov 8(%rsi), %rdx       # items[item_idx].data
    shl $3, %rcx            # sizeof(struct data *) == 8
    add %rcx, %rdx          # data + data_idx * sizeof(struct data *)
    mov (%rdx), %rsi
    
    # Verificar se val_idx < items[item_idx].data[data_idx]->length
    mov -32(%rbp), %rcx     # val_idx
    mov 2(%rsi), %dx        # items[item_idx].data[data_idx]->length
    cmp %dx, %cx
    jge invalid             # Se val_idx >= length, salta para invalid

    # Verificar se items[item_idx].data[data_idx]->flags & mask
    mov -40(%rbp), %r8w     # mask
    mov (%rsi), %ax         # items[item_idx].data[data_idx]->flags
    and %r8w, %ax
    jz invalid              # Se flags & mask == 0, salta para invalid

    # Retornar &items[item_idx].data[data_idx]->vals[val_idx]
    lea 4(%rsi, %rcx, 2), %rax
    jmp end

invalid:
    mov $0, %rax

end:
	leave
	ret

	.section	.note.GNU-stack
