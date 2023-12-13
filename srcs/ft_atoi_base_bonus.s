global ft_atoi_base
extern ft_isspace, ft_strchr

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
    mov rsi, rdi
    mov rdx, rdi
    .loop:
        mov dil, byte [rsi]
        test dil, dil
        jz .done
        call is_valid_base_char
        test rax, rax
        jz .no
        inc rsi
        jmp .loop
    .done:
        sub rsi, rdx
        cmp rsi, 2
        jl .no
        jmp .yes
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
