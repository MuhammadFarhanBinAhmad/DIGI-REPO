// HLP2: adaptor-iter.cpp [pghali@digipen.edu]
// This source file illustrates the applications of the three types of
// iterator adaptors: stream iterators, insert iterators, and reverse iterators.
// The stream iterator example shows how we can write a one-liner to construct
// a container with values from a file ...
// Likewise, we can write a one-liner to copy the values from a container
// to output stream [file, standard output, ...]
// The insert iterator examples show how we can write one-line code to
// copy values from source container and ***insert*** them into the destination container.
// Reverse iterators allow you to travel in the reverse direction ...
// Compile/link: g++ -std=c++17 adaptor-iter.cpp
// Run: ./a.out numbers.txt
 
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <string>
#include <fstream>
#include <iterator>

template <typename Cont>
void print(Cont const& c, std::string const& pre, std::string const& pos="\n") {
  std::cout << pre;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << pos;
}

// this copy algorithm is written to work as broadly as possible:
// it uses operators in input category - the most general category that
// specifies a range to read from ...
// also, it uses operators in output category - the most general category
// for writing values ...
template <typename InIter, typename OutIter>
OutIter copy(InIter src_beg, InIter src_end, OutIter dst_beg) {
  while (src_beg != src_end) {
    *dst_beg++ = *src_beg++;
  }
  return dst_beg;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "usage: ./a.out numbers.txt\n";
    return 0;
  }

  std::ifstream ifs{argv[1]};
  if (!ifs) {
    std::cout << "unable to open file " << argv[1] << "\n";
    return 0;
  }

  // using input stream iterators:
  // here, the input range of values to initialize the vector<int> is
  // specified by the first value in the input file stream represented
  // by ifs and the range ends when end-of-file is reached in the file
  std::vector<int> vi(std::istream_iterator<int>{ifs}, std::istream_iterator<int>{} );

  // here, we're specifying the destination range to write int values 
  // in the copy function to be the standard output
  // std::ostream_iterator<int>(std::cout, " ") creates an ostream iterator
  // for std::cout, with the string " " as the delimiter between the int values
  std::cout << "vi: ";
  ::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::deque<int> di;
  // A front inserter or front insert iterator appends a value at the end
  // of a container by calling the push_front() member function.
  // A front inserter must be initialized with its container at creation time.
  // The std::front_inserter() function provides a convenient way of doing this.
  // In addition, we're using a reverse iterator to specify the source range ...
  ::copy(vi.rbegin(), vi.rend(), std::inserter(di, std::begin(di)));
  print(di, "di: ");

  std::forward_list<int> fi;
  // A front inserter or front insert iterator appends a value at the end
  // of a container by calling the push_front() member function.
  // A front inserter must be initialized with its container at creation time.
  // The std::front_inserter() function provides a convenient way of doing this.
  // Here we use a front inserter to insert the contents of di to fi:
  // In addition, we're using a reverse iterator to specify the source range ...
  ::copy(di.rbegin(), di.rend(), std::front_inserter(fi));
  print(fi, "fi: ");

  std::list<int> li;
  // A back inserter or back insert iterator appends a value at the end
  // of a container by calling the push_back() member function.
  // A back inserter must be initialized with its container at creation time.
  // The std::back_inserter() function provides a convenient way of doing this.
  // Here we use a back insert to insert the contents of fi to li
  ::copy(fi.begin(), fi.end(), std::back_inserter(li));
  print(li, "li: ");
}
