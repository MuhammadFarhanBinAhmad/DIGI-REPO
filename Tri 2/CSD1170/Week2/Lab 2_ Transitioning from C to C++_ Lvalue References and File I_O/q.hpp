#ifndef Q_HPP
#define Q_HPP
 /******************************************************************************/
/*!
\file   q.hpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS170
\par    Section A
\par    Lab #2 :Transitioning From C to C++ [Part 2]
\date   14/01/2022
\brief  
  A script does the following:
  1. Count the total amount of char in the input file
  2. Count the total letter,whitespace,digits and special characters in the file
  3. Count the total number of uppercase & lowercase letter ans also count how many time does a letter come up
  4. Give the percentage of how character appear in the file
  6. Give the percentage of how much each category appear in the file
  5. Count the total number of number there is in the text file, add them up together and give the average value
  
*/
/******************************************************************************/
#include <string> // don't remove

namespace hlp2 {
  
  struct Tsunami {
    int day =0;
    int month = 0;
    int year;

    int total_Death;
    double height;
    char location[100];
  };
  
  // declaration of interface functions ...
Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt);
void print_tsunami_data(Tsunami const *arr,int size, std::string const& file_name);
  
} // end namespace hlp2
#endif
