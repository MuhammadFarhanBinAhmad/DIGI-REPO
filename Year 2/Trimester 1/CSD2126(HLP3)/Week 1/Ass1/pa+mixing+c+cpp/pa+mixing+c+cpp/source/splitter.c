// provide file header documentation using Doxygen tags ...

// add other headers from C standard library ...
#include "splitter.h"

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
#define FOUR_K 4096 // Don't modify this!!!

SplitResult split_join(int argc, char *argv[]) {
  SplitResult rs = E_NO_ACTION;
	
  // parse command-line arguments to determine whether to split a file
  // into smaller files	or to join smaller files into original file ...

  // ...

  return rs;
}
