global ft_list_push_front, ft_list_size, ft_list_sort
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
    jz .done
    mov rdx, [rdi]
    mov qword [rax + 8], rdx
    mov qword [rdi], rax
    .done:
        ret

ft_list_size:
    xor rax, rax
    .loop:
        cmp qword rdi, 0
        jz .done
        mov rdi, qword [rdi + 8]
        inc rax
        jmp .loop
    .done:
        ret

ft_cmp:
    mov rax, rdi
    sub rax, rsi
    ret

ft_list_sort:
    mov rdx, rsi
    push rdi
    mov rdi, [rdi]
    call ft_list_size
    pop rdi
    mov rcx, rax
    dec rcx
    .outer_loop:
        mov r9, [rdi]
        .inner_loop:
            mov r8, [r9 + 8]
            test r8, r8
            jz .continue_outer_loop
            push r8
            push r9
            push rcx
            push rdi
            push rdx
            mov rdi, [r9]
            mov rsi, [r8]
            call rdx
            pop rdx
            pop rdi
            pop rcx
            pop r9
            pop r8
            cmp eax, 0
            jle .continue_inner_loop
            mov r10, [r9]
            mov r11, [r8]
            mov [r8], r10
            mov [r9], r11
            .continue_inner_loop:
                mov r9, r8
                jmp .inner_loop
        .continue_outer_loop:
            loop .outer_loop
    ret