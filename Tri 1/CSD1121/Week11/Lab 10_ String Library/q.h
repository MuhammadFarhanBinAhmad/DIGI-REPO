// @todo: Add a file-level documentation header as explained in Lab 2 specs ...

// @todo: Copy type aliases and macros from the current specs

// @todo: Provide function-level documentation header for each function 
// as explained in Assignment 2 specs ...
// It is important that you provide a function-level documentation header in
// this [header] file since this file is what you would provide to your
// clients and other users ...

// @todo: Now, provide the declaration or prototype of the functions 
// build_path, compare_string, describe_string, and find_string
#include <stdio.h>
#include <stddef.h>
//#define USE_STRING

#ifdef USE_STRING
#include <string.h>
#define STRLEN strlen
#define STRCPY strcpy
#define STRCAT strcat
#define STRCMP strcmp
#define STRSTR strstr
#else
#include "my_string.h"
#define STRLEN my_strlen
#define STRCPY my_strcpy
#define STRCAT my_strcat
#define STRCMP my_strcmp
#define STRSTR my_strstr
#endif
void* debug_malloc(size_t size);
void debug_free(void* ptr);

const char* build_path(const char* parent,const char* separator,const char* const folders[],size_t count);
void compare_string(const char* lhs,const char* rhs);
void describe_string(const char* text);
void find_string(const char* string,const char* substring);

size_t my_strlen(const char* str);
char* my_strcpy(char* dest, const char* src);
char* my_strcat(char* dest, const char* src);
int my_strcmp(const char* lhs, const char* rhs);
char* my_strstr(const char* str, const char* substr);
