.global my_memcmp

my_memcmp:
    push %rbp
    movq %rsp, %rbp
    movq %rdi, -8(%rbp)           # ptr1
    movq %rsi, -16(%rbp)          # ptr2
    movq %rdx, -24(%rbp)          # num

    movq -8(%rbp), %rdi           # carrega o ptr1 em rdi
    movq -16(%rbp), %rsi          # carrega o ptr2 em rsi
    movq -24(%rbp), %rcx          # carrega num em rcx

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
    leave
    ret


