global ft_putchar, ft_putstr, ft_putendl, ft_putunbr
extern ft_strlen

ft_putchar:
    push rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    pop rdi
    ret

ft_putstr:
    call ft_strlen
    mov rdx, rax
    mov rax, 1
    mov rsi, rdi
    mov rdi, 1
    syscall
    ret

ft_putendl:
    call ft_putstr
    mov rdi, 10
    call ft_putchar
    ret

ft_putunbr:
    cmp rdi, 10
    jl .digit
    mov rax, rdi
    mov rcx, 10
    xor rdx, rdx
    div rcx
    mov rdi, rax
    push rdx
    call ft_putunbr
    pop rdi
    .digit:
        add rdi, 48
        call ft_putchar
        ret