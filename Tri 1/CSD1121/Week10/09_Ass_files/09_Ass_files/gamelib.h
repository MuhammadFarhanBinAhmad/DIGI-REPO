/*!
@file       gamelib.h 
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 7
@date       30/10/2020
@brief      This file contains declarations of functions needed by the game.
            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#ifndef GAMELIB_H
#define GAMELIB_H

#include "cardlib.h"

// Loads a game by reading it from text[] into the array of cards.
void load_game(const char text[], Card game[]);

// Plays a game.
void play_game(Card game[]);

// Displays the sequence of cards.
void display_game(const Card game[]);

#endif // GAMELIB_H
