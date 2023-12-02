global ft_write
extern __errno_location

section .text

ft_write:
    mov rax, 1
	syscall
    cmp rax, 0
    jge .success

    .fail:
        mov rdx, rax
        neg rdx
        call __errno_location
        mov [rax], rdx
        mov rax, -1
        ret

    .success:
        ret
