#pragma once

typedef void(*FP)(void);
extern int current, previous, next;


extern FP pfLoad, pfInitialize, pfUpdate, pfDraw, pfFree, pfUnload;


void GSM_Initilize(int startingState);
void GSM_Update();
