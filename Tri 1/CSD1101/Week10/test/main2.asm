section .data
    msg db "Hello world!",10      ; 10 is the ASCII code for a new line (LF)

section .text
    global _start
    extern puts

_start:
    mov rdi, msg
    call puts
    add rsp, 0x8

    mov rax, 60
    mov rdi, 0
    syscall  