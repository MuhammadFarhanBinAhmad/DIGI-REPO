#include <stdio.h>
#include <stdlib.h>
#include "FString.h"

#define MAX_SIZE 256

int main(void)
{
    FILE *textFile = fopen("Input.txt","r");
    long unsigned int count;

    //check file is open
    if (!textFile)
    {
        return 0;
    }
    //get count for malloc
    while(fgetc(textFile) != EOF)
    {
        count++;
    }
    
    //set size
    long unsigned int size  = sizeof(char) * count;
    char *text_Size = malloc((size_t)size);
    //check if malloc was succesful
    if (text_Size == 0)
    {
        return 0;
    }
    
    //reset cursor to the start of the text file
    fseek(textFile,0,SEEK_SET);

    int index =0;

    while (fgets(text_Size,size,textFile) != NULL)
    {
        printf("%s",text_Size);
    }
    
}