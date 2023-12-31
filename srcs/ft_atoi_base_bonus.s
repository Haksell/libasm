global ft_atoi_base
extern ft_isspace, ft_strchr, ft_strlen

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
    mov rdx, rdi
    .loop:
        mov sil, byte [rdi]
        test sil, sil
        jz .done
        push rdi
        mov dil, sil
        call is_valid_base_char
        pop rdi
        test rax, rax
        jz .no
        inc rdi
        push rdi
        call ft_strchr
        pop rdi
        test rax, rax
        jnz .no
        jmp .loop
    .done:
        sub rdi, rdx
        cmp rdi, 2
        jl .no
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
    mov r8, rdi
    pop rdi
    pop rsi
    test rax, rax
    jz .invalid_base
    .skip_whitespace:
        movzx rdx, byte [rdi]
        push rdi
        mov rdi, rdx
        call ft_isspace
        pop rdi
        test rax, rax
        jz .get_sign
        inc rdi
        jmp .skip_whitespace
    .get_sign:
        mov rcx, 1
        .get_sign_loop:
            cmp byte [rdi], '-'
            je .negate
            cmp byte [rdi], '+'
            je .continue
            jmp .calculate
            .negate:
                neg rcx
            .continue:
                inc rdi
                jmp .get_sign_loop
    .calculate:
        mov r9, 0
        .calculate_loop:
            movzx rdx, byte [rdi]
            test rdx, rdx
            jz .done
            push rdi
            push rsi
            mov rdi, rsi
            mov rsi, rdx
            call ft_strchr
            pop rsi
            pop rdi
            test rax, rax
            jz .done
            sub rax, rsi
            imul r9, r8
            add r9, rax
            inc rdi
            jmp .calculate_loop
    .done:
        mov rax, r9
        imul rax, rcx
        ret
    .invalid_base:
        ret
