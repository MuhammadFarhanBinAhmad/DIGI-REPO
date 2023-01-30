/*
* print-ints.c - shows format specifiers (d, i, u, o, x, X) and length
* modifiers (h, l, ll) used by function printf for printing integer values.
*
* Input (from standard input): none
* Side effect of program: Write to standard output various integer values
* illustrating format specifiers of printf function
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror print-ints.c -o print-ints.out
*
* Run: ./print-ints.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf

int main(void) {
  int val = 345;

  // format specifier d to print signed integer value
  printf("Format specifier %%d:   %d\n", val);
  // format specifier d to print signed integer value
  printf("Format specifier %%d:   %d\n", +val); // + sign doesn't print
  // format specifier d to print signed integer value
  printf("Format specifier %%d:   %d\n", -val); // - sign prints
  // format specifier i to print signed integer value
  printf("Format specifier %%i:   %i\n", -val); // i same as d
  // format specifier u to print unsigned integer value
  printf("Format specifier %%u:   %u\n", val);
  // format specifier u to print unsigned integer value
  printf("Format specifier %%u:   %u\n", -val); // prints 2's comp of -455
  // format specifier o to print unsigned integer value in octal
  printf("Format specifier %%o:   %o\n", val);
  // format specifier o to print unsigned integer value in octal
  printf("Format specifier %%o:   %o\n", -val); // prints 2's comp of -455 in octal
  // format specifier x to print unsigned integer value in hexadecimal with [a-f]
  printf("Format specifier %%x:   %x\n", val);
  // format specifier x to print unsigned integer value in hexadecimal with [A-F]
  printf("Format specifier %%x:   %X\n", val);
  // format specifier x to print unsigned integer value in hexadecimal
  printf("Format specifier %%x:   %x\n", -val); // prints 2's comp of -455 in hex
  // format specifier x to print unsigned integer value in hexadecimal
  printf("Format specifier %%X:   %X\n", -val); // prints 2's comp of -455 in hex
  // length modifier h used with format specifier d to print unsigned integer value as short
  printf("Format specifier %%hd:  %hd\n", val);
  // length modifier h used with format specifier d to print unsigned integer value as short
  printf("Format specifier %%hd:  %hd\n", 65535); // should print -1
  // length modifier l used with format specifier d to print signed integer value as long int
  printf("Format specifier %%ld:  %ld\n", -20000000L);
  // length modifier l used with format specifier u to print unsigned integer value as unsigned long int
  printf("Format specifier %%lu:  %lu\n", 20000000UL); // L suffix means constant is of type signed long int
  // length modifier l used with format specifier u to print unsigned integer value as unsigned long int
  printf("Format specifier %%lu:  %lu\n", -20000000L); // L suffix means constant is of type signed long int
  // length modifier ll used with format specifier d to print signed integer value as unsigned long long int
  printf("Format specifier %%lld: %lld\n", -20000000LL); // LL suffix means constant is of type signed long long int
  // length modifier ll used with format specifier d to print signed integer value as unsigned long long int
  printf("Format specifier %%llu: %llu\n", 20000000LLU); // LL suffix means constant is of type signed long long int

  return 0;
}
