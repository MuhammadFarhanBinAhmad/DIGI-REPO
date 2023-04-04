/******************************************************************************/
/*!
\file   xref.cpp
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
#include "xref.hpp"

namespace hlp2
{

    std::pair<std::map<std::string, std::vector<std::pair<int, int>>>, int>
    xref(std::string const &filename,
         std::string const &whitespace,
         bool case_sensitivity,
         std::set<std::string> const &exclude)
    {

        // define a map from string to vector<pair<int,int>>
        std::pair<std::map<std::string, std::vector<std::pair<int, int>>>, int> ret{};
        std::string line{};

        // open file stream
        std::ifstream myfile(filename);
        // use hlp2::punc_stream to purge whitespace from each line of input
        // and split the line into words
        hlp2::punc_stream ps{myfile};
        ps.whitespace(whitespace);
        ps.case_sensitive(case_sensitivity);
        // remember current line in file
        // go through each of word in vector returned by punc_stream
        // remember current position in line

        using VPII = std::vector<std::pair<int,int>>;
        std::map<std::string,VPII> sm{}; // xref table
        int line_num{0}, word_pos{1}; // word occurs at line 1 and at position 1
        bool excluded = false;
        
        //Grab line
        for (std::vector<std::string> words; ps >> words;)
        {
            ++line_num;
            //Check word.If word is part of excluded, break loop
            for (std::string const &word : words)
            {
                for(std::string exclude_word: exclude)
                {
                    if (word == exclude_word)
                    {
                        excluded = true;
                        break;
                    }
                }
                if (excluded)
                {
                    excluded = false;
                    continue;
                }
                //add word in vector
                sm[word].push_back(std::make_pair(line_num, word_pos));
                word_pos++;
            }
            word_pos= 1;
        }
        //place all collected data into new pair ro return
        std::pair<std::map<std::string, std::vector<std::pair<int, int>>>, int> result{};
        result.first = sm;
        result.second = line_num;

        myfile.close();
        // if word is not in exclude
        // use word to index map and use vector's push_back member
        // to append pair representing current line number and
        // current position within the line to the vector
        // line_num represents number of lines in file ...
        return result;
    }
    void print_wordmap(std::map<std::string, std::vector<std::pair<int, int>>> const &words)
    {
    //Note to self. Dont use auto next time. I allow it once cause last lab
    for (auto const& [word, line_word_pairs] : words) 
    {
        if (line_word_pairs.size() == 1)
        {
        std::cout << "\"" << word << "\" occurs " << line_word_pairs.size() << " time and is located at: \n";
        }
        else
        {
            std::cout << "\"" << word << "\" occurs " << line_word_pairs.size() << " times and is located at: \n";

        }
        for (auto const& [line, word_pos] : line_word_pairs) 
        {
            std::cout << "\tline: " << line << ", position: " << word_pos << "\n";
        }
    }

    }
}
