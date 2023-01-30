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
// match(es) the declaration(s) in q.h ...const char* build_path(
#include "q.h"

const char* build_path(const char* parent,const char* separator,const char* const folders[],size_t count)
{

    long unsigned int arraysize = 0;
    arraysize +=STRLEN(parent);
    for (int i = 0; i < (int)count;i++)
    {
        arraysize += STRLEN(folders[i]);
        arraysize += STRLEN(separator);
    }
    char *filepath = debug_malloc(arraysize+1);
    
    STRCPY(filepath,parent);
    for(int i =0 ;i < (int)count;i++)
    {
        STRCAT(filepath,folders[i]);
        STRCAT(filepath,separator);
    }
    filepath[arraysize] = '\0';
    return filepath;

}
void compare_string(const char* lhs,const char* rhs)
{
    int value= STRCMP(lhs,rhs);
    if (value > 0)
    {
        printf("Left string goes first.\n");
    }
    if (value < 0)
    {
        printf("Right string goes first.\n");
    }
    if (value ==0)
    {
        printf("Both strings are equal.\n");
    }
}
void describe_string(const char* text)
{
    printf("The length of the path \"%s\" is %ld.\n",text,STRLEN(text));
}
void find_string(const char* string,const char* substring)
{
   char *pos = STRSTR(string,substring);
   printf("Searching for a string:\n");
   printf("\tText:     %s\n",string);
   printf("\tSub-text: %s\n",substring);
    pos ? printf("\tResult:   found %ld characters at a position %td.\n", 
                 STRLEN(substring), pos - string)
        : printf("\tResult:   not found\n");
}
