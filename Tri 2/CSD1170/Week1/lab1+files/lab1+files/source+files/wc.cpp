/******************************************************************************/
/*!
\file   wc.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS170
\par    Section A
\par    Lab #1
\date   7/01/2022
\brief  
  A script which read from a text file and
  1. Print the total char in the file (byte)
  2. Print the total line there is in the file (line)
  3. Print the total word count in the file (word)
  
*/
/******************************************************************************/


/******************************************************************************/
/*!
  \class Stack
  \brief  
    The stack class implements a Last-In-First-Out (LIFO) data
    structure for storing/retrieving integers.

    Operations include:

    - Add an item to the stack
    - Remove an item from the stack
    - Read item on top of the stack
    - Check to see if the stack is empty
    - Check to see if the stack is full
    - Output the stack to a stream
    - Return the number of items on the stack
    - Return the size of the stack
*/
/******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>

namespace {
  const size_t MAX_LINE_LEN {2048};
}

namespace hlp2 {
  void wc(int argc,char *argv[])
  {
    int line = 0;
    int byte = 0;
    int word = 0;
    
    int t_line = 0;
    int t_byte = 0;
    int t_word = 0;

    int total_File = 1;

    int i =0;

    bool whitespace = true;

    char ch[MAX_LINE_LEN];

    while (total_File < argc)
    {
          std::fstream file(argv[total_File], std::ios_base::in);

          //FILE CHECK
          if (!file.is_open())
          {
            std:: cout << "Fail to open lol" << std::endl;
            break;
          }

          //*Getline append '\n' to '\0'(Debugging for 30 min can save you 3 min of reading :))
          while(file.getline(ch,MAX_LINE_LEN-1))
          {

            i = 0;
            
            while(ch[i] != '\0')
            {

              //End of word
              if (ch[i] == ' ' || ch[i] == '\t')
              {
                whitespace = true;
                i++;
                byte++;
                continue;
              }
            
              //Start of new word
              if(whitespace)
              {
                if (ch[i] >= '!' &&ch[i] <= '~' )
                {
                  word++;
                  whitespace = false;
                  i++;
                  byte++;
                  continue;
                }
              }
              //MISC
              i++;
              byte++;
            }
            //compensate for newline char
            if(!file.eof())
            {
              line++;
              byte++;
            }
            whitespace = true;
          }
          if (total_File >2)
          {
            word++;
          }
          std::cout << 
          std::right << std::setw(7) << line 
          << std::right << std::setw(8) << word 
          << std::right <<  std::setw(8) << byte 
          << ' ' <<argv[total_File] << std::endl;

          t_line+= line;
          t_byte+= byte;
          t_word+= word;

          line = 0;
          byte = 0;
          word = 0;

          file.close();

          total_File++;
    }
    std::cout << 
    std::setw(8) << t_line 
    <<std::setw(7) << t_word 
    << std::setw(8) << t_byte 
    << ' ' << "total" << std::endl;
  }
}
