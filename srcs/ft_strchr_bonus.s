global ft_strchr

ft_strchr:
    .loop:
        mov al, byte [rdi]
        cmp al, sil
        je .found
        test al, al
        jz .notfound
        inc rdi
        jmp .loop
    .found:
        mov rax, rdi
        ret
    .notfound:
        xor rax, rax
        ret
