// HLP2
// 02/06/2022
// Implementation file for a Student type that is used to introduce ADT 
// development with classes as in handout+intro+classes.pdf

#include <iostream>
#include "student.hpp"

namespace {
  void foo();
  void boo();
}

int main() {
  using namespace hlp2;
  std::cout << "sizeof(Student): " << sizeof(Student) << "\n";
  foo();
  boo();
}

namespace {
  void foo() {
  using namespace hlp2;
  std::cout << "***** Begin *****\n";
  Student john("jdoe", 20, 3, 3.10);
  Student jane("jsmith", 19, 2, 3.95);
  Student jim("jbob", 22, 4, 2.76);
    
  john.set_age(21);   // Modify john
  john.set_gpa(3.25);

  jane.set_age(24);   // Modify jane
  jane.set_gpa(4.0);

  jim.set_age(23);    // Modify jim
  jim.set_gpa(2.98);

  john.display();     // Display all
  jane.display();
  jim.display();

  // test copy constructor
  Student jim_replica {jim}, john_replica{john};
  jim_replica.set_login("jim_replica");   jim_replica.display();
  john_replica.set_login("john_replica"); john_replica.display();

  // test copy assignment
  john_replica = jim_replica;
  john_replica.display();
  std::cout << "***** End *****\n";
}

void boo() {
  using namespace hlp2;
  // Create a constant object 
  const Student john("jdoe", 20, 3, 3.10f);

  //john.set_age(25); // Error, as expected.
  //john.set_year(3); // Error, as expected.

  john.get_age();   // Error, not expected.
  john.display();   // Error, not expected.
}

} // end anonymous namespace
