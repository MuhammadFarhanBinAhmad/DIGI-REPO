#include "Engine.h"

bool endsystem;

void EndEngine(testThread &tt, int time)
{
    while (!tt.exitFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(time));
        std::cout << "Timer has ended. Closing thread\n"
                  << std::endl;
        std::cout << "END ENGINE\n"
                  << std::endl;
        tt.exitFlag = true;
        endsystem = true;
    }
}
void AutoSave(testThread &tt, int time)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(time));
        time_t x = std::time(0);
        char *y = ctime(&x);
        std::ofstream MyFile("AnotherDateFile.txt");

        // Write to the file
        MyFile << "The date and time according to your local time zone is: " << y << std::endl;
        std::cout << "FILE SAVE\n";
        // Close the file
        MyFile.close();
    }
}

void PrintStuff()
{
    time_t x = std::time(0);
    char *y = ctime(&x);
    std::ofstream MyFile("AnotherDateFile.txt");

    // Write to the file
    MyFile << "The date and time according to your local time zone is: " << y << std::endl;
    std::cout << "FILE SAVE\n";
    // Close the file
    MyFile.close();
}
void AutoSaving()
{
    while (true)
    {
        time_t x = std::time(0);
        char *y = ctime(&x);
        std::ofstream MyFile("DateFile.txt");

        // Write to the file
        MyFile << "The date and time according to your local time zone is: " << y << std::endl;
        std::cout << "FILE SAVE\n";
        // Close the file
        MyFile.close();
    }
}
void RunEngine()
{
    // testThread myThreadthree(EndEngine, 3);
    // testThread AutoSaveThread(AutoSave, 2);
    // how to check if all thread has ended
    //  testThread TestPrint(PrintStuff,2);
    //  testThread Saving(AutoSaving,2);
    //  testThread EndEngine(EndEngine,4);

    // Player testPlayer;
    // testPlayer.Start();

    EntityState Player;
    EnemyState Enemy;

    Player.AddState("Idle");
    Player.AddState("Walking");
    Player.AddState("Running");

    Enemy.AddState("Patrolling");
    Enemy.AddState("Walking");
    Enemy.AddState("Running");
    Enemy.AddState("Attacking");

    Player.StateTransistion("Idle");
    Enemy.StateTransistion("Patrolling");

    while (!endsystem)
    {
        std::cout << "ENGINE RUNNING\n"
                  << std::endl;
        Player.EventHandler();
        Enemy.EventHandler();
        Player.StateTransistion("Running");
        Enemy.StateTransistion("Attacking");
        // Check if exitFlag is true and join the thread
        // if (myThreadthree.exitFlag)
        // {
        //     myThreadthree.joinThread();

        // }
        // testPlayer.Update();
    }
}