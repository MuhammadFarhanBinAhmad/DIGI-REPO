// HLP2 02/2020
// A map is an associative container, i.e., values are associated with a key.
// The key can have any type with an ordering either provided by operator <
// (via the std::less<T> function) or by a function object establishing a
// strict weak ordering.
// With maps, it is straightforward to count the number of times that each
// distinct word occurs in a file.
//
// Usage: ./a.out text-file-with-words
#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "usage: ./a.out text-file-with-words\n";
    return 0;
  }

  std::ifstream ifs {argv[1]}; // ifs is input stream representing an
  if (!ifs) {                  // abstraction to read from input file
    std::cout << "unable to open file " << argv[1] << "\n";
    return 0;
  }

  // The following statement defines histogram as a map that holds values of
  // type int that are each associated with keys of type string. We often
  // speak of such a container as "a map from string to int," because we can
  // use the map by giving it a string as a key, and getting back the
  // associated int data.
  // The way we define histogram captures our intent to associate each word
  // that we need with an integer counter that records how many times we've
  // seen that word. The input loop reads the input file stream, a word at
  // a time, into s.
  std::map<std::string, int> histogram;
  std::string s;
  std::string::size_type maxlen{}; // length of the longest name
  while (ifs >> s) {
    // This is the interesting part. What happens here is that we look inside
    // histogram, using the word that we just read as the key. The result of
    // histogram[s] is the integer that is associated with the string stored
    // in s. We then use ++ to increment that integer, which indicates that
    // we've seen the word once more.
    // What happens when we encounter a word for the first time? In that case,
    // histogram will not yet contain an element with that key. When we index a
    // map with a key that has not yet been seen, the map automatically creates
    // a new element with that key. That element is value-initialized, which for
    // simple types such as int, is equivalent to setting the value to zero. Thus,
    // when we read a new word for the first time and execute ++histogram[s] with
    // that new word, we're guaranteed that the value of histogram[s] will be zero
    // before we increment it. Incrementing histogram[s] will, therefore, correctly
    // indicate that we've seen that word once so far.
    ++histogram[s];

    // for pretty printing, find maximum length of words in histogram
    maxlen = std::max(maxlen, s.size());
  }

  // Once we've read the entire input, we must write the counters and the associated
  // words. We do so in much the same way as we would write the contents of a list or
  // a vector. We iterate thro' the container using a range-for loop. Recall that an
  // associative array stores a collection of key-value pairs. Using [] to access a
  // map element conceals this fact, because we put the key iside the [] and get back
  // the associated value. So, for example, histogram[s] is an int. However, when we
  // iterate over a map, we must have a way to get at both the key and the associated
  // value. The map container lets us do so by using the companion library type pair.
  // A pair is a simple data structure that holds two elements, which are named
  // first and second. Each element in a map is really a pair, with a first member
  // that contains the key and a second member that contains the associated value.
  // When we iterate over a map using a range-for statement, we iterate over a
  // value that is of the pair type associated with the map. In the case of 
  // histogram, the type of each element is pair<const std::string, int>.
  // Note that the pair associated with a map has a key type that is const. Because
  // the pair key is const, we are prevented from changing the value of an element's
  // key. If the key were not const, we might implicitly change the element's
  // position within the map. Accordingly, the key is always const, so that if we
  // iterate over a map<std::string, int>, we get a pair<const std::string, int>.
  // With this knowledge, we can see that the output statement writes each key
  // (that is, each distinct word from the input) followed by space as filler
  // followed by the corresponding count. Here, we print 3 words in each row.
  std::cout << "Total words in histogram: " << histogram.size() << "\n";
  int rowctr {1};
  for (std::pair<const std::string, int> const& p : histogram) {
    std::cout << "<" << p.first << std::string(maxlen+1-p.first.size(), ' ')
              << ": " << p.second << ">";
    if (rowctr == 3) {
      std::cout << "\n";
      rowctr = 1;
    } else {
      std::cout << " | ";
      ++rowctr;
    }
  }
  std::cout << "\n";

  // Suppose we want to print the words in order of descending order of frequency.
  // Since there could be many words with the same frequency, we'll use a multimap.
  // The entries with the same key are stored next to each other so we can iterate
  // over them.
  // To create the multimap rev_histogram in decreasing order of word frequency,
  // we need to flip the first and second members of the pair<std::string, int>
  // to create a pair<int, std::string> which is then inserted to rev_histogram.
  std::multimap<int, std::string, std::greater<int>> rev_histogram;
  // flip key/value pair
  for(std::pair<const std::string, int> const& p : histogram) {
    std::pair<int, std::string> fp = std::make_pair(p.second, p.first);
    rev_histogram.insert(fp);
  }

  std::cout << "\nTotal elements in rev_histogram: " << rev_histogram.size() << "\n";
  std::cout << "Printing multimap in order of descending frequency:\n";
  rowctr = 1;
  for (std::pair<const int, std::string> const& p : rev_histogram) {
    std::cout << "<" << p.second << std::string(maxlen+1-p.second.size(), ' ')
              << ": " << p.first << ">";
    if (rowctr == 3) {
      std::cout << "\n";
      rowctr = 1;
    } else {
      std::cout << " | ";
      ++rowctr;
    }
  }
  std::cout << "\n";
}
