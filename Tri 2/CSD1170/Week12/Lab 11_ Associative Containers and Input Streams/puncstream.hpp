/******************************************************************************/
/*!
\file   puncstream.hpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 10: Defining Semi-Realistic Input Stream
\date   25/03/2022
\brief
    whitespace - Set what is white space
    add_whitespace - add char that is define is a whitespace
    is_whitespace - check if the char is a whitespace
    case_sensitive - set stream's case-sensitivity
    is_case_sensitive - return case sensitivity
    operator>> - process word from text file and place it in string
    operator bool() - ???
    print - print out the text
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace hlp2
{
    class punc_stream
    {
        public:
        punc_stream(std::istream &is);                        // attach to input stream
        void whitespace(std::string const &s);                // make s the whitespace set
        void add_whitespace(char ch);                         // add to whitespace set
        bool is_whitespace(char ch) const;                    // is ch in whitespace set?
        void case_sensitive(bool b);                          // set stream's case-sensitivity
        bool is_case_sensitive() const;                       // return case sensitivity
        punc_stream &operator>>(std::vector<std::string> &s); // see below
        operator bool() const;
        private:
        std::istream& source; // source of characters
        std::string white; // characters considered whitespace
        bool sensitive;
        bool complete;
    };
    void print(std::map<std::string, size_t> histogram, std::string const& pre = "", std::string const& post = "\n");

}
