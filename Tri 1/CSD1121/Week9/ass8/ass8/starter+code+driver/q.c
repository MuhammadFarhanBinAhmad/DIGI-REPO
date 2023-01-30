// TODO: File documentation block required

// NOTE 2: Even if you don't need the NULL, don't remove this macro ...
#define NULL ((void*)0) 
#include <stdio.h>
#include "q.h"

char const* find(char const* begin, char const* end, char val)//DONE
{
    char *p = begin;
    char *q = end;

    while (p < end)
    {
        printf("val = %c\n",val);
        if (*p == val)
        {
        printf("p = %c\n",*p);
        return *p;
        }
        p++;
    }
    return NULL;
}
char const* find_any(char const *begin, char const *end,char const *vals, int len)
{
    char const* p = begin;
    char const* q = end;
    char const* t = begin;
    for (int i = 0; i < len; i++)
    {
        for (t; t < q; t++)
        {
            if (*t == *vals)
            {
                return vals;
            }
        }
        t = p;
        vals++;
    }
    return NULL;
}
int count(char const *begin, char const *end, char val)//DONE
{
    char *p = begin;
    char *q = end;
    int total =0;
    while (p < end)
    {
        if (*p == val)
        {
            total++;
        }
        p++;
    }
    return total;

}
int count_any(char const *begin, char const *end, char const *vals, int len)
{
    const char* p = begin;
    const char* q = end;
    const char* t = begin;
    int total = 0;
    for (int i = 0; i < len; i++)
    {
        for (t; t < q; t++)
        {
            if (*t == *vals)
            {
                total++;
            }
        }
        t = p;
        vals++;

    }
    return total;
}
int compare(char const *begin1, char const *begin2, int len)//DONE
{
    int sum = (int)*begin1 - *begin2;
    return sum;
}
void exchange(char *begin1, char *begin2, int len)//DONE?
{
    int i =0;
    while(i < len)
    {
        char temp = *begin1;
        *begin1 = *begin2;
        *begin2 = temp;
        begin1++;
        begin2++;
        i++;
    }

}
void copy(char *dst, char *src, int len)
{

}