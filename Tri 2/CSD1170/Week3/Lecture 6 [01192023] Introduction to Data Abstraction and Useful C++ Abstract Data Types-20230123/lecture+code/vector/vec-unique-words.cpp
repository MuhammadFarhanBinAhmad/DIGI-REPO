// HLP2: unique-words-ver1.cpp
// 01/26/2022
// This complete program illustrates problem solving using the
// C++ standard library: std::string, std::vector, iterators, and algorithms.
// The premise of the program is this:
// Consider a text file such as wap.txt containing lots of lines of text.
// We would like to identify the unique words in the text and write this unique
// list of words [lexicographically ordered in ascending order] to an output file.
// This can be easily done using the C++ standard library: std::string, std::vector,
// and std::copy, std::sort, std::unique algorithms declared in <algorithm>
// The algorithm's outline is:
// 1) open input and output text files whose filenames are provided by the user
// 2) define an empty std::vector<std::string> container called total_words
// 2) for each line in input text file
//      use function line_splitter to determine the individual words in the line;
//      add these words to total_words.
// 3) lexicographically sort the contents of total_words in ascending order
// 4) since we want unique words, we remove adjacent words that are equivalent
//    except the first word - this was the point of sorting the vector so that
//    equivalent values become adjacent to each other. This is done by applying
//    std::unique algorithm on total_words. Now, each word in total_words is unique.
// 5) Write the unique words in total_words to the output file stream.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// Function that returns the "words" obtained by splitting a line of text ...
// The function will define two indices i and j, that will delimit each "word" in turn.
// The idea is that we'll locate a "word" by computing values for i and j such
// that the "word" will be the characters in the range [i, j).
// Once we've these indices, we'll use the characters that they delimit to create
// a new std::string, which we'll copy into the vector words.
std::vector<std::string> line_splitter(std::string const& line) {
  // there are six possible whitespace characters in ASCII that delimit a "word"
  static std::string const whitespace{" \t\n\v\r\f"};
  std::vector<std::string> words;
  std::string::size_type i{0};
  while (i < line.size()) {
    // ignore leading whitespace characters ...
    i = line.find_first_not_of(whitespace, i);
    // find end of next word ...
    std::string::size_type j = line.find_first_of(whitespace, i);
    // if we found some non-whitespace characters, we've a new "word"
    if (i != j) {
      words.push_back(line.substr(i, j-i));
      i = j;
    }
  }
  return words;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: ./a.out input-file-name copy-file-name\n";
    return 0;
  }
  
  // associate file streams with input and output file names ...
  std::ifstream ifs {argv[1]};
  if (!ifs) {
    std::cout << "Unable to open input file " << argv[1] << "\n";
    return 0;
  }
  std::ofstream ofs {argv[2]};
  if (!ofs) {
    std::cout << "Unable to open output file " << argv[2] << "\n";
    return 0;
  }

  std::vector<std::string> total_words;
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> words_in_line = line_splitter(line);
    // Add each value in vector words_in_line to end of total_words ...
#if 1
    for (std::string const& x : words_in_line) {
      total_words.push_back(x);
    }
#else
    // The std::copy algorithm can be used to replace the above loop. However,
    // there's a complication: the std::copy algorithm expects the destination
    // vector total_words to have enough room for the new string values to be
    // added. But, total_words may not have enough memory to accommodate these
    // new words. The standard library provides a std::back_inserter iterator
    // adaptor that ensures that each string value is "inserted" [with memory
    // allocations if necessary]. 
    std::copy(std::begin(words_in_line), std::end(words_in_line), std::back_inserter(total_words));
#endif
  }
  ifs.close();

  // by default, sort uses the overloaded operator< to compare string values
  // in the range - the net result is that string elements in total_words are
  // lexicographically sorted in ascending order ... 
  std::sort(std::begin(total_words), std::end(total_words));
  std::cout << "size of original list of words: " << total_words.size() << "\n";

  // Now, we want only the unique strings in total_words ...
  // This is easy to accomplish using the std::unique algorithm. As the name implies,
  // std::unique removes all repeated values except the first from the container.
  // However, std::unique doesn't actually shrink the size of the container. Instead,
  // it returns an iterator to one past the last element not removed.
  // We then use this iterator to shrink the vector by removing the elements using
  // member function erase().
  std::vector<std::string>::iterator unique_it = std::unique(std::begin(total_words), std::end(total_words));
  total_words.erase(unique_it, std::end(total_words));
  // the C++ idiom is to replace the previous two statements with the following statement:
  //total_words.erase(std::unique(std::begin(total_words), std::end(total_words)), std::end(total_words));
  std::cout << "size of unique list of words: " << total_words.size() << "\n";

  // we now iterate thro' each unique "word" in total_words and write the word to stdout
#if 0
  for (std::string const& x : total_words) {
    ofs << x << "\n"; // we want each "word" on a new line
  }
#else
  // The above "copy" loop can be replaced with std::copy algorithm that uses
  // an output stream iterator to write to the file stream:
  std::copy(std::begin(total_words), std::end(total_words), std::ostream_iterator<std::string>(ofs, "\n"));
#endif
  
  ofs.flush(); // request all characters in buffer to be written to file
  ofs.close();
}
