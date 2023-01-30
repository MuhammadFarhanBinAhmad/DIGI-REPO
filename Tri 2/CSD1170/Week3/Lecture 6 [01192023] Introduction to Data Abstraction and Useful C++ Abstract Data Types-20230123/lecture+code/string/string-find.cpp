// HLP2: string-find.cpp
// 01/24/2022
// A common programming pattern is to loop through a sequence finding all
// occurrences of a specific item. In the program below, the find interface
// of class std::string is used to determine the number of  space characters
// in the string.
// The reader could update the program to take user input.

#include <string>
#include <iostream>

int main() {
  std::string line {"This is not a haiku"
                    " "
                    "Today is a good day"
                    " "
                    "Tomorrow will be a better day"
                    };
  std::cout << "<" << line << ">\n";

  // We want to find the number of spaces in a string.
  // The string class provides six different search functions [find, rfind,
  // find_first_of, find_first_not_of, find_last_of, find_last_not_of], each
  // of which has four overloaded versions: https://en.cppreference.com/w/cpp/string/basic_string/find
  // looking at these six functions, find seems to be the simplest:
  // it looks for its char argument and returns the index of the first match
  // that is found, or std::string::npos if there is no match.
  // The type of index returned (including npos) is std::string::size_type.
  // So, what is std::string::size_type?
  // The string and other library types define several companion types so that
  // these library types can be used in a machine-independent manner. Type
  // size_type is one of these companion types. To use the size_type defined by
  // string, we must use the scope operator to say that name size_type is defined
  // in string class, like this: std::string::size_type
  // We know that size_type is an unsigned type big enough to hold the size of any
  // string. Any string member function that returns size_type must be stored in
  // a variable of type size_type.
  // npos is a member defined by string type to represent the largest possible
  // value of type size_type. A machine independent way of specifying the largest
  // possible value is -1 (meaning the largest possible unsigned value in whatever
  // is the largest type of the machine).
  // 
  // We use the fact that find returns an index of the first match that is found,
  // or npos if there is no match to count the number of occurrences of the space
  // character by calling find in a while loop:
  int space_ctr {0};
  std::string::size_type pos {std::string::npos};
  // continue searching until there are no more occurrences of ' '
  while ( (pos = line.find(' ', pos+1)) != std::string::npos) {
    ++space_ctr;
  }
  std::cout << "spaces: " << space_ctr << "\n";
  
  // The condition in the while resets pos to the index of the first number
  // encountered starting from the current value of pos. So long as find returns
  // a valid index, we know a space character has been encountered.
  // Notice that pos is incremented - otherwise, the loop would never terminate.
  // to see why, consider what would happen if we didn't do the increment. On
  // the second iteration through the loop, we start looking at the character
  // indexed by pos. That character would be a number, so find would repeatedly
  // return the same pos.
  // For this reason, we start the initial position for pos at -1.
}
