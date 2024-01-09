#include "StateHandler.h"
StateHandler::~StateHandler() {}

void StateHandler::AddState(std::string NewState)
{
    int size = States.size();
    States[size] = NewState;
}
void StateHandler::RemoveState(std::string StateToRemove)
{
    auto it = States.begin();

    for (; it != States.end();it++)
    {
        if (it->second ==StateToRemove)
        {
            States.erase(it->first);
            break;
        }
    }

    if (it== States.end())
    {
        std::cout << "Not found\n";
    }
}
void StateHandler::StateTransistion(std::string newState)
{
    auto it = States.begin();
    int key{};

    for (; it != States.end();it++)
    {
        if (it->second ==newState)
        {
            key = it->first;
            std::cout << "State Change\n";
            break;
        }
    }

    if (it== States.end())
    {
        std::cout << "Not found\n";
    }

    currentState = key;
}
int StateHandler::GetTotalStates()
{
    return States.size();
}
std::string StateHandler::GetCurrentState()
{
    return States[currentState];
}
