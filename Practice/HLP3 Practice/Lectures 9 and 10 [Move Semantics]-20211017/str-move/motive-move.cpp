#include <iostream>
#include <vector>
#include <string>
#include "str.h"
// CSD2125
// 10/07: RVO and move semantics

// First, let's begin by seeing how RVO helps. Compile without RVO and without move semantics for Str:
// g++ -std=c++17 -fno-elide-constructors str.cpp motive-move.cpp -o str17-noelide-nomove.out
// Note: the no-elide flag doesn't affect std::vector<>!!!
// Run and see count of Str ctors invoked: ./str17-noelide-nomove.out
// This should print a count of 5 Str ctors being invoked. Can you figure out why there
// are 5 Str ctors being invoked?

// With RVO and without Str move semantics:
// g++ -std=c++17 str.cpp motive-move.cpp -o str17-elide-nomove.out
// Run and see count of Str ctors invoked: ./str17-noelide-nomove.out
// This should print a count of 4 Str ctors being invoked. Can you figure out why there
// are 4 Str ctors being invoked? 

// Now, let's see whether move semantics for Str class can help when there is no RVO.
// Compile without RVO and with move semantics for Str:
// g++ -std=c++17 str.cpp motive-move.cpp -fno-elide-constructors -D=STR_MOVE -o str17-noelide-move.out
// Run and see count of Str ctors invoked: ./str17-noelide-move.out
// There are 3 Str copy ctors and 2 Str move ctors being invoked. Can you figure out where
// Str copy ctors are being replaced with move ctors?

// Now, compile with both RVO and move semantics on:
// g++ -std=c++17 -D=STR_MOVE str.cpp motive-move.cpp -o str17-elide-move.out
// Run and see count of Str ctors invoked: ./str17-elide-move.out
// You should see RVO and move semantics in action with the count of Str ctors reduced to 3 and
// only 1 (rather than 2) Str move ctors being invoked. Can you figure out where the Str move ctor
// is being replaced with "elision".

std::vector<Str> f() {
  std::vector<Str> w;
  w.reserve(3);

  Str s{"data"}; // always one Str ctor: Str(char const*)

  w.push_back(s); // always one Str copy ctor: Str(Str const&)
  
  /*
  There are four cases to consider.

  Without both RVO and move semantics: s+s requires two Str copy ctors and push_back(s+s)
  will require one more copy ctor for a total of 3 Str copy ctors being invoked.
  
  With RVO and without move semantics: s+s requires one Str copy ctor; the temporary from 
  op+(Str const&, Str const&) is "elided" as return value of the op+ function; and
  push_back(s+s) will require one more copy ctor for a total of 2 Str copy ctors being invoked.
  
  Without RVO but with Str move semantics: s+s requires one Str copy ctor; the temporary from
  op+(Str const&, Str const&) is "moved" as return value; and push_back(s+s) will perform
  one more "move" to construct the vector<Str> element with the stolen resources of the temporary
  returned by op+. All of this means that there is one Str copy ctor invoked and two Str moves.

  With RVO and move semantics: s+s requires one Str copy ctor; the temporary from
  op+(Str const&, Str const&) is "elided" as return value; and push_back(s+s) will perform
  one "move" to construct the vector<Str> element with the stolen resources of the temporary
  returned by op+. All of this means that there is one Str copy ctor invoked and one Str move.
  */
  w.push_back(s+s);

  /*
  RVO doesn't come into play in the following push_back operation. It just about whether
  there is a copy ctor or move ctor used to initialize the vector<Str> element.
  If there are no move semantics, there will be a copy ctor invoked for an object s that
  will soon go out of scope. Even though the std::move() changes the type of expression s to Str&&,
  the compiler will still call the copy ctor since Str doesn't define a move ctor.
  On the other hand, if Str defines a move ctor, then push_back will 
  w.push_back(std::move(s));

  There's more ...
  When the following return statement is executed, is the std::vector<Str> object w "elided" or
  "moved"?
  It depends on whether the returned object is initializing or assigning the right hand side object.
  For initializing, "elision" would take place. For assignment, the vector's move assignment operator
  would be used.
  In either case, no futher Str copies will be made.
  */
  return w;
}

int main() {
  std::vector<Str> v;
  // useless stuff ...
  std::cout << "v.size(): " << v.size() << "\n";
  // now assign a temporary returned by f() to previously defined vector<Str> object v ...  
  v = f();
  // use v
  for (Str const& s : v) {
    std::cout << s << "\n";
  }
  // print how many copies and how many moves ...
  std::cout << "Str::CopyCount(): " << Str::CopyCount()
#ifdef STR_MOVE
  << " | Str::MoveCount(): " << Str::MoveCount()
#endif
  << "\n";
}
