/*
int my_memcmp(const void *ptr1, const void *ptr2, size_t num);
*/
	.globl my_memcmp
my_memcmp:
	xor  %rax, %rax               # zerar rax para comparação

    #TODO: verificar se o tamanho é maior que 0
    #TODO  verificar se o tamanho maior ou igual a 64
    #TODO: verificar se os ponteiros são alinhados
    #TODO: verificar se o tamanho é maior ou igual a 8

compare_loop_quad:
    movq (%rdi), %r8             # carregar a quadword do ptr1 em %r8
    movq (%rsi), %r9             # carrega a quadword do ptr2 em %r9
    jne  compare_loop_byte
    add  %rdx, %rdi              # incrementar %rdi, por size_t num
    add  %rdx, %rsi              # incrementar %rsi, por size_t num
    dec  %rcx                    # decrementar contador
    #TODO: verificar se o contador é maior que 63
    jnz  compare_loop_quad       # enquanto o contador não chegar a zero, repete o loop
    jz   end                     # se igual, retorna zero

compare_loop_byte:
    movb (%rdi), %al              # carrega byte do ptr1 em al
    movb (%rsi), %bl              # carrega byte do ptr2 em bl
    cmp  %bl, %al                 # compara al e bl
    jne  not_equal                # se diferente salta para not_equal
    inc  %rdi                     # incrementa ptr1
    inc  %rsi                     # incrementa ptr2
    dec  %rcx                     # decrementa contador
    #TODO: verificar se o contador é maior que 7
    jnz  compare_loop_byte        # enquanto o contador não chegar a zero, repete o loop
    jmp  end

compare_loop_bit:
    movb %al, %r8b                # move al para r8b
    movb %bl, %r9b                # move bl para r9b
    and  $1, %r8b                 # and bit a bit
    and  $1, %r9b                 # and bit a bit
    cmp  %r9b, %r8b               # compara bit a bit
    jne  not_equal                # se diferente salta para not_equal
    shr  $1, %al                  # shift right al
    shr  $1, %bl                  # shift right bl
    dec  $rcx                     # decrementa contador
    jnz  compare_loop_bit         # enquanto o contador não chegar a zero, repete o loop

not_equal:
    mov  $r9b, %al                 # move r8b para al
    sub  %r8b, %al                 # calcula a difrença

end:
	ret

	.section	.note.GNU-stack
