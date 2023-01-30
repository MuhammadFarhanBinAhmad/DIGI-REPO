// HLP2: string-iterate.cpp
// 01/24/2022
// The following code illustrates overloaded operators of std::string and
// the use of overloaded subscript operator and range-for statements
// to iterate thro' each character in the string.

#include <string>   // string
#include <array>    // array
#include <iostream> // cout and cin
#include <cctype>   // for isalpha, islower, toupper

int main() {
  std::cout << "Enter your first and last names: ";
  std::string first_name, second_name; // default construction
  // the string input operator will discard any leading whitespace (spaces,
  // newlines, tabs). It then reads characters until the next whitespace
  // character is encountered.
  std::cin >> first_name >> second_name;
  std::cout << "Hello " << first_name << " " << second_name << "\n";

  // a non-member function overloads the + operator for string and C-style
  // string operands (as long as we have a string operand):
  std::string full_name = first_name + " "; // full_name = op+(first_name + " ");

  // a member function overloads the += operator for extending a string object
  // which in this case is full_name:
  full_name += second_name; // full_name.op+=(second_name);

  // print the greeting again:
  std::cout << "Hello again ";
  // we can iterate through each element of the sequence using the overloaded
  // subscript operator.
  // a member function overloads the [] operator for referencing any element
  // of the sequence.
  // the size member function returns number of characters in sequence.
  for (std::string::size_type i{0}; i < full_name.size(); ++i) {
    std::cout << full_name[i]; // full_name.op[](i);
  }
  std::cout << "\n";


  // print the greeting again:
  std::cout << "Three Hello's to you ";
  // if we want to do something to every character in a string, by far the
  // simplest approach is to use the range-for statement.
  // this statement iterates through the elements in a given sequence and
  // performs some operation on each value in that sequence.
  for (char x : full_name) {
    std::cout << x;
  }
  std::cout << "\n";

  // the range-for statement can also be used to modify the sequence over which
  // we're iterating by using a reference to each element in the sequence.
  // here, we'll convert a lower-case character in sequence to upper-case:
  for (char& x : full_name) {
    x = std::islower(x) ? std::toupper(x) : x;
  }
  
  // we again use the range-for to print the name for a third time,
  // except now, in upper-case characters:
  std::cout << "Upper-case Hello's to you: ";
  for (char x : full_name) {
    std::cout << x;
  }
  std::cout << "\n";

  // we can iterate thro' the elements of a C++ sequence or container using a
  // concept called iterator.
  // std::begin(full_name) and std::end(full_name) return pointers to the first
  // and one-past-the-last elements of the string.
  // On the other hand, std::cbegin(full_name) and std::cend(full_name) return 
  // pointers to read-only chars.
  // Meanwhile, the interface on std::string itself provides member functions
  // begin()/cbegin() and end()/cend() functions ...
  // More details about iterators are in the handout on strings.
  std::cout << "Iterator Hello's to you: ";
  std::string::const_iterator cit {std::cbegin(full_name)};
  while (cit != std::cend(full_name)) {
    std::cout << *cit;
    ++cit;
  }
  std::cout << '\n';

  std::cout << "Iterator hello's to you: ";
  // using read/write iterators to convert from upper-case to lower-case ...
  for (std::string::iterator it {std::begin(full_name)}, last{std::end(full_name)}; it != last; ++it) {
    *it = std::isupper(*it) ? std::tolower(*it) : *it;
    std::cout << *it;
  }
  std::cout << '\n';

  // SIDENOTE: The range-for statement can also be used for static arrays and std::array variables:
  int int_array[] = {10, 20, 30, 40, 50};
  int sum {0};
  for (int x : int_array) {
    sum += x;
  }
  std::cout << "Sum of elements in int_array: " << sum << "\n";

  std::array<int, 5> int_array2{-10,-20,-30,-40,-50};
  int sum2{0};
  for (int x : int_array2) {
    sum2 += x;
  }
  std::cout << "Sum of elements in int_array2: " << sum2 << "\n";
}
