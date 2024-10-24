    .section .text

    .global my_memcmp

my_memcmp:
    xor  %rax, %rax               # zerar rax para comparação

compare_loop:
    movb (%rdi), %al              # carrega byte do ptr1 em al
    movb (%rsi), %bl              # carrega byte do ptr2 em bl
    cmp  %bl, %al                 # compara al e bl
    jne  not_equal                # se diferente salta para not_equal
    inc  %rdi                     # incrementa ptr1
    inc  %rsi                     # incrementa ptr2
    dec  %rcx                     # decrementa contador
    jnz  compare_loop             # enquanto o contador não chegar a zero, repete o loop

    movl $0, %eax                 # se igual, retorna zero
    jmp  end

not_equal:
    sub %bl, %al                  # calcula a difrença

end:
    ret

    # this section eliminates liking warnings
    .section .note.GNU-stack,"",@progbits

