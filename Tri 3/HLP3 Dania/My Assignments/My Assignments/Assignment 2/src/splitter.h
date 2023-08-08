#ifndef SPLITTER_HPP
#define SPLITTER_HPP

namespace CSD2125 {

// don't change this macro/constant because if you allocate
// more memory than this, the online grader crash your submission
// since it has been set up with some pre-defined limits
// that will prevent your program from accessing more than this
// limit. Just don't do it!!!
// Until C++17, it was not possible to define a single instance of
// objects such as MAX_SPLIT_SIZE for the entire program. Now, it is
// possible to do that using the inline specifier. 
inline constexpr int MAX_SPLIT_SIZE{4096};

enum class SplitResult {
  E_BAD_SOURCE,
  E_BAD_DESTINATION,
  E_NO_MEMORY,
  E_SMALL_SIZE,
  E_NO_ACTION,
  E_SPLIT_SUCCESS,
  E_JOIN_SUCCESS
};

SplitResult split_join(int argc, char *argv[]);

}

#endif 
