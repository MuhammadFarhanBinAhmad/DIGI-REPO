
#include "pch.h"
#include "GameStateManager.h"
/* Start Header ************************************************************************/
/*!
\file <csd1130_gsm.cpp>
\author <Muhammad Farhan Bin Ahmad,b.muhammadfarhan,2200544>
\par <b.muhammadfarhan@digipen.edu>
\date <Jan 13,2023>
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
\breif main - Handle all program and function in sln.
*/
/* End Header **************************************************************************/

#include "Input.h"
#include "System.h"

int main()
{
    //Systems initialize
    System_Initialize();
    //Game State Manager initialize
    //Initialize start of game
    GSM_Initialize(0);

    while (current != GS_QUIT)
    {
        //Load data from files
        if (current != GS_RESTART)
        {
            GSM_Update();
            fpLoad();
        }
        else
        {
            next = previous;
            current = previous;
        }
        //Initialize all variables and data
        fpInitialize();
        //the game loop
        while(next == current)
        {
            //DURING GAMEPLAY
            //Handle input,physic etc.
            //Render images
            Input_Handle();
            fpUpdate();
            fpDraw();
        }
        //Free data upon end of level
        fpFree();

        //If game isnt being restart, unload all data from current level
        if (next != GS_RESTART)
        {
            fpUnload();
        }
        previous = current;
        current = next;
    }
    //END OF PROGRAM. EXIT PROGRAM
    System_Exit();
    return 0;
}