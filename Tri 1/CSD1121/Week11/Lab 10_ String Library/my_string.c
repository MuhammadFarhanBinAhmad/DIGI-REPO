// @todo: Add a file documentation header as explained in the specs ...

// @todo: Add necessary C standard library headers here ...

// You should document [not necessary for grading but an excellent habit
// to acquire] your implementation of functions to aid
// in debugging and maintenance not only by yourself but by others in
// your software development team ...

// Remember, the function-level documentation header in my_string.h is primarily
// meant for your clients. The documentation header here is primarily for
// use by you [and other on your team] solely to aid maintenance and
// debugging tasks ...


// @todo: Provide the definition(s) of function(s) that
// match the declaration(s) in my_string.h ...

// For each function -

// Add documentation [for yourself and not for grading] for the function ...

// @todo: Provide the definition of the function(s) that
// match(es) the declaration(s) in my_string.h ...
#include "q.h"
size_t my_strlen(const char* str)
{
    size_t count =0;

    while(str[count] != '\0')
    {
        count++;
    }
    return count;
}
char* my_strcpy(char* dest, const char* src)
{

    //size_t count = STRLEN(src);


    //for (size_t i =0 ; i < count; i++)
    //{
    //    dest[i] = src[i];
    //    /*if (src[i] == '\0')
    //    {
    //        break;
    //    }*/
    //}

    int destlen = 0;
    int srclen = 0;

    for (; src[srclen]; srclen++, destlen++)
    {
        dest[destlen] = src[srclen];
    }
    dest[destlen] = '\0';
    return dest;
}

char* my_strcat(char* dest, const char* src)
{

    int destlen = 0;
    int srclen = 0;

    while (dest[destlen] != '\0')
    {
        destlen++;
    }
    for (; src[srclen] != '\0'; srclen++, destlen++)
    {
        dest[destlen] = src[srclen];
    }
    dest[destlen] = '\0';

    return dest;
}

int my_strcmp(const char* lhs, const char* rhs)
{
    while(*lhs != '\0'&& *rhs != '\0')
    {
        lhs++;
        rhs++;
        if (*lhs - *rhs > 0)
        {
            return -1;
        }
        if (*lhs - *rhs < 0)
        {
            return 1;
        }
        
    }
    return 0;
}

char* my_strstr(const char* str, const char* substr)
{
    int offset = 0;
    int index =0;

    while ((substr[index] != str[offset]) && (str[offset] != '\0'))
    {
        offset++;
    }
    for (int i = 0, j = 0; substr[i] != '\0'; i++, j++)
    {
        if (substr[i] != str[offset + j])
        {
            return '\0';
        }
    }
    return (char*)(str + offset);
}