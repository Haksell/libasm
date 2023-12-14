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
    test rax, rax
    jz .done
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
    .done:
        ret

%macro FT_LIST_REMOVE_IF_PUSH_ALL 0
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
%endmacro

%macro FT_LIST_REMOVE_IF_POP_ALL 0
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
%endmacro

ft_list_remove_if:
    mov r8, 0
    mov r9, [rdi]
    .loop:
        test r9, r9
        jz .move_begin
        mov r10, qword [r9 + 8]
        FT_LIST_REMOVE_IF_PUSH_ALL
        mov rdi, [r9]
        mov rsi, rsi
        call rdx
        FT_LIST_REMOVE_IF_POP_ALL
        test eax, eax
        jz .remove
        jmp .keep
        .remove:
            test r8, r8
            jz .remove_done
            mov r11, qword [r9 + 8]
            mov qword [r8 + 8], r11
            .remove_done:
                test rcx, rcx
                jz .free_node
                FT_LIST_REMOVE_IF_PUSH_ALL
                mov rdi, [r9]
                call rcx
                FT_LIST_REMOVE_IF_POP_ALL
                .free_node:
                    FT_LIST_REMOVE_IF_PUSH_ALL
                    mov rdi, r9
                    call free
                    FT_LIST_REMOVE_IF_POP_ALL
                    jmp .continue_loop
        .keep:
            test r8, r8
            jnz .keep_done
            mov qword [rdi], r9
            .keep_done:
                mov r8, r9
                jmp .continue_loop
        .continue_loop:
            mov r9, r10
            jmp .loop
    .move_begin:
        test r8, r8
        jnz .done
        mov qword [rdi], 0
        .done:
            ret