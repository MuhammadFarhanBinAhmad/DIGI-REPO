/******************************************************************************/
/*!
\file   puncstream.cpp
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
#include "puncstream.hpp"

namespace hlp2
{
    punc_stream::punc_stream(std::istream &is)
        : source{is}
    {
        sensitive = false;
        complete = false;
    }
    void punc_stream::whitespace(std::string const &s)
    {
        white = s;
    }
    void punc_stream::add_whitespace(char ch)
    {
        white += ch;
    }
    bool punc_stream::is_whitespace(char ch) const
    {
        size_t found = white.find(ch);

        if (found != std::string::npos)
        {
            return true;
        }
        return false;
    }
    void punc_stream::case_sensitive(bool b)
    {
        sensitive = b;
    }
    bool punc_stream::is_case_sensitive() const
    {
        return sensitive;
    }
    punc_stream &punc_stream::operator>>(std::vector<std::string> &s)
    {
        s.clear();
        std::string line;
        std::getline(source, line);
        for (size_t i = 0; i < line.size(); i++)
        {
            if (!sensitive && line[i] >= 'A' && line[i] <= 'Z')
            {
                line[i] += 32;
            }
            else if (is_whitespace(line[i]))
            {
                line[i] = ' ';
            }
        }

        std::istringstream iss{line};
        std::string word;

        while (iss >> word)
        {
            s.push_back(word);
        }

        return *this;
    }
    punc_stream::operator bool() const
    {
        if (source)
        {
            return true;
        }
        return false;
    }

    void print(std::map<std::string, size_t> histogram, std::string const &pre, std::string const &post)
    {
        std::cout << pre;
        for (std::pair<const std::string, size_t> const &p : histogram)
        {
            std::cout << "<" << p.first << ">: " << p.second << '\n';
        }
        std::cout << post;
    }
}
