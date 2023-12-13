global ft_isspace

ft_isspace:
    cmp edi, ' '
    je .yes
    cmp edi, 9
    jl .no
    cmp edi, 13
    jg .no
    .yes:
        mov rax, 1
        ret
    .no:
        xor rax, rax
        ret