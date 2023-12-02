global ft_strcpy

section .text

ft_strcpy:
    xor rcx, rcx

    .loop:
        mov dl, byte [rsi + rcx]
        cmp dl, 0
        mov [rdi + rcx], dl
        je .done
        inc rcx
        jmp .loop

    .done:
        mov rax, rdi
        ret
