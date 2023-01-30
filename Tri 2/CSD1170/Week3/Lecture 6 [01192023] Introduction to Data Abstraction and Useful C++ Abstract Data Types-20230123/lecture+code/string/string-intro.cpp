// HLP2: string-intro.cpp
// 01/24/2022
// The following code illustrates the reading a sequence of characters
// from the standard input stream using overloaded operator>> function
// provided by the interface of std::string.
// Notice that similar to scanf(), a string is delimited by whitespace
// characters. This means the following program cannot be used to read
// the full name of the user.
/*
The string type is defined in header <string>. An object of type string
contains a sequence of zero or more characters. If n is an integer,
c is a char, is is an input stream, and os is an output stream, then
the string operations include:

std::string s;
          Defines s as a variable of type std::string that is initially empty.
std::string t = s;
          Defines t as a variable of type std::string that initially contains
          a copy of the characters in s, where s can be either a string or a
          string literal.
std::string z(n, c);
          Defines z as a variable of type std::string that initially contains
          n copies of the character c. Here, c must be a char, not a string or
          a string literal.
os << s   Writes the characters contained in s, without any formatting changes,
          on the output stream denoted by os. The result of the expression is os.
is >> s   Reads and discards characters from the stream denoted by is until
          encountering a character that is not whitespace. Then reads successive
          characters from is into s, overwriting whatever value s might have had,
          until the next character read would be whitespace. The result is is.
s + t     The result of this expression is an std::string that contains a copy of
          the characters in s followed by a copy of the characters in t. Either s
          or t, but not both, may be a string literal or a value of type char.
s.size()  The number of characters in s.	
*/

#include <iostream>
#include <string> // must be included to use std::string

// ask for a person's name and greet the person
int main() {
  std::cout << "Please enter your first name: ";
  std::string name;	// define name
  std::cin >> name; // read string from standard input into object name

  // write a greeting
  std::cout << "Hello, " << name << "!" << "\n";
}
