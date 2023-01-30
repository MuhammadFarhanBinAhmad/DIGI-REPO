// HLP2: string-find-replace-substr.cpp
// 01/24/2022
// This program illustrates the application of the find, replace, substr
// interface of the string class.
// This program uses command-line arguments to generate temporary filenames.
// For example, if you start the program as
//   string2 prog.dat mydir hello. oops.tmp end.dat
// the output is
//   prog.dat  ->  prog.tmp
//   mydir     ->  mydir.tmp
//   hello.    ->  hello.tmp
//   oops.tmp  ->  oops.xxx
//   end.dat   ->  end.tmp
//	
// Usually, the generated filename has the extension .tmp, whereas the temporary
// filename for a name with the extension .tmp is .xxx.

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "Usage: ./a.out prog.dat mydir hello. oops.tmp end.dat\n";
    return 0;
  }
  const std::string suffix{"tmp"};
  
  for(int i{1}; i < argc; ++i) {
    // process argument as filename
    std::string filename = argv[i], tmpname(filename);
		
/*
string::size_type
-----------------
All STL and the standard C++ library containers provide the type size_type. If
cont is the name of a STL (or C++ library) container, then cont::size_type is
the name of the appropriate unsigned integral type for holding the size of any
object of type container. That is, string::size_type is the unsigned integral 
type that can hold the size of any string object. It is important for you to 
use string::size_type to define idx to ensure that idx is capable of containing 
the index of any character in filename, no matter how large that number might be.
We could simply have said that idx has type int, and indeed, doing so would 
probably work. However, the value of idx depends on the size of the input to the
program, and we have no control over how long that input might be. It is 
conceivable that someone might give our program a string so long that an int is
insufficient to contain its length.
*/

/*
Searching and Finding in strings
--------------------------------
The C++ standard library provides many abilities to search and find characters
or substrings in a string:
1. By using member functions, you can search
  - a single character, a character sequence (substring), or one of a certain set
  of characters
  - forward and backward
  - starting from any position at the beginning or inside the string
2. By using the regex library, you can search for more complicated patterns of
character sequences. The regex library is not covered in HLP2.
3. By using STL algorithms, you can also search for single characters or specific
character sequences. These algorithms also allow the use of their own comparison
criteria. STL algorithms will be covered in 2nd half of the current semester.

Member functions for searching and finding
------------------------------------------
All search functions use the term "find" inside their name. They try to find a
character position given a value that is passed as an argument. How the search
proceeds depends on the exact name of the find function. Here are the list of
all search functions for strings:

-------------------------------------------------------------------------
  String function   |           Effect
-------------------------------------------------------------------------
find()              | Finds the first occurrence of value
rfind()             | Finds the last occurrence of value (reverse find)
find_first_of()     | Finds the first character that is part of value
find_last_of()      | Finds the last character that is part of value
find_first_not_of() | Finds the first character that is not part of value
find_last_not_of()  | Finds the last character that is not part of value
--------------------------------------------------------------------------
All search functions return the index of the first character of the character
sequence that matches the search. If the search fails, they return npos.
The search functions use the following argument scheme:
1. The first argument is always the value that is searched for.
2. The second optional value indicates the index at which to start the search
in the string.
3. The optional third argument is the number of characters of the value to
search.

If a search function fails, it returns string::npos. Be very careful when
using the string value npos and its type. When you want to check the
return value, always use string::size_type, NOT int or unsigned for the type
of the return value; otherwise, the comparison of the return value with
string::npos might not work. This behavior is the result of the design decision
that npos is defined as -1. Unfortunately, string::size_type must be an unsigned
integral type. Because -1 is converted into an unsigned integral type, the
exact value of npos depends on the exact definition of type size_type.

See Section 9.5 of the text for more information on string operations.
*/
    // search period in filename		
    std::string::size_type idx = filename.find('.');
    // filename does not contain any period, add suffix ".tmp"
    if (idx == std::string::npos) {
      tmpname += '.' + suffix;
    }
    else {
      // get filename's extension consisting of all characters after the period
      std::string extname = filename.substr(idx+1); // use all characters 
      // contains period but no extension: append "tmp"
      if (extname.empty()) {
        tmpname += suffix;
      } else if (extname == suffix) { // replace extension "tmp" with "xxx"
        // see page 362 of text for more information on replace function
        tmpname.replace(idx+1, extname.size(), "xxx");
      } else { // replace any extension with "tmp"
        tmpname.replace(idx+1, std::string::npos, suffix);
      }
    }
		
    // print filename and temporary name
    std::cout << filename << " => " << tmpname << "\n";
  }
}
