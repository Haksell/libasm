global ft_strdup
extern ft_strcpy, ft_strlen, malloc

ft_strdup:
    call ft_strlen
    inc rax
    push rdi
    mov rdi, rax
    call malloc wrt ..plt
    pop rdi
    test rax, rax
    jz .done
    mov rsi, rdi
    mov rdi, rax
    call ft_strcpy
    .done:
        ret
