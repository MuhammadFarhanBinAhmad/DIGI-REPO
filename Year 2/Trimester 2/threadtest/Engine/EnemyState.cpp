#include "EnemyState.h"

void EnemyState::EventHandler() const
{
    switch (currentState)
    {
    case 0:
        std::cout << "Patrolling\n";
        break;
    case 1:
        std::cout << "Walking\n";
        break;
    case 2:
        std::cout << "Running\n";
        break;
    case 3:
        std::cout << "Attacking\n";
        break;
    default:
        break;
    }
}