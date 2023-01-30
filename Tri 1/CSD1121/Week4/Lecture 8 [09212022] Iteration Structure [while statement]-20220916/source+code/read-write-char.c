/*
* read-write-char.c - source file illustrating the use of C standard library
* I/O functions: getchar and putchar.
*
* Input from standard input: sequence of characters
* Side effect of program: Echo each character back to standard output.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror read-write-char.c -o read-write-char.out
*
* Run: ./read-write-char.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

int main(void) {
  int max_cnt = 5;
  printf("type %d characters and press return: ", max_cnt);
  int i = 0;
  while (i < max_cnt) {
    /*
    Recall that I/O is implemented by the standard library using streams. A
    stream is an abstraction that connects the terminal (keyboard and screen) 
    to the program. The library supports both text (human-readable) and binary
    stream. Text stream represents human-readable text with each byte 
    containing values from the ASCII character set. On the other hand, a binary
    stream is a string of unprocessed bytes with each byte potentially 
    representing non-ASCII values. In general, binary streams represent digital
    images, audio, and video. Here, we're only concerned with text streams.
    
    A text stream is a sequence of lines; each line has zero or more characters
    followed by newline ('\n') character.
    
    The standard library provides several functions for reading or writing one
    character at a time. Functions getchar and putchar are the simplest.
    
    Each time it is called, getchar reads the next input character from a text
    stream and returns that as its value. That is, after ch = getchar(); the
    variable ch contains the next character of input.
    */
    int ch = getchar();
    // The function putchar prints a character to stdout each time it is called
    putchar(ch);
    
    i += 1;
  }
  // put newline to better understand output
  putchar('\n');
  
  return 0;
}
