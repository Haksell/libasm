global ft_strcpy

ft_strcpy:
    mov rax, rdi

    .loop:
        mov dl, byte [rsi]
        mov [rdi], dl
        test dl, dl
        jz .done
        inc rdi
        inc rsi
        jmp .loop

    .done:
        ret
