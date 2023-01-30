// HLP2: initializer-list.cpp
// 01/24/2022
// Twenty students were asked to rate on a scale of 1 to 5 the difficulty
// of HLP2 assessments with 1 being "easy" and 5 being "hard".
// Use a std::array<> container to store the 20 int responses [read from a
// file] and print the frequency of each rating in a pretty tabular form.
// A text file survey-results.txt with 20 ratings is provided.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <array>

// anonymous namespace
namespace {
  int const SURVEY_COUNT {20};
  int const SURVEY_RANGE {5+1};

  // TODO FOR READER:
	// Replace lengthy type names with aliases specified with keyword using ...

  // read responses from survey from file ...
  std::array<int, SURVEY_COUNT> read_survey(char const *file_name);
  // compute frequencies of survey responses ...
  std::array<int, SURVEY_RANGE> frequency(std::array<int, SURVEY_COUNT> const& arr);
  // print frequencies of survey responses in pretty tabular form ...
  void print(std::array<int, SURVEY_RANGE> const&);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./program input-file-with-atleast-20-survey-results\n";
    return 0;
  }

  std::array<int, SURVEY_COUNT> survey = read_survey(argv[1]);
  std::array<int, SURVEY_RANGE> freq = frequency(survey);
  print(freq);
}

namespace {

std::array<int, SURVEY_COUNT>
read_survey(char const *file_name) {
  std::array<int, SURVEY_COUNT> arr{};
  std::ifstream ifs{file_name};
  if (!ifs) {
    return arr;
  }

  // we'll assume the input file has at least 20 values between 1 and 5
  for (int& val : arr) {
    ifs >> val;
    // make val be in range [1, 5]
    val = val < 1 ? 1 : val;
    val = val > 5 ? 5 : val;
  }

  return arr;
}

std::array<int, SURVEY_RANGE>
frequency(std::array<int, SURVEY_COUNT> const& survey) {
  std::array<int, SURVEY_RANGE> freq{};
  for (int val : survey) {
    // use response value as index to array freq and then
    // increment that element
    ++freq[val];
  }
  return freq;
}

void print(std::array<int, SURVEY_RANGE> const& freq) {
  std::cout << "Rating" << std::setw(5) << " " << "Frequency\n";
  std::cout << "--------------------\n";
  for (size_t idx {1}; idx < freq.size(); ++idx) {
    std::cout << std::setw(4) << idx << std::setw(12) << freq[idx] << '\n';
  }
}
}
