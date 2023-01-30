// This file can only have these 5 files included and therefore you should not
// remove the following include directives nor provide additional include directives!!!

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "q.hpp" // compiler needs definition of type Tsunami

// anonymous namespace for any helper functions that you wish to implement
namespace MyFunction{

    //CLEAR ARRAY AND SPECIAL VARIABLES
  void ResetVar(char *ch, int &current_Char_Pos)
  {
    for (int i = 0 ; i  < 100; i++)
    {
      ch[i] = '\0';
    }
    current_Char_Pos = 0;
  }
  void ConvertType(char ch[],int& current_Cat,hlp2::Tsunami& tsu)
  {
    //INT
    if (current_Cat <= 3)
    {
      int temp = 0;
      temp = std::atoi(ch);
      switch (current_Cat)
      {
        case 0:
        {
          tsu.day = temp;
          break;
        }
        case 1:
        {
          tsu.month = temp;
          break;
        }
        case 2:
        {
          tsu.year = temp;
          break;
        }
        case 3:
        {
          tsu.total_Death = temp;
          break;
        }
      }
    }
    //FLOAT
    if (current_Cat == 4)
    {
      double temp = 0;
      temp = std::atof(ch);
      tsu.height = temp;
    }
    //CHAR
    if (current_Cat == 5)
    {
      int i = 0;
      int j = 0;
      //Offset white space
      if (ch[0] == ' ')
      {
        i++;
      }
      while(ch[i] != '\0')
      {
        //Stop when remaining char is all white spaces
        //Replaces it with '\0'
        if(ch[i] == ' ' && ch[i+1] == ' ')
        {
          //Stop copying from buffer
          tsu.location[j] = '\0';

          break;
        }
        else
        {
          tsu.location[j] = ch[i];
          j++;
          i++;
        }
      }

    }
    in_file >> arr[i].day >> month
    current_Cat++;
  }
  double CalculateAverage(hlp2::Tsunami const *tsu,const int size)
  {
    double average = 0;
    for (int i = 0; i < size ; i++)
    {
      average += tsu[i].height;
    }
    return average/(double)size;
  }
  double FindHighestHeight(hlp2::Tsunami const *tsu,const int size)
  {
    double h_Height =0;
    for (int i = 0; i < size ; i++)
    {
      if (tsu[i].height > h_Height)
      {
        h_Height = tsu[i].height;
      }
    }
    return h_Height;
  }
}

namespace hlp2 
{
  Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt)
  {
    int totaltsunami = 0;
    char ch;

      //READ FILE
      std::ifstream readfile(file_name,std::ios_base::in);
      //Standard check
      if (!readfile)
      {
        std::cout << "Fail to open file" << std::endl;
      }
      while (readfile.get(ch))
      {
        if (ch == '\n')
        {
          totaltsunami++;
        }
      }
      readfile.clear();//clear fail and eof bits
      readfile.seekg(0);//reset to start of file

      max_cnt = totaltsunami;
      Tsunami* const tsu = new Tsunami[totaltsunami]{}; //RMB TO DELETE

      int current_Tsunami = 0;
      int current_Cat =0;
      bool white_Space = false;
      char charbuffer[100];
      int current_Char_Pos =0;

      //Cat 0 = Date
      //Cat 1 = Month(Not the lighting alert type)
      //Cat 2 = Year
      //Cat 3 = Death
      //Cat 4 = Height
      //Cat 5 = Location

      while(readfile.get(ch))
      {
        //ONLY CHECK FOR THE FIRST FOR CATEGORY
        if (current_Cat <= 4)
        {
          //Switch depending if ch is a white space. Use to indicate start/end of word
          switch (white_Space)
          {
          case false:
            if(ch == ' ')
            {
              white_Space = true;
              if (current_Char_Pos >0)
              {
                charbuffer[current_Char_Pos] = '\0';
                MyFunction::ConvertType(charbuffer,current_Cat,tsu[current_Tsunami]);
                MyFunction::ResetVar(charbuffer,current_Char_Pos);
              }
            }
            else
            {
              charbuffer[current_Char_Pos] = ch;
              current_Char_Pos++;
            }
            break;
          case true:
              //START OF NEW WORD
            if ((ch >= 'A' && ch <= 'Z')||(ch >= 'a' && ch <= 'z')||(ch >= '0' && ch <= '9') || ch == ',' || ch == '.')
            {
              charbuffer[current_Char_Pos] = ch;
              current_Char_Pos++;
              white_Space = false;
            }
            break;
          }
        }
        //FOR LOCATION
        //Location, unlike the other, may contain space inbetween that is needed. Thus need use peek to ensure that space is between 2 words
        else
        {
          if (ch == ' ')
          {
            //Check if space is between 2 words
            if(readfile.peek() >= 'A' && readfile.peek() <= 'Z')
            {
              charbuffer[current_Char_Pos] = ch;
              current_Char_Pos++;
              continue;
            }
          }
          if ((ch >= 'A' && ch <= 'Z')||(ch >= 'a' && ch <= 'z')||(ch >= '0' && ch <= '9')|| ch == ','||ch == '.' )
          {
            charbuffer[current_Char_Pos] = ch;
            current_Char_Pos++;
            continue;
          }
        }
        //END OF LINE
        if (ch == '\n')
        {
           //Need reset values and add '\0' to ensure no reading of garbage value
          charbuffer[current_Char_Pos] = '\0';
          MyFunction::ConvertType(charbuffer,current_Cat,tsu[current_Tsunami]);
          MyFunction::ResetVar(charbuffer,current_Char_Pos);
          current_Tsunami++;
          current_Cat = 0;
        }
      }
      readfile.close();
      return tsu;
  }

  void print_tsunami_data(Tsunami const *arr,int size, std::string const& file_name)
  {
      std::ofstream outfile(file_name);

      double height_Average = MyFunction::CalculateAverage(arr,size);
      double height_Highest = MyFunction::FindHighestHeight(arr,size);

      if (!outfile.is_open())
      {
        std::cout << "Fail to create" <<std::endl;
      }
      outfile << std::setprecision(2) << std::fixed;
      outfile << "List of tsunamis:"<< std::endl;
      outfile << "-----------------"<< std::endl;
      for (int i = 0 ; i < size;i++)
      {
        if (arr[i].day >=10)
        {
          outfile << arr[i].day << ' ';
        }
        else
        {
          outfile << '0' << arr[i].day << ' ';
        }
        if (arr[i].month >=10)
        {
          outfile << arr[i].month << ' ';
        }
        else
        {
          outfile << '0' << arr[i].month << ' ';
        }
        outfile << arr[i].year<< std::setw(7) << std::right << arr[i].total_Death << std::setw(11) << std::right<< arr[i].height<< "     " << std::left << arr[i].location  << std::endl;
      }

      outfile << std::endl;
      outfile << "Summary information for tsunamis"<< std::endl;
      outfile << "--------------------------------"<< std::endl<< std::endl;

      outfile << "Maximum wave height (in meters): " <<  height_Highest << std::endl<< std::endl;

      outfile << "Average wave height (in meters):" << ' ' << std::setw(5) << std::right<< height_Average<< std::endl<< std::endl;

      outfile << "Tsunamis with greater than average height " << height_Average << ':' << std::endl;
      for (int i = 0 ; i < size;i++)
      {
        if (arr[i].height >= height_Average)
        {
          outfile << arr[i].height << "     " << std::left << arr[i].location << std::endl;
        }
      }


      outfile.close();
  }
}
