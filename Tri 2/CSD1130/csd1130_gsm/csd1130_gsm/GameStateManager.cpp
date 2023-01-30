#include "GameStateManager.h"
#include "pch.h"

int current = 0 , previous = 0, next = 0;

FP pfLoad = nullptr, pfInitialize = nullptr, pfUpdate = nullptr, pfDraw = nullptr, pfFree = nullptr, pfUnload = nullptr;

