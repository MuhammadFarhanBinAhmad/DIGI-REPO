
 /******************************************************************************/
/*!
\file   q.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS170
\par    Section A
\par    Lab #3 :Lab: Problem Solving with std::strings
\date   21/01/2022
\brief  
  A script does the following:
  1. Convert words into pig-latin(tak halal bro)
*/
/******************************************************************************/
#include <iostream>//by right no need io but now its just standard
#include <string>
namespace hlp2
{
 std::string to_piglatin(std::string word)
{
    std::string takhalal_Word;
    int Upper = isupper(word[0]);//Check if 1st letter is cap
    std::size_t location = word.find_first_of("aeiouAEIOU");//Check for Vowel
    std::size_t yocation = word.find_first_of("Yy");//Check if 1st word start with y. If so treat y as a consonant

        //Check for y to see if yocation and location are of same value
        if (yocation!=0)
        {
            location = (location<yocation)?location:yocation;
        }
        if (location != std::string::npos)
        {
            //Convert the 1st word to lower cap if its upper cap
            if (Upper)
            {
                word[0] = std::tolower(word[0]);
            }
            //add letter before the vowel to takhalal
            for (size_t i =0; i < location ; i++)
            {
                takhalal_Word += word[i];
            }
            word = word.substr(location);//erase the same letter we copied. We want to move it to the back
            word += takhalal_Word;
            
            //If its a vowel
            if(location ==0 && yocation !=0)
            {
            word += "-yay";
            }
            else
            {
            word+= "-ay";
            }
            
        }
        //no vowel found
        else
        {
        word += "-way";
        }
    //Convert 1st word to upper cap if the word orginally had a capital letter
    if (Upper)
    {
        word[0] = std::toupper(word[0]);
    }
    return word;


}   
}