global ft_list_push_front
extern malloc

ft_list_new:
    push rdi
    mov rdi, 16
    call malloc
    pop rdi
    test rax, rax
    jz .done
    mov qword [rax], rdi
    mov qword [rax + 8], 0
    .done:
        ret

ft_list_push_front:
    push rdi
    push rsi
    mov rdi, rsi
    call ft_list_new
    pop rsi
    pop rdi
    test rax, rax
    mov rdx, [rdi]
    mov qword [rax + 8], rdx
    mov qword [rdi], rax
    .done:
        ret