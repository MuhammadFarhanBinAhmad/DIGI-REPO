/******************************************************************************/
/*!
\file   xref.hpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 11: Generating a Cross-Reference Table
\date   31/03/2022
\brief
    xref - cross refer words and 
    print_wordmap - Print value from map
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <iterator>
#include "puncstream.hpp"


namespace hlp2
{
    using Key = std::string;
    using Pair = std::pair<int, int>;
    using Value = std::vector<Pair>;

    std::pair<std::map<std::string, std::vector<std::pair<int, int>>>, int>
    xref(std::string const &filename,
         std::string const &whitespace,
         bool case_sensitivity,
         std::set<std::string> const &exclude);
    void print_wordmap(std::map<std::string, 
    std::vector<std::pair<int, int>>> const &words);
}
std::set<std::string> exclude_words();
