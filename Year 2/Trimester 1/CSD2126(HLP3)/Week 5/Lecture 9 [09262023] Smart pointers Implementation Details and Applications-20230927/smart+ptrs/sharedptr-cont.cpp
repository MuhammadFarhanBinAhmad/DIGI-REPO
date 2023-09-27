// CSD2125 10/11
// sharedptr-cont.cpp
// Illustrates usage of std::shared_ptr<T> smart pointer in conjunction with
// std::vector as a better alternative to using std::shared_ptr<T[]> ...

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <cctype>

int main() {
  // temperature records by days
  std::vector<std::shared_ptr<std::vector<double>>> records;
  size_t day{1}; // day 1 begins

  while (true) {
    // vector created in the free store to store current day's temperatures
    std::shared_ptr<std::vector<double>> day_records{std::make_shared<std::vector<double>>()};
    records.push_back(day_records);
    
    std::cout << "Enter temperatures for day " << day++ << " "
              << "separated by by spaces. Enter 1000 to end:\n";
    while (true) {
      double t;
      std::cin >> t;
      if (t == 1000.0) break;
      day_records->push_back(t);
    }

    std::cout << "Enter another day's temperature (Y or N)? ";
    char answer{};
    std::cin >> answer;
    if (std::toupper(answer) != 'Y') break;
  }

  day = 1;
  for (std::shared_ptr<std::vector<double>> record : records) {
    double total{};
    size_t count{};

    std::cout << "Temperatures for day " << day++ << "\n";
    std::cout << std::setprecision(2) << std::fixed;
    for (double temp : *record) {
      total += temp;
      std::cout << temp << (++count % 5 == 0 ? "\n" : " ");
    }
    std::cout << "\nAverage temperature: " << total/static_cast<double>(count) << "\n";
  }
}
