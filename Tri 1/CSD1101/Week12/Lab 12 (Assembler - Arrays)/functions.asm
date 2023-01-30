; ------------------------------------------------------------------
; File: functions.asm
; Project: CSD1100 Assignment 12
; Author: Vadim Surov, vsurov@digipen.edu
; Co-Author: Muhammad Farhan Bin Ahmad, b.muhammadfarhan.edu
;
; Compile: nasm -f elf64 -g -F dwarf functions.asm -o functions.o
; Link: gcc main.o functions.o -o main.o -lm
; Run: ./main 0
; Debug: gdb main
;  (gdb) b len
;  (gdb) run
;  0
;  ...
;  To see a string in memory by address in rdi use gdb's command:
;  (gdb) p/d (char[20]) *$rdi
;   ...
;
; Copyright: 2021, Digipen Institute of Technology, Singapore
;
; Note: All functions use at most 6 parameters
;      p1, p2, p3, p4, p5, p6
;      located in registers
;      rdi, rsi, rdx, rcx, r8, r9
;      accordingly.
; Note 2: Use instruction cmp byte [rdi+rcx], 0 to campare
;         a byte by adddress rdi*rci with 0
; ------------------------------------------------------------------
    section .text

    global len
    global countn
    global counta
    global counts

len:
; TODO: - Given a null-terminated string. First parameter 
;         has address of the string.
;       - Find and return the length of the string.
;       - The string can be any length. When empty, return 0.
;       - It's not allowed to use any standard library function.
    mov rcx,0;set counter to 0
    cmp byte [rdi+rcx], 0; compare rcx and rdi, check if current is 0
    je exit;if 0, jump return rax

    count:
    add rcx,1;add counter
    cmp byte [rdi+rcx], 0;compare if current char is 0
    jne count;if not 0, loop

    exit:
    mov rax,rcx;exit program
    ret 

_loop:


countn:
; TODO: - Given a null-terminated string. First parameter 
;         has address of the string.
;       - Find and return the number of digits in 
;         the string.
;       - The string can be any length. When empty, return 0.
;       - It's not allowed to use any standard library function.
; Hints:- Digit '0' has ASCII code 48, '1' - 49, ... '9' - 57.
;       - You can use your function len.
    call len
    

    mov rcx ,rax ;value from rcx to rax. set rcx as my counter
    mov r10,0;char counter
    cmp rcx,0;check char, if 0, then jump to end
    je end;if 0, jump return rax

    countnumber:
    cmp byte [rdi+rcx], 48
    jl minuscounter;check is ascii value if less than 48
    cmp byte [rdi+rcx], 57
    jg minuscounter;check is ascii value if larger than 48
    add r10,1

    minuscounter:
    sub rcx,1
    cmp rcx,0
    jl end
    jmp countnumber

    end:
    mov rax,r10
    ret    ; return rax;



counta:
; TODO: - Given a null-terminated string. First parameter 
;         has address of the string.
;       - Find and return the number of alphabet letters in 
;         the string.
;       - The string can be any length. When empty, return 0.
;       - It's not allowed to use any standard library function.
; Hints:- Letters have ASCII codes 65-90 and 97-122.
;       - You can use your function len.
    call len
    

    mov rcx ,rax ;value from rcx to rax. set rcx as my counter
    mov r11,0;char counter
    cmp rcx,0;check char, if 0, then jump to end
    je endchar

    checkchar:
    cmp byte [rdi+rcx], 65
    jl minuscharcounter
    cmp byte [rdi+rcx], 122
    jg minuscharcounter
    cmp byte [rdi+rcx], 90
    jle addcharcounter
    cmp byte [rdi+rcx], 97
    jge addcharcounter

    jmp minuscharcounter
    
    addcharcounter:
    add r11,1;char counter

    minuscharcounter:
    sub rcx,1
    cmp rcx,0

    jl endchar
    jmp checkchar


    endchar:
    mov rax,r11
    ret    ; return rax

counts:
; TODO: - Given a null-terminated string. First parameter 
;         has address of the string.
;       - Find and return the number of special characters in 
;         the string.
;       - Special character is a character which is neither a digit
;         not a letter.
;       - The string can be any length. When empty, return 0.
;       - It's not allowed to use any standard library function.
; Hint: - You can use your functions len, countn, and counta.

    call len

    mov r12,rax

    call counta
    sub r12,rax
    call countn
    sub r12,rax

    mov rax,r12


    ret    ; return rax