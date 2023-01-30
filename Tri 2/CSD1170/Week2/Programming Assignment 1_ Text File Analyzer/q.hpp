 /******************************************************************************/
/*!
\file   q.hpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS170
\par    Section A
\par    Assignment #1 :Programming Assignment: Text File Analyzer
\date   11/01/2022
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

#ifndef Q_HPP_
#define Q_HPP_



namespace hlp2 {
  void q(char const *input_filename, char const *analysis_file);
}

#endif
