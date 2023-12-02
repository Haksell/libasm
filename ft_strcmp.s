global ft_strcmp

section .text

ft_strcmp:
    xor eax, eax
    xor rcx, rcx
    xor r8, r8
    xor r9, r9

    .loop:
        mov r8b, byte [rdi + rcx]
        mov r9b, byte [rsi + rcx]
        cmp r8b, r9b
        jne .diff
        test r8b, r8b
        jz .same
        inc rcx
        jmp .loop
    
    .diff:
        mov al, r8b
        sub eax, r9d
        ret

    .same:
        ret