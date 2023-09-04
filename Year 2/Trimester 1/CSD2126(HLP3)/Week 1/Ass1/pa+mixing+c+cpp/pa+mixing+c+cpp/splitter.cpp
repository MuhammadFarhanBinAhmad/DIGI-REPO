/*****************************************************************//**
 * \file	spliter.cpp
 * \brief	Split up binary file to smaller binary or join multiple binary file to one binary file
 *        depending on your console command prompt
 *
 * \author	FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
 * \date	02-SEP-2023
***********************************************************************/
#include "splitter.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>


constexpr int FOUR_K {4096}; // Don't modify this!!!
	/*!***********************************************************************
	* \brief SplitResult split_join(int argc, char *argv[])
	* Use to set data of a new/editted password and website
	* \param argc
	* argument count
	* \param argv
	* argument prompt
	* \return
	* An enum commond that tells the outcome of the attempt splitting/merging
	*************************************************************************/
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

    offset++;//3

    if (chuncksize > FOUR_K)
    {
      chuncksize = FOUR_K;
    }
    //Too small
    else if (chuncksize <=0)
    {
      return SplitResult::E_SMALL_SIZE;
    }

    if ((std::string)argv[offset] != "-o")
    {
      std::cout << "-o\n";
      return SplitResult::E_NO_ACTION;
    }
    //END OF SPLITTING
    offset++;//4

    std::string output = argv[offset];

    offset++;//5

    if ((std::string)argv[offset] != "-i")
    {
      std::cout << "-i\n";
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

    offset++;//7

    if (!file)
    {
      return SplitResult::E_BAD_SOURCE;
    }

    int numbering = 1;

    for (size_t count = 0; count < temp_str.size();count += chuncksize)
    {
      //creating a new file
      std::stringstream temp_strstream;
      temp_strstream << output << std::setfill('0') << std::setw(4) << numbering++;
      std::string actualOutput = temp_strstream.str();
      std::ofstream newFile(actualOutput);

      //Check file valid
      if (!newFile)
      {
        return SplitResult::E_BAD_SOURCE;
      }

      std::string temp_SubStr = temp_str.substr(count,chuncksize);

      newFile<<temp_SubStr;
      newFile.close();
    }

    file.close();
    return SplitResult::E_SPLIT_SUCCESS;

  }
  //Now check if its joining
  else if((std::string)argv[offset] == "-j")
  {
    offset++;//2
    if ((std::string)argv[offset] != "-o")
    {
      std::cout << "-o\n";
      return SplitResult::E_NO_ACTION;
    }
    offset++;//3
    std::string out_file = argv[offset];
    offset++;//4
    if ((std::string)argv[offset] != "-i")
    {
      std::cout << "i\n";
      return SplitResult::E_NO_ACTION;
    }
    offset++;//5

    std::ofstream newFile(out_file);

    for (;static_cast<int>(offset) < argc ; offset++)
    {
      std::string tempInputStr = argv[offset];
      std::string tempStr;
      std::stringstream inBuffer;
      std::fstream infileHandle;

      infileHandle.open(tempInputStr, std::ios::in);
      //Checks if input directory is valid
      if (!infileHandle)
      { 
          return SplitResult::E_BAD_SOURCE;
      }

      inBuffer << infileHandle.rdbuf();
      tempStr = inBuffer.str();
      newFile << tempStr;
      infileHandle.close();
    }
    newFile.close();

    return SplitResult::E_JOIN_SUCCESS;
  }

  return SplitResult::E_NO_ACTION;
}
