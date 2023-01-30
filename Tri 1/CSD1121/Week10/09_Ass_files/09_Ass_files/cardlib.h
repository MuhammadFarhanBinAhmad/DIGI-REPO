/*!
@file       cardlib.h 
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 7
@date       30/10/2020
@brief      This file contains constants and types needed by the game.
            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#ifndef CARDLIB_H
#define CARDLIB_H

// Pre-processor constants

// Maximum number of cards of input
// 52 + "00" (end indicator)
#define N 53

// Maximum length of an input text string
// * 2 letters each card
// * 1 space separator after each card
// * the end of line sequence (up to 2 characters; in Windows "\r\n")
#define LEN (3 * N + 2)

// Types

typedef unsigned char CardIndex;
typedef char CardSuit;
typedef char CardRank;

typedef struct Card
{
	CardSuit suit;
	CardRank rank;
} Card;

#endif // CARDLIB_H
