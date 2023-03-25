// See specs for complete description of what you need to implement in this file.

// Don't forget documentation: a file header is required; every function and type that you
// define must have appropriate documentation

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

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
    void print(std::vector<std::string> str, std::string const& pre="", std::string const& post="\n");

}
