// provide file header documentation using Doxygen tags ...

// add other necessary headers from C++ standard library ...
// Note: you cannot use C standard library I/O ...
#include "splitter.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
constexpr int FOUR_K {4096}; // Don't modify this!!!

SplitResult split_join(int argc, char *argv[]) 
{
  //USE THIS TO REFERENCE AND COUNT THE OFFSET
  // ./sj.out -j -o ./joined-data/collected -i ./split-data/chunk*
  //Need to check if letter command and do respective command and action

  size_t offset = 1;//offset console command

  //START OF SPLITTING
  //Check if its splitting
  if ((std::string)argv[offset] == "-s")
  {
    //REMINDER - Keep track of offset please. Later forgot = Hide and seek :)
    offset++;//2
    std::stringstream strstream(argv[offset]);
    
    int chuncksize = 0;
    strstream >> chuncksize;//get size
    
    //CHECK SIZE
    //Too big
    if (chuncksize > FOUR_K)
    {
      chuncksize = FOUR_K;
    }
    //Too small
    else if (chuncksize <=0)
    {
      return SplitResult::E_SMALL_SIZE;
    }

    offset++;//3

    if ((std::string)argv[offset] == "-o")
    {
        return SplitResult::E_NO_ACTION;
    }
    //END OF SPLITTING
    offset++;//4

    std::string output = argv[offset];

    offset++;//5

    if ((std::string)argv[offset] != "-i")
    {
      return SplitResult::E_NO_ACTION;
    }

    offset++;//6

    std::string input = argv[offset];
    std::string temp_str;

    std::ifstream file(input);
    std::stringstream in_Buffer;
    std::fstream in_FileHandler;

    in_FileHandler.open(input,std::ios::in);

    //Check file
    if (!in_FileHandler)
    {
      return SplitResult::E_BAD_SOURCE;
    }

    in_Buffer << in_FileHandler.rdbuf();
    temp_str = in_Buffer.str();

    offset++;
    //
    if (!file)



  }
  //Now check if its joining
  else if((std::string)argv[offset] == "-j")
  {
    offset++;
    if ((std::string)argv[offset] == "-o")
    {

    }
    else if ((std::string)argv[offset] == "-i")
    {

    }
  }
  /*
  need check for each command
  -s = split file into chuck
  -o = path-to-chunk-file-name
  
  */

  // parse command-line arguments to determine whether to split a file
  // into smaller files	or to join smaller files into original file ...

  // ...

  return rs;
}
