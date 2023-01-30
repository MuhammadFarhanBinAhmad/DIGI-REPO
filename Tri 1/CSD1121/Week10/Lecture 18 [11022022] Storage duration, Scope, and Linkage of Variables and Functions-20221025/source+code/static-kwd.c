/*
Within a function or a block, variables that by default have automatic storage
duration can be defined to have static storage duration using keyword static.
*/

#include <stdio.h> // declare function printf

// declarations (not definitions) of functions
// name of function parameter is not required in declaration ...
char digit_to_hex_char_ver1(int);
char digit_to_hex_char_ver2(int);
char digit_to_hex_char_ver3(int);

// declaration (and definition) of function main
int main(void) {
  printf("Decimal value 10 is hex digit %c\n", digit_to_hex_char_ver1(10));
  printf("Decimal value 12 is hex digit %c\n", digit_to_hex_char_ver1(12));
  printf("Decimal value 14 is hex digit %c\n", digit_to_hex_char_ver1(14));
}

// definition of function digit_to_hex_char
char digit_to_hex_char_ver1(int digit) {
  char const hex_chars[] = "0123456789ABCDEF";
  return hex_chars[digit];
}

// version 2 of the function - more efficient but terse
char digit_to_hex_char_ver2(int digit) {
  /*
  We don't need to define and instantiate array hex_chars everytime this
  function is invoked. Instead we use literal string "0123456789ABCDEF"
  as the array name.
  */
  return "0123456789ABCDEF"[digit];
}

// version 3 of the function - efficient but not necessarily terse
char digit_to_hex_char_ver3(int digit) {
  /*
  Here, we specify array hex_chars to have static storage duration. That is,
  the array is instantiated before program begins execution and will stay
  alive throughout the duration of the program. Using qualfier const, we
  ensure that the array hex_chars is read-only. This is more efficient than
  version 1 which has to instantiate the array every time the function is
  invoked and then discard the array when program execution returns from the
  function. It is less terse than version 2 because an array name with the
  subscript operator is used whereas in version 2, we used literal string
  "0123456789ABCDEF" as the array name.
  */
  static char const hex_chars[] = "0123456789ABCDEF";
  return hex_chars[digit];
}
