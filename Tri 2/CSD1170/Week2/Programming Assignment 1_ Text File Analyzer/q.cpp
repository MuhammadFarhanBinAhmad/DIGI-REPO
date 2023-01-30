#include <iostream>
#include <iomanip>
#include <fstream>

namespace hlp2 {
  void q(char const *input_filename, char const *analysis_file)
  {
      //GET FILE NAME
      char infilename[10];
      int ch_pos=0;

      while (*input_filename != '\0')
      {
          infilename[ch_pos] = *input_filename;
          ch_pos++;
          input_filename++;
      }
      infilename[ch_pos] = '\0';

      //READ FILE
      std::fstream read_File(infilename, std::ios_base::in);
      if (!read_File.is_open())
      {
          std::cout << "File " << infilename << " not found." << std::endl;
      }

      char ch;
      int byte = 0;
      int space = 0;
      double percent_Space = 0;

      int digit = 0;
      double percent_Digit = 0;

      int specialchar = 0;
      double percent_SpecialChar = 0;

      int total_Letter = 0;
      double percent_TotalLetter = 0;
      int upper_Letter = 0;
      double percent_UpperLetter = 0;
      int lower_Letter = 0;
      double percent_LowerLetter = 0;

      char alp[26]{'a','b','c','d' ,'e' ,'f' ,'g' ,'h' ,'i' ,'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
      int alp_Total[26]{ 0 };
      double alp_Percentage[26]{ 0.0 };
      int current_Alphabet = 0;

      int total_Number = 0;
      char numberbuffer[15];
      int numberholder[300]{0};
      int current_Number = 0;
      int numberplacement = 0;
      int total_Sum = 0;
      double average_Sum = 0.00;
      //Get all char data(whitespace,char,digits,alphabet(upper & lower))
      while (read_File.get(ch))
      {
          //WHITESPACES
          if (ch == ' ' || ch == '\n')
          {
              ++space;
          }
          //DIGITS
          if (ch >= '0' && ch <= '9')
          {
              ++digit;
              numberbuffer[numberplacement] = ch;
              numberplacement++;
          }
          //SPECIAL CHARACTEER
          if ((ch >= '!' && ch <= '/') || (ch >= ':' && ch <= '@') || (ch >= '[' && ch <= '`') || (ch >= '{' && ch <= '~'))
          {
              specialchar++;
          }
          ///ALPHABET
          //LOWERCASE
          if (ch >= 'a' && ch <= 'z')
          {
              lower_Letter++;
              total_Letter++;
          }
          //UPPPERCASE
          if (ch >= 'A' && ch <= 'Z')
          {
              upper_Letter++;
              total_Letter++;
              //convert to lowercase
              ch += 32;
          }
          //NEW NUMBER
          if ((ch < '0' && numberplacement > 0 )|| (ch > '9' && numberplacement > 0))
          {
              current_Number = std::atoi(numberbuffer);
              numberplacement = 0;
              numberholder[total_Number] = current_Number;
              total_Number++;
              //Clear numberbuffer
              for (int i =0;i < 15;i++)
              {
                numberbuffer[i] = '\0';
              }
          }
          //TOTAL OF EACH ALPHABET
          while (current_Alphabet < 26)
          {
              if (ch == alp[current_Alphabet])
              {
                  alp_Total[current_Alphabet]++;
              }
              current_Alphabet++;
          }
          current_Alphabet = 0;
      }
      //TOTAL CHAR
      byte += total_Letter+digit+space+specialchar;

      //Find Percentage of all type(total word,white spaces,digit etc.)
      //LETTER PERCENTAGE
      percent_TotalLetter = (((double)total_Letter / (double)byte) * 100);
      //WHITE SPACE PERCENTAGE
      percent_Space = (((double)space / (double)byte) * 100);
      //DIGITS
      percent_Digit = (((double)digit / (double)byte) * 100);
      //OTHER CHARS
      percent_SpecialChar = (((double)specialchar / (double)byte) *100);
      //UPPERCASE
      percent_UpperLetter = (((double)upper_Letter / (double)total_Letter) * 100);
      //LOWERCASE
      percent_LowerLetter = (((double)lower_Letter / (double)total_Letter) * 100);
      
      //SUM OF INT
      for (int i =0; i < total_Number;i++)
      {
        total_Sum += numberholder[i];
      }
      //AVERAGE OF INT
      if (total_Number >0)
      {
      average_Sum = (double)total_Sum/(double)total_Number;
      }
      //FREE
      read_File.close();

      //GET FILE NAME
      char outfilename[10];
      ch_pos = 0;

      while (*analysis_file != '\0')
      {
          outfilename[ch_pos] = *analysis_file;
          ch_pos++;
          analysis_file++;
      }
      outfilename[ch_pos] = '\0';//add null terminator after grabbing all char
      //WRITE FILE
      std::ofstream out_File(outfilename);
      if (!out_File.is_open())
      {
          std::cout<< "Fail to open lol";
      }
      
      //USE SETPRECISION(2) ROUND OFF TO 2 D.P
      //USE STD::FIXED TO ENSURE ALL ARE SET 2 D.P
      out_File<< "Statistics for file: " << infilename << std::endl;
      out_File<< "---------------------------------------------------------------------" << std::endl << std::endl;

      out_File << "Total # of characters in file: " << byte << std::endl << std::endl;

      out_File << "Category            How many in file             % of file"<<std::endl;
      out_File << "---------------------------------------------------------------------"<< std::endl;
      out_File << std::setprecision(2) << std::fixed;
      out_File << "Letters" << std::setw(29) << total_Letter << std::setw(20) << percent_TotalLetter << " %" << std::endl;
      out_File << "White space"<< std::setw(25) << space << std::setw(20) << percent_Space<< " %" << std::endl;
      out_File << "Digits"<< std::setw(30) << digit << std::setw(20) << percent_Digit<< " %" << std::endl;
      out_File << "Other characters"<< std::setw(20) << specialchar << std::setw(20) << percent_SpecialChar<< " %" << std::endl <<std::endl<<std::endl;


      out_File << "LETTER STATISTICS" << std::endl << std::endl;

      out_File << "Category            How many in file      % of all letters"<< std::endl;
      out_File << "---------------------------------------------------------------------"<< std::endl;
      out_File << "Uppercase "<< std::setw(26) << upper_Letter << std::setw(20) << percent_UpperLetter<< " %" << std::endl;
      out_File << "Lowercase "<< std::setw(26) << lower_Letter << std::setw(20) << percent_LowerLetter<< " %" << std::endl;

      current_Alphabet = 0;
      //PERCENTAGE OF EACH ALPHABET
      while (current_Alphabet < 26)
      {
          alp_Percentage[current_Alphabet] = (((double)alp_Total[current_Alphabet] / (double)total_Letter) * 100);
          out_File << alp[current_Alphabet] << std::setw(35) << alp_Total[current_Alphabet] << std::setw(20) << alp_Percentage[current_Alphabet]<< " %" << std::endl;
          current_Alphabet++;
      }
      out_File << std::endl << std::endl;

      out_File << "NUMBER ANALYSIS" << std::endl << std::endl;
      
      //VALUE OFFSET FOR FORMATTING
      int num_offset = 0;
      int sum_offset = 0;
      int average_offset = 0;
      
      if (total_Number >= 10)
      {
        num_offset = 1;
        if (total_Number >= 100)
        {
            num_offset = 2;
        }
      }
      if (total_Sum > 10)
      {
        sum_offset = 1;
        if (total_Sum >= 100)
        {
            sum_offset = 2;
            if (total_Sum >= 1000)
            {
            sum_offset = 3;
            }
        }
      }
      if (average_Sum >= (double)10)
      {
        average_offset = 1;
      }
      out_File << "Number of integers in file:"<< std::setw(11 + num_offset) << total_Number << std::endl;
      out_File << "Sum of integers:"<< std::setw(22+ sum_offset) << std::right <<  total_Sum << std::endl;
      out_File << "Average of integers:"<< std::setw(21 + average_offset) << average_Sum << std::endl;
      out_File << "_____________________________________________________________________" << std::endl;

      //FREE
      out_File.close();
  }
}
