/******************************************************************************/
/*!
\file   pa.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Assignment 3: Problem Solving with vectors and strings
\date   25/01/2022
\brief
  A script does the following:
  1. fill_vector_from_istream - Read from a text and grabbing the name and population of country into CountryInfo struct name and population variable
  2. max_name_length - Get the length of the country with the longest char count
  3. sort - swap the CountryInfo element depeding on the condition stated by the 4 bool function (cmp_name_less,cmp_name_greater,cmp_pop_less,cmp_pop_greater)
  4. write_to_ostream - Out put data, after all the data have been correctly sorted, into a text file
  5. cmp_name_less - Compare the CountryInfo element to see which name alphabetically comes first(a-z)
  6. cmp_name_greater - Compare the CountryInfo element to see which name alphabetically comes first(z-a)
  7. cmp_pop_less - Compare the CountryInfo element to see which population is smaller
  8. cmp_pop_greater - Compare the CountryInfo element to see which population is bigger
*/
/******************************************************************************/
#include <iostream>
#include <string>
#include <vector>

namespace HLP2
{
    struct CountryInfo 
    {
        std::string name; // country's name - *exactly* as in input file
        long int pop; // country's population
    };

    using Ptr_Cmp_Func = bool (*)(CountryInfo const&, CountryInfo const&);
    typedef bool (*Ptr_Cmp_Func)(CountryInfo const&, CountryInfo const&);

    std::vector<CountryInfo> fill_vector_from_istream(std::istream& is);
    size_t max_name_length(std::vector<CountryInfo> const&);
    void sort(std::vector<CountryInfo>& rv, Ptr_Cmp_Func cmp);
    void write_to_ostream(std::vector<CountryInfo> const& v,std::ostream& os, size_t fw);
    bool cmp_name_less(CountryInfo const& left, CountryInfo const& right);
    bool cmp_name_greater(CountryInfo const& left, CountryInfo const& right);
    bool cmp_pop_less(CountryInfo const& left, CountryInfo const& right);
    bool cmp_pop_greater(CountryInfo const& left, CountryInfo const& right);
}