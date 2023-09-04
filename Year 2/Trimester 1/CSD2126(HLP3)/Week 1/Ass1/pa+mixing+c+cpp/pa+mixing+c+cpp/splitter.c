/*****************************************************************//**
 * \file	spliter.c
 * \brief	Split up binary file to smaller binary or join multiple binary file to one binary file
 *        depending on your console command prompt
 *
 * \author	FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
 * \date	02-SEP-2023
***********************************************************************/
#include "splitter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FOUR_K 4096 // Don't modify this!!!
//#define FOUR_K 40 // Don't modify this!!!
//Note to self: If c++/c mixing. Pls do C first.:.)
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
  SplitResult rs = E_NO_ACTION;

  
  size_t offset = 1;//offset console command
  
  if (strcmp(argv[offset],"-s") == 0)
  {
    offset++;//2
    
    int desired_FileSize = 0;

    sscanf(argv[offset],"%d",&desired_FileSize);

    if (desired_FileSize <= 0 )
    {
      return rs = E_SMALL_SIZE;
    }

    offset++;//3

    if (strcmp(argv[offset],"-o") == 1)
    {
      printf("-o");
      return rs = E_NO_ACTION;
    }

    offset++;//4

    offset++;//5

    if (strcmp(argv[offset],"-i") == 1)
    {
      printf("-i");
      return rs = E_NO_ACTION;
    }
    
    offset++;//6

    FILE *in_file = fopen(argv[offset],"rb");
    if (!in_file)
    {
      return rs = E_BAD_SOURCE;
    }

    //Get size of file
    fseek(in_file,0,SEEK_END);
    size_t fileSize = ftell(in_file);
    int byte_left = fileSize;
    fseek(in_file,0,SEEK_SET);

    int file_Version = 1;

    while(byte_left > 0)
    {
      char* text_Buffer;
      text_Buffer = (char*)malloc(desired_FileSize * sizeof(char));//Allocate space

      if (!text_Buffer)
      {
        printf("Mem allocate fail");
        return rs = E_NO_ACTION;
      }
      
      char filefullname[50];
      char* filename = argv[4];

      sprintf(filefullname, "%s%04d",filename , file_Version++);
      FILE *output_File = fopen(filefullname,"wb");

      if (!output_File)
      {
        printf("Fail to create file");
        return rs = E_NO_ACTION;
      }

      int file_SizeLeft;

      //Decide size for current file to be exported
      if (byte_left > desired_FileSize)
      {
        file_SizeLeft = desired_FileSize;
      }
      else
      {
        file_SizeLeft = byte_left;
      }

      //Copy data into new file
      while (file_SizeLeft > 0)
      {

        if (file_SizeLeft >= FOUR_K)
        {
          size_t bytesRead = fread(text_Buffer, 1, FOUR_K, in_file);
          fwrite(text_Buffer,1,bytesRead,output_File);
          file_SizeLeft -= FOUR_K;
          byte_left -= FOUR_K;
        }
        else
        {
          size_t bytesRead = fread(text_Buffer, 1, file_SizeLeft, in_file);
          fwrite(text_Buffer,1,bytesRead,output_File);
          byte_left -= file_SizeLeft;
          file_SizeLeft -= file_SizeLeft;
        }
      }

      fclose(output_File);
      free(text_Buffer);
      text_Buffer = NULL;

    }
    fclose(in_file);
    return rs = E_SPLIT_SUCCESS;
  }

  //JOIN FILE TOGETHER
  else if (strcmp(argv[offset],"-j") == 0)
  {
      offset++;//2

      if (strcmp(argv[offset],"-o") == 1)
      {
        printf("o\n");
        return rs = E_NO_ACTION;
      }

      offset++;//3
      
      FILE *output_File;
      output_File = fopen(argv[offset],"wb");

      if (!output_File)
      {
        printf("fail to open");
        return rs = E_BAD_SOURCE;
      }

      offset++;//4

      if (strcmp(argv[offset],"-i") == 1)
      {
        printf("i\n");
        return rs = E_NO_ACTION;
      }

      offset++;//5

      int filenamesize = 0;//grab size of
      int p = 0;
      while(argv[offset][p] != '\0')
      {
        p++;
        filenamesize++;
      }

      char in_FileName[100] = "";

      //Grab file name without number
      int pos = 0;
      while (!isdigit(argv[offset][pos]))
      {
        in_FileName[pos] = argv[offset][pos];
        pos++;
      }

      for (int variant =1; variant <= argc;variant++)
      {

        char filefullname[200] = "";
        
        sprintf(filefullname,"%s%04d",in_FileName,variant);

        FILE *target_file = fopen(filefullname,"rb");
        if (!target_file)
        {
          break;
        }
        else
        {
          int ch;
          while ((ch = fgetc(target_file))!= EOF)
          {
            fputc(ch,output_File);
          }
        }

        fclose(target_file);
      }

      fclose(output_File);

      return rs = E_JOIN_SUCCESS;
  }

  return rs;


}
