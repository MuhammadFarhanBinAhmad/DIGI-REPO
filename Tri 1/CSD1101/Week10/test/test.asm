section .data
fmt     db "%lld",10,0
a         dq 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
n         dq 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14

section .text
    global _start
    extern printf

_start:
    mov    rcx, [n+24]
    mov    rbx, a
    syscall
next:
    mov    rax, [rbx+rcx*8]
    printf fmt, rax
    loop   next

    mov rax, 60
    mov rdi, 0
    syscall 