#include <stdio.h>
#include "FString.h"

char toUpper(char *text)
{
    if (*text >= 'a' && *text <= 'z')
        {
            *text = (char)(*text -32);
        }
    return *text;
}
char* toLower(char *text)
{
    if (*text >= 'A' && *text <= 'Z')
        {
            *text = (char)(*text + 32);
        }
}
