// HLP2
// Culmination of discussion on class design and implementation.
// Testing interface/implementation of class hlp2::Str ...

#include <iostream>
#include "str.hpp"
#include <cctype>
#include <algorithm>

// definitions of functions private to this source file ...
namespace {
  bool greater_than(char lhs, char rhs) {
    return lhs > rhs;
  }
}

int main() {
  hlp2::Str s1;
  hlp2::Str s2{"hello"};
  hlp2::Str s3{s2};

  std::cout << "How many Str objects so far ... " << hlp2::Str::get_count() << "\n"; 

  std::cout << "s1: <" << s1 << ">\n";
  std::cout << "s2: <" << s2 << ">\n";
  std::cout << "s3: <" << s3 << ">\n";

  s1 = s2;
  s2 = "world";
  s3 = s1 + " " + s2;

  std::cout << "s1: <" << s1 << ">\n";
  std::cout << "s2: <" << s2 << ">\n";
  std::cout << "s3: <" << s3 << ">\n";

  for (hlp2::Str::size_type i {0}; i < s3.size(); ++i) {
    if (std::islower(s3[i])) {
      s3[i] = std::toupper(s3[i]);
    }
  }
  std::cout << "s3: <" << s3 << ">\n";

  hlp2::Str const cs {s3};
  std::cout << "cs: <";
  for (hlp2::Str::size_type i {0}; i < cs.size(); ++i) {
    std::cout << cs[i];
  }
  std::cout << ">\n";
  std::cout << "cs: <";
  for (hlp2::Str::value_type x : cs) {
    std::cout << x;
  }
  std::cout << ">\n";

  std::cout << "Enter a string: ";
  hlp2::Str in_str;
  std::cin >> in_str;
  std::cout << "printing in_str using op<<: <" << in_str << ">\n";
  std::cout << "printing in_str using range-for: <";
  for (hlp2::Str::value_type x : in_str) {
    std::cout << x;
  }
  std::cout << ">\n";

  std::cout << "after sorting in_str in ascending order: ";
  std::sort(in_str.begin(), in_str.end(), greater_than);
  std::cout << '<' << in_str << ">\n";
  std::cout << "after sorting in_str in descending order: ";
  std::sort(std::begin(in_str), std::end(in_str));
  std::cout << '<' << in_str << ">\n";

  hlp2::Str foo {'a','l','p','h','a'}; //"alpha";
  hlp2::Str bar {'b', 'e', 't', 'a'};  // "beta";
  std::cout << "foo is: <" << foo << "> | bar is: <" << bar << ">\n";

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

  std::cout << "How many String objects so far ... "  << hlp2::Str::get_count() << "\n"; 

#if 0
	// testing the overloaded << and >> operators
	std::cout << "Reading a string: ";
	std::cin >> s;
	std::cout << "Printing contents of object s using friend function: " << s << std::endl;
#endif
}
