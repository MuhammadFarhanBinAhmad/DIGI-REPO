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
#include <iomanip>
#include <string>
#include <vector>
#include "pa.hpp"

namespace HLP2
{
    std::vector<CountryInfo> fill_vector_from_istream(std::istream& is)
    {
        std::vector<CountryInfo> CI;
        std::string buffer;

        while (getline(is,buffer))
        {
            CountryInfo temp{};
            
            int word_Start_Location = buffer.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()");
            int word_End_Location = buffer.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()");
            int number_Start_Location = buffer.find_first_of("1234567890");
            int number_End_Location = buffer.find_last_of("1234567890");

            std::string str_Population = buffer.substr(number_Start_Location, number_End_Location - number_Start_Location + 1);//grab all the number char inside the string
            //Erase all the ',' present in the number string
            for (size_t i = 0; i < str_Population.size(); i++)
            {
                if (str_Population[i] == ',')
                {
                    str_Population.erase(str_Population.find_first_of(","), 1);
                }
            }
            temp.name = buffer.substr(word_Start_Location, word_End_Location - word_Start_Location+1);//Get location name
            temp.pop = std::stol(str_Population);//convert number string into long int

            CI.push_back(temp);//place new CoutryInfo into vector array CI
        }
        return CI;
        
    }
    size_t max_name_length(std::vector<CountryInfo> const& CountInfo)
    {
        size_t ch_Length = 0;

        //Compare and check which Country has the longest name
        for (CountryInfo temp : CountInfo)
        {
            if (temp.name.size() > ch_Length)
            {
                ch_Length = temp.name.size();
            }
        }

        return ch_Length;

    }
    void sort(std::vector<CountryInfo>& rv, Ptr_Cmp_Func cmp)
    {
        int size = rv.size();
        //Bubble sort algorithm
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                //Initial swap depending on which function the pointer function is pointing
                if (cmp(rv[i], rv[j]))
                {
                    CountryInfo temp = rv[i];
                    rv[i] = rv[j];
                    rv[j] = temp;
                }
            }
        }
    }
    void write_to_ostream(std::vector<CountryInfo> const& v,std::ostream& os, size_t fw)
    {
        //Output to textfile
        for (CountryInfo temp : v)
        {
            os << std::setfill(' ') << std::left << std::setw(fw) << temp.name << temp.pop << std::endl;
        }
    }
    //ALL THE POINTER FUNCTION
    bool cmp_name_less(CountryInfo const& left, CountryInfo const& right)
    {
        return left.name > right.name;
    }
    bool cmp_name_greater(CountryInfo const& left, CountryInfo const& right)
    {
        return left.name < right.name;
    }
    bool cmp_pop_less(CountryInfo const& left, CountryInfo const& right)
    {
        return left.pop > right.pop;

    }
    bool cmp_pop_greater(CountryInfo const& left, CountryInfo const& right)
    {

        return left.pop < right.pop;
    }
}