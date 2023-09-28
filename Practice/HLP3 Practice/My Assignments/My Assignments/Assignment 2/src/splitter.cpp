#include "splitter.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

namespace CSD2125
{
    SplitResult split_join(int argc, char *argv[])
    {
        size_t i = 1;

        if ((std::string)argv[i] == "-s")
        {
            i++; //i = 2
            std::stringstream strstream (argv[i]);
            int chunkSize = 0;
            strstream >> chunkSize;
            //If the size provided is too big, limit it by setting max size defined in header
            i++; //i = 3
            if(chunkSize > MAX_SPLIT_SIZE)
            {
                chunkSize = MAX_SPLIT_SIZE;
            }
            //if the size provide is too small, eg 0 or negative values
            else if (chunkSize <= 0)
            {
                return SplitResult::E_SMALL_SIZE;
            }
            if((std::string)argv[i] != "-o")
            {
                std::cout << "o" << std::endl;
                return SplitResult::E_NO_ACTION;
            }
            i++; //i = 4

            std::string output = argv[i];
            i++; //i = 5

            if((std::string)argv[i] != "-i")
            {
                std::cout << "i" << std::endl;
                return SplitResult::E_NO_ACTION;
            }
            i++; // i = 6

            std::string input = argv[i];
            std::ifstream file(input);
            std::stringstream inBuffer;
            std::fstream infileHandle;
            std::string tmpstr;

            infileHandle.open(input, std::ios::in);
            //Checks if input directory is valid
            if (!infileHandle)
            { 
                return SplitResult::E_BAD_SOURCE;
            }

            inBuffer << infileHandle.rdbuf();
            tmpstr = inBuffer.str();
            i++; //i = 7

            //Loop thru file to split the file
            std::string tempStr;

            //Checks if input directory is valid
            if (!file)
            { 
                return SplitResult::E_BAD_SOURCE;
            }

            int numbering = 1;
            for(size_t count = 0; count < tmpstr.size(); count+=chunkSize)
            {
                //create new file
                std::stringstream tempstream;
                tempstream << output << std::setfill('0') << std::setw(4) << numbering++;
                std::string actualOutput = tempstream.str();
                std::ofstream newFile(actualOutput);
                //Checks output directory is valid
                if (!newFile)
                { 
                    return SplitResult::E_BAD_SOURCE;
                }
                //cut up input/tempstr
                std::string tmpSubStr = tmpstr.substr(count, chunkSize);
                //store cut up piece into a new file into newly created file
                newFile << tmpSubStr;
                newFile.close();
            }

            file.close();
            return SplitResult::E_SPLIT_SUCCESS;
        }

        //Detects if it is calling for joining
        else if((std::string)argv[i] == "-j")
        {
            i++; // i = 2
            if((std::string)argv[i] != "-o")
            {
                std::cout << "o" << std::endl;
                return SplitResult::E_NO_ACTION;
            }
            i++; // i = 3
            std::string output = argv[i];
            i++; // i = 4
            if((std::string)argv[i] != "-i")
            {
                std::cout << "i" << std::endl;
                return SplitResult::E_NO_ACTION;
            }
            i++; // i = 5
            
            std::ofstream newFile(output);
            for (;(int)i < argc; i++)
            {
                std::string tempInputStr = argv[i];
                std::string tempStr;
                std::ifstream file(tempInputStr);
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
}

