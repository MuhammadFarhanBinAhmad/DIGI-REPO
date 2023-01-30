// HLP1: 05/18/2016
// char.c: consists of code from class lecture illustrating the
// character handling and string handling functions in the
// presentation deck on character strings.

#include <stdio.h>

// equivalent to isalpha() declared in <ctype.h>
int is_alpha(int ch) {
  return ( ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') ) ? 1 : 0;
}

// equivalent to isdigit() declared in <ctype.h>
int is_digit(int ch) {
  return ('0' <= ch && ch <= '9') ? 1 : 0;
}

// equivalent to tolower() declared in <ctype.h>
int to_lower(int ch) {
  return ('A' <= ch && ch <= 'Z') ? ch-'A'+'a' : ch;
}

// equivalent to toupper() declared in <ctype.h>
int to_upper(int ch) {
  return ('a' <= ch && ch <= 'z') ? ch-'a'+'A' : ch;
}

// convert lower-case characters in str to upper-case ...
void make_upper(char str[]) {
  for (int i = 0; str[i]; ++i) {
    str[i] = to_upper(str[i]);
  }
}

// print characters in str to standard output ...
void print_str(char const str[]) {
  for (int i = 0; str[i]; ++i) {
    fputc(str[i], stdout);
  }
  fputc('\n', stdout);
}

int main(void) {
  // test to_upper
  char ch = '#';
  printf("Character before %c and after calling to_upper(ch): %c\n", ch, to_upper(ch));
  ch = 'Z';
  printf("Character before %c and after calling to_upper(ch): %c\n", ch, to_upper(ch));
  ch = 'z';
  printf("Character before %c and after calling to_upper(ch): %c\n", ch, to_upper(ch));

  // for the reader: test the other functions: is_alpha, is_digit, and to_lower

  // string handling functions ...
  char city[] = {'s','i','n','g','a','p','o','r','e','\0'};
  // the null terminating character '\0' is just 0 ...
  // this means the previous initializer could have been written as:
  // char city[] = {'s','i','n','g','a','p','o','r','e',0};

  // C/C++ provide shorthand to specify initializers for c-string:
  // char city[] = "singapore";

  // call the function we've implemented to print characters in city to stdout
  print_str(city);
  // make characters in city uppercase if they're lowercase
  make_upper(city); 
  print_str(city); // print (now uppercase) characters in city to stdout
  // can also print using printf:
  printf("%s\n", city);
  // can also print using fputs ...
  fputs(city, stdout);
  // but fputs doesn't insert newline ...
  fputc('\n', stdout);

  return 0;
}
