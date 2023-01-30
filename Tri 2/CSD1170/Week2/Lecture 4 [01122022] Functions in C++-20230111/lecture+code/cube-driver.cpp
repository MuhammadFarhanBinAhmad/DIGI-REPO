// HLP2: cube-driver.cpp
// 01/18/2022
// The following code contains the driver that exercises overloaded functions
// cube [declared in cube.hpp and defined in cube.cpp] and is meant to illustrate
// the idea that function overloading with built-in types yields surprising results.
// Therefore, Well-designed systems must not include functions with parameters
// that are closely related or such a system must provide explicit overloads
// for every built-in type [just as the standard library does for operator<< functions
// for std::ostream class or for operator>> functions for std::istream class]
// Uncomment lines 109-111 of this file to get calls to functions fail
// because they're ambiguous.

#include <iostream>
#include "cube.hpp"

/*
cube.hpp declares 4 overloads for cube():

namespace misc_stuff {

int cube(int);
float cube(float);
long cube(long);
double cube(double);

}

In many cases, it is easy to figure out which overloaded function matches
a given call. However, it is not so simple when the overloaded functions
have the same number of parameters and when one or more of the parameters
have types that are related by conversions.
According to page 245 of the text, in order to determine the best match,
the compiler ranks the conversions that could be used to convert each
argument to the type of its corresponding parameter. Conversions are ranked
as follows:
1. An exact match. An exact match happens when:
  - the argument and parameter types are identical.
  - the argument is converted from an array or function type to corresponding
    pointer types.
  - A top-level const is added to or discarded from the argument. In the
  context of non-pointer variables, ci defined as
  int const ci = 10;
  has top-level constness because variable ci is itself const.
2. Match through const conversion. (This is not discussed here.)
3. Match through a promotion. (Discussed below.)
4. Match through an arithmetic conversion. There are complicated rules that
define a hierarchy of type conversions in which values are converted to
the widest possible type.
5. Match through class-based conversion. (Not discussed here.)

The important thing to remember is that promotions and conversions among
built-in types can yield surprising results in the context of function
matching. Well-designed systems must not include functions with parameters
that are closely related or such a system must provide explicit overloads
for every built-in type [just as the standard library does for operator<< functions
for std::ostream class or for operator>> functions for std::istream class]
*/

int main() {
  int int_val{3};
  float flt_val{3.14f};
  double dbl_val{3.33};
  long lon_val{3L};
  
  // There will be perfect matches for following calls to cube():
  misc_stuff::cube(int_val); // cube(int_val)
  misc_stuff::cube(flt_val); // cube(flt_val)
  misc_stuff::cube(dbl_val); // cube(dbl_val)
  misc_stuff::cube(lon_val); // cube(lon_val)

  // The big question is what happens if calls to cube are made with other built-in types?

  // 1) What happens if we make a call with const arguments?
  int const ci {4};
  /*
  ci has top-level constness. Recall that top-level constness is ignored
  when copying. That is, although ci is a const int, the value in ci is an int.
  The constness of ci matters only for operations that might change ci. When we
  call cube with ci as argument, we're copying ci to the int parameter. Copying
  ci doesn't change ci. Therefore, the overload cube(int) will be the
  perfect match.
  */
  misc_stuff::cube(ci);

  /*
  2) What happens if we make a call with arguments of other numerical types
  such as bool, char, unsigned char, short, unsigned short?
  According to this link:
  https://docs.microsoft.com/en-us/cpp/cpp/standard-conversions?view=msvc-160,
  values of shorter integral types are promoted to type int if int can
  represent the full range of the original type. Otherwise, they are promoted
  to unsigned int.

  The following arguments can all fit into an int, so cube(int) will match.
  */
  misc_stuff::cube(static_cast<bool>(0));           // cube(int)
  misc_stuff::cube(static_cast<char>(63));          // cube(int)
  misc_stuff::cube(static_cast<unsigned char>(63)); // cube(int)
  misc_stuff::cube(static_cast<short>(3));          // cube(int)
  misc_stuff::cube(static_cast<unsigned short>(3)); // cube(int)

  /*
  3) What happens if we have arguments of type unsigned int or unsigned long?
  According to pages 159-160 of the text, unsigned int and unsigned long
  fall into arithmetic conversions. Since an unsigned int or unsigned long or
  unsigned long long can be converted to int or long or float or double, these
  two calls will result in ambiguous calls.
  */
  //misc_stuff::cube(static_cast<unsigned int>(3));       // ambiguous
  //misc_stuff::cube(static_cast<unsigned long>(3));      // ambiguous
  //misc_stuff::cube(static_cast<unsigned long long>(3)); // ambiguous

/*
So, the most important thing to remember is that the rules for promotions and
conversions with built-in types are too complicated so we must either provide
explicit overloads for all closely related parameters.
*/
}
