%macro DEFINE_WRAPPER 2
    global %1
    %1:
        mov rax, %2
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

extern __errno_location
DEFINE_WRAPPER ft_read, 0
DEFINE_WRAPPER ft_write, 1
