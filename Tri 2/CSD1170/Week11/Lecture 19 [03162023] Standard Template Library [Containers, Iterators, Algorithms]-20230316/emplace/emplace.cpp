// HLP2: emplace.cpp [pghali@digipen.edu]
// Compile/link like this to see difference between emplace_back() and push_back():
// g++ -std=c++17 emplace.cpp string.cpp -D=DEBUG
// Execute executable program as usual
#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include "string.h"

/*
To pass the preprocessor the DEBUG macro (to print when construction and destruction
takes place for hlp2::String objects), use the -D option in the command-line:

g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror -D=DEBUG emplace.cpp string.cpp
*/

// print all elements of any container as long as the element type overloads
// the left-shift operator
template <typename Cont>
void print(Cont const& c, hlp2::String const& pre, hlp2::String const& pos="\n") {
  std::cout << pre;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << pos;
}

int main() {
/*
If you have a container holding, say, hlp2::Strings, it seems logical that when you add
a new element via an insertion function (i.e., insert or push_back), the type of element
you’ll pass to the function will be hlp2::String. After all, that’s what the container
has in it. Logical though this may be, it’s not always true. Consider this code:
*/
  std::vector<hlp2::String> vs; // container of hlp2::String
  vs.reserve(100); // to avoid re-allocations

  std::cout << "-------Using std::vector<>::push_back() to add an object------\n";
  vs.push_back("Seattle");      // add string literal
  std::cout << "-------Done------\n";

/*
Here, the container holds hlp2::Strings, but what you have in hand—what you’re actually
trying to push_back - is a string literal, i.e., a sequence of characters inside quotes.
A string literal is not a hlp2::String, and that means that the argument you’re passing
to push_back is not of the type held by the container.

push_back for std::vector is overloaded for lvalues and rvalues as follows:

template <class T,                           // from the C++11
          class Allocator = allocator<T>>    // Standard
class vector {
public:
  …
  void push_back(const T& x);                // insert lvalue
  void push_back(T&& x);                     // insert rvalue
  …
};

In the call:

  vs.push_back("Seattle");

compilers see a mismatch between the type of the argument (const char[8]) and
the type of the parameter taken by push_back (a reference to hlp2::String).
They address the mismatch by generating code to create a temporary
hlp2::String object from the string literal, and they pass that temporary
object to push_back. In other words, they treat the call as if it had been
written like this:

vs.push_back(hlp2::String("Seattle")); // create temporary hlp2::String
                                       // and pass it to push_back

this code isn’t as efficient as it should be.

To create a new element in a container of hlp2::Strings, they understand, a
hlp2::String constructor is going to have to be called, but the code above 
doesn’t make just one constructor call. It makes two. And it calls the 
hlp2::String destructor, too. You can see it by compiling the code with the
-D=DEBUG option and then executing the program. Here’s what happens at runtime
in the call to push_back:

1) A temporary hlp2::String object is created from string literal "Seattle".
This object has no name; we’ll call it temp. Construction of temp is the first
hlp2::String construction. Because it’s a temporary object, temp is an rvalue.

2) temp is passed to the lvalue overload for push_back (because we have not
implemented the move constructor for hlp2::String), where it’s bound to the
lvalue reference parameter x. A copy of x is then constructed in the memory for
the std::vector using the copy constructor of hlp2::String. This construction 
- the second one - is what actually creates a new object inside the std::vector.

3) Immediately after push_back returns, temp is destroyed, thus calling the 
hlp2::String destructor.

Notice that if there were a way to take the string literal and pass it directly
to the code in step 2 that constructs the hlp2::String object inside the
std::vector, we could avoid constructing and destroying temp. That would be 
maximally efficient. There is a way to do exactly what is needed for maximal 
efficiency in the call to push_back. It’s to not call push_back. push_back is
the wrong function. The function you want is emplace_back.

emplace_back does exactly what we desire: it uses whatever arguments are passed
to it to construct a hlp2::String directly inside the std::vector. No temporaries
are involved:
*/
  std::cout << "-------Using std::vector<>::emplace_back() to add an object------\n";
  vs.emplace_back("Singapore");
  std::cout << "-------Done------\n";

/*
emplace_back is available for every standard container that supports push_back. 
Similarly, every standard container that supports push_front supports emplace_front.
And every standard container that supports insert (which is all but std::forward_list
and std::array) supports emplace. The associative containers offer emplace_hint to 
complement their insert functions that take a “hint” iterator, and std::forward_list
has emplace_after to match its insert_after.

What makes it possible for emplacement functions to outperform insertion functions is
their more flexible interface. Insertion functions take objects to be inserted, while
emplacement functions take constructor arguments for objects to be inserted. This 
difference permits emplacement functions to avoid the creation and destruction of 
temporary objects that insertion functions can necessitate.

Because an argument of the type held by the container can be passed to an emplacement
function (the argument thus causes the function to perform copy or move construction),
emplacement can be used even when an insertion function would require no temporary.
In that case, insertion and emplacement do essentially the same thing. For example,
given
*/
  hlp2::String city("Sao Paulo");

/*
both of the following calls are valid, and both have the
same net effect on the container:
*/
  vs.push_back(city);    // copy-construct city at end of vs
  vs.emplace_back(city); // ditto

/*
Try out emplace, emplace_back for other containers ...
*/
}