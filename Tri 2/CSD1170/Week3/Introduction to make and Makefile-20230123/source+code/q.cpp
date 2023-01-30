#include "q.h"

namespace hlp2 {

bool check_distinct(std::vector<int> cont) {
  std::vector<int>::iterator first {cont.begin()}, last{cont.end()};
  while (first != last) {
    std::vector<int>::iterator first2 {first+1};
    while (first2 != last) {
      if (*first2 == *first) {
        return false; // found two elements with same value
      }
      ++first2;
    }
    ++first;
  }
  return true;
}

} // end namespace hlp2
