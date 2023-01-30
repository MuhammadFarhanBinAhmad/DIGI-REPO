; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1100 Assignment 10
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Muhammad Farhan Bin Ahmad, b.muhammad@digipen.edu
; .
; Compile: nasm -f elf64 functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
; .
; Copyright: 2021, Digipen Institute of Technology, Singapore
; .
; Note: All functions use at most 6 parameters
;      p1, p2, p3, p4, p5, p6
;      located in registers
;      rdi, rsi, rdx, rcx, r8, r9
;      accordingly.
; ------------------------------------------------------------------

    section .text

    global f1
    global f2
    global f3
    global f4
    global f5

f1:
; TODO: Return 5th integer parameter.

    mov rax,r8;place value of r8 in register rax
    ret

f2:
; TODO: Return the result of addition of the first 3 integer parameters.
    mov rax,0;clear rax
    add rax,rdi;rax = rax+rdi
    add rax,rsi;rax = rax+rsi
    add rax,rdx;rax = rax+rdx
    ret

f3:
; TODO: Return the result of calculation p1 * p2 + p3 / p4 + 1,
;       where operator / calculates an integer result.
; Tip: Be aware that parameter p4 in rdx is used in both * and /.

    ;rax = rdx
    mov rax,rdx
    mov rdx,0;clear rdx
    idiv rcx; r15 = p3 / p4;rax = top,rcx = remainder
    mov r15,rax;r15 = current rax value

    mov rax,rdi;rax = rdi
    mov rdx,0;reset rdx value
    imul rax,rsi
    ; rax = p1 * p2

    add rax,r15
    ; rax += r15
    
    add rax,1
    ; rax++

    ret

f4:
; TODO: Return the result of calculation 
;       p1 * 100000 + p2 * 10000 + p3 * 1000 + p4 * 100 + p5 * 10 + p6 * 1.
; Tip: Use push/pop to save rdx temporarily in stack to do multiplications.


    ; r11 = p1 * 100000
    mov rax,rdi;rax = rdi
    push rdx;push because currnet value in rdx need be use later and this register will be overwritten
    imul rax,100000; rax *= 100000
    mov r11,rax

    ; r12 = p2 * 10000
    mov rax,0;sanity check
    mov rax,rsi;change value in rxi into the value in rsi
    imul rax,10000;rax*= 10000
    mov rdx,0;clear rdx
    mov r12,rax

    ; r13 = p3 * 1000
    pop rdx;by right can put in rax directly, but gut feeling says no so yeah
    mov rax,rdx
    mov rdx,0
    imul rax,1000
    mov r13,rax

    ; r14 = p4 * 100
    mov rax,rcx
    imul rax,100
    mov r14,rax

    ; r15 = p5 * 10
    mov rax,r8
    imul rax,10
    mov r15,rax

    ; rax = p6 + r11 + r12 + r13 + r14 + r15
    mov rax,r9;sanity check
    add rax,r11
    add rax,r12
    add rax,r13
    add rax,r14
    add rax,r15
    ret

f5:
; TODO: Return the result of calculation 
;       p1 / 100000 - p2 / 10000 - p3 / 1000 - p4 / 100 - p5 / 10.

    ; r11 = p1 / 100000
    push rdx;push cause he will be needed later
    mov rdx,0;Avoid floating point error
    mov rax,rdi;rax = rdi
    mov r11,100000
    idiv r11
    mov r11,rax

    ; r12 = p2 / 10000
    mov rax,rsi
    mov rdx,0
    mov r12,10000
    idiv r12
    mov r12,rax

    ; r13 = p3 / 1000
    mov rdx,0
    pop rax
    mov r13,1000
    idiv r13
    mov r13,rax

    ; r14 = p4 / 100    
    mov rdx,0
    mov rax,rcx
    mov r14,100
    idiv r14
    mov r14,rax

    ; r15 = p5 / 10
    mov rdx,0
    mov rax,r8
    mov r15,10
    idiv r15
    mov r15,rax

    ; rax = r11 - r12 - r13 - r14 - r15
    mov rax,r11
    sub rax,r12
    sub rax,r13
    sub rax,r14
    sub rax,r15
    ret 

