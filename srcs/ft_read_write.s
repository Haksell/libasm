%macro SYSCALL_ERRNO 1
    mov rax, %1
	syscall
    test rax, rax
    js .fail
    ret
    .fail:
        mov rdx, rax
        neg rdx
        call __errno_location
        mov [rax], rdx
        mov rax, -1
        ret
%endmacro

global ft_read, ft_write
extern __errno_location

section .text

ft_read:
    SYSCALL_ERRNO 0

ft_write:
    SYSCALL_ERRNO 1
