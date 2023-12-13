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
    mov r8, rsi ; cmp
    push rdi
    mov rdi, [rdi]
    call ft_list_size
    pop rdi
    mov rcx, rax
    .outer_loop: ; TODO: loop .outer_loop
        test rcx, rcx
        jz .done
        mov r9, [rdi] ; node
        .inner_loop:
            mov rdx, [r9 + 8] ; node->next
            test rdx, rdx
            jz .continue_outer_loop

            push rcx
            push rdx
            push rdi
            push rsi
            push r8
            push r9
            push r10
            push r11
            
            mov rdi, [r9] ; node->data
            mov rsi, [rdx] ; node->next->data
            call ft_cmp
            
            pop r11
            pop r10
            pop r9
            pop r8
            pop rsi
            pop rdi
            pop rdx
            pop rcx
            
            cmp rax, 0
            jle .continue_inner_loop

            mov r10, [r9]
            mov r11, [rdx]
            mov [rdx], r10
            mov [r9], r11

            .continue_inner_loop:
                mov r9, rdx
                jmp .inner_loop
        .continue_outer_loop:
            dec rcx
            jmp .outer_loop

    .done:
        ret