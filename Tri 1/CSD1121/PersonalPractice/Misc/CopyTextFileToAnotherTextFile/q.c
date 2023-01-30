#include <stdio.h>
#include <ctype.h>


int Encryptchar(char c,int change)
{
    return c+change;
}
int Decryptchar(char c,int change)
{
    return c-change;
}
int main(void)
{

    char str[100];

    int ch;

    FILE *in = fopen("og.txt","r");
    FILE *out = fopen("toCopy.txt","w");
    FILE *decrpyt = fopen("decrypt.txt","w");
    int charcount;
    int spacecount;
    int tabcount;
    int numcount;
    int newlinecount;
    int puctcount;
    int returncount;

    if (in)
    {
        /*while(fgets(str,256,in) !=NULL)//Read till the end of the txt.file
        {
            fputs(str,out);
        }*/
        while ((ch = fgetc(in)) !=EOF)
        {
            ch = Encryptchar(ch,3);
            fputc((char)ch,out);
            ch = Decryptchar(ch,3);
            fputc((char)ch,decrpyt);

            if (isalpha(ch))
            {
                charcount++;
            }
            if (ispunct(ch))
            {
                puctcount++;
            }
            if (isdigit(ch))
            {
                numcount++;
            }
            if(((char)ch == '\n'))
            {
                newlinecount++;
            }
            if(((char)ch == '\t'))
            {
                tabcount++;
            }
            if(((char)ch == '\r'))
            {
                returncount++;
            }
            if(((char)ch == ' '))
            {
                spacecount++;
            }
        }
        fprintf(decrpyt,"\ntotal char: %d\n",charcount);
        fprintf(decrpyt,"\ntotal punt: %d\n",puctcount);
        fprintf(decrpyt,"\ntotal number: %d\n",numcount);
        fprintf(decrpyt,"\ntotal newline: %d\n",newlinecount);
        fprintf(decrpyt,"\ntotal tab: %d\n",tabcount);
        fprintf(decrpyt,"\ntotal return: %d\n",returncount);
        fprintf(decrpyt,"\ntotal space: %d\n",spacecount);

    }
    
    else
    {
        printf("Fail to open");
    }

    fclose(in);
    fclose(out);
    fclose(decrpyt);
}