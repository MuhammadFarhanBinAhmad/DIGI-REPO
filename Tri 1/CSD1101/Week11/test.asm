
section .data
fmt db "%lld",10,0

section .text
 global _start
 extern printf


_start:
 push 10
 push 20
 push 30

 mov rdi,fmt
 pop rsi
 pop rsi
 pop r15
 xor rax,rax
 call printf

 mov rax, 60
 mov rdi, 0
 syscall
