// Polymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Ranger.h"
#include "Wizard.h"
#include "Warrior.h"

int main()
{
    Ranger* R = new Ranger;
    Wizard* Wiz = new Wizard;
    Warrior* War = new Warrior;

    R->SetStats();
    R->SetSkills();
    R->PrintStats();

    Wiz->SetStats();
    Wiz->SetSkills();
    Wiz->PrintStats();

    War->SetStats();
    War->SetSkills();
    War->PrintStats();

    delete R;
    delete Wiz;
    delete War;
 //   MY BEST FRIEND AND WORST ENEMY :)
 //Enable run-time memory check for debug builds.
    #if defined(DEBUG) | defined(_DEBUG)
	    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif
}
