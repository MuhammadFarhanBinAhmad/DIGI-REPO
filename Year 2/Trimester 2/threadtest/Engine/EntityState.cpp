#include "EntityState.h"

void EntityState::EventHandler() const
{
    switch (currentState)
    {
    case 0:
        std::cout << "Idle\n";
        break;
    case 1:
        std::cout << "Walking\n";
        break;
    case 2:
        std::cout << "Running\n";
        break;
    default:
        break;
    }
}