/*==============================================================================
Simple Event Example
Copyright (c), Firelight Technologies Pty, Ltd 2012-2023.

This example demonstrates the various ways of playing an event.

#### Explosion Event ####
This event is played as a one-shot and released immediately after it has been
created.

#### Looping Ambience Event ####
A single instance is started or stopped based on user input.

#### Cancel Event ####
This instance is started and if already playing, restarted.

For information on using FMOD example code in your own programs, visit
https://www.fmod.com/legal
==============================================================================*/
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "common.h"
#include <glfw3.h>

#include <iostream>

void InitWindow();

static GLFWwindow* window;

void PlayAudio(int key)
{

}
void LoadBank()
{

}

/*TODO*/
/*
*   Make code neater
*   Use GLFW to play sound.
*   Change bank audio to global variable instead of local
*/
int main(void)
{
    InitWindow();
    //FMOD_Main();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        std::cout << "check";
        FMOD_Main();
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwTerminate();
    }
        
}
void InitWindow()
{
    /* Initialize the library */
    if (!glfwInit())
        std::cout << "FAIL TO INITIALIZE GLFW\n";

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "FAIL TO INITIALIZE WINDOW\n";
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwSetKeyCallback(window, key_callback);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
int FMOD_Main()
{
    void* extraDriverData = NULL;
    Common_Init(&extraDriverData);

    FMOD::Studio::System* system = NULL;
    ERRCHECK(FMOD::Studio::System::create(&system));

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    FMOD::System* coreSystem = NULL;
    ERRCHECK(system->getCoreSystem(&coreSystem));
    ERRCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));

    ERRCHECK(system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData));

    FMOD::Studio::Bank* masterBank = NULL;
    ERRCHECK(system->loadBankFile(Common_MediaPath("MasterTest.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));

    FMOD::Studio::Bank* stringsBank = NULL;
    ERRCHECK(system->loadBankFile(Common_MediaPath("MasterTest.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));

    FMOD::Studio::Bank* sfxBank = NULL;
    ERRCHECK(system->loadBankFile(Common_MediaPath("Test.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &sfxBank));

    // Get the Looping Ambience event
    FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    ERRCHECK(system->getEvent("event:/SFX/Ambiance", &loopingAmbienceDescription));

    FMOD::Studio::EventInstance* loopingAmbienceInstance = NULL;
    ERRCHECK(loopingAmbienceDescription->createInstance(&loopingAmbienceInstance));

    // Get the 4 Second Surge event
    FMOD::Studio::EventDescription* cancelDescription = NULL;
    ERRCHECK(system->getEvent("event:/SFX/SoundEffect", &cancelDescription));

    FMOD::Studio::EventInstance* cancelInstance = NULL;
    ERRCHECK(cancelDescription->createInstance(&cancelInstance));

    // Get the Single Explosion event
    FMOD::Studio::EventDescription* explosionDescription = NULL;
    ERRCHECK(system->getEvent("event:/SFX/UI", &explosionDescription));

    // Start loading explosion sample data and keep it in memory
    ERRCHECK(explosionDescription->loadSampleData());

    do
    {
        Common_Update();
        if (Common_BtnPress(BTN_ACTION1))
        {
            // One-shot event
            FMOD::Studio::EventInstance* eventInstance = NULL;
            ERRCHECK(explosionDescription->createInstance(&eventInstance));

            ERRCHECK(eventInstance->start());

            // Release will clean up the instance when it completes
            ERRCHECK(eventInstance->release());
        }

        if (Common_BtnPress(BTN_ACTION2))
        {
            ERRCHECK(loopingAmbienceInstance->start());
        }

        if (Common_BtnPress(BTN_ACTION3))
        {
            ERRCHECK(loopingAmbienceInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
        }

        if (Common_BtnPress(BTN_ACTION4))
        {
            // Calling start on an instance will cause it to restart if it's already playing
            ERRCHECK(cancelInstance->start());
        }

        ERRCHECK(system->update());

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    ERRCHECK(sfxBank->unload());
    ERRCHECK(stringsBank->unload());
    ERRCHECK(masterBank->unload());

    ERRCHECK(system->release());

    Common_Close();

    return 0;
}
