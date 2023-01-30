; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1100 Assignment 11
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Muhammad Farhan Bin Ahmad, b.muhammadfarhan@digipen.edu
;
; Compile: nasm -f elf64 -g -F dwarf functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
; Run: ./main 0
; Debug: gdb main
;  (gdb) b f1
;  (gdb) run
;  ...
;  0
;  ...
;  (gdb) ...
;
; Copyright: 2021, Digipen Institute of Technology, Singapore
;
; Note: All functions use at most 6 parameters
;      p1, p2, p3, p4, p5, p6
;      located in registers
;      rdi, rsi, rdx, rcx, r8, r9
;      accordingly.
; ------------------------------------------------------------------

    section .text

    global f1
    global f2

f1:
; TODO: - Given two circles with central points at (p1,p2), (p3,p4),
;       and radii p5, p6. All values in p1, ..., p6 are integers.
;       - Create code that determins intersection
;       or non-intersection of the circles.
;       - You code must return 1 when intersecting or 0 otherwise
;       based on the result of calculation.
;       - Tip 1: use the method without square root calculations:
;       if  <= (p5+p6)^2 then return 1
;       - Tip 2: do not use pow() function to calculate x^2, use 
;       x*x instead.
;       - Note that a point is a circle with radius 0.
    sub rdi,rdx;rdi = rdi-rdx
    sub rsi,rcx;rsi = rsi-rcx
    mov rdx,0

    ;(p1-p3)^2
    mov rax,rdi
    imul rdi
    push rax;push mul value to stack
    pop r10;r10 = rax
    mov rdx,0;sanity check
    mov rax,0

    ;(p2-p4)^2
    mov rax,rsi
    imul rsi
    push rax;push mul value to stack
    pop r11;r11 = rax
    mov rdx,0;sanity check
    mov rax,0

    ;(p1-p3)^2+(p2-p4)^2 - Distance
    add r10,r11

    ;(p5+p6)^2 - radius
    add r8,r9
    mov rax,r8
    imul r8
    push rax
    pop r12
    mov rdx,0
    mov rax,0

    ;(p1-p3)^2+(p2-p4)^2<=(p5+p6)^2
    cmp r10,r12
    jle _return
    xor rax,rax
    ret ; return rax;

_return:
    mov rax,1
    ret
f2:
; TODO: - Calculare (p1+0)*(p2+0) + (p1+1)*(p2+1) + (p1+2)*(p2+2) + .... +
;           (p1+p3)*(p2+p3)
;       - Tip: Accumulate the result in reverse order by decrementing 
;           p3 or (p1+p3) and (p2+p3)


    mov r12,0;total value
    jp _Loop

_Loop:

    ;keep og value of p1 and p2
    mov r10 ,rdi
    mov r11,rsi

    push rdx

    add r10,rdx;p1+p3
    add r11,rdx;p2+p3
    mov rax,r10;rax = rdi
    imul r11;rax*rsi :(p1+p3)*(p2+p3)

    add r12,rax; push value from mul to r12
    xor rax,rax;clear rax for next loop

    pop rdx;pop back rdx
    dec rdx;check value of rdx
    cmp rdx,0
    jge  _Loop;check if value is more than 0

    mov rax,r12;cause value return is rax(dunno why)
    ret; return rax;


