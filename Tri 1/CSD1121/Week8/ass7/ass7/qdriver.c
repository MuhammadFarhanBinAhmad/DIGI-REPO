// TODO1: Add file header documentation ...


/*!
@file q.h
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@ Assignment 7: Encryption/Decryption with Pointers
@date 22/10/22
@brief 1. Encrypts a plain text input file by writing the encrypted text into a ciphered text output file.
2. Decrypts a ciphered text input file into a deciphered text output file.
3. Counts the number of words in the deciphered text file
*/
#include "q.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void) {

	int letter;
	char line[255];
	int key_length=0;
	int key_Count = 0;

	FILE *file_Source = fopen("plain.txt","r");
	FILE *file_Key = fopen("key.txt","r");

    //file check
	if (!file_Source)
	{
		fputs("Unable to open plain.txt!!!\n", stderr);
    	return 0;
	}	
	if(fgets(line, 255, file_Key) == NULL) {	//checking to see if file actually has the key
		fputs("No key detected\n", stderr);

		return 0;
	}
	//grab total length of key
    while (fgets(line, 255, file_Key) != NULL) 
    {
	    key_length += (int)strlen(line);
    }
  key_length -= 1;//compensate null terminator

#ifdef ENCRYPT

	FILE *file_Encrypt = fopen("cipher.txt","w");

	key_Count = 0;
	int word_Encrypted = 0;

	while(1)
	{
		letter = (int)(fgetc(file_Source));//grab a char in plain.txt
		word_Encrypted = encrypt(&letter,line[key_Count]);//encrypt char
		fputc(word_Encrypted,file_Encrypt);//place it in cipher txt
		key_Count = (++key_Count > key_length-1)?0:key_Count;//check which letter its in, go above key value(7),will reset
		if(letter ==EOF)
		{
			break;
		}
	}

	fclose(file_Encrypt);
	fclose(file_Source);

#else

	FILE *file_Encrypted = fopen("cipher.txt","r");
	FILE *file_Decryprted = fopen("out-plain.txt","w");

	key_Count = 0;
	int word_Count =0;
	int word_Decrypted = 0;

	int word_previous = -1;

	while (1)
	{
		letter = (int)(fgetc(file_Encrypted));//grab char in cipher txt

		if (letter == EOF)//stop reading of file
		{
			break;
		}

		word_Decrypted = decrypt(&letter,line[key_Count]);//decrypt char
		fputc(word_Decrypted,file_Decryprted);//put char in out-plain txt.
		key_Count = (++key_Count > key_length-1)?0:key_Count;//check which letter its in, go above key value(7),will reset

		if (word_previous == -1)
		{
			word_previous = word_Decrypted;
			continue;
		}
        //check if char is a space/tab/newline/escape/number
		if (isdigit(word_previous)||isalpha(word_previous)||ispunct(word_previous))
		{
			switch((char)word_Decrypted)
			{
				case' ':
				case'\n':
				case'\t':
				case'\r':
				case'\v':
				case'\f':
				word_Count++;//add to word count if is
				break;
				default:
				break;
			}
		}
		word_previous = word_Decrypted;//go check next char
	}
	fprintf(stderr,"Words:%d\n",word_Count);

	fclose(file_Encrypted);
	fclose(file_Decryprted);


#endif

	fclose(file_Key);
		//im still not a fan of reading char or from files. sigh
	return 0;
}