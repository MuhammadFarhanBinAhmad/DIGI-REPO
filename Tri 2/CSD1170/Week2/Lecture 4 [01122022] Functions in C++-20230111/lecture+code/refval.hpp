// HLP2: refval.hpp
// 01/18/2022
// The following code contains the driver that exercises overloaded functions
// foo [declared in refval.hpp and defined in refval.cpp] and is meant to 
// illustrate the idea that function overloading with value and reference 
// types will almost always fail.

#ifndef REFVAL_HPP
#define REFVAL_HPP

/*
The problem with the three overloads below is that we're mixing overloads
of value and reference parameters. This will prevent the following call
to always fail:

int i;
misc_stuff::foo(i); // ambiguous: is it foo(int) or foo(int&)?

Remember that call-by-value semantics can be simulated by call-by-const-
reference semantics. Therefore, removing the declaration foo(int);
will continue to provide call-by-value and call-by-reference semantics.
*/

namespace misc_stuff {

// uncomment following line to see compiler error messages from failed overload resolution...
//void foo(int); 
void foo(int&);
void foo(int const&);

} // end namespace misc_stuff

#endif
