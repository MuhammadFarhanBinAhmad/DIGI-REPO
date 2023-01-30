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
#ifndef Q_H
#define Q_H

// Don't remove!!!
// We're limiting ASCII set to the basic character set
// with encoding from 0 to 127
#define ASCII_COUNT 128//i forgot this existed

int encrypt(int* letter,char keytext);
int decrypt(int* letter,char keytext);

// TODO2: your clients will be given this header file since they
// will have no access to the definitions of functions
// encrypt and decrypt - therefore, provide header documentation
// for function encrypt

// TODO3: declaration for function encrypt

// TODO4: your clients will be given this header file since they
// will have no access to the definitions of functions
// encrypt and decrypt - therefore, provide header documentation
// for function decrypt

// TODO5: declaration for function decrypt


#endif // Q_H
