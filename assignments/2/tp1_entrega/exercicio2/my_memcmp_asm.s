    .text
    .global my_memcmp

# Função my_memcmp
# Parâmetros:
# - rdi: Ponteiro para ptr1
# - rsi: Ponteiro para ptr2
# - rdx: Número de bytes para comparar (num)
my_memcmp:
    push %rbp
    mov %rsp, %rbp
    push %rdi
    push %rsi
    push %rcx
    push %r8

    # Alinhar os ponteiros para múltiplos de 8
    # Comparar byte a byte até que estejam alinhados
.align_check:
    mov %rdi, %r9
    and $7, %r9
    jz .aligned

    # Comparação byte a byte para alinhamento
    cmp $0, %rdx
    jle .end

    movzbl (%rdi), %r9d
    movzbl (%rsi), %r8d
    cmp %r9d, %r8d
    jne .mismatch_byte

    add $1, %rdi
    add $1, %rsi
    sub $1, %rdx

    jmp .align_check

.aligned:
    # Comparação principal: 64 bits de cada vez
    cmp $8, %rdx
    jl .compare_byte

    .align 8
.compare_qword:
    mov (%rdi), %rcx         # Carregar 64 bits de ptr1
    mov (%rsi), %r8          # Carregar 64 bits de ptr2
    cmp %r8, %rcx            # Comparar
    jne .mismatch_qword
    add $8, %rdi             # Avançar para a próxima palavra de 64 bits
    add $8, %rsi
    sub $8, %rdx             # Reduz o número de bytes restantes
    cmp $8, %rdx
    jge .compare_qword

.compare_byte:
    test %rdx, %rdx
    jz .end

.compare_byte_loop:
    movzbl (%rdi), %r9d      # Carregar byte de ptr1
    movzbl (%rsi), %r8d      # Carregar byte de ptr2
    cmp %r8d, %r9d           # Comparar
    jne .mismatch_byte
    add $1, %rdi             # Avançar para o próximo byte
    add $1, %rsi
    sub $1, %rdx             # Reduz o número de bytes restantes
    test %rdx, %rdx
    jnz .compare_byte_loop

.end:
    mov $0, %eax
    pop %r8
    pop %rcx
    pop %rsi
    pop %rdi
    leave
    ret

.mismatch_qword:
    # Encontrou uma diferença nos 64 bits comparados
    mov %rcx, %rax
    sub %r8, %rax
    jmp .end

.mismatch_byte:
    # Encontrou uma diferença nos bytes comparados
    mov %r9d, %eax
    sub %r8d, %eax
    jmp .end
