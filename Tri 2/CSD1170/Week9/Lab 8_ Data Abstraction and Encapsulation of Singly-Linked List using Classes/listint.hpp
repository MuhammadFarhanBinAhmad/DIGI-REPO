// File header documentation is required!!!

// Provide include guards
// Don't include either of the following two headers: <forward_list> and <list>
// You may need to include <cstddef> for size_t [which is the largest unsigned type from the C standard library]

// All names from here on must be in namespace hlp2.
// Don't add any names that are private to the implementation source file listint.cpp in this file.
// Necessary declarations are described in the spec.

// Ensure every member function declared in class ListInt has a header!!!

// Declare this as a friend function in class ListInt:
std::ostream& operator<<(std::ostream& os, const ListInt& rhs);