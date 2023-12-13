global ft_atoi_base
extern ft_isspace, ft_strchr, ft_strlen

extern strchr ; TODO: remove

section .text

is_valid_base_char:
    and edi, 0xff
    call ft_isspace
    cmp rax, 1
    je .no
    cmp dil, '-'
    je .no
    cmp dil, '+'
    je .no
    mov rax, 1
    ret
    .no:
        xor rax, rax
        ret

is_valid_base:
    push rdi
    call ft_strlen
    pop rdi
    cmp rax, 2
    jl .no
    .loop:
        mov sil, byte [rdi]
        test sil, sil
        jz .yes

        push rdi
        mov dil, sil
        call is_valid_base_char
        pop rdi
        test rax, rax
        jz .no

        inc rdi

        push rdi
        call strchr
        pop rdi
        test rax, rax
        jnz .no

        jmp .loop
    .yes:
        mov rax, 1
        ret
    .no:
        xor rax, rax
        ret

ft_atoi_base:
    push rsi
    push rdi
    mov rdi, rsi
    call is_valid_base
    pop rdi
    pop rsi
    test rax, rax
    jnz .valid
    ret
    .valid:
        mov rax, 42
        ret
