// File header documentation is required!!!

// This file must contain definitions of ALL member functions of class hlp2::punc_stream.

// Don't forget to add the definition of function hlp2::print that was declared in puncstream.hpp!!!
#include "puncstream.hpp"

namespace hlp2
{
    punc_stream::punc_stream(std::istream &is)
    : source{is},sensitive{false}
    {
        
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
        while (s)
        {
            /* code */
        }
        
    }
    punc_stream::operator bool() const
    {
        return complete;
    }

    void print(std::map<std::string,size_t> histogram, std::string const& pre="", std::string const& post="\n")
    {
        // write each word and its associated count to standard output
        for (std::pair<const std::string,size_t> const& p : histogram) {
        std::cout << "<" << p.first << ">: " << p.second << "\n";
        }

    }
}
