// @todo: Add a file documentation header as explained in the specs ...

// @todo: Add necessary C standard library headers here ...

// You should document [not necessary for grading but an excellent habit
// to acquire] your implementation of functions to aid
// in debugging and maintenance not only by yourself but by others in
// your software development team ...

// Remember, the function-level documentation header in q.h is primarily
// meant for your clients. The documentation header here is primarily for
// use by you [and other on your team] solely to aid maintenance and
// debugging tasks ...


// @todo: Provide the definition(s) of function(s) that
// match the declaration(s) in q.h ...

// For each function -

// Add documentation [for yourself and not for grading] for the function ...

// @todo: Provide the definition of the function(s) that
// match(es) the declaration(s) in q.h ...
#include <stdio.h>
#include <string.h>
#include "q.h"

char* str_to_upper(char* string)
{
    char *first = string;
    while(*string != '\0')
    {
        if (*string >= 'a' && *string <= 'z')
        {
            *string = (char)(*string-32);
        }
        string++;
    }
    return first;

}
WordCount words_starting_with(const char* dictionary, char letter)
{
    FILE *textfile = fopen(dictionary,"r");
    int count =0;
    char string[LONGEST_WORD+2];

    if (textfile == NULL)
    {
        return FILE_ERR_OPEN;
    }
    if(letter >= 'a')
    {
        letter = (char)(letter - (char)('a' - 'A'));
    }

    while(fgets(string,LONGEST_WORD,textfile) !=NULL)
    {
        str_to_upper(string);

        if (string[0] == (char)letter)
        {
            count++;
        }
    }
    fclose(textfile);
    return count;
    
}
ErrorCode spell_check(const char* dictionary, const char* word)
{
    FILE *textfile = fopen(dictionary,"r");
    char string[LONGEST_WORD+1];
    char word_string[LONGEST_WORD+2];

    strcpy(word_string,word);

    if( textfile == NULL)
    {
        return FILE_ERR_OPEN;
    }

    str_to_upper(word_string);

    while(fgets(string,LONGEST_WORD+2,textfile) != NULL)
    {
        str_to_upper(string);

        for(int i=0; i< LONGEST_WORD;++i)
        {
            if(i == 0 && string[i] == '\n')
            {
                break;
            }
            if (string[i] == '\n' && word_string[i] == '\0')
            {
            fclose(textfile);
            return WORD_OK;
            }
            if (string[i] != word_string[i])
            break;
        }

    }
    fclose(textfile);
    return WORD_BAD;
}

ErrorCode word_lengths(const char* dictionary, WordCount lengths[], WordLength count)
{
    FILE *textfile = fopen(dictionary,"r");
    char word_string[LONGEST_WORD+2];

    if (textfile == NULL)
    {
        return WORD_BAD;
    }

    while(fgets(word_string,LONGEST_WORD+1,textfile)!= NULL)
    {
        for (short i =1 ; i <= count;i++)
        {
            if ((strlen(word_string) - 1 ) == (long unsigned int)i)
            {
                ++lengths[i];
            }
        }
    }
    return WORD_OK;
}
ErrorCode info(const char* dictionary, DictionaryInfo* info)
{
    FILE *textfile = fopen(dictionary,"r");
    if (textfile == NULL)
    {
        return WORD_BAD;
    }
    char word_string[LONGEST_WORD+2];

    info->shortest = 51;
    info->count = 0;
    while(fgets(word_string,LONGEST_WORD+2,textfile)!= NULL)
    {
            if (strlen(word_string)-1 > info->longest)
            {
                info->longest = (WordLength)(strlen(word_string)-1);
            }
            if (strlen(word_string)-1 < info->shortest)
            {
                info->shortest = (WordLength)(strlen(word_string)-1);
            }
        info->count++;

    }
    return WORD_OK;
}