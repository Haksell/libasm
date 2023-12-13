global ft_list_push_front, ft_list_remove_if, ft_list_size, ft_list_sort
extern free, malloc

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
            mov r10, [r8]
            mov r11, [r9]
            mov [r8], r11
            mov [r9], r10
            .continue_inner_loop:
                mov r9, r8
                jmp .inner_loop
        .continue_outer_loop:
            loop .outer_loop
    ret


ft_list_delete_one:
    test rdi, rdi
    jz .done
    mov r11, [rsi + 8]
    mov [rdi + 8], r11
    .done:
        call free

ft_list_remove_if:
    mov r8, 0
    mov r9, [rdi]
    .loop:
        test r9, r9
        jz .done
        mov r10, [r9 + 8]
        cmp qword [r9], 0
        je .delete

        mov r11, r8
        mov r8, r9
        test r11, r11
        jnz .continue
        mov [rdi], r9
        jmp .continue

        .delete:
            push rsi
            push rdi
            call ft_list_delete_one
            pop rdi
            pop rsi
            jmp .continue

        .continue:
            mov r9, 10
            jmp .loop

    .done:
        test r8, r8
        jz .empty
        ret
    .empty:
        mov qword [rdi], 0
        ret