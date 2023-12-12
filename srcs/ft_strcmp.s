global ft_strcmp

section .text

ft_strcmp:
    xor eax, eax
    xor edx, edx

    .loop:
        mov al, byte [rdi]
        mov dl, byte [rsi]
        cmp al, dl
        jne .done
        test al, al
        jz .done
        inc rdi
        inc rsi
        jmp .loop
    
    .done:
        sub eax, edx
        ret
